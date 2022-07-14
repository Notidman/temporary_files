#include "dynamicalloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

static void 
read_elements(float* data, size_t size)
{
  assert(data != NULL);
  for(size_t i = 0; i < size; ++i)
  {
    printf("Enter element %ld: ", i + 1);
    scanf("%f", data + i);
  }
}

static float 
find_max(float *data, size_t size)
{
  assert(data != NULL);
  float max = *data;
  for(size_t i = 1; i < size; ++i)
    if ( max < data[i])
      max = data[i];
  return max;
}

void 
run_ls2(void)
{
  int num;
  printf("Enter count elements: ");
  scanf("%d", &num);

  float *data = NULL;
  assert( (data = (float*)calloc(num, sizeof(float))) != NULL);
  puts("");
  read_elements(data, num);
  printf("Max = %.2f\n", find_max(data, num));
}
