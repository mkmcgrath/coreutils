#include <stdio.h>
int filecopy(FILE *fp) {
  int c;
  while ((c = getc(fp)) != EOF) {
    putc(c, stdout);
  }
}

int main(int argc, char *argv[], FILE *fp) {
  if (argc == 1) {
    filecopy(stdin);
  }

  else {
    while (--argc > 0) {
      if ((fp = fopen(*++argv, "r")) == NULL) {
        printf("cat: i have no idea what '%s' is... \n", *argv);
        break;

      } else {
        filecopy(fp);
        fclose(fp);
      }
    }

    return 0;
  }
}
