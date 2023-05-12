#include <FastLED.h>

#define LED_PIN     12
#define NUM_LEDS    30
#define A_PIN 2 // (D0)
#define B_PIN 3 // (D1)
//#define C_PIN 4 // (D2)
//#define D_PIN 5 // (D3)

CRGB leds[NUM_LEDS];

byte x_gedruktA = 0;
//byte x_gedruktB = 0;
//byte x_gedruktC = 0;
//byte x_gedruktD = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  all_LEDS_off(1000);
  attachInterrupt(digitalPinToInterrupt(A_PIN), trigger1, RISING);
  attachInterrupt(digitalPinToInterrupt(B_PIN), trigger2, RISING);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println(x_gedruktA);
  //delay(100); //not needed 
  
  if (x_gedruktA == 0) all_LEDS_off(1000);
  if (x_gedruktA == 1) thema_1();
  if (x_gedruktA == 2) police1();
  if (x_gedruktA == 3) police2();
  if (x_gedruktA == 4) police3();
}

void trigger1(){
  x_gedruktA++;
}
void trigger2(){
  x_gedruktA = 0;
  all_LEDS_off(1000);
}

void newGroup(byte startLED, byte stopLED, int msDelay, byte r, byte g, byte b){
  for (int i=startLED; i<stopLED; i++){
    leds[i] = CRGB(r, g, b);
    FastLED.show();
  }
  delay(msDelay);
}

void thema_1(){
  for (int i=0; i<3; i++){
    newGroup(0,6,10,255,50,0);
    newGroup(12,18,10,255,50,0);
    newGroup(24,30,10,255,50,0);
    all_LEDS_off(5);
  }
  for (int i=0; i<3; i++){
    newGroup(6,12,10,255,50,0);
    newGroup(18,24,10,255,50,0);
    all_LEDS_off(5);
  }
}

void police1(){
  for (int i=0; i<3; i++){
    newGroup(0,15,50,0,0,255);
    all_LEDS_off(1);
  }
  for (int i=0; i<3; i++){
    newGroup(15,30,50,255,0,0);
    all_LEDS_off(1);
  }
}

void police2(){
  for (int i=0; i<3; i++){
    newGroup(0,8,50,0,0,255);
    newGroup(22,30,50,255,0,0);
    all_LEDS_off(1);
  }
  for (int i=0; i<3; i++){
    newGroup(8,15,50,0,0,255);
    newGroup(15,22,50,255,0,0);
    all_LEDS_off(1);
  }
}

void police3(){
  for (int i=0; i<3; i++){
    newGroup(0,6,10,255,0,0);
    newGroup(12,18,10,255,0,0);
    newGroup(24,30,10,255,0,0);
    all_LEDS_off(5);
  }
  for (int i=0; i<3; i++){
    newGroup(6,12,10,0,0,255);
    newGroup(18,24,10,0,0,255);
    all_LEDS_off(5);
  }
}

void all_LEDS_off(int msDelay){
  for (int i=0; i<NUM_LEDS; i++){
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
  }
  delay(msDelay);
}
