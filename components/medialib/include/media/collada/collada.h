#ifndef MEDIALIB_COLLADA_PARSER_HEADER
#define MEDIALIB_COLLADA_PARSER_HEADER

#include "scene.h"
#include "animation.h"
#include <common/parser.h>

namespace medialib
{

//���������� ����������!!!

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Item>
class ColladaLib
{
  public:
    ColladaLib (const Collada&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Count () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Item operator [] (size_t index) const;
    Item operator [] (const char* id) const;

  private:
    const ColladaImpl *impl;
};

typedef ColladaLib<ColladaMesh>          ColladaMeshLib;
typedef ColladaLib<ColladaMaterial>      ColladaMaterialLib;
typedef ColladaLib<ColladaEffect>        ColladaEffectLib;
typedef ColladaLib<ColladaLight>         ColladaLightLib;
typedef ColladaLib<ColladaCamera>        ColladaCameraLib;
typedef ColladaLib<ColladaController>    ColladaControllerLib;
typedef ColladaLib<ColladaNode>          ColladaNodeLib;
typedef ColladaLib<ColladaVisualScene>   ColladaVisualSceneLib;
typedef ColladaLib<ColladaAnimation>     ColladaAnimationLib;
typedef ColladaLib<ColladaAnimationClip> ColladaAnimationClipLib;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Collada
{
  friend class ColladaWrappers;
  template <class T> friend class ColladaLib;
  public: 
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Collada  (common::Parser::Log* log, const char* file_name);
    ~Collada ();
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    ColladaVisualScene ActiveScene () const;
    
  private:
    Collada (ColladaImpl*);

  private:
    ColladaImpl* impl;
};

}

#endif
