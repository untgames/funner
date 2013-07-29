#ifndef RENDER_SCENE_INTERCHANGE_TYPES_HEADER
#define RENDER_SCENE_INTERCHANGE_TYPES_HEADER

namespace render
{

namespace scene
{

namespace interchange
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef   signed int   int32;
typedef unsigned int   uint32;
typedef   signed short int16;
typedef unsigned short uint16;
typedef   signed char  int8;
typedef unsigned char  uint8;
typedef float          float32;

typedef uint32         command_id_t;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Command
{
  command_id_t command_id;   //������������� �������
  uint32       command_size; //������ �������
};

}

}

}

#endif
