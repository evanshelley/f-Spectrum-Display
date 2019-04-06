#include <arduinoFFT.h>
#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>

// Initialise 32x16 DMD
DMD dmd(1,1);

// Initialise FFT
arduinoFFT FFT = arduinoFFT();

const uint16_t samples = 64; //This value MUST ALWAYS be a power of 2

double vReal[samples];
double vImag[samples];

void setup() {
  Serial.begin(9600);

}

void loop() {

  int i = 0;

  // buffer
  int value = 0;

  // Sampling
  while (i < samples) {
    value = analogRead(A0);
    vReal[i] = value;
    vImag[i] = 0;
  }

  // Window samples according to Hamming function
  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  // Compute FFT
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
  // Calculate magnitudes of each frequency
  FFT.ComplexToMagnitude(vReal, vImag, samples);

  // Display magnitudes in real time

}
