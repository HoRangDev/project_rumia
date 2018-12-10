#include "World/World.hpp"
#include "World/Actor.hpp"
#include "Component/Transform.hpp"

namespace rumia
{
   World::World()
   {
   }

   World::~World()
   {
      Unload();
   }

   json World::Serialize() const
   {
      json object = json::object();
      
      json actorList = json::array();
      for (Actor* actor : m_actors)
      {
         if (!actor->HasParent())
         {
            actorList.push_back(actor->Serialize());
         }
      }

      object["actors"] = actorList;
      return object;
   }

   void World::DeSerialize(const json& object)
   {
      if (!object.is_null())
      {
         auto itr = object.find("actors");
         if (itr != object.end())
         {
            json actorList = (*itr);
            for (json actor : actorList)
            {
               Actor* newActor = new Actor();
               newActor->DeSerialize(actor);
               AddActor(newActor);
            }
         }
      }
   }

   void World::LoadFromFile(const std::string& filePath)
   {
      // @TODO: Implement Load World
   }

   void World::SaveToFile(const std::string& filePath)
   {
      // @TODO: Implement Save World
   }

   Actor* World::CreateActor()
   {
      Actor* newActor = new Actor();
      m_actors.emplace_back(newActor);
      return newActor;
   }

   void World::AddActor(Actor* actor)
   {
      if (actor != nullptr)
      {
         m_actors.emplace_back(actor);

         Transform* transform = actor->GetTransform();
         std::vector<Transform*> children = transform->GetChildren();
         for (auto child : children)
         {
            Actor* childActor = child->GetActor();
            AddActor(childActor);
         }
      }
   }

   void World::RemoveActor(Actor* actor)
   {
      if (actor != nullptr)
      {
         auto itr = std::find(m_actors.begin(), m_actors.end(), actor);
         m_actors.erase(itr);

         // also remove children
         Transform* transform = actor->GetTransform();
         std::vector<Transform*> children{ std::move(transform->GetChildren()) };
         for (auto child : children)
         {
            Actor* childActor = child->GetActor();
            RemoveActor(childActor);
         }

         SafeDelete(actor);
      }
   }

   void World::Unload()
   {
      for (auto actor : m_actors)
      {
         SafeDelete(actor);
      }

      m_actors.clear();
      m_actors.shrink_to_fit();
   }

   void World::Tick()
   {
      for (auto actor : m_actors)
      {
         actor->Tick();
      }
   }
}