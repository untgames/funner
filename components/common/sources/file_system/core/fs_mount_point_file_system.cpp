#include "shared.h"

using namespace stl;
using namespace common;
using namespace xtl;

MountPointFileSystem::MountPointFileSystem (MountFileSystem& _owner)
  : owner (_owner)
  { }

MountPointFileSystem::file_t MountPointFileSystem::FileOpen (const char* file_name,filemode_t,size_t)
{
  raise_not_supported ("MountPointFileSystem::FileOpen","Unable to open mount-point file '%s'",file_name);
  return (file_t)0;
}

void MountPointFileSystem::FileClose (file_t)
{
}

size_t MountPointFileSystem::FileRead (file_t,void*,size_t)
{
  raise_not_supported ("MountPointFileSystem::FileRead");
  return 0;
}

size_t MountPointFileSystem::FileWrite (file_t,const void* buf,size_t size)
{
  raise_not_supported ("MountPointFileSystem::FileWrite");
  return 0;
}

void MountPointFileSystem::FileRewind (file_t)
{
  raise_not_supported ("MountPointFileSystem::FileRewind");
}

filepos_t MountPointFileSystem::FileSeek (file_t,filepos_t)
{
  raise_not_supported ("MountPointFileSystem::FileSeek");
  return 0;
}

filepos_t MountPointFileSystem::FileTell (file_t)
{
  raise_not_supported ("MountPointFileSystem::FileTell");
  return 0;
}

filesize_t MountPointFileSystem::FileSize (file_t)
{
  raise_not_supported ("MountPointFileSystem::FileSize");
  return 0;
}

void MountPointFileSystem::FileResize (file_t,filesize_t)
{
  raise_not_supported ("MountPointFileSystem::FileResize");
}

bool MountPointFileSystem::FileEof (file_t)
{
  raise_not_supported ("MountPointFileSystem::FileEof");
  return true;
}

void MountPointFileSystem::FileFlush (file_t)
{
  raise_not_supported ("MountPointFileSystem::FileFlush");
}

void MountPointFileSystem::Remove (const char* file_name)
{
  FileSystemSingleton::Instance ().Unmount (file_name);
}

void MountPointFileSystem::Rename (const char* file_name,const char* new_name)
{
  ICustomFileSystemPtr file_system = owner.file_system;
  
  FileSystemSingleton::Instance ().Unmount (file_name);
  
  try
  {
    FileSystemSingleton::Instance ().Mount (new_name,file_system);
  }
  catch (FileMountException& exception)
  {
    FileSystemSingleton::Instance ().Mount (file_name,file_system);
    exception.Touch ("MountPointFileSystem::Rename");
    throw;
  }
}

void MountPointFileSystem::Mkdir (const char*)
{
}

bool MountPointFileSystem::IsFileExist (const char*)
{
  return true;
}

bool MountPointFileSystem::GetFileInfo (const char* name,FileInfo& info)
{
  info = owner.mount_point_info;
  return true;
}

void MountPointFileSystem::Search (const char* mask,const FileSearchHandler& insert_handler)
{
  raise_not_supported ("MountPointFileSystem::Search");
}
