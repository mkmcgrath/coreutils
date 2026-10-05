#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define BLUE "\033[01;34m"
#define CYAN "\033[01;36m"
#define GREEN "\033[01;32m"
#define YELLOW "\033[40;33;01m"
#define MAGENTA "\033[01;35m"
#define RESET "\033[0m"

const char *color_for(mode_t m) {
  if (S_ISDIR(m))
    return BLUE;
  if (S_ISLNK(m))
    return CYAN;
  if (S_ISFIFO(m))
    return YELLOW;
  if (S_ISSOCK(m))
    return MAGENTA;
  if (S_ISBLK(m) || S_ISCHR(m))
    return YELLOW;
  if (m & (S_IXUSR | S_IXGRP | S_IXOTH))
    return GREEN;
  return "";
}

int print_from_inode() {
  printf("inode\n");

  return 0;
}

int main(int argc, char **argv) {

  setvbuf(stdout, NULL, _IOLBF, 0); // dont buffer output until program end

  int c;
  DIR *dp;              // dp is a pointer to a DIR
  struct dirent *dirp;  // dirp is a pointer to a struct dirent
  DIR *dp1;             // allow us to scan dir first to get a count of all entries
  struct dirent *dirp1; // same as above

  const char *tgtdir = "."; // setting tgtdir (targetdir) to . in case program is called w/o argument
  int mono = 0;
  int showhidden = 0;
  int showlong = 0;
  int help = 0;

  while ((c = getopt(argc, argv, "malh")) != EOF) {
    switch (c) {
    case 'm': { // disable color
      mono = 1;
      break;
    }

    case 'a': {
      showhidden = 1;
      break;
    }

    case 'l': {
      showlong = 1;
      break;
    }
    case 'h': {
      help = 1;
      break;
    }
    }
  }

  if (optind < argc) {
    tgtdir = argv[optind];
  }

  if ((dp = opendir(tgtdir)) == NULL) { // targetdir needs to actually exist
    perror("opendir");                  // give us the error to read
    printf("target does not exist\n");
    exit(1);
  }

  dp1 = opendir(tgtdir); // dp1 lets us get a count of the size of the items within the target dir
  int i = 0;             // increment
  while ((dirp1 = readdir(dp1)) != NULL) {
    i++;
  }

  struct entries { // struct to allow us to sort filenames
    int firstChar;
    char filename[256];
    off_t size;
    mode_t mode;
  };

  struct entries items[i]; // this is the point of dp1 and dirp1, to allow us to properly size the entries array

  i = 0; // reset increment
  int dfd = dirfd(dp);

  while ((dirp = readdir(dp)) != NULL) {        // catch when we run out of entries
    if (showhidden || dirp->d_name[0] != '.') { // hidden file support
      struct stat st;
      if (fstatat(dfd, dirp->d_name, &st, AT_SYMLINK_NOFOLLOW) != 0) {
        perror(dirp->d_name);
        continue;
      }
      items[i].firstChar = dirp->d_name[0]; // load firstchar of dirent for sorting
      snprintf(items[i].filename, sizeof(items[i].filename), "%s", dirp->d_name);
      items[i].mode = st.st_mode;
      items[i].size = st.st_size;

      i++; // increment
    }
  }

  for (int a = 1; a < i; a++) { // algorithm to sort alphabetically
    struct entries key = items[a];

    int b = a - 1;
    while (b >= 0 && items[b].firstChar > key.firstChar) {
      items[b + 1] = items[b];
      b--;
    }
    items[b + 1] = key;
  }

  const char *color;
  char b = 0;

  for (int a = 0; a < i; a++) { // finally print all items[] entries in order
    printf("%s%s%s  ", color_for(items[a].mode), items[a].filename, RESET);
  }
  printf("\n");

  closedir(dp);
  exit(0);
}
