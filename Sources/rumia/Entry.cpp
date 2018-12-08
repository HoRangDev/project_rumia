#include "Core/EngineDefines.hpp"
#include "World/Actor.hpp"
#include "Component/Transform.hpp"

#include <iostream>

using namespace rumia;

int main()
{
   Actor* parentActor = new Actor();
   Actor* actor = new Actor();
   Transform* newTransform = ComponentRegistry::GetInstance().Acquire<rumia::Transform>(actor);
   Transform* parentTransform = ComponentRegistry::GetInstance().Acquire<Transform>(actor);
   Transform* otherTransform = ComponentRegistry::GetInstance().Acquire<Transform>(actor);

   newTransform->SetLocalPosition(glm::vec3(0.0f, 0.0f, 1.0f));
   otherTransform->SetLocalPosition(glm::vec3(1.0f, 0.0f, 0.0f));
   parentTransform->SetLocalPosition(glm::vec3(0.0f, 1.0f, 0.0f));

   newTransform->SetParent(otherTransform);

   auto pos = newTransform->GetPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;
   pos = newTransform->GetLocalPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;

   otherTransform->SetParent(parentTransform);
   pos = newTransform->GetPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;
   pos = newTransform->GetLocalPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;

   parentTransform->Translate(glm::vec3(2.0f, 0.0f, 0.0f));
   pos = newTransform->GetPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;
   pos = newTransform->GetLocalPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;

   otherTransform->Translate(glm::vec3(0.0f, 1.0f, 0.0f));
   pos = newTransform->GetPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;
   pos = newTransform->GetLocalPosition();
   std::cout << pos.x << "," << pos.y << "," << pos.z << std::endl;

   std::cout << otherTransform->GetTypeName() << std::endl;

   return 0;
}