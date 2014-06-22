#ifndef SCENE_GRAPH_TEXT_HEADER
#define SCENE_GRAPH_TEXT_HEADER

#include <stl/auto_ptr.h>
#include <sg/visual_model.h>

namespace media
{

//forward declarations
class  Font;
class  FontLibrary;
struct FontCreationParams;

}

namespace scene_graph
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �� ���������� ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum TextModelEvent
{
  TextModelEvent_AfterCharDescsUpdate, //����������� ����� ��������� ������ ��������

  TextModelEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct CharDesc
{
  unsigned int code;      //��� �������
  media::Font* font;      //����� (����� ���� �������)
  math::vec3f  position;  //������� �������
  math::vec2f  size;      //������ �������
  math::vec4f  color;     //���� �������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TextModel: public VisualModel
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetMaterial  (const char* material);
    const char* Material     () const;
    size_t      MaterialHash () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������-�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetTextureSemantic  (const char* semantic);
    const char* TextureSemantic     () const;
    size_t      TextureSemanticHash () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t          CharsCount () const;
    const CharDesc* Chars      () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t CharsCapacity () const;
    void   ReserveChars  (size_t count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (TextModel& sender, TextModelEvent event_id)> EventHandler;

    xtl::connection RegisterEventHandler (TextModelEvent event_id, const EventHandler& event_handler);
    
    using VisualModel::RegisterEventHandler;

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TextModel  (const media::FontLibrary& font_library);
    ~TextModel ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const media::FontLibrary& FontLibrary () const;
          media::FontLibrary& FontLibrary ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void      ResizeChars       (size_t count);
    CharDesc* CharsForUpdate    ();
    void      UpdateCharsNotify ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AcceptCore (Visitor&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RebuildChars ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void RebuildCharsCore () = 0;
    
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum TextLineAlignment
{
  TextLineAlignment_Center = 0,   //�� ������
  TextLineAlignment_Left = 1,     //�� ������ ����
  TextLineAlignment_Right = 2,    //�� ������� ����
  TextLineAlignment_Top = 1,      //�� �������� ����
  TextLineAlignment_Bottom = 2,   //�� ������� ����
  TextLineAlignment_BaseLine = 3, //�� ������� �����

  TextLineAlignment_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TextLine: public TextModel
{
  public:
    typedef xtl::com_ptr<TextLine>       Pointer;
    typedef xtl::com_ptr<const TextLine> ConstPointer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static Pointer Create (const media::FontLibrary&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetColor (const math::vec4f& color);
    void               SetColor (float red, float green, float blue);
    void               SetColor (float red, float green, float blue, float alpha);
    const math::vec4f& Color    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������������ �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetCharsColorFactors (size_t first, size_t count, const math::vec4f& color);
    const math::vec4f& CharColorFactor      (size_t index) const;
    void               CharsColorFactors    (size_t first, size_t count, math::vec4f* colors) const;
    const math::vec4f& CharColor            (size_t index) const;
    void               CharsColors          (size_t first, size_t count, math::vec4f* colors) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                SetTextUtf8   (const char* text_utf8);
    void                SetTextUtf32  (const unsigned int* text_utf32, size_t length);
    const char*         TextUtf8      () const;
    const unsigned int* TextUtf32     () const;
    size_t              TextLength    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t TextUtf8Hash  () const;
    size_t TextUtf32Hash () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                             SetFont               (const char* font_name);
    void                             SetFontCreationParams (const media::FontCreationParams&);
    const char*                      Font                  () const;
    const media::FontCreationParams& FontCreationParams    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� ������������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetSpacingMultiplier (float spacing_multiplier);
    float SpacingMultiplier    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void              SetAlignment           (TextLineAlignment horizontal, TextLineAlignment vertical);
    void              SetHorizontalAlignment (TextLineAlignment alignment);
    void              SetVerticalAlignment   (TextLineAlignment alignment);
    TextLineAlignment VerticalAlignment      () const;
    TextLineAlignment HorizontalAlignment    () const;

    using TextModel::RebuildChars;

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TextLine  (const media::FontLibrary&);
    ~TextLine ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AcceptCore (Visitor&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ���� � �������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void BindProperties (common::PropertyBindingMap& bindings);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RebuildCharsCore ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

#endif
