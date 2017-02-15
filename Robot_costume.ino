#include <Bounce2.h>
#include <LEDEffect.h>

int LED_ERROR = 6;
int LED_OK = 3;
int LED_HEART = 9;
int EMERGENCY_STOP = 5;


enum LEffect {BLINK, ON, OFF, HEARTBEAT};

struct Effect {
  LEffect effect;
  int speed;
};

// we have 3 LEDS
const int LEDS = 3;

const Effect moods[][LEDS] = {
  // HEART               OK              ERROR
  {{BLINK, 125},       {OFF, 1},         {BLINK, 75}}, // ERROR mood  
  {{HEARTBEAT, 30},    {ON, 1},          {OFF, 1}},   // CALM mood
  {{HEARTBEAT, 10},    {BLINK, 500},     {OFF, 1}},   // EXCITED mood
  {{HEARTBEAT, 8},     {BLINK, 125},     {OFF, 1}},   // WARNING mood
};

// LED pin assignments   
LEDEffect leds[LEDS] = { { LED_HEART },  { LED_OK },  { LED_ERROR } };

const int MOODS = sizeof(moods)/sizeof(Effect)/LEDS;
const int ERROR_MOOD = 0;
const int CALM_MOOD = 1;
int currentMood = 1;
unsigned long moodDuration = 0;
unsigned long time = 0;

Bounce stop_button = Bounce(); 

void setup() {
  // set up the emergency stop with debouncing
  pinMode(EMERGENCY_STOP, INPUT_PULLUP);
  stop_button.attach(EMERGENCY_STOP);
  stop_button.interval(5); // interval in ms

  randomSeed(analogRead(0));
  
  changeMood(currentMood);
};
  

void loop() {
  // Update the Bounce instance :
  stop_button.update();

  // Get button events
  bool stop_pressed = stop_button.rose();
  bool stop_released = stop_button.fell();

  if(currentMood != ERROR_MOOD) {
    if(millis() > time + moodDuration) { // timeout    
      time = millis();

      // once in a while go into error state - only the emergency stop exits from the error state
      bool goToErrorState = (random(0,20) == 0);
      if(goToErrorState)
        changeMood(ERROR_MOOD);
      else {
        int newMood = random(CALM_MOOD, MOODS-1);
        changeMood( newMood );
      }
    }
  }

  if(stop_pressed) {
    changeMood(CALM_MOOD);
  }
  
  for(int led=0; led < LEDS ; led++)
    leds[led].update();  
};

void changeMood(int mood) {
  currentMood = mood;
  moodDuration = random(5000, 15000);
  
  for(int led=0; led < LEDS ; led++) {
    const Effect &effect = moods[mood][led];   
    switch(effect.effect) {
      case BLINK:
        leds[led].blink(effect.speed);
        break;
      case HEARTBEAT:
        leds[led].breath(effect.speed);
        break;
       case ON:
        leds[led].on();
        break;
       case OFF:
        leds[led].off();
        break;
    }    
  }
}

