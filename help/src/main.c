#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "car.h"

int
main()
{
  char *mark;
  strcpy(mark, "Lada");
  s_car *car = init_car(mark, 2002, 106.8, 210);
  car = free_car(car);
  return EXIT_SUCCESS;
}
