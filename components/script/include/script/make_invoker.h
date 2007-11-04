#ifndef SCRIPTLIB_MAKE_INVOKER_HEADER
#define SCRIPTLIB_MAKE_INVOKER_HEADER

#include <xtl/any.h>
#include <xtl/function.h>
#include <xtl/type_list.h>

#include <script/invoker.h>

namespace script
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����� ��� ������������� �������� � ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Signature, class Fn> Invoker make_invoker (Fn fn);
template <class Fn>                  Invoker make_invoker (Fn fn);

#include <script/detail/make_invoker.inl>

}

#endif
