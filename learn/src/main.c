#include <stdlib.h>

#define IO 0
#define STRUCTS 0
#define THREADS 0
#define CLIENT_SERVER 1

#if IO
#include "wcharlearn.h"
#include "dynamicalloc.h"
#include "structlearn.h"
#include "iolearn.h"
#include "filework.h"
#include "dirwork.h"
#endif

#if STRUCTS 
#include "queue.h"
#include "tree.h"
#endif

#if THREADS
#include "threads.h"
#endif

#if CLIENT_SERVER
#include "server.h"
#include "client.h"
#endif

int 
main(void)
{
  return EXIT_SUCCESS;
}
