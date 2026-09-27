#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// todo: cleanup, error handling, argument parsing, securing code
// this program pulls from energy_full to give an accurate reading of where the battery's actually at since the health
// decreases over time

int main(int argc, char *argv[]) {
  FILE *f = fopen("/sys/class/power_supply/BAT0/energy_full", "r");
  FILE *g = fopen("/sys/class/power_supply/BAT0/energy_now", "r");
  int energy_full;
  int energy_now;

  if (fscanf(f, "%d", &energy_full) != 1 || fscanf(g, "%d", &energy_now) != 1) {
    fprintf(stderr, "smthn went wrong\n");
    fclose(f);
    fclose(g);
    return 1;
  }
  fclose(f);
  fclose(g);

  // printf("energy_full %d\n", energy_full);
  // printf("energy_now %d\n", energy_now);

  double percent = ((double)energy_now / energy_full) * 100;
  int intpercent = ((double)energy_now / energy_full) * 100;

  printf("%.2f%%\n", percent);
  //  printf("percent %d\n", intpercent);

  // printf(".%d\n", remainder);

  return 0;
}
