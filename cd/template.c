#include <fcntl.h>
#include <unistd.h>

// simple template for one shot utilities

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    // int fd = open(argv[i], O_CREAT, 0666); //implementation from touch.c
    close(fd);
  }
  return 0;
}
