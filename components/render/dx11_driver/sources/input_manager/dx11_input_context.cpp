#include "shared.h"

using namespace render::low_level;
using namespace render::low_level::dx11;

/*
===================================================================================================
    InputManagerContextState
===================================================================================================
*/

/*
    �������� ���������� ��������� ��������� ��������� �������� ������
*/

typedef xtl::com_ptr<InputBuffer> InputBufferPtr;

struct InputManagerContextState::Impl: public DeviceObject
{
  InputLayoutPtr input_layout;                                      //������� ������  
  InputBufferPtr vertex_buffers [DEVICE_VERTEX_BUFFER_SLOTS_COUNT]; //��������� ������ 
  InputBufferPtr index_buffer;                                      //��������� �����
  bool           is_dirty;                                          //���� "���������"

/// �����������
  Impl (const DeviceManager& device_manager)
    : DeviceObject (device_manager)
    , is_dirty (true)
  {
  }

/// ����������
  virtual ~Impl () {}

/// ���������� �� ���������
  void UpdateNotify ()
  {
    is_dirty = true;
  }
};

/*
    ����������� / ����������
*/

InputManagerContextState::InputManagerContextState (const DeviceManager& device_manager)
  : impl (new Impl (device_manager))
{
}

InputManagerContextState::InputManagerContextState (Impl* in_impl)
  : impl (in_impl)
{
}

InputManagerContextState::~InputManagerContextState ()
{
}

/*
    ����������� ����������
*/

InputManagerContextState::Impl& InputManagerContextState::GetImpl () const
{
  return *impl;
}

/*
    ���������� ������������� ������� ������
*/

void InputManagerContextState::SetInputLayout (InputLayout* state)
{  
  impl->input_layout = state;

  impl->UpdateNotify ();
}

InputLayout* InputManagerContextState::GetInputLayout () const
{
  return impl->input_layout.get ();
}

/*
    ���������� ���������� ��������
*/

void InputManagerContextState::SetVertexBuffer (size_t vertex_buffer_slot, IBuffer* in_buffer)
{
  try
  {
    InputBuffer* buffer = cast_object<InputBuffer> (*impl, in_buffer, "", "buffer");

    if (vertex_buffer_slot >= DEVICE_VERTEX_BUFFER_SLOTS_COUNT)
      throw xtl::make_range_exception ("", "vertex_buffer_slot", vertex_buffer_slot, DEVICE_VERTEX_BUFFER_SLOTS_COUNT);

    impl->vertex_buffers [vertex_buffer_slot] = buffer;

    impl->UpdateNotify ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::InputManagerContextState::SetVertexBuffer");
    throw;
  }
}

IBuffer* InputManagerContextState::GetVertexBuffer (size_t vertex_buffer_slot) const
{
  try
  {
    if (vertex_buffer_slot >= DEVICE_VERTEX_BUFFER_SLOTS_COUNT)
      throw xtl::make_range_exception ("", "vertex_buffer_slot", vertex_buffer_slot, DEVICE_VERTEX_BUFFER_SLOTS_COUNT);

    return impl->vertex_buffers [vertex_buffer_slot].get ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::InputManagerContextState::GetVertexBuffer");
    throw;
  }
}

/*
    ���������� ��������� �������
*/

void InputManagerContextState::SetIndexBuffer (IBuffer* in_buffer)
{
  try
  {
    InputBuffer* buffer = cast_object<InputBuffer> (*impl, in_buffer, "", "buffer");

    impl->index_buffer = buffer;

    impl->UpdateNotify ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::InputManagerContextState::SetIndexBuffer");
    throw;
  }
}

IBuffer* InputManagerContextState::GetIndexBuffer () const
{
  return impl->index_buffer.get ();
}

/*
===================================================================================================
    InputManagerContext
===================================================================================================
*/

struct InputManagerContext::Impl: public InputManagerContextState::Impl
{
  DxContextPtr   context;        //��������
  InputLayoutPtr default_layout; //������ �� ���������

/// �����������
  Impl (const DeviceManager& device_manager, const DxContextPtr& in_context, const InputLayoutPtr& in_default_layout)
    : InputManagerContextState::Impl (device_manager)
    , context (in_context)
    , default_layout (in_default_layout)
  {
    static const char* METHOD_NAME = "render::low_level::dx11::InputManagerContext::Impl::Impl";

    if (!context)
      throw xtl::make_null_argument_exception (METHOD_NAME, "context");

    if (!default_layout)
      throw xtl::make_null_argument_exception (METHOD_NAME, "default_layout");
  }
};

/*
    ����������� / ����������
*/

InputManagerContext::InputManagerContext (const DeviceManager& device_manager, const DxContextPtr& context, const InputLayoutPtr& input_layout)
  : InputManagerContextState (new Impl (device_manager, context, input_layout))
{
}

InputManagerContext::~InputManagerContext ()
{
}

/*
    ��������� ��������� ������ � ��������
*/

InputManagerContext::Impl& InputManagerContext::GetImpl () const
{
  return static_cast<Impl&> (InputManagerContextState::GetImpl ());
}

namespace
{

const UINT VB_OFFSETS [DEVICE_VERTEX_BUFFER_SLOTS_COUNT] = {0};

}

void InputManagerContext::Bind ()
{
  try
  {
      //�������� ����� "���������"

    Impl& impl = GetImpl ();

    if (!impl.is_dirty)
      return;

      //�������������� ����������� ����������

    InputLayout* layout = impl.input_layout ? impl.input_layout.get () : impl.default_layout.get ();

    ID3D11Buffer* buffers [DEVICE_VERTEX_BUFFER_SLOTS_COUNT];

    ID3D11Buffer**  dst_buffer = buffers;
    InputBufferPtr* src_buffer = impl.vertex_buffers;

    for (size_t i=0; i<DEVICE_VERTEX_BUFFER_SLOTS_COUNT; i++, dst_buffer++, src_buffer++)
      *dst_buffer = *src_buffer ? &(*src_buffer)->GetHandle () : (ID3D11Buffer*)0;

    impl.context->IASetVertexBuffers (0, DEVICE_VERTEX_BUFFER_SLOTS_COUNT, buffers, layout->GetStrides (), VB_OFFSETS);
    impl.context->IASetIndexBuffer   (impl.index_buffer ? &impl.index_buffer->GetHandle () : (ID3D11Buffer*)0, layout->GetIndexFormat (), layout->GetIndexBufferOffset ());

      //������� ����� "���������"

    impl.is_dirty = false;
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::InputManagerContext::Bind");
    throw;
  }
}