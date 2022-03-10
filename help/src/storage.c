#include <stdio.h>
#include <stdlib.h>
#include "storage.h"

s_car** init_storage()
{
  s_car **storage;

  if( !( storage = (struct Car**)malloc( sizeof(struct Car*) * STORAGE_SIZE ) ))
  {
    printf("Error: memory alloc");
  }

	return storage;
}

s_car** free_storage(s_car **storage)
{
  if ( storage == NULL)
	{
    return 0;
	}
	else
	{
    for(size_t i = 0; i < STORAGE_SIZE; ++i)
		{
      storage[i] = free_car(storage[i]);
		}

		free(storage);
	}

	return 0;
}
