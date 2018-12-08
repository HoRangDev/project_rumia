#pragma once
#include "Component/Component.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <vector>

namespace rumia
{
   class RUMIA Transform : public Component
   {
      RUMIA_COMPONENT(Transform, EComponentType::Transform);
   public:
      Transform(Actor* actor);

      void SetLocalPosition(const glm::vec3& position);
      void SetPosition(const glm::vec3& position);
      glm::vec3 GetLocalPosition() const;
      glm::vec3 GetPosition() const;
      void Translate(const glm::vec3& translation);

      void SetLocalScale(const glm::vec3& scale);
      void SetScale(const glm::vec3& scale);
      glm::vec3 GetLocalScale() const;
      glm::vec3 GetScale() const;
      void Scale(const glm::vec3& scale);

      void SetLocalRotation(const glm::quat& rotation);
      void SetLocalRotation(const glm::vec3& euler);
      void SetRotation(const glm::quat& rotation);
      void SetRotation(const glm::vec3& euler);
      glm::quat GetLocalRotation() const;
      glm::vec3 GetLocalRotationEuler() const;
      glm::quat GetRotation() const;
      glm::vec3 GetRotationEuler() const;
      void Rotate(const glm::quat& rotation);
      void Rotate(const glm::vec3& euler);

      void SetParent(Transform* newParent);
      Transform* GetParent() const { return m_parent; }

      std::vector<Transform*> GetChildrean() const { return m_children; }

      glm::mat4 GetMatrix() const;
      glm::mat4 GetLocalMatrix() const;
      glm::mat4 GetInverseMatrix() const;

      void UpdateTransform();

   private:
      void PreSetParent();
      void PostSetParent();

   public:
      static glm::quat EulerToQuaternion(const glm::vec3& euler);
      static glm::vec3 QuaternionToEuler(const glm::quat& rotation);

   private:
      Transform*  m_parent;

      glm::vec3   m_position;
      glm::vec3   m_scale;
      glm::quat   m_rotation;

      glm::mat4 m_matrix;
      glm::mat4 m_localMatrix;

      std::vector<Transform*> m_children;

      bool  m_bParentUpdated;
   };
}