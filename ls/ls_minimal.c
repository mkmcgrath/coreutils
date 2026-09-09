#include <dirent.h>
#include <stdio.h>
int main() { // the smallest functional version of the ls utility
  const char *path = ".";
  DIR *dirp = opendir(path);
  struct dirent *entry;
  while ((entry = readdir(dirp)) != NULL) {
    printf("%s\t", entry->d_name);
  }
  printf("\n");
  closedir(dirp);
  return 0;
}
