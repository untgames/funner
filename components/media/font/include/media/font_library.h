#ifndef MEDIALIB_FONT_LIBRARY_HEADER
#define MEDIALIB_FONT_LIBRARY_HEADER

#include <media/font.h>

#include <xtl/functional_fwd>

namespace media
{

//forward declarations
class FontLibrary;

//////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���� ������
//////////////////////////////////////////////////////////////////////////////////////////////////
enum FontWeight
{
  FontWeight_DontCare   = 0,
  FontWeight_Thin       = 100,
  FontWeight_ExtraLight = 200,
  FontWeight_UltraLight = 200,
  FontWeight_Light      = 300,
  FontWeight_Normal     = 400,
  FontWeight_Regular    = 400,
  FontWeight_Medium     = 500,
  FontWeight_SemiBold   = 600,
  FontWeight_DemiBold   = 600,
  FontWeight_Bold       = 700,
  FontWeight_ExtraBold  = 800,
  FontWeight_UltraBold  = 800,
  FontWeight_Heavy      = 900,
  FontWeight_Black      = 900
};

//////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ������
//////////////////////////////////////////////////////////////////////////////////////////////////
struct FontCreationParams
{
  size_t      font_size;       //������ ������� � ��������
  size_t      font_size_eps;   //���������� ���������� �� ��������� ������� ��� ������ ������ (���� �������� ������ ������ ����������� ��������)
  size_t      weight;          //��� ������ � ��������� �� 0 �� 1000, ���� �������� ����� 0 - ������������ ��� �� ���������
  int         escapement;      //������ � �������� ����� �������
  bool        bold;            //������������ �� ������ ������ ������
  bool        itallic;         //������������ �� ��������� ������ ������
  bool        underlined;      //������������ �� �������������
  bool        striked;         //������������ �� ��������������
  size_t      stroke_size;     //������� ������� � �������� ����� �������
  size_t      horizontal_dpi;  //�������������� ��������� ����� �������� ���������� �����������
  size_t      vertical_dpi;    //������������ ��������� ����� �������� ���������� �����������
  const char* charset_name;    //��� ������������� ������ ��������
};

//////////////////////////////////////////////////////////////////////////////////////////////////
///�����
//////////////////////////////////////////////////////////////////////////////////////////////////
class IFontDesc
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t FontsCount () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������� / ��� ��������� / ��� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual const char* FamilyName (size_t index) = 0;
    virtual const char* StyleName (size_t index) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Font CreateFont    (size_t index, const FontCreationParams&) = 0;
    virtual bool CanCreateFont (size_t index, const FontCreationParams&) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void AddRef () = 0;
    virtual void Release () = 0;

 protected:
    virtual ~IFontDesc () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class FontDesc
{
  friend class FontLibrary;

  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FontDesc  (const FontDesc&);
    ~FontDesc ();    

    FontDesc& operator = (const FontDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Source () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������� / ��� ��������� / ��� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* FamilyName () const;
    const char* StyleName  () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Font CreateFont     (const FontCreationParams&) const;
    bool CanCreateFont  (const FontCreationParams&) const;

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FontDesc (const char* source, IFontDesc* desc, size_t index);

  private:
    struct Impl
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class FontLibrary
{
  public:
    typedef xtl::iterator<FontDesc>       Iterator;
    typedef xtl::iterator<const FontDesc> ConstIterator;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FontLibrary  ();
    FontLibrary  (const FontLibrary& source);
    ~FontLibrary ();

    FontLibrary& operator = (const FontLibrary&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name    () const;
    void        SetName (const char* name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������ ������� � ���������� / �������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size    () const;
    bool   IsEmpty () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Iterator      CreateIterator ();
    ConstIterator CreateIterator () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* ItemId (const ConstIterator&) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    FontDesc Find (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadFont    (const char* file_name);
    void LoadFonts   (const char* wildcard);
    void UnloadFont  (const char* file_name);
    void UnloadFonts (const char* wildcard);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Font CreateFont (const char* name, const FontCreationParams& params);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void EnableCache   () { SetCacheState (true); }
    void DisableCache  () { SetCacheState (false); }
    void SetCacheState (bool state);
    bool CacheState    () const;

    void        SetCacheDir (const char* dir_name);
    const char* CacheDir    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (FontLibrary&);

  private:
    struct Impl;
    Impl* impl;
};

//////////////////////////////////////////////////////////////////////////////////////////////////
///�����
//////////////////////////////////////////////////////////////////////////////////////////////////
void swap (FontLibrary&, FontLibrary&);

//////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
//////////////////////////////////////////////////////////////////////////////////////////////////
typedef common::ResourceSerializerManager<IFontDesc* (const char*), void (const char*, const Font&)> FontManager;

}

#endif
