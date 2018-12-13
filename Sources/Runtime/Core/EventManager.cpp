#include "Core/EventManager.hpp"

namespace rumia
{
   EventManager& EventManager::GetInstance()
   {
      static EventManager inst;
      return inst;
   }

   void EventManager::Subscribe(uint32 eventType, void* subscriber, Callback&& callback)
   {
      m_events[eventType].push_back(std::make_pair(
         subscriber, 
         std::forward<Callback>(callback)));
   }

   void EventManager::UnSubscribeEnqueue(uint32 eventType, void* subscriber)
   {
      auto itr = m_events.find(eventType);
      if (itr != m_events.end())
      {
         m_unsubQueueMap[eventType].push_back(subscriber);
      }
   }

   void EventManager::UnSubscribe(uint32 eventType, std::vector<Subscriber>& subscribers)
   {
      auto unsubItr = m_unsubQueueMap.find(eventType);
      if (unsubItr != m_unsubQueueMap.end())
      {
         for (auto unsubscriber : unsubItr->second)
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

         unsubItr->second.clear();
         //unsubItr->second.shrink_to_fit();
      }
   }

   void EventManager::Notify(uint32 eventType, const EventDataType& data)
   {
      auto itr = m_events.find(eventType);
      if (itr != m_events.end())
      {
         std::vector<Subscriber>& subscribers = (*itr).second;
         UnSubscribe(eventType, subscribers);
         for (Subscriber& subscriber : subscribers)
         {
            subscriber.second(data);
         }
      }
   }
}