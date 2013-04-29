#ifndef RENDER_LOW_LEVEL_SHADER_HEADER
#define RENDER_LOW_LEVEL_SHADER_HEADER

#include <render/low_level/common.h>
#include <render/low_level/object.h>

namespace render
{

namespace low_level
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ShaderDesc
{
  const char* name;             //��� ������� (��� ������ ��������������� ���������)
  size_t      source_code_size; //����� ������ � �������� ����� ������� (size_t (-1) - ����� ������������ �������������)
  const char* source_code;      //����� � �������� �����
  const char* profile;          //������� �������
  const char* options;          //����� ���������� (� ����������� �� �������)
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IProgram: virtual public IObject
{
};

}

}

#endif
