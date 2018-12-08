#include "Transform.hpp"

// @TODO: Test
namespace rumia
{
   RUMIA_REGISTER_COMPONENT(Transform);

   Transform::Transform(Actor* actor) :
      m_parent(nullptr),
      m_position(glm::vec3()),
      m_scale(glm::vec3(1.0f)),
      m_rotation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)),
      m_matrix(glm::mat4()),
      m_localMatrix(glm::mat4()),
      m_bParentUpdated(false),
      Component(actor)
   {
   }

   void Transform::SetLocalPosition(const glm::vec3& position)
   {
      if (position != m_position)
      {
         m_position = position;
         UpdateTransform();
      }
   }

   void Transform::SetPosition(const glm::vec3& position)
   {
      glm::vec3 localPosition = (m_parent == nullptr) ?
         position : position - m_parent->GetPosition();
      SetLocalPosition(localPosition);
   }

   glm::vec3 Transform::GetLocalPosition() const
   {
      return m_position;
   }

   glm::vec3 Transform::GetPosition() const
   {
      return (m_parent == nullptr) ?
         m_position : m_position + m_parent->GetPosition();
   }

   void Transform::Translate(const glm::vec3& translation)
   {
      SetLocalPosition(m_position + translation);
   }

   void Transform::SetLocalScale(const glm::vec3& scale)
   {
      if (scale != m_scale)
      {
         m_scale = scale;
         UpdateTransform();
      }
   }

   void Transform::SetScale(const glm::vec3& scale)
   {
      glm::vec3 localScale = (m_parent == nullptr) ?
         scale : scale / m_parent->GetScale();
      SetLocalScale(localScale);
   }

   glm::vec3 Transform::GetLocalScale() const
   {
      return m_scale;
   }

   glm::vec3 Transform::GetScale() const
   {
      return (m_parent == nullptr) ? m_scale : m_scale * m_parent->GetScale();
   }

   void Transform::Scale(const glm::vec3& scale)
   {
      SetScale(m_scale * scale);
   }

   void Transform::SetLocalRotation(const glm::quat& rotation)
   {
      if (rotation != m_rotation)
      {
         m_rotation = rotation;
         UpdateTransform();
      }
   }

   void Transform::SetLocalRotation(const glm::vec3& euler)
   {
      glm::quat rot = EulerToQuaternion(euler);
      SetLocalRotation(rot);
   }

   void Transform::SetRotation(const glm::quat& rotation)
   {
      glm::quat localRot = (m_parent == nullptr) ?
         rotation : (rotation * glm::inverse(m_parent->GetRotation()));
      SetLocalRotation(localRot);
   }

   void Transform::SetRotation(const glm::vec3& euler)
   {
      glm::quat rot = EulerToQuaternion(euler);
      SetRotation(rot);
   }

   glm::quat Transform::GetLocalRotation() const
   {
      return m_rotation;
   }

   glm::vec3 Transform::GetLocalRotationEuler() const
   {
      return QuaternionToEuler(m_rotation);
   }

   glm::quat Transform::GetRotation() const
   {
      return (m_parent == nullptr) ? m_rotation : m_rotation * m_parent->GetRotation();
   }

   glm::vec3 Transform::GetRotationEuler() const
   {
      glm::quat rot = GetRotation();
      return Transform::QuaternionToEuler(rot);
   }

   void Transform::Rotate(const glm::quat& rotation)
   {
      SetLocalRotation(glm::normalize(m_rotation * rotation));
   }

   void Transform::Rotate(const glm::vec3& euler)
   {
      Rotate(EulerToQuaternion(euler));
   }

   void Transform::SetParent(Transform* newParent)
   {
      if (newParent != m_parent && newParent != this)
      {
         PreSetParent();
         if (m_parent != nullptr)
         {
            auto end = m_parent->m_children.end();
            auto itr = std::find(
               m_parent->m_children.begin(),
               end, this);

            if (end != itr)
            {
               m_parent->m_children.erase(itr);
            }
         }

         m_parent = newParent;
         if (newParent != nullptr)
         {
            newParent->m_children.push_back(this);
         }

         PostSetParent();
         UpdateTransform();
      }
   }

   glm::mat4x4 Transform::GetMatrix() const
   {
      return m_matrix;
   }

   glm::mat4x4 Transform::GetInverseMatrix() const
   {
      return glm::inverse(m_matrix);
   }

   void Transform::UpdateTransform()
   {
      if (!m_bParentUpdated)
      {
         glm::mat4 modelMat = (m_parent == nullptr) ?
            glm::mat4() : m_parent->GetMatrix();

         glm::mat4 _identity = glm::mat4();
         glm::mat4 scale = glm::scale(_identity, GetScale());
         glm::mat4 rotation = glm::toMat4(GetRotation());
         glm::mat4 translation = glm::translate(_identity, GetPosition());

         m_localMatrix = translation * rotation * scale;
         m_matrix = (m_parent == nullptr) ?
            m_localMatrix : (m_localMatrix * m_parent->GetMatrix());

         for (Transform* child : m_children)
         {
            child->UpdateTransform();
         }
      }
   }

   void Transform::PreSetParent()
   {
      m_bParentUpdated = true;
      for (Transform* child : m_children)
      {
         child->PreSetParent();
      }

      // make it independent to parent from leaf children to parent
      if (m_parent != nullptr)
      {
         m_position += m_parent->GetPosition();
         m_rotation *= m_parent->GetRotation();
         m_scale *= m_parent->GetScale();
      }
   }

   void Transform::PostSetParent()
   {
      SetPosition(m_position);
      SetRotation(m_rotation);
      SetScale(m_scale);

      for (Transform* child : m_children)
      {
         child->PostSetParent();
      }
      m_bParentUpdated = false;
   }

   glm::quat Transform::EulerToQuaternion(const glm::vec3& euler)
   {
      glm::quat xAxis = glm::angleAxis(euler.x, glm::vec3(1.0f, 0.0f, 0.0f));
      glm::quat yAxis = glm::angleAxis(euler.y, glm::vec3(0.0f, 1.0f, 0.0f));
      glm::quat zAxis = glm::angleAxis(euler.z, glm::vec3(0.0f, 0.0f, 1.0f));

      glm::quat rot = xAxis * yAxis * zAxis;
      return rot;
   }

   // Based on http://bediyap.com/programming/convert-quaternion-to-euler-rotations/
   glm::vec3 Transform::QuaternionToEuler(const glm::quat& rot)
   {
      float r11 = -2.0f * (rot.y*rot.z - rot.w*rot.x);
      float r12 = (rot.w*rot.w) - (rot.x*rot.x) - (rot.y*rot.y) + (rot.z*rot.z);
      float r21 = 2.0f * (rot.x*rot.z + rot.w*rot.y);
      float r31 = -2.0f * (rot.x*rot.y - rot.w*rot.z);
      float r32 = (rot.w * rot.w) + (rot.x*rot.x) - (rot.y*rot.y) - (rot.z*rot.z);
      return glm::vec3(std::atan2(r11, r12), std::asin(r21), std::atan2(r31, r32));
   }
}