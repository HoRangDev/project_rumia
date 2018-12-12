#include "Core/EngineDefines.hpp"
#include "Core/Helper.hpp"
#include "World/Actor.hpp"
#include "World/World.hpp"
#include "Core/Helper.hpp"
#include "Component/Transform.hpp"
#include "Core/EventManager.hpp"

#include <iostream>

using namespace rumia;

int main()
{
   World* world1 = new World();
   Actor* testActor = world1->CreateActor();
   testActor->SetName("I am parent!");
   Transform* trans = testActor->GetTransform();

   trans->SetLocalPosition(glm::vec3{ 3.0f, 2.0f, 1.1f });
   trans->SetScale(glm::vec3{ 0.5f, 0.5f, 0.5f });

   Actor* testChildActor = world1->CreateActor();
   testChildActor->SetName("I am child!");
   Transform* transOfChild = testChildActor->GetTransform();

   transOfChild->SetParent(trans);

   auto serializedStr = world1->Serialize().dump(4);
   std::cout << serializedStr << std::endl;

   World* world2 = new World();
   helper::DeSerialize(world2, serializedStr);

   testActor->SetActive(false);
   std::cout << trans->IsActivated() << std::endl;
   testActor->SetActive(true);
   trans->SetActive(false);
   std::cout << trans->IsActivated() << std::endl;
   std::cout << testActor->Serialize().dump(4) << std::endl;
   trans->SetActive(true);
   std::cout << trans->IsActivated() << std::endl;
   
   return 0;
}