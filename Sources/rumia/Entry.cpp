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
   parentTransform->SetLocalRotation(glm::vec3(glm::radians(20.0f), glm::radians(0.0f), 0.0f));
   newTransform->SetRotation(glm::vec3(glm::radians(30.0f), glm::radians(0.0f), 0.0f));
   auto var = newTransform->GetLocalRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;
   
   newTransform->SetParent(parentTransform);
   var = newTransform->GetLocalRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;
   var = newTransform->GetRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;

   Transform* otherTransform = ComponentRegistry::GetInstance().Acquire<Transform>(actor);
   otherTransform->SetRotation(glm::vec3(glm::radians(10.0f), 0.0f, 0.0f));
   newTransform->SetParent(otherTransform);
   var = newTransform->GetLocalRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;
   var = newTransform->GetRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;

   newTransform->SetParent(nullptr);
   var = newTransform->GetRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;

   newTransform->SetParent(otherTransform);
   var = newTransform->GetLocalRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;
   otherTransform->SetParent(parentTransform);
   var = newTransform->GetLocalRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;
   var = newTransform->GetRotationEuler();
   std::cout << glm::degrees(var.x) << ", " << glm::degrees(var.y) << ", " << glm::degrees(var.z) << std::endl;

   return 0;
}