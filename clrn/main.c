#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct dump_buffer_s
{
  size_t size;
  void *data;
} dumpBuffer_t;

static struct dump_buffer_s *
malloc_dump_buffer (void)
{
  dumpBuffer_t *dbuff = (dumpBuffer_t *) malloc (sizeof (dumpBuffer_t));
  dbuff->size = 0;
  dbuff->data = NULL;
  return dbuff;
}

static struct dump_buffer_s *
free_dump_buffer (struct dump_buffer_s *dbuff)
{
  assert (dbuff->data != NULL);
  assert (dbuff != NULL);

  free (dbuff->data);
  free (dbuff);
  
  dbuff->data = NULL;
  dbuff = NULL;

  return dbuff;
}

static size_t
fsize (FILE * f)
{
  assert (f != NULL);
  fseek (f, 0L, SEEK_END);
  const size_t size = ftell (f);
  fseek (f, 0L, SEEK_SET);
  return size;
}

static dumpBuffer_t *
fdump (FILE * f)
{
  assert (f != NULL);
  dumpBuffer_t *buff = malloc_dump_buffer ();
  buff->size = fsize (f) + 1;
  buff->data = malloc (buff->size);
  char ch_buffer;
  size_t i = 0;
  for (; (ch_buffer = fgetc (f)) != EOF; ++i)
    {
        if (ferror (f))
    	{
    	  free_dump_buffer (buff);
    	  break;
    	}

      ((char *) buff->data)[i] = ch_buffer;
    }
  return buff;
}

int
main (void)
{
  const char *fname = "test.txt";
  FILE *f = fopen (fname, "r");
  dumpBuffer_t *buff = fdump (f);
  printf ("Buffer size = %lu\nFile data = %s\n", buff->size,
	  (char *) buff->data);
  printf ("Strlen size = %lu\n", strlen ((char *) buff->data));
  assert(free_dump_buffer(buff) == NULL);
  fclose (f);
  return 0;
}