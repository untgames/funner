#ifndef COMMONLIB_STREAMS_HEADER
#define COMMONLIB_STREAMS_HEADER

#include <stl/auto_ptr.h>
#include <xtl/functional_fwd>
#include <xtl/common_exceptions.h>

namespace stl
{

//forward declaration
template <class Char, class Traits, class Allocator> class basic_string;

}

namespace xtl
{

//forward declaration
template <class FwdIter> class iterator_range;

}

namespace math
{

//forward declarations
template <class T, unsigned int Size> class vector;
template <class T, unsigned int Size> class matrix;
template <class T>                    class quat;

}

namespace common
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class OutputStreamBuffer
{
  public:
    enum { DEFAULT_BUFFER_SIZE = 8192 };

    typedef xtl::function<size_t (const void* buffer, size_t buffer_size)> WriteFunction;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    explicit OutputStreamBuffer  (size_t buffer_size = DEFAULT_BUFFER_SIZE);
    explicit OutputStreamBuffer  (const WriteFunction& writer, size_t buffer_size = DEFAULT_BUFFER_SIZE);
             ~OutputStreamBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Write (const void* buffer, size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size   () const;
    void   Resize (size_t buffer_size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ����������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetUserBuffer (void* buffer, size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                 SetWriter (const WriteFunction&);
    const WriteFunction& Writer    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ������ �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static size_t DefaultWriter (const void* buffer, size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Flush ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (OutputStreamBuffer&);

  private:
    OutputStreamBuffer (const OutputStreamBuffer&); //no impl
    OutputStreamBuffer& operator = (const OutputStreamBuffer&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (OutputStreamBuffer&, OutputStreamBuffer&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputStreamBuffer
{
  public:
    enum { DEFAULT_BUFFER_SIZE = 8192 };

    typedef xtl::function<size_t (void* buffer, size_t buffer_size)> ReadFunction;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    explicit InputStreamBuffer  (size_t buffer_size = DEFAULT_BUFFER_SIZE);
    explicit InputStreamBuffer  (const ReadFunction& reader, size_t buffer_size = DEFAULT_BUFFER_SIZE);
             ~InputStreamBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Read (void* buffer, size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size   () const;
    void   Resize (size_t buffer_size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ����������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetUserBuffer (void* buffer, size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                SetReader (const ReadFunction&);
    const ReadFunction& Reader    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ������ �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static size_t DefaultReader (void* buffer, size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (InputStreamBuffer&);

  private:
    InputStreamBuffer (const InputStreamBuffer&); //no impl
    InputStreamBuffer& operator = (const InputStreamBuffer&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (InputStreamBuffer&, InputStreamBuffer&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������: ���������� �������� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct StreamWriteException: virtual public xtl::exception {};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ������ (����� ������ � UTF8)
///////////////////////////////////////////////////////////////////////////////////////////////////
class OutputTextStream
{
  public:
    typedef OutputStreamBuffer::WriteFunction WriteFunction;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    explicit OutputTextStream  (size_t buffer_size = OutputStreamBuffer::DEFAULT_BUFFER_SIZE);
    explicit OutputTextStream  (const WriteFunction& writer, size_t buffer_size = OutputStreamBuffer::DEFAULT_BUFFER_SIZE);
             ~OutputTextStream ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const OutputStreamBuffer& Buffer () const;
          OutputStreamBuffer& Buffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� (������� �������� ����������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Write (const char* string);
    void Write (const char* string, size_t length);
    void Write (const wchar_t* string);
    void Write (const wchar_t* string, size_t length);

  private:
    OutputTextStream (const OutputTextStream&); //no impl
    OutputTextStream& operator = (const OutputTextStream&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
void write (OutputTextStream&, const char* string);
void write (OutputTextStream&, const wchar_t* string);

template <class Traits, class Allocator>
void write (OutputTextStream&, const stl::basic_string<char, Traits, Allocator>&);

template <class Traits, class Allocator>
void write (OutputTextStream&, const stl::basic_string<wchar_t, Traits, Allocator>&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
void write (OutputTextStream&, char symbol);
void write (OutputTextStream&, wchar_t symbol);
void write (OutputTextStream&, size_t count, char symbol);
void write (OutputTextStream&, size_t count, wchar_t symbol);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� �����
///  format:
///    ""      - ����� � ��������������� �� ���������
///    "hex"   - ����� � ����������������� �������
///    "#"     - ����� � ������������ �� ��������� (' ') � ������� �� ������ 1
///    "000"   - ����� � ������������ 0 � ������� 3
///    "+##"   - ����� � ������������ �� ���������, ������� 3 � ��������� �����
///    "hex:#" - ����� � ������������ �� ���������, ������� 1 � ����������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    //������� �������� �������!!!
void write (OutputTextStream&, int value, const char* format="");
void write (OutputTextStream&, long value, const char* format="");
void write (OutputTextStream&, unsigned int value, const char* format="");
void write (OutputTextStream&, unsigned long value, const char* format="");

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� � ��������� ������
///  format (���������� ����� ������, �������� ������� ���������):
///    ���������� ����� - ������ ������� ����� � ��������������� �� ���������
///    ".##" - ������ �� ������ 2-� (1.2=1.2, 1.211=1.2)
///    ".00" - ������ 2 (1.2=1.20, 1.211=1.21)
///////////////////////////////////////////////////////////////////////////////////////////////////
    //������� �������� �������!!!
void write (OutputTextStream&, float value, const char* format="");
void write (OutputTextStream&, double value, const char* format="");
void write (OutputTextStream&, long double value, const char* format="");

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���������� ��������
///  format:
///    "alpha" - ����� � ��������� ���� (true, false)
///    ""      - ����� � ��������� ���� (0, 1)
///////////////////////////////////////////////////////////////////////////////////////////////////
void write (OutputTextStream&, bool value, const char* format);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ �������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T, unsigned int size>
void write (OutputTextStream&, const math::vector<T, size>& value, const char* format="");

template <class T, unsigned int size>
void write (OutputTextStream&, const math::matrix<T, size>& value, const char* format="");

template <class T>
void write (OutputTextStream&, const math::quat<T>& value, const char* format="");

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class InIter>
void write_range (OutputTextStream&, InIter first, InIter last);

template <class InIter>
void write_range (OutputTextStream&, InIter first, InIter last, const char* format);

template <class FwdIter>
void write (OutputTextStream&, const xtl::iterator_range<FwdIter>&);

template <class FwdIter>
void write (OutputTextStream&, const xtl::iterator_range<FwdIter>&, const char* format);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����� ������ � ������ ������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <common/detail/streams.inl>

}

#endif
