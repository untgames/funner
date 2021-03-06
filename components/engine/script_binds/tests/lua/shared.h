#ifndef SCRIPTBINDS_TESTS_SHARED_HEADER
#define SCRIPTBINDS_TESTS_SHARED_HEADER

#include <stdio.h>
#include <string.h>
#include <time.h>

#include <xtl/bind.h>
#include <xtl/connection.h>
#include <xtl/shared_ptr.h>

#include <common/console.h>
#include <common/file.h>
#include <common/log.h>
#include <common/strlib.h>
#include <common/time.h>

#include <math/matrix.h>
#include <math/quat.h>

#include <script/environment.h>
#include <script/bind.h>
#include <script/shell.h>

#include <syslib/application.h>

#include <physics/manager.h>

#include <engine/attachments.h>

using namespace script;
using namespace math;

void print_log (const char* log, const char* message)
{
  printf ("%s: %s\n", log, message);
}

inline void print (float x)
{
  printf ("%g", x);
}

inline void print (const vec3f& v)
{
  printf ("[%g %g %g]", v.x, v.y, v.z);
}

template <class T>
inline void print (const char* tag, const T& value)
{
  printf ("%s: ", tag);
  print  (value);
  printf ("\n");
}

inline const char* get_typename (const xtl::any& variant)
{
  return variant.type ().name ();
}

/*
    Выполнение скрипта
*/

void load_script (IInterpreter& interpreter, const char* file_name)
{
  common::InputFile file (file_name);

  stl::string buffer ((size_t)file.Size (), ' ');

  file.Read (&buffer [0], (size_t)buffer.size ());

  interpreter.DoCommands (file_name, buffer.c_str (), buffer.size ());
}

#endif
