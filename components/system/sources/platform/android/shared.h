#include <ctime>
#include <cstdio>

#include <unistd.h>
#include <errno.h>

#include <jni.h>
#include <android/input.h>
#include <android/keycodes.h>
#include <android/looper.h>
#include <android/log.h>
#include <android/native_window_jni.h>

#include <stl/auto_ptr.h>

#include <xtl/type_traits>
#include <xtl/bind.h>
#include <xtl/common_exceptions.h>
#include <xtl/function.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>

#include <common/file.h>
#include <common/log.h>
#include <common/property_map.h>
#include <common/singleton.h>
#include <common/strlib.h>
#include <common/time.h>

#include <syslib/keydefs.h>
#include <syslib/thread.h>

#include <shared/platform.h>
#include <shared/message_queue.h>

namespace syslib
{

namespace android
{

/// ��������� ����������� ������
JavaVM* get_vm ();

/// ��������� ��������� ������� ����
JNIEnv& get_env ();

/*
    JNI ������
*/

///��������� �������� ��������� JNI �������
template <class T> struct jni_local_ref_strategy
{
  static T*   clone   (T* ptr) { return (T*)get_env ().NewLocalRef (ptr); }
  static void release (T* ptr) { get_env ().DeleteLocalRef (ptr); }  
};

///��������� �������� ���������� JNI �������
template <class T> struct jni_global_ref_strategy
{
  static T*   clone   (T* ptr) { return (T*)get_env ().NewGlobalRef (ptr); }
  static void release (T* ptr) { get_env ().DeleteGlobalRef (ptr); }  
};

template <class T> class global_ref;

/// ��������� JNI ������
template <class T> class local_ref: public xtl::intrusive_ptr<typename xtl::type_traits::remove_pointer<T>::type, jni_local_ref_strategy>
{
  typedef xtl::intrusive_ptr<typename xtl::type_traits::remove_pointer<T>::type, jni_local_ref_strategy> base;
  public:
    typedef typename base::element_type element_type;

    local_ref () {}
    local_ref (element_type* ptr, bool addref = true) : base (ptr, addref) {}
    local_ref (const local_ref& ref) : base (ref) {}

    template <class T1> local_ref (const local_ref<T1>& ref) : base (ref) {}    
    template <class T1> local_ref (const global_ref<T1>& ref) : base (&*ref) {}    
};

/// ���������� JNI ������
template <class T> class global_ref: public xtl::intrusive_ptr<typename xtl::type_traits::remove_pointer<T>::type, jni_global_ref_strategy>
{
  typedef xtl::intrusive_ptr<typename xtl::type_traits::remove_pointer<T>::type, jni_global_ref_strategy> base;
  public:
    typedef typename base::element_type element_type;

    global_ref () {}
    global_ref (element_type* ptr, bool addref = true) : base (ptr, addref) {}
    global_ref (const global_ref& ref) : base (ref) {}

    template <class T1> global_ref (const global_ref<T1>& ref) : base (ref) {}
    template <class T1> global_ref (const local_ref<T1>& ref) : base (&*ref) {}    
};

/*
    ����� ������� � �����
*/

inline jmethodID find_static_method (JNIEnv* env, jclass class_, const char* name, const char* signature)
{
  jmethodID result = env->GetStaticMethodID (class_, name, signature);
  
  if (!result)
  {
    if (env->ExceptionOccurred ())
      env->ExceptionClear ();    
  
    throw xtl::format_operation_exception ("JNIEnv::GetStaticMethodID", "Static method '%s %s' not found", name, signature);
  }
    
  return result;
}

inline jmethodID find_method (JNIEnv* env, jclass class_, const char* name, const char* signature)
{
  jmethodID result = env->GetMethodID (class_, name, signature);    
  
  if (!result)
  {
    if (env->ExceptionOccurred ())
      env->ExceptionClear ();  
  
    throw xtl::format_operation_exception ("JNIEnv::GetMethodID", "Method '%s %s' not found", name, signature);
  }
    
  return result;
}

inline jfieldID find_field (JNIEnv* env, jclass class_, const char* name, const char* type)
{
  jfieldID result = env->GetFieldID (class_, name, type);
  
  if (!result)
  {
    if (env->ExceptionOccurred ())
      env->ExceptionClear ();    
  
    throw xtl::format_operation_exception ("JNIEnv::GetFieldID", "Field '%s %s' not found", type, name);
  }

  return result;
}

/*
    ������ ��� ������ �� ��������
*/

class jni_string
{
  public:
    jni_string (JNIEnv* inEnv, jstring inJavaString)
      : env (inEnv)
      , javaString (inJavaString)
      , string (0)
    {
      string = env->GetStringUTFChars (javaString, 0);            
    }
    
    ~jni_string ()
    {
      if (!string || !env || !javaString)
        return;
        
      env->ReleaseStringUTFChars (javaString, string);
    }
    
    const char* get () const { return string; } 
  
  private:
    JNIEnv*     env;
    jstring     javaString;
    const char* string;
};

/*
    �������
*/

local_ref<jstring> tojstring    (const char* s);
void               check_errors ();

template <class T> T check_errors (T result)
{
  check_errors ();
  
  return result;
}

/*
    ���������� ��������
*/

///�������� ������� ����������
struct ApplicationContext
{
  JavaVM*             vm;          //����������� ������
  global_ref<jclass>  utils_class; //EngineUtils class
  
  ApplicationContext () : vm (0) {}
};

/// ����� ����� � ����������
void start_application (JavaVM* vm, jobject activity, const char* program_name, const char* args, const char* env_vars);

/// ����������� ������� ��������� ������ ����
void register_window_callbacks (JNIEnv* env);

/// ����������� ������� ��������� ������ activity
void register_activity_callbacks (JNIEnv* env, jclass activity_class);

/// ��������� ��������� ������� ����������
const ApplicationContext& get_context ();

/// ��������� activity
void set_activity (jobject activity);

/// ��������� �������� activity
jobject get_activity ();

/*
    ���������� ����������������
*/

int log_printf  (int level, const char* format, ...);
int log_vprintf (int level, const char* format, va_list args);
int log_info    (const char* format, ...);
int log_error   (const char* format, ...);

void startStdioRedirection    (JavaVM*);
void shutdownStdioRedirection ();

}

}
