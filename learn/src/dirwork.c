#include "dirwork.h"
#include <dirent.h>

void 
run_ls6(void)
{
#if CREATE_DIR | READ_DIR | REMOVE_DIR | CLOSE_DIR | CURRENT_DIR
  const char * dirname = "dirtest";
#endif
#if CREATE_DIR
  mkdir(dirname, S_IRWXU);
#endif
#if READ_DIR
  DIR *dir = opendir(dirname);
  struct dirent *dirp = NULL; 
  while ( (dirp = readdir(dir)) != NULL)
  {
    printf("File name = %s\n", dirp->d_name);
  }
#endif
#if REMOVE_DIR
  rmdir(dirname);
#endif
#if CLOSE_DIR
  closedir(dir);
#endif
#if CURRENT_DIR
  const size_t buff_size = 1000;
  char buff[buff_size];
  getcwd(buff, buff_size);
  printf("%s\n", buff);
#endif
#if PROG
  // main (argc,argv)
  int argc = 2;
  char *argv[] = {"learn", "testdir"};
  assert( (2 == argc) && "\n Enter name dir first arg\n");
  // Buffer for dir name
  char buff[128] = {0};
  // Copy way user
  strcpy(buff, argv[1]);

  DIR *dp = NULL;
  // Open stream dir
  assert( (dp = opendir(argv[1])) != NULL );
  if(buff[strlen(buff) - 1] == '/')
  {
    strcpy(buff+strlen(buff), "newDir/");
  }
  else
  {
    strcpy(buff+strlen(buff), "/newDir/");
  }

  printf("\n Create new dir [%s]\n", buff);
  // Create new dir
  mkdir(buff, S_IRWXU | S_IRWXG | S_IRWXO);
  printf("\n In dir [%s] \n", argv[1]);

  // Read dir
  struct dirent *dptr = NULL;
  while( (dptr = readdir(dp)) != NULL )
    printf(" [%s] ", dptr->d_name);
  
  // Close stream
  
  closedir(dp);
  rmdir(buff);
  puts("");
#endif
}
