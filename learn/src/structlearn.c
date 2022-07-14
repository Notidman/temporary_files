#include "structlearn.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct student_s
{
  int ticket;
  int group;
  char name[52];
};

struct course_s
{
  int mark;
  char subject[30];
};


void run_ls3(void)
{
  printf("Struct size: %ld\n", sizeof(struct student_s));
  struct student_s s = {34, 4, "Anton"};

  printf("name: %s\ngroup: %d\nticket: %d\n",
        s.name, s.group, s.ticket);

  const size_t students_size = 30;
  struct student_s students[students_size];
  for(size_t i = 0; i < students_size; ++i)
  {
    students[i].group = i * 1000 % students_size;
    students[i].ticket = i * 10000 % students_size;
    strcpy(students[i].name, "TESTNAME");
  }

  printf("Enter the number of entries: ");
  fflush(stdout);

  size_t course_size;
  scanf("%lu", &course_size);

  struct course_s *ptr_course = NULL;
  assert( (ptr_course = (struct course_s*)malloc(
          course_size * sizeof(struct course_s))) != NULL);

  for(size_t i = 0; i < course_size; ++i)
  {
    ptr_course[i].mark = i * 10000000 % course_size;
    strcpy(ptr_course[i].subject, "TESTSUBJECT");
  }

  printf("\nResult:\n");

  for(size_t i = 0; i < course_size; ++i)
  {
    printf("Subject: %s\nMark: %d\n",
        ptr_course[i].subject, ptr_course[i].mark);
  }

}
