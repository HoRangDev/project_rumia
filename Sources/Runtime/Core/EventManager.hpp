#pragma once
#include "Core/Helper.hpp"

#include <variant>
#include <map>
#include <tuple>
#include <vector>
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

   using EventDataType = std::variant<bool, uint8, int8, uint16, int16, int16, uint32, int32, uint64, int64, std::string,
      Actor*, std::vector<Actor*>, glm::vec2, glm::vec3, glm::vec4, glm::mat4, glm::quat>;
   using Callback = std::function<void(EventDataType)>;
   using Subscriber =std::pair<void*, Callback>;

   class RUMIA EventManager
   {
   public:
      static EventManager& GetInstance();

      void Subscribe(uint32 eventType, void* subscriber, Callback&& callback);
      void UnSubscribe(uint32 eventType, void* subscriber);

      void Notify(uint32 eventType, const EventDataType& data = 0);

   private:
      std::map<uint32, std::vector<Subscriber>> m_events;

   };
}

#define EVENT_HANDLER(func) [this](EventDataType){func();}
#define EVENT_HANDLER_DATA(func) [this](EventDataType data){func(data);}

#define SUBSCRIBE_EVENT(eventType, subscriber, func) EventManager::GetInstance().Subscribe(eventType, subscriber, func);

#define NOTIFY(eventType) EventManager::GetInstance().Notify(eventType);
#define NOTIFY_WITH_DATA(eventType, data) EventManager::GetInstance().Notify(eventType, data);