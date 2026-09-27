#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

// attempt to show file metadata
// eventually will integrate with ls.c as the -l option

int main(int argc, char **argv) {
  struct stat st;
  if (stat(argv[1], &st) != 0) {
    perror(argv[1]);
    return 1;
  }
  printf("size: %lld\n", (long long)st.st_size);
  printf("device ID: %li\n", st.st_dev);
  printf("file type & mode: %ui\n", st.st_mode);
  if (S_ISDIR(st.st_mode)) {
    printf("dat jawn a directoreh\n");
  }

  if (S_ISREG(st.st_mode)) {
    printf("dat jawn regelleh\n");
  }
}
