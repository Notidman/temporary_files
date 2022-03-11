#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

static const char *FILE_NAME = "carDB.txt";
static const int old_limit = 2000;
static double average_speed = 0;

static char mark[STORAGE_SIZE][MARK_SIZE] = {"Lada", "Priora", "Lada", "Sidan", "Subaru"};
static int years[STORAGE_SIZE] = { 1996, 1874, 1999, 2002, 2003};
static double masses[STORAGE_SIZE] = { 190, 340, 450, 100, 240};
static double speeds[STORAGE_SIZE] = { 207, 124, 156, 189, 190};
static s_car **storage = NULL;

static void write_data_cars(const char *name_file);
static void find_max_speed_car(const char *name_file);
static void all_mark_cars(const char *name_file);
static void old_max_speed_cars(const char *name_file);
static void list_new_most_weight(const char *name_file);

int
main()
{
  // Write data in new file 
  puts("Write in file");
  write_data_cars(FILE_NAME);
  puts("End");


  puts("a) Find max speed");
  find_max_speed_car(FILE_NAME);
  puts("End");

  puts("b) Find all mark");
  all_mark_cars(FILE_NAME);
  puts("End");

  puts("c) Find most max speed cars in olds");
  old_max_speed_cars(FILE_NAME);
  puts("End");

  puts("d) Find most weight new cars");
  list_new_most_weight(FILE_NAME);
  puts("End");

  return EXIT_SUCCESS;
}



void write_data_cars(const char *name_file)
{
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
}


void find_max_speed_car(const char *name_file)
{
  FILE *f = fopen(name_file, "r");
  
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

  // find average speed
  double sum = 0.0;
  for(size_t i = 0; i < STORAGE_SIZE; ++i)
  {
    sum += strtod(speed_list[i], NULL); 
  }

  average_speed = sum / STORAGE_SIZE;
  int counter = 0;
  for(size_t i = 0; i < STORAGE_SIZE; ++i)
  {
    if ( strtod(speed_list[i], NULL) > average_speed )
    {
      ++counter;
    }
  }

  printf("Count most speed car: %d\n", counter);
  fclose(f);
}

void all_mark_cars(const char *name_file)
{
  FILE *f = fopen(name_file, "r");
  
  char mark_lists[STORAGE_SIZE][20] = {0};
  char mark_name[20] = {0};
  char type[20] = {0};
  size_t find_count = 0;

  // find marks
  for(size_t i = 0; !(feof(f)) ; ++i)
  {
    fscanf(f, "%s : %s", type, mark_name);
    
    if( !(strcmp(type, "mark")) )
    {
      strcpy(mark_lists[find_count], mark_name);
      ++find_count;
    }
  }

  // print unique marks
  for(size_t i = 0; i < STORAGE_SIZE; ++i)
  {
    bool check = true;
    for(size_t j = i + 1; j < STORAGE_SIZE - 1; ++j) 
    {
      if ( strcmp(mark_lists[i], mark_lists[j]) == 0)
      {
        check = false;
      }
    }

    if(check)
      printf("%s\n", mark_lists[i]);
  }

  fclose(f);
}

void old_max_speed_cars(const char *name_file)
{
  FILE *f = fopen(name_file, "r");
  
  char year_lists[STORAGE_SIZE][20] = {0};
  char year[20] = {0};
  char type[20] = {0};
  size_t find_count = 0;

  // find years
  for(size_t i = 0; !(feof(f)) ; ++i)
  {
    fscanf(f, "%s : %s", type, year);
    
    if( !(strcmp(type, "year")) )
    {
      strcpy(year_lists[find_count], year);
      ++find_count;
    }
  }

  fseek(f, 0, SEEK_SET);
  
  char speed_list[STORAGE_SIZE][20] = {0};
  char value[20] = {0};
  find_count = 0;

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

  //out most max speed cars in olds
  for(size_t i = 0; i < STORAGE_SIZE; ++i)
  {
    if( (strtod(year_lists[i], NULL) < old_limit) && (average_speed < strtod(speed_list[i], NULL)))
      printf("%ld] %s : %s\n", i+1, year_lists[i], speed_list[i]);
  }
  fclose(f);
}

typedef struct
{
  char mark[30];
  double mass;
} MassMarks;
MassMarks mm[STORAGE_SIZE] = {0};

cmpMM(const void *a, const void *b)
{
  return ( ((MassMarks*)a)->mass - ((MassMarks*)b)->mass);
}

void list_new_most_weight(const char *name_file)
{
  FILE *f = fopen(name_file, "r");
  
  char mass[20] = {0};
  char type[20] = {0};
  size_t find_count = 0;

  // find mass
  for(size_t i = 0; !(feof(f)) ; ++i)
  {
    fscanf(f, "%s : %s", type, mass);
    
    if( !(strcmp(type, "mass")) )
    {
      mm[find_count].mass = strtod(mass, NULL);
      ++find_count;
    }
  }

  fseek(f, 0, SEEK_SET);
  char mark_name[20] = {0};
  find_count = 0;

  // find marks
  for(size_t i = 0; !(feof(f)) ; ++i)
  {
    fscanf(f, "%s : %s", type, mark_name);
    
    if( !(strcmp(type, "mark")) )
    {
      strcpy(mm[find_count].mark, mark_name);
      ++find_count;
    }
  }

  qsort(mm, STORAGE_SIZE, sizeof(MassMarks), cmpMM);

  for(size_t i = 0; i < STORAGE_SIZE; ++i)
  {
    printf("%ld] %s : %lf\n", i+1, mm[i].mark, mm[i].mass);
  }


  fclose(f);
}
