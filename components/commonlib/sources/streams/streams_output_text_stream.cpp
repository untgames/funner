#include "shared.h"

using namespace common;

const size_t FORMAT_BUFFER_SIZE = 16; //������ ������ ��������������

/*
    �������� ���������� ���������� ������ ������
*/

struct OutputTextStream::Impl
{
  OutputStreamBuffer buffer; //�����

  Impl (size_t buffer_size, const WriteFunction& in_writer = &OutputStreamBuffer::DefaultWriter) : buffer (in_writer, buffer_size) {}
};

/*
    ����������� / ����������
*/

OutputTextStream::OutputTextStream (size_t buffer_size)
  : impl (new Impl (buffer_size))
  {}

OutputTextStream::OutputTextStream (const WriteFunction& writer, size_t buffer_size)
  : impl (new Impl (buffer_size, writer))
  {}

OutputTextStream::~OutputTextStream ()
{
}

/*
    ����� ������
*/

const common::OutputStreamBuffer& OutputTextStream::Buffer () const
{
  return impl->buffer;
}

common::OutputStreamBuffer& OutputTextStream::Buffer ()
{
  return impl->buffer;
}

/*
    ����� �����
*/

void OutputTextStream::Write (const char* string, size_t size)
{
  if (!string && size)
    RaiseNullArgument ("common::OutputTextStream::Write(const char*,size_t)", "string");
    
  size_t write_size = impl->buffer.Write (string, size);
    
  if (write_size != size)
    Raise<StreamWriteException> ("common::OutputTextStream::Write", "Could not write block with size %u to the buffer (write_size=%u)",
                                 size, write_size);
}

void OutputTextStream::Write (const char* string)
{
  if (!string)
    RaiseNullArgument ("common::OutputTextStream::Write(const char*)", "string");
    
  Write (string, strlen (string));
}

void OutputTextStream::Write (const wchar_t*, size_t)
{
  RaiseNotImplemented ("common::OutputTextStream::Write(const wchar_t*,size_t)");
}

void OutputTextStream::Write (const wchar_t* string)
{
  if (!string)
    RaiseNullArgument ("common::OutputTextStream::Write(const wchar_t*)", "string");

  return Write (string, wcslen (string));
}

namespace common
{

/*
    ����� �����
*/

void write (OutputTextStream& stream, const char* string)
{
  stream.Write (string);
}

void write (OutputTextStream& stream, const wchar_t* string)
{
  stream.Write (string);
}

/*
    ����� ��������
*/

void write (OutputTextStream& stream, char symbol)
{
  stream.Write (&symbol, 1);
}

void write (OutputTextStream& stream, signed char symbol)
{
  stream.Write (reinterpret_cast<const char*> (&symbol), 1);
}

void write (OutputTextStream& stream, unsigned char symbol)
{
  stream.Write (reinterpret_cast<const char*> (&symbol), 1);
}

void write (OutputTextStream& stream, wchar_t symbol)
{
  stream.Write (&symbol, 1);
}

/*
    ����� ����� �����
      format:
        ""      - ����� � ��������������� �� ���������
        "hex"   - ����� � ����������������� �������
        "#"     - ����� � ������������ �� ��������� (' ') � ������� �� ������ 1
        "000"   - ����� � ������������ 0 � ������� 3
        "+##"   - ����� � ������������ �� ���������, ������� 3 � ��������� �����
        "hex:#" - ����� � ������������ �� ���������, ������� 1 � ����������������� �������
*/

namespace
{

//���������� ������� � printf-�����
void get_int_printf_format (const char*& format, bool sign, char buffer [FORMAT_BUFFER_SIZE])
{
  char* pos         = buffer;
  char  base_format = sign ? 'd' : 'u';

  *pos++ = '%';

  if (!strncmp (format, "hex:", 4))
  {
    base_format  = 'x';
    format      += 4;
  }
  else if (!strncmp (format, "oct:", 4))
  {
    base_format  = 'o';
    format      += 4;
  }
  else if (!strncmp (format, "dec:", 4))
  {
    base_format  = 'u';
    format      += 4;
  }
  
  switch (*format)
  {
    case '+':
    case '-':
      *pos++ = '+';
      format++;
      break;
  }

  string_wrappers::snprintf (pos, FORMAT_BUFFER_SIZE - (pos - buffer), "%s%u%c",
                             *format == '0' ? "0" : "", strlen (format), base_format);
}

//������ ������ �����
void write_int (OutputTextStream& stream, unsigned int value, const char* format, bool sign)
{
  if (!format)
    RaiseNullArgument ("common::write", "format");

  char format_buffer [FORMAT_BUFFER_SIZE], value_buffer [16];

  get_int_printf_format (format, sign, format_buffer);

  string_wrappers::snprintf (value_buffer, sizeof (value_buffer), format_buffer, value);

  stream.Write (value_buffer);
}

}

void write (OutputTextStream& stream, int value, const char* format)
{
  write_int (stream, static_cast<unsigned int> (value), format, true);
}

void write (OutputTextStream& stream, unsigned int value, const char* format)
{
  write_int (stream, value, format, false);
}

/*
  ����� ����� � ��������� ������
    format (���������� ����� ������, �������� ������� ���������):
      ���������� ����� - ������ ������� ����� � ��������������� �� ���������
      ".##" - ������ �� ������ 2-� (1.2=1.2, 1.211=1.2)
      ".00" - ������ 2 (1.2=1.20, 1.211=1.21)
*/

namespace
{

//���������� ������� � printf-�����
void get_float_printf_format (const char*& format, char buffer [FORMAT_BUFFER_SIZE])
{
  char* pos = buffer;

  *pos++ = '%';

  switch (*format)
  {
    case '+':
    case '-':
      *pos++ = '+';
      format++;
      break;
  }
  
  const char *dot = strchr (format, '.');
  
  if (dot)
  {
    const char* frac_format = dot + 1;
    size_t      frac_size   = strlen (frac_format);
    
    string_wrappers::snprintf (pos, FORMAT_BUFFER_SIZE - (pos - buffer), "%s%u.%uf",
                             *format == '0' ? "0" : "", dot - format + frac_size + 1, frac_size);
  }
  else
  {
    string_wrappers::snprintf (pos, FORMAT_BUFFER_SIZE - (pos - buffer), "%s%ug",
                             *format == '0' ? "0" : "", strlen (format));
  }
}

}

void write (OutputTextStream& stream, double value, const char* format)
{
  if (!format)
    RaiseNullArgument ("common::write", "format");

  char format_buffer [FORMAT_BUFFER_SIZE], value_buffer [16];

  get_float_printf_format (format, format_buffer);

  string_wrappers::snprintf (value_buffer, sizeof (value_buffer), format_buffer, value);

  stream.Write (value_buffer);  
}

void write (OutputTextStream& stream, float value, const char* format)
{
  write (stream, static_cast<double> (value), format);
}

void write (OutputTextStream& stream, long double value, const char* format)
{
  write (stream, static_cast<double> (value), format);
}

/*
    ����� ���������� ��������
      format:
        "alpha" - ����� � ��������� ���� (true, false)
        ""      - ����� � ��������� ���� (0, 1)
*/

void write (OutputTextStream& stream, bool value, const char* format)
{
  if (!format)
    RaiseNullArgument ("common::write", "format");
    
  if (!strcmp (format, "alpha")) stream.Write (value ? "true" : "false");
  else if (!*format)             stream.Write (value ? "1" : "0");
  else
  {
    RaiseInvalidArgument ("common::write", "format", format);
  }
}

}
