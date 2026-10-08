#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    int fd = open(argv[i], O_CREAT, 0666);
    int fcntl(fd, F_DUPFD);
  }
}
