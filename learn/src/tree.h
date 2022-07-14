#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include "macroloop.h"

struct node_s {
  char data;
  struct node_s *left;
  struct node_s *right;
};

extern struct node_s* malloc_node(char data);
extern void free_node(struct node_s *node);

extern void run_tree(void);
