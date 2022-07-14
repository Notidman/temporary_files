#include "iolearn.h"

#include <stdio.h>
#include <stdlib.h>

static char* 
read_string(void)
{
  char *ptr_str = (char*)malloc(sizeof(char));
  char buff_ch = '\0';
  size_t i = 1;
  while( (buff_ch = getchar()) != '\n' )
  {
    ptr_str = (char*)realloc(ptr_str, sizeof(char) + i);
    ptr_str[i-1] = buff_ch;
    ++i;
  }
  ptr_str[i] = '\0';

  return ptr_str;
}

void 
run_ls4(void)
{
  char *ptr_str = read_string();
  printf("%s\n", ptr_str);
  free(ptr_str);
}
