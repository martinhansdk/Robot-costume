#include <Bounce2.h>
#include <LEDEffect.h>

enum LEffect {BLINK, ON, OFF, HEARTBEAT};

struct Effect {
  LEffect effect;
  int speed;
};

// we have 3 LEDS
const int LEDS = 3;

const Effect moods[][LEDS] = {
  // HEART               OK              ERROR
  {{HEARTBEAT, 1000},  {ON, 1},          {OFF, 1}},   // CALM mood
  {{HEARTBEAT, 100},   {BLINK, 10},      {OFF, 1}},   // EXCITED mood
  {{BLINK, 10},        {OFF, 1},         {ON, 1}},    // ERROR mood
};

// LED pin assignments    HEART  OK      ERROR
LEDEffect leds[LEDS] = { { 5 },  { 6 },  { 7 } };

void setup() {
  
};


void loop() {
  
  
};
