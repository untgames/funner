#ifndef RENDER_SCENE_SERVER_TECHNIQUE_MANAGER_SHARED_HEADER
#define RENDER_SCENE_SERVER_TECHNIQUE_MANAGER_SHARED_HEADER

#include <xtl/function.h>

#include <common/component.h>

#include <shared/technique.h>

namespace render
{

namespace scene
{

namespace server
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TechniqueManager
{
  public:
    typedef xtl::function<Technique* (RenderManager& manager, const common::ParseNode& configuration)> TechniqueCreator;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void RegisterTechnique       (const char* technique, const TechniqueCreator& creator);
    static void UnregisterTechnique     (const char* technique);
    static void UnregisterAllTechniques ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static TechniquePtr CreateTechnique (const char* technique, RenderManager& manager, const common::ParseNode& configuration);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class TechniqueRegistrator
{
  public:
    TechniqueRegistrator ();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class TechniqueComponentRegistrator: public common::ComponentRegistrator<TechniqueRegistrator<T> >
{
  public:
    TechniqueComponentRegistrator ();
};

#include <shared/detail/technique_manager.inl>

}

}

}

#endif