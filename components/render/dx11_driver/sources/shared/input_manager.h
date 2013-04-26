#ifndef RENDER_DX11_DRIVER_INPUT_MANAGER_HEADER
#define RENDER_DX11_DRIVER_INPUT_MANAGER_HEADER

#include <stl/auto_ptr.h>

#include <render/low_level/device.h>

#include <shared/common.h>
#include <shared/device_manager.h>
#include <shared/input_layout.h>

namespace render
{

namespace low_level
{

namespace dx11
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputManagerContextState
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputManagerContextState  (const DeviceManager&);
    ~InputManagerContextState ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void         SetInputLayout (InputLayout* state);
    InputLayout* GetInputLayout () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void     SetVertexBuffer (size_t vertex_buffer_slot, IBuffer* buffer);
    IBuffer* GetVertexBuffer (size_t vertex_buffer_slot) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void     SetIndexBuffer (IBuffer* buffer);
    IBuffer* GetIndexBuffer () const;

  protected:
    struct Impl;

    Impl& GetImpl () const;

    InputManagerContextState (Impl*);

  private:
    InputManagerContextState (const InputManagerContextState&); //no impl
    InputManagerContextState& operator = (const InputManagerContextState&); //no impl

  private:
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputManagerContext: public InputManagerContextState
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputManagerContext  (const DeviceManager&, const DxContextPtr&, const InputLayoutPtr&);
    ~InputManagerContext ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ������ � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind ();

  protected:
    struct Impl;

    Impl& GetImpl () const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputManager  (const DeviceManager&);
    ~InputManager ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputLayout*  CreateInputLayout (const InputLayoutDesc& desc);
    IBuffer*      CreateBuffer      (const BufferDesc& desc);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static const char* GetVertexAttributeSemanticName (VertexAttributeSemantic semantic);

  private:
    InputManager (const InputManager&); //no impl
    InputManager& operator = (const InputManager&); //no impl

  private:  
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

}

}

#endif
