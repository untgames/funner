#include "shared.h"

using namespace render::low_level;
using namespace render::low_level::dx11;

/*
===================================================================================================
    ContextState
===================================================================================================
*/

ContextState::ContextState (const DeviceManager& manager)
  : render_target_context_state (manager)
  , texture_manager_context_state (manager)
  , input_manager_context_state (manager)
  , shader_manager_context_state (manager)
  , output_manager_context_state (manager)
  , query_manager_context_state (manager)
{
}

/*
===================================================================================================
    Context
===================================================================================================
*/

/*
    Конструктор
*/

Context::Context (const DxContextPtr& in_context, const DeviceManager& device_manager, ShaderLibrary& shader_library, const InitialResources& initial_resources, const DefaultResources& default_resources)
try
  : IDeviceContextImpl (device_manager)
  , context (in_context)
  , render_target_context (device_manager, in_context)
  , texture_manager_context (device_manager, in_context)
  , input_manager_context (device_manager, in_context, default_resources)
  , shader_manager_context (shader_library, in_context, default_resources)
  , output_manager_context (device_manager, in_context, default_resources)
  , query_manager_context (device_manager, in_context)
  , current_primitive_type (PrimitiveType_Num)
  , render_targets_changed ()
{
  if (!context)
    throw xtl::make_null_argument_exception ("", "context");

  if (initial_resources.render_target_view && initial_resources.depth_stencil_view)
  {
    OSSetRenderTargetView (0, initial_resources.render_target_view.get ());
    OSSetDepthStencilView (initial_resources.depth_stencil_view.get ());
    RSSetViewport         (0, initial_resources.viewport);
    RSSetScissor          (0, initial_resources.scissor);
  }

  ISSetInputLayout       (initial_resources.input_layout.get ());
  OSSetBlendState        (initial_resources.blend_state.get ());
  OSSetDepthStencilState (initial_resources.depth_stencil_state.get ());
  RSSetState             (initial_resources.rasterizer_state.get ());
}
catch (xtl::exception& e)
{
  e.touch ("render::low_level::dx11::Context::Context");
  throw;
}

Context::~Context ()
{
}

/*
    Получение низкоуровневого дескриптора
*/

ID3D11DeviceContext& Context::GetHandle ()
{
  return *context;
}

/*
    Управление входным уровнем (input-stage)
*/

void Context::ISSetInputLayout (IInputLayout* in_state)
{
  try
  {
    InputLayout* state = cast_object<InputLayout> (in_state, "", "state");

    input_manager_context.SetInputLayout (state);
    shader_manager_context.SetInputLayout (state);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ISSetInputLayout");
    throw;
  }
}

void Context::ISSetVertexBuffer (size_t vertex_buffer_slot, IBuffer* buffer)
{
  try
  {
    input_manager_context.SetVertexBuffer (vertex_buffer_slot, buffer);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ISSetVertexBuffer");
    throw;
  }
}

void Context::ISSetIndexBuffer (IBuffer* buffer)
{
  try
  {
    input_manager_context.SetIndexBuffer (buffer);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ISSetIndexBuffer");
    throw;
  }
}

IInputLayout* Context::ISGetInputLayout ()
{
  try
  {
    return input_manager_context.GetInputLayout ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ISGetInputLayout");
    throw;
  }
}

IBuffer* Context::ISGetVertexBuffer (size_t vertex_buffer_slot)
{
  try
  {
    return input_manager_context.GetVertexBuffer (vertex_buffer_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ISGetVertexBuffer");
    throw;
  }
}

IBuffer* Context::ISGetIndexBuffer ()
{
  try
  {
    return input_manager_context.GetIndexBuffer ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ISGetIndexBuffer");
    throw;
  }
}

/*
    Управление уровнем вывода вершин
*/

void Context::SOSetTargets (size_t buffers_count, IBuffer** buffers, const size_t* offsets)
{
  try
  {
    input_manager_context.SOSetTargets (buffers_count, buffers, offsets);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SOSetTargets");
    throw;
  }
}

void Context::SOSetTarget (size_t stream_output_slot, IBuffer* buffer, size_t offset)
{
  try
  {
    input_manager_context.SOSetTarget (stream_output_slot, buffer, offset);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SOSetTarget");
    throw;
  }
}

IBuffer* Context::SOGetTarget (size_t stream_output_slot)
{
  try
  {
    return input_manager_context.SOGetTarget (stream_output_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SOGetTarget");
    throw;
  }
}

size_t Context::SOGetTargetOffset (size_t stream_output_slot)
{
  try
  {
    return input_manager_context.SOGetTargetOffset (stream_output_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SOGetTargetOffset");
    throw;
  }
}

/*
    Управление шейдерными уровнями (shader-stage)
*/

void Context::SSSetProgram (IProgram* program)
{
  try
  {
    shader_manager_context.SetProgram (program);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSSetProgram");
    throw;
  }
}

void Context::SSSetProgramParametersLayout (IProgramParametersLayout* layout)
{
  try
  {
    shader_manager_context.SetProgramParametersLayout (layout);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSSetProgramParametersLayout");
    throw;
  }
}

void Context::SSSetConstantBuffer (size_t buffer_slot, IBuffer* buffer)
{
  try
  {
    shader_manager_context.SetConstantBuffer (buffer_slot, buffer);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSSetConstantBuffer");
    throw;
  }
}

IProgramParametersLayout* Context::SSGetProgramParametersLayout ()
{
  try
  {
    return shader_manager_context.GetProgramParametersLayout ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSGetProgramParametersLayout");
    throw;
  }
}

IProgram* Context::SSGetProgram ()
{
  try
  {
    return shader_manager_context.GetProgram ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSGetProgram");
    throw;
  }
}

IBuffer* Context::SSGetConstantBuffer (size_t buffer_slot)
{
  try
  {
    return shader_manager_context.GetConstantBuffer (buffer_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSGetConstantBuffer");
    throw;
  }
}

/*
    Управление текстурами
*/

void Context::SSSetSampler (size_t sampler_slot, ISamplerState* state)
{
  try
  {
    texture_manager_context.SetSampler (sampler_slot, state);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSSetSampler");
    throw;
  }
}

void Context::SSSetTexture (size_t sampler_slot, ITexture* texture)
{
  try
  {
    texture_manager_context.SetTexture (sampler_slot, texture);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSSetTexture");
    throw;
  }
}

ISamplerState* Context::SSGetSampler (size_t sampler_slot)
{
  try
  {
    return texture_manager_context.GetSampler (sampler_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSGetSampler");
    throw;
  }
}

ITexture* Context::SSGetTexture (size_t sampler_slot)
{
  try
  {
    return texture_manager_context.GetTexture (sampler_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SSGetTexture");
    throw;
  }
}

/*
    Управление растеризатором (rasterizer-stage)
*/

void Context::RSSetState (IRasterizerState* state)
{
  try
  {
    output_manager_context.SetRasterizerState (state);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::RSSetState");
    throw;
  }
}

void Context::RSSetViewport (size_t render_target_slot, const Viewport& viewport)
{
  try
  {
    render_targets_changed = true;

    render_target_context.SetViewport (render_target_slot, viewport);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::RSSetViewport");
    throw;
  }
}

void Context::RSSetScissor (size_t render_target_slot, const Rect& scissor_rect)
{
  try
  {
    render_targets_changed = true;

    render_target_context.SetScissor (render_target_slot, scissor_rect);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::RSSetScissor");
    throw;
  }
}

IRasterizerState* Context::RSGetState ()
{
  try
  {
    return output_manager_context.GetRasterizerState ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::RSGetState");
    throw;
  }
}

const Viewport& Context::RSGetViewport (size_t render_target_slot)
{
  try
  {
    return render_target_context.GetViewport (render_target_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::RSGetViewport");
    throw;
  }
}

const Rect& Context::RSGetScissor (size_t render_target_slot)
{
  try
  {
    return render_target_context.GetScissor (render_target_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::RSGetScissor");
    throw;
  }
}

/*
    Управление выходным уровнем (output-stage)
*/

void Context::OSSetBlendState (IBlendState* state)
{
  try
  {
    output_manager_context.SetBlendState (state);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSSetBlendState");
    throw;
  }
}

void Context::OSSetDepthStencilState (IDepthStencilState* state)
{
  try
  {
    output_manager_context.SetDepthStencilState (state);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSSetDepthStencilState");
    throw;
  }
}

void Context::OSSetStencilReference (size_t reference)
{
  try
  {
    output_manager_context.SetStencilReference (reference);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSSetStencilReference");
    throw;
  }
}

IBlendState* Context::OSGetBlendState ()
{
  try
  {
    return output_manager_context.GetBlendState ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSGetBlendState");
    throw;
  }
}

IDepthStencilState* Context::OSGetDepthStencilState ()
{
  try
  {
    return output_manager_context.GetDepthStencilState ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSGetDepthStencilState");
    throw;
  }
}

size_t Context::OSGetStencilReference ()
{
  try
  {
    return output_manager_context.GetStencilReference ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSGetStencilReference");
    throw;
  }
}

/*
    Управление менеджером целевых буферов отрисовки
*/

void Context::OSSetRenderTargets (size_t count, IView** render_target_views, IView* depth_stencil_view)
{
  try
  {
    if (!render_target_views && count)
      throw xtl::make_null_argument_exception ("", "render_target_views");

    render_targets_changed = true;

    for (size_t i=0; i<count; i++)
      render_target_context.SetRenderTargetView (i, render_target_views [i]);

    for (size_t i=count; i<DEVICE_RENDER_TARGET_SLOTS_COUNT; i++)
      render_target_context.SetRenderTargetView (i, 0);

    render_target_context.SetDepthStencilView (depth_stencil_view);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSSetRenderTargets");
    throw;
  }
}

void Context::OSSetRenderTargetView (size_t render_target_slot, IView* render_target_view)
{
  try
  {    
    render_targets_changed = true;

    render_target_context.SetRenderTargetView (render_target_slot, render_target_view);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSSetRenderTargetView");
    throw;
  }
}

void Context::OSSetDepthStencilView (IView* depth_stencil_view)
{
  try
  {    
    render_targets_changed = true;

    render_target_context.SetDepthStencilView (depth_stencil_view);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSSetDepthStencilView");
    throw;
  }
}

IView* Context::OSGetRenderTargetView (size_t render_target_slot)
{
  try
  {    
    return render_target_context.GetRenderTargetView (render_target_slot);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSGetRenderTargetView");
    throw;
  }
}

IView* Context::OSGetDepthStencilView ()
{
  try
  {    
    return render_target_context.GetDepthStencilView ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::OSGetDepthStencilView");
    throw;
  }
}

void Context::ClearRenderTargetView (size_t view_index, const Color4f& color)
{
  try
  {    
    render_target_context.ClearRenderTargetView (view_index, color);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ClearRenderTargetView");
    throw;
  }
}

void Context::ClearDepthStencilView (size_t clear_flags, float depth, unsigned char stencil)
{
  try
  {    
    render_target_context.ClearDepthStencilView (clear_flags, depth, stencil);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ClearDepthStencilView");
    throw;
  }
}

void Context::ClearViews (size_t clear_flags, size_t views_count, const size_t* view_indices, const Color4f* colors, float depth, unsigned char stencil)
{
  try
  {    
    render_target_context.ClearViews (clear_flags, views_count, view_indices, colors, depth, stencil);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::ClearViews");
    throw;
  }
}

/*
   Генерация мип-уровней текстуры (необходимо для текстур в которые ведется рендеринг)
*/

void Context::GenerateMips (ITexture* texture)
{
  try
  {
    texture_manager_context.GenerateMips (texture);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::GenerateMips");
    throw;
  }
}

/*
    Управление предикатами отрисовки
*/

void Context::SetPredication (IPredicate* predicate, bool predicate_value)
{
  try
  {
    query_manager_context.SetPredication (predicate, predicate_value);
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::SetPredication");
    throw;
  }
}

IPredicate* Context::GetPredicate ()
{
  try
  {
    return query_manager_context.GetPredicate ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::GetPredicate");
    throw;
  }
}

bool Context::GetPredicateValue ()
{
  try
  {
    return query_manager_context.GetPredicateValue ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::dx11::Context::GetPredicateValue");
    throw;
  }
}

/*
    Работа со списками команд
*/

ICommandList* Context::FinishCommandList (bool restore_state)
{
  throw xtl::make_not_implemented_exception (__FUNCTION__);
}

void Context::ExecuteCommandList (ICommandList* list, bool restore_state)
{
  throw xtl::make_not_implemented_exception (__FUNCTION__);
}

/*
    Установка состояния подуровней в контекст
*/

void Context::Bind ()
{
  try
  {
    render_target_context.Bind ();
    texture_manager_context.Bind ();
    input_manager_context.Bind ();
    output_manager_context.Bind ();
    shader_manager_context.Bind ();  
    query_manager_context.Bind ();
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::Bind");
    throw;
  }
}

/*
    Рисование примитивов
*/

namespace
{

D3D11_PRIMITIVE_TOPOLOGY get_topology (PrimitiveType type)
{
  switch (type)
  {
    case PrimitiveType_PointList:       return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
    case PrimitiveType_LineList:        return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
    case PrimitiveType_LineStrip:       return D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
    case PrimitiveType_TriangleList:    return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    case PrimitiveType_TriangleStrip:   return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
    case PrimitiveType_TriangleFan:     throw xtl::format_not_supported_exception ("", "Primitive type %s not supported", get_name (type));
    default:                            throw xtl::make_argument_exception ("", "primitive_type", type);
  }
}

}

void Context::PrepareDraw (PrimitiveType type)
{
  try
  {
    Bind ();

    if (current_primitive_type != type)
    {
      context->IASetPrimitiveTopology (get_topology (type));

      current_primitive_type = type;
    }
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::PrepareDraw");
    throw;
  }  
}

void Context::Draw (PrimitiveType primitive_type, size_t first_vertex, size_t vertices_count)
{
  try
  {
    PrepareDraw   (primitive_type);
    context->Draw (vertices_count, first_vertex);
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::Draw");
    throw;
  }
}

void Context::DrawIndexed (PrimitiveType primitive_type, size_t first_index, size_t indices_count, size_t base_vertex)
{
  try
  {
    PrepareDraw          (primitive_type);
    context->DrawIndexed (indices_count, first_index, base_vertex);
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::DrawIndexed");
    throw;
  }
}

void Context::DrawInstanced (PrimitiveType primitive_type, size_t vertex_count_per_instance, size_t instance_count, size_t first_vertex, size_t first_instance_location)
{
  try
  {
    PrepareDraw            (primitive_type);
    context->DrawInstanced (vertex_count_per_instance, instance_count, first_vertex, first_instance_location);
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::DrawInstanced");
    throw;
  }
}

void Context::DrawIndexedInstanced (PrimitiveType primitive_type, size_t index_count_per_instance, size_t instance_count, size_t first_index, size_t base_vertex, size_t first_instance_location)
{
  try
  {
    PrepareDraw                   (primitive_type);
    context->DrawIndexedInstanced (index_count_per_instance, instance_count, first_index, base_vertex, first_instance_location);
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::DrawIndexedInstanced");
    throw;
  }
}

void Context::DrawAuto (PrimitiveType primitive_type)
{
  try
  {
    PrepareDraw       (primitive_type);
    context->DrawAuto ();
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::DrawAuto");
    throw;
  }
}

/*
    Ожидание завершения выполнения буфера команд
*/

void Context::Flush ()
{
  try
  {
    context->Flush ();
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("render::low_level::dx11::Context::Flush");
    throw;
  }
}

/*
    Копирование состояний
*/

void Context::Capture (const StateBlockMask& mask, ContextState& state) const
{
  render_target_context.CopyTo   (mask, state.render_target_context_state);
  texture_manager_context.CopyTo (mask, state.texture_manager_context_state);
  input_manager_context.CopyTo   (mask, state.input_manager_context_state);
  shader_manager_context.CopyTo  (mask, state.shader_manager_context_state);
  output_manager_context.CopyTo  (mask, state.output_manager_context_state);
  query_manager_context.CopyTo   (mask, state.query_manager_context_state);
}

void Context::Apply (const StateBlockMask& mask, const ContextState& state)
{
  state.render_target_context_state.CopyTo   (mask, render_target_context);
  state.texture_manager_context_state.CopyTo (mask, texture_manager_context);
  state.input_manager_context_state.CopyTo   (mask, input_manager_context);
  state.shader_manager_context_state.CopyTo  (mask, shader_manager_context);
  state.output_manager_context_state.CopyTo  (mask, output_manager_context);
  state.query_manager_context_state.CopyTo   (mask, query_manager_context);
}
