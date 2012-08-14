#ifndef COMMONLIB_HASH_HEADER
#define COMMONLIB_HASH_HEADER

#include <cstddef>

namespace common
{

/*
        CRC32
*/

size_t crc32 (const void* data,size_t size,size_t init_value=0xFFFFFFFF);

/*
        Adler32
*/

size_t adler32 (const void* data,size_t size,size_t init_value=1);

/*
        MD5
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��� ����������������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Md5Context
{
  public:
     Md5Context  ();
     ~Md5Context ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
     void Update (const void* buf, size_t len);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������� � ������������� ��������������� ���-��������
///////////////////////////////////////////////////////////////////////////////////////////////////     
     void Finish (unsigned char result_hash_value [16]);
     
  private:
    Md5Context (const Md5Context&); //no impl
    Md5Context& operator = (const Md5Context&); //no impl
     
  private:     
    struct Impl;
    Impl* impl;
};

//����������� ����� ������
void md5 (const void* buf, size_t len, unsigned char result_hash_value [16]);

/*
    SHA256
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��� SHA-256
///////////////////////////////////////////////////////////////////////////////////////////////////
class Sha256Context
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructor / destructor
///////////////////////////////////////////////////////////////////////////////////////////////////
     Sha256Context  ();
     ~Sha256Context ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
     void Update (const void* data, size_t data_size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
     void Finish (unsigned char (&result_hash_value) [32]);

  private:
    Sha256Context (const Sha256Context&);             //no impl
    Sha256Context& operator = (const Sha256Context&); //no impl

  private:
    struct Impl;
    Impl* impl;
};

void sha256 (const void* data, size_t size, unsigned char (&result_hash_value) [32]);

/*
    SHA1
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��� SHA-1
///////////////////////////////////////////////////////////////////////////////////////////////////
class Sha1Context
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructor / destructor
///////////////////////////////////////////////////////////////////////////////////////////////////
     Sha1Context  ();
     ~Sha1Context ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
     void Update (const void* data, size_t data_size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
     void Finish (unsigned char (&result_hash_value) [20]);

  private:
    Sha1Context (const Sha1Context&);             //no impl
    Sha1Context& operator = (const Sha1Context&); //no impl

  private:
    struct Impl;
    Impl* impl;
};

void sha1 (const void* data, size_t size, unsigned char (&result_hash_value) [20]);

/*
    ����������� �����
*/

size_t strhash   (const char*,size_t init_hash=0xFFFFFFFF);
size_t strihash  (const char*,size_t init_hash=0xFFFFFFFF);
size_t strhash   (const wchar_t*,size_t init_hash=0xFFFFFFFF);
size_t strihash  (const wchar_t*,size_t init_hash=0xFFFFFFFF);
size_t strnhash  (const char*,size_t length,size_t init_hash=0xFFFFFFFF);
size_t strnihash (const char*,size_t length,size_t init_hash=0xFFFFFFFF);
size_t strnhash  (const wchar_t*,size_t length,size_t init_hash=0xFFFFFFFF);
size_t strnihash (const wchar_t*,size_t length,size_t init_hash=0xFFFFFFFF);

}

#endif
