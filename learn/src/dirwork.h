#pragma once

#define CREATE_DIR 0
#define READ_DIR 0
#define REMOVE_DIR 0
#define CLOSE_DIR 0
#define CURRENT_DIR 0
#define PROG 1

#if CREATE_DIR
#include <sys/stat.h>
#include <sys/types.h>
/* int mkdir(const char *pathname, mode_t mode); */
#endif
#if READ_DIR
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
// DIR* opendir(const char *name); // open stream
// struct dirent* readdir(DIR *dirp); // read stream by readdir
// int closedir(DIR *dirp); // after end work, close
#endif
#if REMOVE_DIR
#include <unistd.h>
#endif
#if CLOSE_DIR
#include <dirent.h>
// closedir(DIR *dirp);
#endif
#if CURRENT_DIR
#include <unistd.h>
// char* getcwd(char *buf, size_t size) // Absoulute way current dir
// copy in buf
#endif

#if PROG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#endif

extern void run_ls6(void);
