#include "car.h"
#include <stdio.h>
#include <stdlib.h>

struct Car* init_car(char *mark, unsigned int year, double mass, double speed)
{
  s_car *new_car; 

  if( !( new_car = (struct Car*)malloc( sizeof(struct Car)) ) )
  {
    printf("Error: memory alloc");
  }

  if( !( new_car->mark = (char*)malloc( sizeof(char) * 30) ) )
  {
    printf("Error: memory alloc");
  }

  return new_car;

}

struct Car* free_car(struct Car *car)
{
  if ( car == NULL || car->mark == NULL)
  {
    return 0;
  }
  else
  {
    free(car->mark);
    free(car);
  }

  return 0;
}
