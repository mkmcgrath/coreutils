#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    int fd = rmdir(argv[i]);
    close(fd);
  }
  return 0;
}
