#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

// adapted from touch.c
// needs expansion

int main(int argc, char *argv[]) {
  char path = ".";
  int mkdir(char *path, mode_t mode);

  return 0;
}
