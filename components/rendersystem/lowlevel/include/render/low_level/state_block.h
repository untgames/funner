#ifndef RENDER_LOW_LEVEL_STATE_BLOCK_HEADER
#define RENDER_LOW_LEVEL_STATE_BLOCK_HEADER

#include <render/low_level/common.h>
#include <render/low_level/object.h>

namespace render
{

namespace low_level
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������ ����� ��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum StateBlockGroup
{
  StateBlockGroup_InputStage,      //����� �������� ������ ���������� ���������
  StateBlockGroup_ShaderStage,     //����� ������ �������� ���������� ���������
  StateBlockGroup_RasterizerStage, //����� ������ ������������ ���������� ���������
  StateBlockGroup_OutputStage,     //����� ��������� ������ ���������� ���������

  StateBlockGroup_Num
};

#pragma pack(push)
#pragma pack(1)
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct StateBlockMask
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
  bool is_input_layout;
  bool is_vertex_buffers [DEVICE_VERTEX_BUFFER_SLOTS_COUNT];
  bool is_index_buffer;
  bool ss_program;
  bool ss_constant_buffer [DEVICE_CONSTANT_BUFFER_SLOTS_COUNT];
  bool ss_program_parameters_layout;
  bool ss_samplers [DEVICE_SAMPLER_SLOTS_COUNT];
  bool ss_textures [DEVICE_SAMPLER_SLOTS_COUNT];
  bool rs_state;
  bool rs_viewport;
  bool rs_scissor;
  bool os_blend_state;
  bool os_depth_stencil_state;
  bool os_render_target_view;
  bool os_depth_stencil_view;
  bool predication;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
  void Set   (StateBlockGroup group, bool value);
  void Set   (StateBlockGroup group);
  void Clear (StateBlockGroup group);
  void Set   ();
  void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
  StateBlockMask  operator ~  () const;
  StateBlockMask& operator |= (const StateBlockMask&);
  StateBlockMask& operator &= (const StateBlockMask&);
  StateBlockMask& operator ^= (const StateBlockMask&);
  StateBlockMask  operator |  (const StateBlockMask&) const;
  StateBlockMask  operator &  (const StateBlockMask&) const;
  StateBlockMask  operator ^  (const StateBlockMask&) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
  bool operator == (const StateBlockMask&) const;
  bool operator != (const StateBlockMask&) const;
};

#pragma pack(pop)

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IStateBlock: virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void GetMask (StateBlockMask&) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Capture () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Apply () = 0;
};

}

}

#endif
