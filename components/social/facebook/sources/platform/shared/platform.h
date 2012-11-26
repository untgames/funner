#ifndef SOCIAL_FACEBOOK_PLATFORM_HEADER
#define SOCIAL_FACEBOOK_PLATFORM_HEADER

#include <shared/default.h>
#include <shared/ios.h>

namespace social
{

namespace facebook
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef IPHONE
  typedef IOsPlatform Platform;
#else
  typedef DefaultPlatform Platform;
#endif

}

}

#endif
