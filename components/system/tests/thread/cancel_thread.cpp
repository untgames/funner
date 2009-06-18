#include "shared.h"

Thread* volatile thread [2] = {0, 0};
bool    volatile cancel_flag = false;

int thread2_run ()
{
  while (!cancel_flag);

  printf ("thread2 started\n");

  thread [0]->Cancel ();

  return 0;
}

int thread1_run ()
{
  printf ("thread1 started\n");

  cancel_flag = true;

  Application::Sleep (5000);

  printf ("thread1 finished\n");

  return 12;
}

int main ()
{
  printf ("Results of cancel_thread_test:\n");

  try
  {
    LogFilter filter ("system.threads.*", &print_log);

    Thread thread1 (&thread1_run), thread2 (&thread2_run);

    thread [0] = &thread1;
    thread [1] = &thread2;

    printf ("join thread2: %d\n", thread [1]->Join ());
    printf ("join thread1: %d\n", thread [0]->Join ());
  }
  catch (std::exception& exception)
  {
    printf ("exception: %s\n", exception.what ());
  }

  return 0;
}
