#include "Core/EventManager.hpp"

namespace rumia
{
   EventManager& EventManager::GetInstance()
   {
      static EventManager inst;
      return inst;
   }

   void EventManager::StageChangeEnqueue(uint32 eventType, ESubscriberState state, void* subscriber, Callback&& callback)
   {
      if (state == ESubscriberState::Subscribe)
      {
         auto itr = m_events.find(eventType);
         if (itr == m_events.end())
         {
            // Initial subscribe!
            SubscribeImmeidate(eventType, subscriber, std::forward<Callback>(callback));
            return;
         }
      }

      m_stateChangeQueueMap[eventType].push_back(std::make_pair(
         state,
         std::make_pair(subscriber, callback) // Subscriber info
      ));
   }

   void EventManager::ProcessChangedState(uint32 eventType, std::vector<Subscriber>& subscribers)
   {
      auto stateItr = m_stateChangeQueueMap.find(eventType);
      if (stateItr != m_stateChangeQueueMap.end())
      {
         std::vector<StateChange>& stateChanges = stateItr->second;
         for (StateChange& stateChange : stateChanges)
         {
            Subscriber& subscriber = stateChange.second;
            switch (stateChange.first)
            {
            case ESubscriberState::Subscribe:
               Subscribe(subscriber.first, std::move(subscriber.second), subscribers);
               break;

            case ESubscriberState::UnSubscribe:
               UnSubscribe(subscriber.first, subscribers);
               break;
            }
         }

         stateChanges.clear();
         //stateChanges.shrink_to_fit();
      }
   }

   void EventManager::Subscribe(void* subscriber, Callback&& callback, std::vector<Subscriber>& subscribers)
   {
      // @TODO: No duplicate subscribe! => Using set?
      auto findDuplicateItr = std::find_if(subscribers.begin(), subscribers.end(), [subscriber](const Subscriber& subscriberInfo)
      {
         return (subscriberInfo.first == subscriber);
      });

      if (findDuplicateItr == subscribers.end())
      {
         subscribers.push_back(std::make_pair(
            subscriber,
            std::forward<Callback>(callback)));
      }
   }

   void EventManager::UnSubscribe(void* unsubscriber, std::vector<Subscriber>& subscribers)
   {
      auto foundSubscriber = std::find_if(subscribers.begin(), subscribers.end(),
         [&unsubscriber](const Subscriber& foundSubscriber) {
         return foundSubscriber.first == unsubscriber;
      });

      if (foundSubscriber != subscribers.end())
      {
         subscribers.erase(foundSubscriber);
      }
   }

   void EventManager::SubscribeImmeidate(uint32 eventType, void* subscriber, Callback&& callback)
   {
      m_events[eventType].push_back(std::make_pair(subscriber, std::forward<Callback>(callback)));
   }
   
   void EventManager::Notify(uint32 eventType, const EventDataType& data)
   {
      auto itr = m_events.find(eventType);
      if (itr != m_events.end())
      {
         std::vector<Subscriber>& subscribers = (*itr).second;
         ProcessChangedState(eventType, subscribers);
         for (Subscriber& subscriber : subscribers)
         {
            subscriber.second(data);
         }
      }
   }
}