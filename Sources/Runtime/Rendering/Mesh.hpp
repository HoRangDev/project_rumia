#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Core/EngineDefines.hpp"
#include "Rendering/RenderingDefs.hpp"

namespace rumia
{
   // m_material->Bind();
   // Renderer ���� material-Meshes �� �����ϰ� ���� material �̸� �ѹ��� ���ε��ϰ�
   // ������ Static Mesh ���� �׸��� �������!
   // StaticMesh�� Draw function ������ Renderer�� ��Ͻ�Ų�Ŀ� ������ Render function ȣ���ϵ���
   // Enqueue �Ҷ� material(key)-mesh �� ��� dictionary �� ����� ��� MeshComponent �� Render�� ȣ��Ǹ�
   // �� �Ŀ� material ������ Batch rendering
   // ���߿� Mesh-Actor ���� ���ִ� ���(Skeletal Animation ���� ���ؼ�) ����
   // Socket Actor �� null �̸� local �ϰ�
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