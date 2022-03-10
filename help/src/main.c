#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

#define LOG_INFO 1
#define FILE_NAME "carDB.txt"

static char mark[STORAGE_SIZE][MARK_SIZE] = {"Lada", "Priora", "Sidan", "Subaru"};
static int years[STORAGE_SIZE] = { 1996, 1999, 2002, 2003};
static double masses[STORAGE_SIZE] = { 190, 450, 100, 240};
static double speeds[STORAGE_SIZE] = { 207, 156, 189, 190};
static s_car **storage = NULL;

void write_data_cars(const char *name_file);
void find_max_speed_car(const char *name_file);
void all_mark_cars(const char *name_file);
void old_max_speed_cars(const char *name_file);
void list_new_most_weight(const char *name_file);

int
main()
{
  write_data_cars(FILE_NAME);

  // Find the maximum speed among cars
  find_max_speed_car(FILE_NAME);
//  all_mark_cars(FILE_NAME);
//  old_max_speed_cars(FILE_NAME);
//  list_new_most_weight(FILE_NAME);

  return EXIT_SUCCESS;
}



void write_data_cars(const char *name_file)
{

#if LOG_INFO
  printf("Start write...\n");
#endif

	storage = init_storage();
	for(size_t i = 0; i < STORAGE_SIZE; ++i)
	{
    storage[i] = init_car(mark[i], years[i], masses[i], speeds[i]); 
	}

	FILE *f_carDB = fopen(name_file, "w");
	for(size_t i = 0; i < STORAGE_SIZE; ++i)
	{
    fprintf(f_carDB, "mark : %s\nyear : %d\nmass : %lf\nspeed : %lf\n\n",
										storage[i]->mark,
										storage[i]->year,
										storage[i]->mass,
										storage[i]->speed);
	}

	fclose(f_carDB);

	storage = free_storage(storage);

#if LOG_INFO
  printf("End write..\n");
#endif

}


void find_max_speed_car(const char *name_file)
{

#if LOG_INFO
  printf("Find max speed...\n");
#endif

  FILE *f = fopen(name_file, "r");
  char buffer_strings[STORAGE_SIZE][264];
  
  char speed_list[STORAGE_SIZE][20] = {0};
  char type[20] = {0};
  char value[20] = {0};
  size_t find_count = 0;

  // find all speeds
  for(size_t i = 0; !(feof(f)) ; ++i)
  {
    fscanf(f, "%s : %s", type, value);
    
    if( !(strcmp(type, "speed")) )
    {
      strcpy(speed_list[find_count], value);
      ++find_count;
    }
  }

  // print max speed 
  double max_speed = 0;
  double tmp_ms = 0;
  for(size_t i = 0; i < STORAGE_SIZE; ++i)
  { 
    tmp_ms = strtod(speed_list[i], NULL); 
    if ( max_speed < tmp_ms) {
      max_speed = tmp_ms;
    }
  }

  printf("Max speed: %lf\n", max_speed);

#if LOG_INFO
  printf("End..\n");
#endif

  fclose(f);
}

void all_mark_cars(const char *name_file);
void old_max_speed_cars(const char *name_file);
void list_new_most_weight(const char *name_file);
