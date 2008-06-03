#include <sg/listener.h>
#include <xtl/visitor.h>
#include <common/exception.h>

using namespace scene_graph;
using namespace common;

/*
    �������� ���������� Listener
*/

struct Listener::Impl
{
  float gain;     //��������
};

/*
    ����������� / ����������
*/

Listener::Listener ()
  : impl (new Impl)
{
  impl->gain = 1.f;
}

Listener::~Listener ()
{
  delete impl;
}

/*
    �������� ���������
*/

Listener::Pointer Listener::Create ()
{
  return Pointer (new Listener, false);
}

/*
    ��������
*/

float Listener::Gain () const
{
  return impl->gain;
}

void Listener::SetGain (float gain)
{
  if (gain < 0)
    raise_out_of_range ("Listener::SetGain", "gain", gain, 0.f, 1e9f);

  impl->gain = gain;
}

/*
    �����, ���������� ��� ��������� �������
*/

void Listener::AcceptCore (Visitor& visitor)
{
  if (!TryAccept (*this, visitor))
    Entity::AcceptCore (visitor);
}
