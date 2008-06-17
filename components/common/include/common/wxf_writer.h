#ifndef COMMONLIB_WXF_WRITER_HEADER
#define COMMONLIB_WXF_WRITER_HEADER

#include <common/streams.h>
#include <string.h>

namespace common
{

//������������� ������ � ����

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������: �������� wxf-���
///////////////////////////////////////////////////////////////////////////////////////////////////
struct WrongWxfTagException: virtual public xtl::exception {};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����, ���������� ������������ ������ � ����� WXF �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class WxfWriter
{
  public:
    enum { 
      DEFAULT_FRAME_INDENT      = 2, //�������� ������� ������ (�� ���������)
      DEFAULT_ATTRIBUTES_INDENT = 16 //�������� ������� ������ ��������� �� ����� ���� (�� ���������)
    };
    
    typedef xtl::function<size_t (const void* buffer, size_t size)> WriteFunction;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    WxfWriter  (const char* file_name, size_t frame_indent=DEFAULT_FRAME_INDENT, size_t attr_indent=DEFAULT_ATTRIBUTES_INDENT);
    WxfWriter  (const WriteFunction& writer, size_t frame_indent=DEFAULT_FRAME_INDENT, size_t attr_indent=DEFAULT_ATTRIBUTES_INDENT);
    ~WxfWriter ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const OutputTextStream& Stream () const;
          OutputTextStream& Stream ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t FrameIndent      () const; //������ �������
    size_t AttributesIndent () const; //������ �� ���� �� ������ ���������

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void BeginFrame (const char* frame_tag);
    void EndFrame   ();

    template <class T> void BeginFrame (const char* frame_tag, const T& value);
    template <class T> void BeginFrame (const char* frame_tag, const T& value, const char* format);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
                       void Write (const char* tag);
    template <class T> void Write (const char* tag, const T& value);
    template <class T> void Write (const char* tag, const T& value, const char* format);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    template <class FwdIter> void Write (const char* tag, const xtl::iterator_range<FwdIter>& range);
    template <class FwdIter> void Write (const char* tag, const xtl::iterator_range<FwdIter>& range, const char* format);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���v�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void WriteComment (const char* comment);
    void WriteComment (const wchar_t* comment);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Flush ();

  private:
    void BeginFrame  ();
    void WriteIndent ();
    void WriteIndent (size_t indent);

    static void CheckTag (const char* tag, const char* function_name);

  private:
    WxfWriter (const WxfWriter&); //no impl
    WxfWriter& operator = (const WxfWriter&); //no impl

  private: 
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ��������� ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> void wxf_write (OutputTextStream&, const T& value);
template <class T> void wxf_write (OutputTextStream&, const T& value, const char* format);

void wxf_write (OutputTextStream&, signed char symbol);
void wxf_write (OutputTextStream&, unsigned char symbol);
void wxf_write (OutputTextStream&, const char* string);
void wxf_write (OutputTextStream&, const wchar_t* string);

template <class Traits, class Allocator> void wxf_write (OutputTextStream&, const stl::basic_string<char, Traits, Allocator>& string);
template <class Traits, class Allocator> void wxf_write (OutputTextStream&, const stl::basic_string<wchar_t, Traits, Allocator>& string);

#include <common/detail/wxf_writer.inl>

}

#endif
