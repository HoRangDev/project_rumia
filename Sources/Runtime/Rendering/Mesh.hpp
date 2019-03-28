#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Core/EngineDefines.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
   // m_material->Bind();
   // Renderer 에서 material-Meshes 를 구성하고 같은 material 이면 한번만 바인드하고
   // 나머지 Static Mesh 들을 그리는 방식으로!
   // StaticMesh의 Draw function 에서는 Renderer에 등록시킨후에 실제로 Render function 호출하도록
   // Enqueue 할때 material(key)-mesh 로 묶어서 dictionary 에 등록후 모든 MeshComponent 의 Render가 호출되면
   // 그 후에 material 단위로 Batch rendering
   // 나중에 Mesh-Actor 연결 해주는 방법(Skeletal Animation 등을 위해서) 강구
   // Socket Actor 가 null 이면 local 하게
   class Renderer;
   class Material;
   class Actor;
   class RUMIA Mesh
   {
   public:
      Mesh(const std::string& meshName = "None");
      virtual ~Mesh();

      virtual void Initialize() final;
      virtual void Render(Renderer* renderer) final;

      bool IsInitialized() const { return m_bInitialized; }
      std::string GetName() const { return m_meshName; }

      void SetMaterial(Material* material) { m_material = material; }
      Material* GetMaterial() const { return m_material; }

   private:
      virtual bool Initialize_Impl() = 0;
      virtual void Render_Impl(Renderer* renderer) = 0;

   private:
      bool           m_bInitialized;
      std::string    m_meshName;
      Material*      m_material;

   };
}