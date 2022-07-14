#include "filework.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>

#define RN1 0
#define RN2 0
#define RN3 0
#define RN4 0
#define RN5 0
#define RN6 1

#if RN6
typedef struct student_s
{
  char fio[32];
  char group[32];
  ushort course;
} student_t;

static struct student_s*
malloc_student(const char* fio,const char *group, const ushort course)
{
  struct student_s *student = (struct student_s*)malloc
    (sizeof(struct student_s));
  printf("%s\n", strcpy(student->fio, fio));
  printf("%s\n", strcpy(student->group, group));
  student->course = course;
  return student;
}

static void
free_student(struct student_s *student)
{
  assert(student != NULL);
  free(student);
}

#endif

typedef struct dump_buffer_s
{
  size_t size;
  void *data;
} dumpbuffer_t;

static struct dump_buffer_s*
malloc_dump_buffer(void)
{
  dumpbuffer_t *dbuff = (dumpbuffer_t*)malloc(sizeof(dumpbuffer_t));
  dbuff->size = 0;
  dbuff->data = NULL;
  return dbuff;
}

static void
free_dump_buffer(struct dump_buffer_s *dbuff)
{
  assert (dbuff->data != NULL);
  assert (dbuff != NULL);

  free (dbuff->data);
  free (dbuff);
}

static void
write_hello_world(FILE *f, size_t count)
{
  while(--count)
    fputs("Hello, world!\n", f);
}

static void
fwritestr(FILE *f, const char *info, size_t count)
{
  while(--count)
    fputs(info, f);
}

static void
fwritech(FILE *f, const char ch, size_t count)
{
  while(--count)
    fputc(ch, f);
}

static char*
freadstr(FILE *f, const size_t length)
{
  char *str = (char*)malloc(length + 1);
  size_t i = 0;
  for(; i < length; ++i)
    str[i] = fgetc(f);
  str[i] = '\0';
  return str;
}

static size_t
fsize(FILE *f)
{
  assert(f != NULL);
  fseek(f, 0L, SEEK_END);
  const size_t size = ftell(f);
  fseek(f, 0L, SEEK_SET);
  return size;
}

static void
printhexdump(const struct dump_buffer_s *dbuff)
{
  for(size_t i = 0; i < dbuff->size; ++i)
    printf("%x ", ((char*)(dbuff->data))[i]);
}

static struct dump_buffer_s* 
fdump(FILE *f)
{
  assert(f != NULL);
  dumpbuffer_t *dbuff = malloc_dump_buffer ();
  dbuff->size = fsize (f) + 1;
  dbuff->data = malloc (dbuff->size);
  char ch_buffer;
  size_t i = 0;
  while((ch_buffer = fgetc (f)) != EOF)
  {
    if (ferror (f))
    {
      free_dump_buffer (dbuff);
      break;
    }

    ((char *) dbuff->data)[i] = ch_buffer;
    ++i;
  }
  return dbuff;
}

void 
run_ls5(void)
{
  const char *filename = "test.txt";

#if RN1
  FILE *filename_m_w = fopen(filename, "w");
  assert(filename_m_w != NULL);
  const char *data = "xxxZZZxxxOOOOxxx\n";
  fwritestr(filename_m_w, data, 2);
  fclose(filename_m_w);

  FILE *filename_m_r = fopen(filename, "r");
  assert(filename_m_r != NULL);
  char * read_str = freadstr(filename_m_r, 11);
  puts(read_str);
  fclose(filename_m_r);
#endif

#if RN2
  FILE *filename_m_r = fopen(filename, "r");
  assert(filename_m_r != NULL);
  printf("size file = %lu\n", fsize(filename_m_r));
  fclose(filename_m_r);
#endif

#if RN3
  FILE *filename_m_r = fopen(filename, "r");
  assert(filename_m_r != NULL);
  dumpbuffer_t *dbuff = fdump(filename_m_r);
  puts("Hex dump:");
  const size_t strlen_size_dbuff = strlen((char*)dbuff->data);
  for(size_t i = 0; i < strlen_size_dbuff; ++i)
    printf("%x ", ((char*)(dbuff->data))[i]);
  printf("\nFile dump = %s\nSize = %lu\nStrlen = %lu\n",
      (char*)dbuff->data, dbuff->size, strlen_size_dbuff);
  fclose(filename_m_r);
  free_dump_buffer(&dbuff);
#endif

#if RN4
  FILE *filename_m_w = fopen(filename, "a");
  assert(filename_m_w != NULL);
  fclose(filename_m_w);
  if(remove(filename))
  {
    printf("Error: file can't remove: %s", filename);
  }
  else
  {
    printf("File remove: %s", filename);
  }

#endif

#if RN5
  /* size_t fread(void* buff, size_t cbyte, size_t type-size, FILE *f) */
  /* size_t fwrite(const void* buff, size_t cbyte, size_t type-size, FILE *f) */
  FILE *ptr_file = fopen(filename, "wb+");
  assert(ptr_file != NULL);
  double data = 33.33;
  int num = 139;
  fwrite(&data, sizeof(double), 1, ptr_file);
  fwrite(&num, sizeof(int), 1, ptr_file);
  fflush(ptr_file);

  // SEEK_SET
  rewind(ptr_file);
  
  data = 0;
  num = 0;
  fread(&data, sizeof(double), 1, ptr_file);
  fread(&num, sizeof(int), 1, ptr_file);
  
  printf("%f %d\n", data, num);
  fclose(ptr_file);

#endif

#if RN6
  FILE *file = fopen(filename, "wb+");
  assert(file != NULL);
  student_t *st = malloc_student("Anton", "D19", 5);
  assert(st != NULL);
  fwrite(st, sizeof(student_t), 1, file);
  free_student(st);
  rewind(file);

  student_t *st2 = malloc_student("", "", 0);
  assert(st2 != NULL);
  fread(st2, sizeof(student_t), 1, file); 
  printf("Fio = %s\nGroup = %s\nCourse = %d\n",
      st2->fio, st2->group, st2->course);
  free_student(st2);
  fclose(file);
#endif

#if RN7
#endif
}
