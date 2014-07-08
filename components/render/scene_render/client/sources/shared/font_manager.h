#ifndef RENDER_SCENE_CLIENT_FONT_MANAGER_SHARED_HEADER
#define RENDER_SCENE_CLIENT_FONT_MANAGER_SHARED_HEADER

#include <stl/auto_ptr.h>

#include <xtl/shared_ptr.h>

namespace media
{

//forward declarations
class  Font;
struct FontCreationParams;
struct RasterizedFontCreationParams;

}

namespace render
{

namespace scene
{

namespace client
{

//forward declarations
class  MaterialManager;
struct FontRenderingTempCache;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � ��������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct RasterizedGlyphInfo
{
  unsigned short image_index; //������ ����������� � ������
  math::vec2f    tex_offset;  //�������� � ��������
  math::vec2f    tex_size;    //������ � ��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Font: public xtl::reference_counter, public xtl::trackable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Font  (MaterialManager& material_manager, const media::Font& font, const media::RasterizedFontCreationParams& creation_params);
    ~Font ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GlyphsCount ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t FirstGlyphCode ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const RasterizedGlyphInfo* RasterizedGlyphs ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t TexturesCount ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* TextureName (size_t texture_index);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

typedef xtl::intrusive_ptr<Font> FontPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class FontMaterial: public xtl::reference_counter, public xtl::trackable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FontMaterial  (MaterialManager& material_manager, const FontPtr& font, const char* material_name, const char* semantic);
    ~FontMaterial ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    client::Font& Font ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t MaterialsCount ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* MaterialName (size_t material_index);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

typedef xtl::intrusive_ptr<FontMaterial>        FontMaterialPtr;
typedef xtl::shared_ptr<FontRenderingTempCache> FontRenderingTempCachePtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class FontManager: public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FontManager  (MaterialManager&);
    ~FontManager ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ / ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FontPtr         CreateFont         (const media::Font&);
    FontMaterialPtr CreateFontMaterial (const media::Font&, const char* material, const char* semantic);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AttachFontLibrary      (const media::FontLibrary&);
    void DetachFontLibrary      (const media::FontLibrary&);
    void DetachAllFontLibraries ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadFont   (const char* id, const char* name, const media::FontCreationParams& params, const char* material, const char* semantic);
    void LoadFont   (const char* init_string);
    void UnloadFont (const char* id);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ����� ������� ���������� ��������� ���� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static bool IsFontParams (const char* resource);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                             SetFontRenderingTempCache (const FontRenderingTempCachePtr&);
    const FontRenderingTempCachePtr& FontRenderingTempCache    () const;

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

}

}

#endif