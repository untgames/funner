#ifndef COMMONLIB_UTF_CONVERTER_HEADER
#define COMMONLIB_UTF_CONVERTER_HEADER

#include <wchar.h>
#include <stl/string_fwd>
#include <common/strconv.h>

namespace common
{
///////////////////////////////////////////////////////////////////////////////////////////////////
///Преобразование кодировок
///////////////////////////////////////////////////////////////////////////////////////////////////

enum Encoding
{
  Encoding_ASCII7,
  Encoding_UTF8,
  Encoding_UTF16LE,
  Encoding_UTF16BE,
  Encoding_UTF32LE,
  Encoding_UTF32BE,

  Encoding_Count
};

void convert_encoding(Encoding       source_encoding,
                      const void*&   source,
                      size_t&        source_size,
                      Encoding       destination_encoding,
                      void*&         destination,
                      size_t&        destination_size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Перекодировка char <-> wchar_t
///////////////////////////////////////////////////////////////////////////////////////////////////
stl::string  tostring  (const wchar_t* string, int length);
stl::string  tostring  (const wchar_t* string);
stl::string  tostring  (const stl::wstring&);
stl::wstring towstring (const char* string, int length);
stl::wstring towstring (const char* string);
stl::wstring towstring (const stl::string&);

};

#endif
