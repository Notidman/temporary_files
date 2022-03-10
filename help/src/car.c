#include "car.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car* init_car(char *mark, unsigned int year, double mass, double speed)
{
  s_car *new_car; 

  if( !( new_car = (struct Car*)malloc( sizeof(struct Car)) ) )
  {
    printf("Error: memory alloc\n");
  }

  if( !( new_car->mark = (char*)malloc( sizeof(char) * MARK_SIZE) ) )
  {
    printf("Error: memory alloc\n");
  }
  
	strcpy(new_car->mark, mark);
	new_car->year = year;
	new_car->mass = mass;
  new_car->speed = speed;

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
