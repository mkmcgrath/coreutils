#include "frequencies.h"
#include <complex.h>
#include <math.h>
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// to compile, use flags -lm and -lsndfile

int SAMPLE_RATE = 44100;
int direction = 1;

constexpr double PI = 3.14159265358979323846;

double phase = PI / 2;

#define FRAMES_PER_BUFFER 256
#define FILE_NAME "output.wav"

// Function to generate a sine wave and write it to a WAV file
void generateAndWriteWave() {
  SNDFILE *file;
  SF_INFO sfinfo;

  // Initializing and defining variables for the function.
  sfinfo.channels = 2;
  sfinfo.samplerate = SAMPLE_RATE;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

  // Open the output file
  file = sf_open(FILE_NAME, SFM_WRITE, &sfinfo);
  if (!file) {
    fprintf(stderr, "Error opening output file\n\n");
    return;
  }

  // Generate and write the sine wave to the buffer
  for (int p = 0; p < 1; p++) {
    //    for (double z = 0; z < .001; z = z + .0001) {
    for (double i = 0, z = 0, x = 0; i < SAMPLE_RATE * 1; i = i + 0.1, z = z + 0.002, x = x + 0.0001) {
      // for (double i = 0; i < SAMPLE_RATE * 6; ++i) {
      double t = (double)i / SAMPLE_RATE;
      // adjust the amplitude for tremolo effect
      double A = sin(x);
      // A = log(A) + A;
      //      printf("%f\n", A);
      float frame[2];

      frame[0] = A * (float)sin(2.0 * PI * (C + z) * t);
      frame[1] = A * (float)cos(2.0 * PI * (C + z) * t);

      sf_writef_float(file, frame, 1);
    }
  }

  // Close the output file
  sf_close(file);
}

int main() {
  // Generate and write the sine wave to the WAV file
  generateAndWriteWave();

  printf("WAV file generated: %s\n", FILE_NAME);

  return 0;
}
