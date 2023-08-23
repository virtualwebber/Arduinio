#include <ezBuzzer.h>
#include <ezButton.h>

#define LOOP_STATE_STOPPED 0
#define LOOP_STATE_STARTED 1
#define RING_DELAY_ON 0
#define RING_DELAY_OFF 1

// constants won't change. Used here to set a pin number
int buzzer_pin = 3;
int count = 0; 

// Variables will change:
ezButton button(7);  // create ezButton object that attach to pin 7;
ezBuzzer buzzer(buzzer_pin); // create ezBuzzer object that attach to a pin;
int loopState = LOOP_STATE_STOPPED;
int ringdelay = RING_DELAY_ON;

 
// notes in the melody:
int melody[] = {
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_G5, NOTE_C5, NOTE_D5,
  NOTE_E5,
  NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5,
  NOTE_F5, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_E5, NOTE_D5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_G5
};

// note durations: 4 = quarter note, 8 = eighth note, etc, also called tempo:
int noteDurations[] = {
  8, 8, 4,
  8, 8, 4,
  8, 8, 8, 8,
  2,
  8, 8, 8, 8,
  8, 8, 8, 16, 16,
  8, 8, 8, 8,
  4, 4
};

void setup() {
  Serial.begin(9600);
  button.setDebounceTime(50); // set debounce time to 100 milliseconds
}

void loop() {
  button.loop(); // MUST call the loop() function first
  buzzer.loop(); // MUST call the buzzer.loop() function in loop()
  
  

  if (button.isPressed()) {
    if (loopState == LOOP_STATE_STOPPED)
       loopState = LOOP_STATE_STARTED;
    else // if(loopState == LOOP_STATE_STARTED)
      loopState = LOOP_STATE_STOPPED;
  }

  if (loopState == LOOP_STATE_STARTED) {
    if (ringdelay == RING_DELAY_ON) {
    delay(15000); //pause before playing ringer 15000 ~ 30 Seconds
    ringdelay = RING_DELAY_OFF;
    }  {
    if (buzzer.getState() == BUZZER_IDLE) {
    int length = sizeof(noteDurations) / sizeof(int);
    buzzer.playMelody(melody, noteDurations, length); // playing
    }
   //Serial.flush();
   //Serial.println("Playing Tone");
    Serial.println("Loop Count = " +String(count));
   //Serial.println("LoopState = " + String(loopState));
   //Serial.println("Button Count = " + String(button_count));
   count+=1;
   if (count == 2500) { // 2500 = Approx 60 seconds
     loopState = LOOP_STATE_STOPPED;
     count = 0;
    }
  }
  }
  if (loopState == LOOP_STATE_STOPPED) {
    if (buzzer.getState() != BUZZER_IDLE) {
      buzzer.stop() ; // stop
      ringdelay = RING_DELAY_ON;
    }
  }

}
