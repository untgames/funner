#ifndef FUNNER_ENGINE_LAUNCHER_HEADER
#define FUNNER_ENGINE_LAUNCHER_HEADER

#ifdef _WIN32
  #define FUNNER_C_API extern "C" __declspec(dllexport)
#elif __GNUC__
  #define FUNNER_C_API extern "C"
#else
  #error "Unknown platform"
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IFunnerApi
{
  public:
    virtual ~IFunnerApi () {}

    virtual bool ParseCommandLine (unsigned int arguments_count, const char** arguments) = 0;
    virtual void Run () = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef IFunnerApi* (*FunnerInitProc)();

FUNNER_C_API IFunnerApi* FunnerInit ();

#endif
