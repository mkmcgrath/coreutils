#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    int fd = unlink(argv[i]);
    close(fd);
  }
  return 0;
}
