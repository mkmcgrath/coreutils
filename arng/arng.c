#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Awful Random Number Generator
// The number generated here uses the stdlib random function with unix time as a
// seed Useful if you need a "random" number, but absolutely do NOT use this in
// anything needing to be secure!! For example, I originally wrote this for a
// low resource anki clone to help me shuffle my decks

int main() {
  time_t now = time(NULL);
  long long seed = (long long)now % 10000;
  srand(seed);
  long random_int = rand();
  printf("%li\n", random_int);
  return 0;
}
