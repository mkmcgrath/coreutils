#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

// todo: fix the colors to actually apply to the filetype

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
  const char *red = "\033[0;31m";
  const char *green = "\033[0;32m";
  const char *brown = "\033[0;33m";
  const char *blue = "\033[0;34m";
  const char *purple = "\033[0;35m";
  const char *cyan = "\033[0;36m";
  const char *yellow = "\033[1;33m";

  const char *colorend = "\033[0;37m";
  int mono = 0;
  int showhidden = 0;
  int showlong = 0;
  int help = 0;

  while ((c = getopt(argc, argv, "malh")) != EOF) {
    switch (c) {
    case 'm': { // disable color
      red = green = brown = blue = purple = cyan = yellow = colorend = "";
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

  if ((dp = opendir(tgtdir)) == NULL) {             // targetdir needs to actually exist
    perror("opendir");                              // give us the error to read
    printf("you will now spontaneously combust\n"); // inform the user of their imminent demise
    exit(1);
  }

  dp1 = opendir(tgtdir); // dp1 lets us get a count of the size of the items within the target dir
  int i = 0;             // increment
  while ((dirp1 = readdir(dp1)) != NULL) {
    i++;
  }

  struct entries { // struct to allow us to sort filenames
    int firstChar;
    //    long int inode; // verdict is still out on if we need to worry about inode
    char filename[256];
  };

  struct entries items[i]; // this is the point of dp1 and dirp1, to allow us to properly size the entries array

  i = 0; // reset increment

  while ((dirp = readdir(dp)) != NULL) {        // catch when we run out of entries
    if (showhidden || dirp->d_name[0] != '.') { // hidden file support
      items[i].firstChar = dirp->d_name[0];     // load firstchar of dirent for sorting
      //      items[i].inode = dirp->d_ino;             // load inode for reference
      snprintf(items[i].filename, sizeof(items[i].filename), "%s",
               dirp->d_name); // load the dirent name string into filename
      i++;                    // increment
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
    b++;
    if (b == 0)
      color = red;
    if (b == 1)
      color = green;
    if (b == 2)
      color = brown;
    if (b == 3)
      color = blue;
    if (b == 4) {
      color = purple;
      b = -1;
    }

    printf("%s%s  %s", color, items[a].filename, colorend);
    // printf("%li %s\n", items[a].inode, items[a].filename); // show inode
  }
  printf("\n");

  closedir(dp);
  exit(0);
}
