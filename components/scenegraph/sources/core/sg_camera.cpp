#include <sg/camera.h>
#include <xtl/visitor.h>

using namespace sg;
using namespace math;

/*
    �������� ���������� Camera
*/

struct Camera::Impl
{
  mat4f proj_matrix;  //������� �������������
  int   dirty_pm;     //��� true ������� ������������� ��������� � �����������
};

/*
    ����������� / ����������
*/

Camera::Camera ()
  : impl (new Impl)
{
  impl->proj_matrix = 1;
  impl->dirty_pm    = 1;
}

Camera::~Camera ()
{
  delete impl;
}

/*
    ������� ��������
*/

const mat4f& Camera::ProjectionMatrix ()
{
  if (impl->dirty_pm)
  {
    ComputeProjectionMatrix (impl->proj_matrix);
    impl->dirty_pm = 0;
  }
  return impl->proj_matrix;
}

/*
    ������ ���������� �������
*/

void Camera::UpdateNotify ()
{
  impl->dirty_pm = 1;
}

/*
    �����, ���������� ��� ��������� �������
*/

void Camera::AcceptCore (Visitor& visitor)
{
  if (!TryAccept (*this, visitor))
    Node::AcceptCore (visitor);
}
