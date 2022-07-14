#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "macroloop.h"

#define MAX_QUEUE_SIZE 10

struct queue_s
{
  char *data[MAX_QUEUE_SIZE];
  int32_t head;
  int32_t tail;
}; 

extern struct queue_s* malloc_queue(void);
extern void free_queue(struct queue_s* queue);

extern void run_queue(void);
