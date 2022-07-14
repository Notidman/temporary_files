#include "thrd.h"

#define POSIXTHREADS 0
#define C11THREADS 1

#if POSIXTHREADS
#include <pthread.h>
// compile with -lpthread

#if 0
  Виды структур:
    pthread_t - поток
    pthread_mutex_t - мьютекс
    pthread_cond_t - условная переменная
    pthread_mutexattr_t - объект атрибутов мьютекса
    pthread_condattr_t - объект атрибута услвной переменной
    pthread_key_t - данные, специфичные для потока
    pthread_attr_t - перечень атрибутов потока
  
  Виды функций:
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
           void *(*start_routine)(void*), void *arg); 
     - создаёт поток
  
    void pthread_exit(void *retval); 
    - если старший поток из функции main()
    выполнит данную функцию, вместо exit() или return, то тогда остальные
    потоки продолжат исполняться, как ни в чём не бывало
  
    int pthread_join(pthreat_t THREAD_IDm void **DATA);
    - ожидает завершения потока обозначенного THREAD_ID
    Если DATA != NULL, то туда мещаются данные, возвращаемые потоком
    через функцию pthread_exit() или через инструкцию return потоковой
    функции
  
    int pthread_cancel(pthread_t THREAD_ID);
    - При удачном завершении функция возвращает код 0, ненулевое значение
    сигнализирует об ошибке
  
    int pthread_detach(pthread_t thread);
    - При удачном завершении функция возвращает код 0, ненулевое значение
    сигнализирует об ошибке
  
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PRG1 1

#if PRG1

#define ARGV1 "10" // Имитация argv[1]
  
  int count; // данные для потоков
  
  static void*
  potok1(void *param) { // потоковая функция
    int upper = atoi(param);
    if( upper > 0 ) {
      for ( int i = 1; i < upper; ++i) {
        printf("%d] Thread 1: count now = %d\n", i, count);
        count += i;
        sleep(2);
      }
    }
  
    pthread_exit(0);
  }

  static void*
  potok2(void *param) {
    int upper = atoi(param);
    if( upper > 0 ) {
      for ( int i = 1; i < upper; ++i) {
        printf("%d] Thread 2: count now = %d\n", i, count);
        count += i;
        sleep(5);
      }
    }
  
    pthread_exit(0);
  }

#endif

#endif


#if C11THREADS
#include <threads.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
  // compile with -lstdthreads  
  // Оболочка для POSIX-потоков
  // работа аналогичная, за исключением:
  // 1] pthread_*() -> thrd_*()
  //    pthread_mutex_*() -> mxt_*()
  //    pthread_cond_*() -> cnd_*()
  // 2] нет эквивалента функции pthread_self()
  // 3] Потоки, мьютексы и условные переменные создаются и инициализируются
  //    без указания определенных атрибутов
/*
  Виды структур:
    thrd_t - тип потока
    mtx_t - тип для мьютекса
    cnd_t - тип условной переменной
  Виды функций:
    thrd_create() - создание потока
    thrd_join() - ожидание потока
*/

#define PRG1 1

#if PRG1
  int count;
#define ARGV1 "10" // argv[1]

  static int
  potok1(void *param) { // потоковая функция
    int upper = atoi(param);
    if( upper > 0 ) {
      for ( int i = 1; i < upper; ++i) {
        printf("%d] Thread 1: count now = %d\n", i, count);
        count += i;
        sleep(2);
      }
    }
  
    thrd_exit(0);
  }

  static int
  potok2(void *param) {
    int upper = atoi(param);
    if( upper > 0 ) {
      for ( int i = 1; i < upper; ++i) {
        printf("%d] Thread 2: count now = %d\n", i, count);
        count += i;
        sleep(5);
      }
    }
  
    thrd_exit(0);
  }
#endif

#endif


void run_threads(void) {
#if POSIXTHREADS
  pthread_t tid1; // индификатор потока
  pthread_attr_t attr1; // атрибуты потока

  pthread_t tid2;
  pthread_attr_t attr2;

  // получим значения атрубитов по умолчанию
  pthread_attr_init(&attr1);
  pthread_attr_init(&attr2);

  // создаём новый поток
  pthread_create(&tid1, &attr1, potok1, ARGV1);
  pthread_create(&tid2, &attr2, potok2, ARGV1);

  // ждём завершения исполнения потока
  pthread_detach(tid2);
  pthread_join(tid1, NULL);
  printf("count = %d\n", count);

#endif

#if C11THREADS
  thrd_t thrd1, thrd2;

  thrd_create(&thrd1, potok1, ARGV1);
  thrd_create(&thrd2, potok2, ARGV1);

  thrd_detach(thrd2);
  thrd_join(thrd1, NULL);
  printf("count = %d\n", count);

#endif
}
