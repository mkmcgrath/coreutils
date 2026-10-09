#include "frequencies.h"
#include <math.h>
#include <sndfile.h>
#include <stdio.h>
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
  sfinfo.channels = 1;
  sfinfo.samplerate = SAMPLE_RATE;
  sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_FLOAT;

  // Open the output file
  file = sf_open(FILE_NAME, SFM_WRITE, &sfinfo);
  if (!file) {
    fprintf(stderr, "Error opening output file\n\n");
    return;
  }

  double x = 1;

  // Generate and write the sine wave to the buffer
  for (int i = 0; i < SAMPLE_RATE * 6; ++i) {

    float sample0 = 0.5f * (float)sin(2.0 * PI * D * i / SAMPLE_RATE);
    float sample1 = 0.5f * (float)sin(2.0 * PI * D * i / SAMPLE_RATE + phase);

    float combinedSample = sample0 + sample1;
    printf("%f\n", combinedSample);
    printf("x=%f\n", x);

    sf_writef_float(file, &combinedSample, 1);
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
