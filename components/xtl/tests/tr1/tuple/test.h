#include <stdio.h>
#include <xtl/tuple>
#include <xtl/type_traits>
#include <xtl/functional>

using namespace tr1;

#define TEST(X) printf ((X)?"expression '%s' is true\n":"failed expression '%s'\n",#X);
