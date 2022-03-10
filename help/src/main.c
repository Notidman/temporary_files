#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

int
main()
{
  char mark[STORAGE_SIZE][MARK_SIZE] = {"Lada", "Priora", "Sidan", "Subaru"};
	int years[STORAGE_SIZE] = { 1996, 1999, 2002, 2003};
	double masses[STORAGE_SIZE] = { 190, 450, 100, 240};
	double speeds[STORAGE_SIZE] = { 207, 156, 189, 190};

	s_car **storage = init_storage();
	for(size_t i = 0; i < STORAGE_SIZE; ++i)
	{
    storage[i] = init_car(mark[i], years[i], masses[i], speeds[i]); 
	}

	FILE *f_carDB = fopen("carDB.txt", "w");
	for(size_t i = 0; i < STORAGE_SIZE; ++i)
	{
    fprintf(f_carDB, "!%ld car\n", i+1);
    fprintf(f_carDB, "mark:%s\nyear:%d\nmass:%lf\nspeed:%lf\n",
										storage[i]->mark,
										storage[i]->year,
										storage[i]->mass,
										storage[i]->speed);
	}

	if ((fclose(f_carDB)))
	{
    printf("Error: don't close file");
		return 1;
	}

	storage = free_storage(storage);
  return EXIT_SUCCESS;
}
