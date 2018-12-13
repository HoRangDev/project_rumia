#pragma once
#include "Core/Helper.hpp"

#include <variant>
#include <map>
#include <tuple>
#include <vector>
#include <queue>
#include <functional>

namespace rumia
{
   class Actor;
   enum EEngineEvent : uint32
   {
      None = 0,
      WindowResize = 1,
      NewWorldActor,
      Tick,
      Render,
      AppClose
   };

   enum class ESubscriberState
   {
      Subscribe,
      UnSubscribe
   };

   using EventDataType = std::variant<bool, uint8, int8, uint16, int16, int16, uint32, int32, uint64, int64, float, double, std::string,
      Actor*, std::vector<Actor*>, glm::vec2, glm::vec3, glm::vec4, glm::mat4, glm::quat>;
   using Callback = std::function<void(EventDataType)>;
   using Subscriber =std::pair<void*, Callback>;
   using StateChange = std::pair<ESubscriberState, Subscriber>;

   class RUMIA EventManager
   {
   public:
      static EventManager& GetInstance();

      void StageChangeEnqueue(uint32 eventType, ESubscriberState state, void* subscriber, Callback&& callback);

      void Notify(uint32 eventType, const EventDataType& data = 0);

   private:
      void ProcessChangedState(uint32 eventType, std::vector<Subscriber>& subscribers);
      void Subscribe(void* subscriber, Callback&& callback, std::vector<Subscriber>& subscribers);
      void UnSubscribe(void* unsubscriber, std::vector<Subscriber>& subscribers);

      /* It must only use to initial subscribe! **/
      void SubscribeImmeidate(uint32 eventType, void* subscriber, Callback&& callback);

   private:
      std::map<uint32, std::vector<Subscriber>> m_events;
      std::map<uint32, std::vector<StateChange>> m_stateChangeQueueMap;

   };
}

#define EVENT_HANDLER(func) [this](EventDataType){func();}
#define EVENT_HANDLER_DATA(func) [this](EventDataType data){func(data);}

#define SUBSCRIBE_EVENT(eventType, subscriber, func) EventManager::GetInstance().StageChangeEnqueue(eventType, ESubscriberState::Subscribe, subscriber, func);
#define UNSUBSCRIBE_EVENT(eventType, subscriber) EventManager::GetInstance().StageChangeEnqueue(eventType, ESubscriberState::UnSubscribe, subscriber, [](EventDataType){});

#define NOTIFY(eventType) EventManager::GetInstance().Notify(eventType);
#define NOTIFY_WITH_DATA(eventType, data) EventManager::GetInstance().Notify(eventType, data);