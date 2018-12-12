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

   void EventManager::UnSubscribe(uint32 eventType, void* subscriber)
   {
      auto itr = m_events.find(eventType);
      if (itr != m_events.end())
      {
         std::vector<Subscriber>& subscribers = (*itr).second;
         auto foundSubscriber = std::find_if(subscribers.begin(), subscribers.end(), 
            [subscriber](const Subscriber& foundSubscriber) {
            return foundSubscriber.first == subscriber;
         });

         if (foundSubscriber != subscribers.end())
         {
            subscribers.erase(foundSubscriber);
         }
      }
   }

   void EventManager::Notify(uint32 eventType, const EventDataType& data)
   {
      auto itr = m_events.find(eventType);
      if (itr != m_events.end())
      {
         std::vector<Subscriber>& subscribers = (*itr).second;
         for (Subscriber& subscriber : subscribers)
         {
            subscriber.second(data);
         }
      }
   }
}