#ifndef RENDER_DX11_DRIVER_SOURCES_HEADER
#define RENDER_DX11_DRIVER_SOURCES_HEADER

#include <cmath>

#include <D3D11.h>

#include <stl/string>
#include <stl/vector>

#include <xtl/bind.h>
#include <xtl/common_exceptions.h>
#include <xtl/intrusive_ptr.h>

#include <common/action_queue.h>
#include <common/component.h>
#include <common/lockable.h>
#include <common/property_map.h>
#include <common/strlib.h>
#include <common/utf_converter.h>

#include <render/low_level/device.h>
#include <render/low_level/driver.h>
#include <render/low_level/utils.h>

#include <render/low_level/helpers/object.h>
#include <render/low_level/helpers/property_list.h>

#include <shared/log.h>
#include <shared/error.h>
#include <shared/input_manager.h>
#include <shared/object.h>
#include <shared/output_manager.h>
#include <shared/render_target_manager.h>
#include <shared/shader_manager.h>
#include <shared/texture_manager.h>
#include <shared/swap_chain.h>

namespace render
{

namespace low_level
{

namespace dx11
{

class Adapter;
class Context;

using helpers::PropertyList;

typedef xtl::com_ptr<Adapter> AdapterPtr;
typedef xtl::com_ptr<Context> ContextPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Output: virtual public IOutput, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Output  (const DxOutputPtr& output);
    ~Output ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IDXGIOutput& GetHandle ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ �����-�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetModesCount ();
    void   GetModeDesc   (size_t mode_index, OutputModeDesc& mode_desc);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� �����-������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetCurrentMode     (const OutputModeDesc&);
    void GetCurrentMode     (OutputModeDesc&);
    void RestoreDefaultMode ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetGammaRamp (const Color3f table [256]);
    void GetGammaRamp (Color3f table [256]);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IPropertyList* GetProperties ();

  private:
    typedef stl::vector<OutputModeDesc> ModeArray;

  private:
    DxOutputPtr  output;     //���������� ������
    stl::string  name;       //��� ����������
    PropertyList properties; //�������� ����������
    ModeArray    modes;      //������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Adapter: virtual public IAdapter, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Adapter  (const DxFactoryPtr& factory, const char* name, const char* dll_path, const char* init_string);
    Adapter  (const DxAdapterPtr& adapter);
    ~Adapter ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������� / ���� � ������ / �������� / ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName        ();
    const char* GetPath        ();
    const char* GetDescription ();
    HMODULE     GetModule      ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �� ������� DX11
///////////////////////////////////////////////////////////////////////////////////////////////////
    IDXGIAdapter& GetHandle ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������� ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t   GetOutputsCount ();
    IOutput* GetOutput       (size_t index);
    Output*  FindOutput      (IDXGIOutput* output);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IPropertyList* GetProperties ();

  private:
    void Init ();

  private:
    typedef xtl::com_ptr<Output>   OutputPtr;
    typedef stl::vector<OutputPtr> OutputArray;

  private:
    DxAdapterPtr adapter;      //�������          
    stl::string  name;         //��� ��������
    stl::string  path;         //���� � ��������
    PropertyList properties;   //�������� ��������
    OutputArray  outputs;      //���������� ������
    HMODULE      module;       //���������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class SwapChain: public ISwapChainImpl
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SwapChain  (const DxFactoryPtr& factory, const AdapterPtr& adapter, const DxDevicePtr& device, const SwapChainDesc& desc);
    ~SwapChain ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IAdapter* GetAdapter ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IDXGISwapChain& GetHandle ();
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (SwapChainDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ������ � ������������ �������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IOutput* GetContainingOutput ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ��������� full-screen mode
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetFullscreenState (bool state);
    bool GetFullscreenState ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������� ������� ������ � ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Present ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IPropertyList* GetProperties ();
    
  private:
    AdapterPtr     adapter;    //�������
    DxSwapChainPtr swap_chain; //������� ������
    SwapChainDesc  desc;       //���������� ������� ������
    PropertyList   properties; //�������� ������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Context: virtual public IDeviceContext, public DeviceObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Context  (const DxContextPtr& context, const DeviceManager& device_manager, ShaderLibrary& shader_library, const InputLayoutPtr& default_input_layout, const IProgramPtr& default_program);
    ~Context ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ID3D11DeviceContext& GetHandle ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Begin (IQuery* async);
    void End   (IQuery* async);
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ������� (input-stage)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void          ISSetInputLayout  (IInputLayout* state);
    void          ISSetVertexBuffer (size_t vertex_buffer_slot,  IBuffer* buffer);
    void          ISSetIndexBuffer  (IBuffer* buffer);
    IInputLayout* ISGetInputLayout  ();
    IBuffer*      ISGetVertexBuffer (size_t vertex_buffer_slot);
    IBuffer*      ISGetIndexBuffer  ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� �������� (shader-stage)
/// � ������ ������������ ������������ ���������� � ��������� � ������� - ������������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                      SSSetProgram                 (IProgram* program);
    void                      SSSetProgramParametersLayout (IProgramParametersLayout* parameters_layout);
    void                      SSSetSampler                 (size_t sampler_slot, ISamplerState* state);
    void                      SSSetTexture                 (size_t sampler_slot, ITexture* texture);
    void                      SSSetConstantBuffer          (size_t buffer_slot, IBuffer* buffer);
    IProgramParametersLayout* SSGetProgramParametersLayout ();
    IProgram*                 SSGetProgram                 ();
    ISamplerState*            SSGetSampler                 (size_t sampler_slot);
    ITexture*                 SSGetTexture                 (size_t sampler_slot);
    IBuffer*                  SSGetConstantBuffer          (size_t buffer_slot);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������� (rasterizer-stage)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void              RSSetState    (IRasterizerState* state);
    void              RSSetViewport (size_t render_target_slot, const Viewport& viewport);
    void              RSSetScissor  (size_t render_target_slot, const Rect& scissor_rect);
    IRasterizerState* RSGetState    ();
    const Viewport&   RSGetViewport (size_t render_target_slot);
    const Rect&       RSGetScissor  (size_t render_target_slot);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ������� (output-stage)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                OSSetBlendState        (IBlendState* state);
    void                OSSetDepthStencilState (IDepthStencilState* state);
    void                OSSetStencilReference  (size_t reference);
    void                OSSetRenderTargets     (size_t views_count, IView** render_target_view, IView* depth_stencil_view);
    void                OSSetRenderTargetView  (size_t render_target_slot, IView* view);
    void                OSSetDepthStencilView  (IView* view);
    IBlendState*        OSGetBlendState        ();
    IDepthStencilState* OSGetDepthStencilState ();
    size_t              OSGetStencilReference  ();
    IView*              OSGetRenderTargetView  (size_t render_target_slot);
    IView*              OSGetDepthStencilView  ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void     SOSetTargets      (size_t buffers_count, IBuffer** buffers, const size_t* offsets);
    void     SOSetTarget       (size_t stream_output_slot, IBuffer* buffer, size_t offset);
    IBuffer* SOGetTarget       (size_t stream_output_slot);
    size_t   SOGetTargetOffset (size_t stream_output_slot);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ClearRenderTargetView (size_t render_target_slot, const Color4f& color);
    void ClearDepthStencilView (size_t clear_flags, float depth, unsigned char stencil);
    void ClearViews            (size_t clear_flags, size_t render_targets_count, const size_t* render_target_indices, const Color4f* colors, float depth, unsigned char stencil);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���-������� �������� (���������� ��� ������� � ������� ������� ���������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GenerateMips (ITexture* texture);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetPredication    (IPredicate* predicate, bool predicate_value);
    IPredicate* GetPredicate      ();
    bool        GetPredicateValue ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void DrawAuto             (PrimitiveType primitive_type);
    void Draw                 (PrimitiveType primitive_type, size_t first_vertex, size_t vertices_count);
    void DrawIndexed          (PrimitiveType primitive_type, size_t first_index, size_t indices_count, size_t base_vertex);
    void DrawInstanced        (PrimitiveType primitive_type, size_t vertex_count_per_instance, size_t instance_count, size_t first_vertex, size_t first_instance_location);
    void DrawIndexedInstanced (PrimitiveType primitive_type, size_t index_count_per_instance, size_t instance_count, size_t first_index, size_t base_vertex, size_t first_instance_location);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ���������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Flush ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ICommandList* FinishCommandList  (bool restore_state);
    void          ExecuteCommandList (ICommandList* list, bool restore_state);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ���������� � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind ();
    void PrepareDraw (PrimitiveType type);

  private:
    DxContextPtr          context;                 //�������� ���������
    RenderTargetContext   render_target_context;   //�������� ����� ���������
    TextureManagerContext texture_manager_context; //�������� ��������� �������
    InputManagerContext   input_manager_context;   //�������� ��������� �������� ������
    ShaderManagerContext  shader_manager_context;  //�������� ��������� ��������
    OutputManagerContext  output_manager_context;  //�������� ��������� ��������� ������
    PrimitiveType         current_primitive_type;  //������� ��� ����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DeviceDebugLayer: public xtl::noncopyable, private common::Lockable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    DeviceDebugLayer  (const DxDevicePtr& device);
    ~DeviceDebugLayer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void StopAndJoin ();

  private:
    void UpdateMessages ();
    void UpdateMessagesCore ();

    typedef xtl::uninitialized_storage<char> Buffer;

  private:
    Log            log;                      //����� ����������� ����������������
    DxDevicePtr    device;                   //���������� ���������
    DxInfoQueuePtr info_queue;               //������� �������������� ���������
    common::Action update_action;            //�������� ���������� ���������
    UINT64         processed_messages_count; //���������� ������������ ���������
    Buffer         message_buffer;           //����� ���������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Device: virtual public IDevice, public Object
{
  public:  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Device  (const AdapterPtr& adapter, const char* init_string);
    ~Device ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ���������� / ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ID3D11Device& GetHandle  ();
    AdapterPtr    GetAdapter ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        GetCaps                        (DeviceCaps&);
    const char* GetCapString                   (DeviceCapString);
    const char* GetVertexAttributeSemanticName (VertexAttributeSemantic semantic);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IInputLayout*             CreateInputLayout             (const InputLayoutDesc&);
    IProgramParametersLayout* CreateProgramParametersLayout (const ProgramParametersLayoutDesc&);
    IRasterizerState*         CreateRasterizerState         (const RasterizerDesc&);
    IBlendState*              CreateBlendState              (const BlendDesc&);
    IDepthStencilState*       CreateDepthStencilState       (const DepthStencilDesc&);
    ISamplerState*            CreateSamplerState            (const SamplerDesc&);
    IBuffer*                  CreateBuffer                  (const BufferDesc&);
    IProgram*                 CreateProgram                 (size_t shaders_count, const ShaderDesc* shader_descs, const LogFunction& error_log);
    ITexture*                 CreateTexture                 (const TextureDesc&);
    ITexture*                 CreateTexture                 (const TextureDesc&, const TextureData&);
    ITexture*                 CreateTexture                 (const TextureDesc&, IBuffer* buffer, size_t buffer_offset, const size_t* mip_sizes);
    ITexture*                 CreateRenderTargetTexture     (ISwapChain* swap_chain, size_t buffer_index);
    ITexture*                 CreateDepthStencilTexture     (ISwapChain* swap_chain);
    IView*                    CreateView                    (ITexture* texture, const ViewDesc&);
    IPredicate*               CreatePredicate               ();
    IQuery*                   CreateQuery                   (QueryType type);
    IStateBlock*              CreateStateBlock              (const StateBlockMask& mask);
    IDeviceContext*           CreateDeferredContext         ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IPropertyList* GetProperties ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������������� ��������� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IDeviceContext* GetImmediateContext ();

  private:
    ITexture* CreateTexture   (const TextureDesc&, const TextureData*);
    void      InitDefaults    ();
    void      StartDebugLayer ();
    void      StopDebugLayer  ();

  private:
    AdapterPtr                         adapter;               //������� ����������
    PropertyList                       properties;            //�������� ����������
    DxDevicePtr                        device;                //���������� ���������
    stl::auto_ptr<DeviceManager>       device_manager;        //�������� ����������
    ContextPtr                         immediate_context;     //���������������� �������� ���������
    stl::auto_ptr<RenderTargetManager> render_target_manager; //�������� ����� ����������
    stl::auto_ptr<TextureManager>      texture_manager;       //�������� �������
    stl::auto_ptr<InputManager>        input_manager;         //�������� �������� ������
    stl::auto_ptr<ShaderManager>       shader_manager;        //�������� ��������
    stl::auto_ptr<OutputManager>       output_manager;        //�������� ��������� ������
    InputLayoutPtr                     default_input_layout;  //������� ������ �� ���������
    IProgramPtr                        default_program;       //��������� �� ���������
    stl::auto_ptr<DeviceDebugLayer>    debug_layer;           //���������� ����
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ��� DX11
///////////////////////////////////////////////////////////////////////////////////////////////////
class Driver: virtual public IDriver, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Driver  ();
    ~Driver ();
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetDescription ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetCaps (DriverCaps&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t    GetAdaptersCount ();
    IAdapter* GetAdapter       (size_t index);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IAdapter* CreateAdapter (const char* name, const char* path, const char* init_string);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ISwapChain* CreateSwapChain (size_t prefered_adapters_count, IAdapter** prefered_adapters, const SwapChainDesc& desc);
    ISwapChain* CreateSwapChain (IDevice* device, const SwapChainDesc& desc);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IDevice* CreateDevice (ISwapChain* swap_chain, const char* init_string);
    IDevice* CreateDevice (size_t prefered_adapters_count, IAdapter** prefered_adapters, const char* init_string);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ����������� ���������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetDebugLog (const LogFunction&);
    const LogFunction& GetDebugLog ();

  private:
    void RegisterAdapter   (IAdapter*);
    void UnregisterAdapter (IAdapter*);

  private: 
    typedef stl::vector<IAdapter*>  AdapterWeakArray;
    typedef xtl::com_ptr<Adapter>   AdapterPtr;
    typedef stl::vector<AdapterPtr> AdapterArray;

  private:
    DxFactoryPtr     factory;             //������� DXGI
    AdapterArray     adapters;            //�������� ���������
    AdapterWeakArray registered_adapters; //������������������ �������� ���������
    Log              log;                 //����� ����������� ����������������
    LogFunction      dummy_log_fn;        //������� ����������� ����������������
};

}

}

}

#endif
