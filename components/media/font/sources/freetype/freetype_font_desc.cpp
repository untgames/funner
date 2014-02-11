#include "shared.h"

using namespace media;
using namespace media::freetype;

namespace
{

const char* LOG_NAME = "media::freetype::FreetypeFontDesc";

typedef xtl::uninitialized_storage<char> DataBuffer;
typedef xtl::shared_ptr<DataBuffer>      DataBufferPtr;

//����� free type
class FreetypeFace : public xtl::reference_counter
{
  public:
    FreetypeFace (const DataBufferPtr& in_data, const FreetypeLibrary& in_library, size_t face_index)
      : data (in_data)
      , library (in_library)
      , face (0)
    {
      library.FT_New_Memory_Face ((const FT_Byte*)data->data (), data->size (), face_index, &face);
      library.FT_Select_Charmap (face, FT_ENCODING_UNICODE);
    }

    ~FreetypeFace ()
    {
      try
      {
        if (face)
        {
          library.FT_Done_Face (face);
        }
      }
      catch (xtl::exception& e)
      {
        common::Log (LOG_NAME).Printf ("Can't destroy freetype face, exception '%s'", e.what ());
      }
    }

    FT_Face FaceHandle ()
    {
      return face;
    }

    //��������� ���������� ���������� ������� ������, ���� ����� �� ������ - ���������� 0
    size_t GetNearestFontSize (size_t size, size_t size_eps)
    {
      if (face->face_flags & FT_FACE_FLAG_SCALABLE)
        return size;

      if (!face->num_fixed_sizes)
        return 0;

      size_t min_size = size > size_eps ? size - size_eps : 1;
      size_t max_size = size + size_eps;

      if (max_size < size)
        max_size = (size_t)-1;

      size_t best_size;
      size_t size_diff  = (size_t)-1;
      bool   size_found = false;

      for (size_t i = 0; i < face->num_fixed_sizes; i++)
      {
        size_t current_size = face->available_sizes [i].width;

        if (current_size >= min_size && current_size <= max_size)
        {
          size_found = true;

          size_t current_size_diff = size > current_size ? size - current_size : current_size - size;

          if (!current_size_diff)
            return size;

          if (current_size_diff < size_diff)
          {
            size_diff = current_size_diff;
            best_size = current_size;
          }
        }
      }

      return size_found ? best_size : 0;
    }

  private:
    FreetypeFace (const FreetypeFace&);             //no impl
    FreetypeFace& operator = (const FreetypeFace&); //no impl

  private:
    DataBufferPtr   data;     //������ ����� ������
    FreetypeLibrary library;  //����������
    FT_Face         face;     //�����
};

typedef xtl::intrusive_ptr<FreetypeFace> FreetypeFacePtr;
typedef stl::vector<FreetypeFacePtr>     FacesArray;

}

namespace media
{

namespace freetype
{

/*
   �����
*/

struct FreetypeFontDesc::Impl
{
  DataBufferPtr   font_data; //������ ����� ������
  FreetypeLibrary library;   //freetype ����������, ������� ������ ��� ����� ��� ��������� ������ �� �������� � ������ �����
  FacesArray      faces;     //������
  stl::string     source;    //�������� ����

  ///����������� / ����������
  Impl (const char* file_name)
    : source (file_name)
  {
    try
    {
      common::InputFile font_file (file_name);

      font_data = DataBufferPtr (new DataBuffer (font_file.Size ()));

      font_file.Read (font_data->data (), font_data->size ());

      FT_Face test_face;

      library.FT_New_Memory_Face ((const FT_Byte*)font_data->data (), font_data->size (), -1, &test_face);

      FT_Long faces_count = test_face->num_faces;

      library.FT_Done_Face (test_face);

      faces.reserve (faces_count);

      for (size_t i = 0; i < faces_count; i++)
        faces.push_back (FreetypeFacePtr (new FreetypeFace (font_data, library, i), false));
    }
    catch (xtl::exception& e)
    {
      e.touch ("media::freetype::FreetypeFontDesc::FreetypeFontDesc");
      throw;
    }
  }
};

}

}

/*
   ����������� / ����������
*/

FreetypeFontDesc::FreetypeFontDesc (const char* file_name)
  : impl (new Impl (file_name))
  {}

FreetypeFontDesc::~FreetypeFontDesc ()
{
  delete impl;
}

/*
   ���������� ������� � ������
*/

size_t FreetypeFontDesc::FontsCount ()
{
  return impl->faces.size ();
}

/*
   ��� ��������� / ��� ��������� / ��� �����
*/

const char* FreetypeFontDesc::FamilyName (size_t index)
{
  if (index > impl->faces.size ())
    throw xtl::make_range_exception ("media::freetype::FreetypeFontDesc::FamilyName", "index", index, 0u, impl->faces.size ());

  return impl->faces [index]->FaceHandle ()->family_name;
}

const char* FreetypeFontDesc::StyleName (size_t index)
{
  if (index > impl->faces.size ())
    throw xtl::make_range_exception ("media::freetype::FreetypeFontDesc::StyleName", "index", index, 0u, impl->faces.size ());

  return impl->faces [index]->FaceHandle ()->style_name;
}

/*
   �������� ������
*/

Font FreetypeFontDesc::CreateFont (size_t index, const FontCreationParams& params)
{
  try
  {
    if (index > impl->faces.size ())
      throw xtl::make_range_exception ("", "index", index, 0u, impl->faces.size ());

    if (!CanCreateFont (index, params))
      throw xtl::make_argument_exception ("", "params");

    const char* charset = CharsetManager::FindCharset (params.charset_name);

    if (!charset)
      throw xtl::make_argument_exception ("", "params.charset");

    FreetypeFacePtr face        = impl->faces [index];
    FT_Face         face_handle = face->FaceHandle ();

    FontBuilder builder;

    builder.SetSource     (impl->source.c_str ());
    builder.Rename        (common::format ("%s %s", face_handle->family_name, face_handle->style_name).c_str ());
    builder.SetFamilyName (face_handle->family_name);
    builder.SetStyleName  (face_handle->style_name);
    builder.SetFontSize   (face->GetNearestFontSize (params.font_size, params.font_size_eps));

    return builder.Font ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("media::freetype::FreetypeFontDesc::CreateFont");
    throw;
  }
}

bool FreetypeFontDesc::CanCreateFont (size_t index, const FontCreationParams& params)
{
  if (index > impl->faces.size ())
    throw xtl::make_range_exception ("media::freetype::FreetypeFontDesc::CanCreateFont", "index", index, 0u, impl->faces.size ());

  if (!impl->faces [index]->GetNearestFontSize (params.font_size, params.font_size_eps))
    return false;

  if (params.weight != FontWeight_Normal)  //not implemented
    return false;

  if (params.escapement)  //not implemented
    return false;

  if (params.bold)  //not implemented
    return false;

  if (params.italic)  //not implemented
    return false;

  if (params.underlined)  //not implemented
    return false;

  if (params.striked)  //not implemented
    return false;

  if (params.stroke_size)  //not implemented
    return false;

  return true;
}
