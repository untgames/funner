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
#include <common/var_registry_container.h>

#include <mathlib.h>
#include <math/io.h>

#include <script/environment.h>
#include <script/bind.h>
#include <script/shell.h>

#include <syslib/application.h>

using namespace script;
using namespace math;

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
    ���������� �������
*/

void load_script (IInterpreter& interpreter, const char* file_name)
{
  common::InputFile file (file_name);

  stl::string buffer (file.Size (), ' ');

  file.Read (&buffer [0], buffer.size ());

  interpreter.DoCommands (file_name, buffer.c_str (), buffer.size ());
}

#endif
