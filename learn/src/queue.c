#include "queue.h"
#include <ctype.h>

static void 
queue_push(struct queue_s *queue, const char *data)
{
  if ( queue->tail == MAX_QUEUE_SIZE )
  {
    puts("Queue overflow!");
    return;
  }

  queue->data[queue->tail] = (char*)malloc(strlen(data) + 1);
  strcpy(queue->data[queue->tail], data);
  ++(queue->tail);
}

static char* 
queue_pop(struct queue_s *queue)
{
  if( queue->tail == queue->head )
  {
    puts("Queue empty!");
    return NULL;
  }

  ++(queue->head);
  return queue->data[queue->head-1];
}

static void
remove_queue_element(struct queue_s *queue)
{
  char *p = NULL;
  if ( (p = queue_pop(queue)) == NULL)
    return;

  puts(p);
}

static void
add_queue_element(struct queue_s *queue)
{
  char buff[128] = {0};

  puts("Enter new string in queue: ");
  fgets(buff, 128, stdin);
  queue_push(queue, buff);
}

static void 
display_queue(struct queue_s *queue)
{
  for(int32_t i = queue->head; i < queue->tail; ++i)
    puts(queue->data[i]);
}

struct queue_s* 
malloc_queue(void)
{
  struct queue_s *queue = (struct queue_s*)
    malloc(sizeof(struct queue_s));
  
  for(size_t i = 0; i < MAX_QUEUE_SIZE; ++i)
    queue->data[i] = NULL;
  
  queue->tail = 0;
  queue->head = 0;

  return queue;
}

void 
free_queue(struct queue_s* queue)
{
  assert(queue != NULL);
  for(size_t i = 0; i < MAX_QUEUE_SIZE; ++i)
    if(queue->data[i] != NULL)
      free(queue->data[i]);
  free(queue);
}


void 
run_queue(void)
{
  struct queue_s *queue = malloc_queue();
  char buff[128];

  __loop__
  {
    puts("N - input, D - output, R - remove, Q - exit: ");
    fgets(buff, 128, stdin);
    *buff = toupper(*buff);
    switch (*buff) {
      case 'N': add_queue_element(queue); break;
      case 'D': display_queue(queue); break;
      case 'R': remove_queue_element(queue); break;
      case 'Q': return;
    }
  }

}

