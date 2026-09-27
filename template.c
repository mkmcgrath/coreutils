#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

  setvbuf(stdout, NULL, _IOLBF, 0); // dont buffer output until program end

  /* COLORS DEFINED HERE */

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

  /* PARSING OF GETOPT() ARGUMENTS */

  int c;

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

  if (optind < argc) {       // if
    printf("hello world\n"); // this line is NOT necessary and will need to be changed.
                             // Whatever goes here occurs when we pass something other than a flag
  }

  exit(0);
}
