#include "Core/EngineDefines.hpp"
#include "Core/Helper.hpp"
#include "World/Actor.hpp"
#include "World/World.hpp"
#include "Core/Helper.hpp"
#include "Component/Transform.hpp"
#include "Core/EventManager.hpp"
#include "Core/Engine.hpp"
#include "Resource/Resource.hpp"
#include "Resource/Texture.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

#include <GL/gl3w.h>
#include <glfw/glfw3.h>

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

   auto splited = helper::SplitString("Test/Test\\MultipleToken", { '/', '\\' });
   for (auto splitStr : splited)
   {
      std::cout << splitStr << std::endl;
   }

   std::cout << helper::CombineString(splited, "-") << std::endl;

   Engine& engine = Engine::GetInstance();
   if (!engine.Initialize(1280, 720, "rumia"))
   {
      return -1;
   }

   // @TODO: Impl editor!
   glfwInit();
   const char* glsl_version = "#version 330 core";
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   GLFWwindow* window = glfwCreateWindow(1280, 720, "test", nullptr, nullptr);
   if (window == nullptr)
   {
      // @TODO: Error log failed to init window
   }

   glfwMakeContextCurrent(window);
   // @TODO: Window callbacks like size callback, mouse, scroll, keyboard.. etc

   //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   int err = gl3wInit();
   int version = gl3wIsSupported(3, 3);

   ImGui::CreateContext();
   ImGui_ImplGlfw_InitForOpenGL(window, true);
   ImGui_ImplOpenGL3_Init(glsl_version);

   Texture tex{ "../Resources/Textures/brickwall.jpg" };
   tex.Load();

   ImGui::StyleColorsDark();
   while (!glfwWindowShouldClose(window))
   {
      glfwPollEvents();

      engine.Tick();
      //@TODO: place engine render
      //@TODO: editor render

      int display_w;
      int display_h;
      //glfwMakeContextCurrent(window);
      //glfwGetFramebufferSize(window, &display_w, &display_h);
      //glViewport(0, 0, display_w, display_h);
      glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      {
         ImGui::Begin("Hello, world!");
         ImGui::Text("hI hI!!");
         ImGui::End();
      }

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      glfwMakeContextCurrent(window);
      glfwSwapBuffers(window);
   }

   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}