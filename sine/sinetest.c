#include <complex.h>
#include <math.h>
#include <stdio.h>

// place to play around with the sine function to experiment before implementing in sine.c

int main() {

  for (float x = 0; x < 10; x = x + 0.1) {

    float y = cabs(sin(x));
    printf("%f\n", y);
  }
}
