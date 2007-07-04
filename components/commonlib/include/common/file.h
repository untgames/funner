#ifndef __COMMONLIB_FILE_SYSTEM__
#define __COMMONLIB_FILE_SYSTEM__

#include <time.h>
#include <design/intrusive_ptr.h>
#include <common/callback.h>
#include <common/exception.h>

namespace common
{

//implementation forwards
class FileImpl;
class FileList;
class FileListImpl;
class FileListBuilder;

//intrusive pointers
typedef design::intrusive_ptr<FileImpl>     FileImplPtr;
typedef design::intrusive_ptr<FileListImpl> FileListImplPtr;

void intrusive_ptr_addref  (FileImpl*);
void intrusive_ptr_release (FileImpl*);
void intrusive_ptr_addref  (FileListImpl*);
void intrusive_ptr_release (FileListImpl*);

/*
    �������� ����������
*/

struct FileExceptionTag;         //��� �������� ������ �������� ����������
struct FileNotFoundExceptionTag; //���� �� ������
struct FileNotDirExceptionTag;   //���� �� �������� ���������
struct FileLoadExceptionTag;     //������ �������� �����
struct FileClosedExceptionTag;   //������� ��������� � ��������� �����
struct FileNoSpaceExceptionTag;  //������������ ����� �� �������� ��� ���������� ��������
struct FileMountExceptionTag;    //������ ������������ �������� �������
struct BufferedFileExceptionTag; //���������� ��������� � ������������ �����

typedef DerivedException<Exception,FileExceptionTag>              FileException;
typedef DerivedException<FileException,FileNotFoundExceptionTag>  FileNotFoundException;
typedef DerivedException<FileException,FileNotDirExceptionTag>    FileNotDirException;
typedef DerivedException<FileException,FileLoadExceptionTag>      FileLoadException;
typedef DerivedException<FileException,FileClosedExceptionTag>    FileClosedException;
typedef DerivedException<FileException,FileNoSpaceExceptionTag>   FileNoSpaceException;
typedef DerivedException<FileException,FileMountExceptionTag>     FileMountException;
typedef DerivedException<FileException,BufferedFileExceptionTag>  BufferedFileException;

/*
    �������� ���������
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� 
///////////////////////////////////////////////////////////////////////////////////////////////////
enum FileModeFlags
{
  FILE_MODE_READ          = 1,  //������ ���������
  FILE_MODE_WRITE         = 2,  //������ ���������
  FILE_MODE_RESIZE        = 4,  //��������� ������� ���������
  FILE_MODE_REWIND        = 8,  //����� ��������� ��������� ��������
  FILE_MODE_SEEK          = 16, //����������� ��������� ��������� ���������
  FILE_MODE_CREATE        = 32, //��� ���������� ���� ��������, ������ ����� ���������
  FILE_MODE_STREAM_READ   = FILE_MODE_READ|FILE_MODE_REWIND,         //������ ������
  FILE_MODE_STREAM_WRITE  = FILE_MODE_WRITE|FILE_MODE_REWIND|FILE_MODE_RESIZE, //������ ������
  FILE_MODE_READ_ONLY     = FILE_MODE_STREAM_READ|FILE_MODE_SEEK,    //������ ����� ������������� �������
  FILE_MODE_WRITE_ONLY    = FILE_MODE_CREATE|FILE_MODE_STREAM_WRITE|FILE_MODE_SEEK,   //������ ����� ������������� ������� (����� ������� �����)
  FILE_MODE_READ_WRITE    = FILE_MODE_READ_ONLY|FILE_MODE_STREAM_WRITE, //������/������ ����� ������������� �������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum FileSearchFlags
{
  FILE_SEARCH_FILES          = 1,  //������ �����
  FILE_SEARCH_DIRS           = 2,  //������ ��������
  FILE_SEARCH_SORT           = 4,  //������������� �� �����
  FILE_SEARCH_NO_PACKS       = 8,  //�� ������ � �����
  FILE_SEARCH_SUBDIRS        = 16, //������ � ������������
  FILE_SEARCH_FULL_PATHS     = 32, //�������� ������ ����
  FILE_SEARCH_FILES_AND_DIRS = FILE_SEARCH_FILES|FILE_SEARCH_DIRS
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������� �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum FileSeekMode
{
  FILE_SEEK_SET, //��������� ������� �� ������ �����
  FILE_SEEK_CUR, //��������� ������� �� �������� ��������� ��������� ���������
  FILE_SEEK_END  //��������� ������� �� ����� �����
};

typedef size_t filesize_t, filemode_t;
typedef time_t filetime_t;
typedef int    filepos_t;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct FileInfo
{
  filetime_t time_create;  //����� �������� �����
  filetime_t time_access;  //����� ���������� ������� � �����
  filetime_t time_modify;  //����� ��������� ����������� �����
  filesize_t size;         //������ �����
  bool       is_dir;       //�������� �� ���� �����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����� ����������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct FileHash
{
  size_t        crc32;    //���-����� CRC32
  unsigned char md5 [16]; //���-����� MD5
};

/*
    ������������� ���������� �������� �������
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������������� �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ICustomFileSystem
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef void* file_t;

    virtual file_t     FileOpen   (const char* name,filemode_t mode_flags,size_t buffer_size) = 0;
    virtual void       FileClose  (file_t) = 0;
    virtual size_t     FileBufferSize (file_t) { return 0; } //ret (size_t)-1 - ����������� ����������
    virtual size_t     FileRead   (file_t,void* buf,size_t size) = 0;
    virtual size_t     FileWrite  (file_t,const void* buf,size_t size) = 0;
    virtual void       FileRewind (file_t) = 0;
    virtual filepos_t  FileSeek   (file_t,filepos_t pos) = 0;
    virtual filepos_t  FileTell   (file_t) = 0;
    virtual filesize_t FileSize   (file_t) = 0;
    virtual void       FileResize (file_t,filesize_t new_size) = 0; 
    virtual bool       FileEof    (file_t) = 0;    
    virtual void       FileFlush  (file_t) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Remove (const char* file_name) = 0;
    virtual void Rename (const char* file_name,const char* new_name) = 0;
    virtual void Mkdir  (const char* dir_name) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual bool IsFileExist (const char* file_name) = 0;
    virtual bool GetFileInfo (const char* file_name,FileInfo& info) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� (Search ���������� ���������� ��������� ������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef CallbackHandler<const char*,const FileInfo&> FileSearchHandler;

    virtual void Search (const char* wc_mask,const FileSearchHandler& handler) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void AddRef  () = 0;
    virtual void Release () = 0;
};

/*
    ������ ��� ������ � ������
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///����
///////////////////////////////////////////////////////////////////////////////////////////////////
class File
{
  friend class FileSystem;
  public:
    File  ();
    File  (const File&);
    ~File ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    filemode_t Mode        () const;
    bool       CanRead     () const;
    bool       CanWrite    () const;
    bool       CanResize   () const;
    bool       CanSeek     () const;
    bool       CanRewind   () const;
    bool       IsReadOnly  () const;
    bool       IsWriteOnly () const;
    bool       IsClosed    () const;
    bool       IsBuffered  () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ / ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Read  (void* buf,size_t size);
    size_t Write (const void* buf,size_t size);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void      Rewind ();
    filepos_t Seek   (filepos_t pos,FileSeekMode mode = FILE_SEEK_SET);
    filepos_t Tell   () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����� / �������� �� ����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    filesize_t Size   () const;
    void       Resize (filesize_t new_size); 
    bool       Eof    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������� �� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Flush ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Close ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ������ �� ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator == (const File&) const;
    bool operator != (const File&) const;

  protected:
    File (FileImpl*);

  private:
    FileImplPtr impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
class StdFile: public File
{
  public:
    StdFile (const char* file_name,filemode_t mode_flags);
    StdFile (const char* file_name,filemode_t mode_flags,size_t buffer_size);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����������� ���� ��� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputFile: public StdFile
{
  public:
    explicit InputFile (const char* file_name);
             InputFile (const char* file_name,size_t buffer_size);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����������� ���� ��� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class OutputFile: public StdFile
{
  public:
    explicit OutputFile (const char* file_name);
             OutputFile (const char* file_name,size_t buffer_size);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����������� ���� ��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class AppendFile: public StdFile
{
  public:
    explicit AppendFile (const char* file_name);
             AppendFile (const char* file_name,size_t buffer_size);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class MemFile: public File
{
  public:
    MemFile (void* buf,size_t size,filemode_t mode_flags=FILE_MODE_READ_WRITE);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
class CustomFile: public File
{
  public:
    CustomFile (ICustomFileSystem* file_system,const char* file_name,filemode_t mode);
    CustomFile (ICustomFileSystem*        file_system,
                ICustomFileSystem::file_t handle,
                filemode_t                mode,
                bool                      auto_close = false);
};

/*
    ������ ������������� ����� ������
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct FileListItem
{
  const char* name; //��� �����
  FileInfo    info; //���������� � �����
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class FileListIterator
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ � ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FileListIterator ();
    FileListIterator (const FileList&);

    FileListIterator& operator = (const FileList&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FileListIterator& operator ++ ();
    FileListIterator& operator -- ();
    FileListIterator  operator ++ (int);
    FileListIterator  operator -- (int);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const FileListItem* operator -> () const;
    const FileListItem& operator *  () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    operator bool () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator == (const FileListIterator&) const;
    bool operator != (const FileListIterator&) const;
    bool operator <  (const FileListIterator&) const;
    bool operator >  (const FileListIterator&) const;
    bool operator <= (const FileListIterator&) const;
    bool operator >= (const FileListIterator&) const;          

  private:
    FileListImplPtr list_impl;
    size_t          pos;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class FileList
{
  friend class FileListIterator;
  friend class FileListBuilder;
  public:
    typedef FileListIterator Iterator;
    typedef FileListItem     ItemType;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    FileList ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ / ���������� �� i-� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t          Size () const;
    const ItemType& Item (size_t index) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Iterator GetIterator () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ������� �� ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool operator == (const FileList&) const;
    bool operator != (const FileList&) const;

  private:
    FileList (FileListImpl*);

  private:
    FileListImplPtr impl;
};

/*
    ������ �������������� ���������� �������� ��������
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class FileSystem
{
  public:
    typedef CallbackHandler<const char*>                     LogHandler;
    typedef CallbackFunction<ICustomFileSystem*,const char*> PackFileCreater;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void        SetCurrentDir (const char* path);
    static const char* GetCurrentDir ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void AddSearchPath        (const char* path);
    static void AddSearchPath        (const char* path,const LogHandler& log_handler);
    static void RemoveSearchPath     (const char* path);
    static void RemoveAllSearchPaths ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / �������� ���������������� ����� ���-������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void RegisterPackFile   (const char* extension,const PackFileCreater& creater);
    static void UnregisterPackFile (const char* extension);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������������� �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void Mount       (const char* path_prefix,ICustomFileSystem* file_system);
    static void Unmount     (const char* path_prefix);
    static void Unmount     (ICustomFileSystem* file_system);
    static void UnmountAll  ();
    static bool IsPathMount (const char* path); //��������: ����������� �� ����

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / �������������� �����, �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void Remove (const char* file_name);
    static void Rename (const char* file_name,const char* new_name);
    static void Mkdir  (const char* dir_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static bool       GetFileInfo (const char* file_name,FileInfo& info);
    static bool       IsFileExist (const char* file_name);
    static bool       IsDir       (const char* file_name);
    static filetime_t GetFileTime (const char* file_name);
    static filesize_t GetFileSize (const char* file_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��� ���� ����������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////        
    static void GetFileHash (File& file,FileHash& out_hash_value);
    static void GetFileHash (const char* file_name,FileHash& out_hash_value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static FileList Search (const char* wc_mask,size_t flags=FILE_SEARCH_FILES_AND_DIRS);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������ ����� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void   SetDefaultFileBufferSize (size_t buffer_size);
    static size_t GetDefaultFileBufferSize ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void CloseAllFiles ();    
};

}

#endif
