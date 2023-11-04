#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <ezButton.h>
#include <EEPROM.h>
ezButton playButton(2);
ezButton volupButton(4);
ezButton voldownbutton(3);
int vol = 10;
bool playing = false;
bool waitingtoplay= false;
int playtime =30000;//30 seconds
int playstart;
int waitdelay = 60000;//60 seconds
int waitingstarttime;
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void setup() {
    //stolen https://maker.pro/arduino/projects/how-to-use-the-dfmini-player-mp3-module-with-arduino
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini"));
  Serial.println(F("Initializing DFPlayer module ... Wait!"));
  if (!myDFPlayer.begin(mySoftwareSerial))
  {
    Serial.println(F("Not initialized:"));
    Serial.println(F("1. Check the DFPlayer Mini connections"));
    Serial.println(F("2. Insert an SD card"));
    while (true);
  }

  Serial.println();
  Serial.println(F("DFPlayer Mini module initialized!"));

  myDFPlayer.setTimeOut(500);
  vol = EEPROM.read(0);
  if(vol>30){vol=15;}
  myDFPlayer.volume(vol); 
  myDFPlayer.EQ(0); 
  //myDFPlayer.play(1);
  //myDFPlayer.loop(1);
  playButton.setDebounceTime(100);
  voldownbutton.setDebounceTime(100);
  playstart=millis();
  
  volupButton.setDebounceTime(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  playButton.loop();
  volupButton.loop();
  voldownbutton.loop();

  if(playButton.isPressed())
  {
    if(playing){
      myDFPlayer.pause();
      playing = false;
      waitingtoplay=false;
    }
    else if (waitingtoplay) {
      //waitingtoplay=false;//if you want a second press while its waiting to play to turn it off
    }
    else {
      waitingtoplay=true;
      waitingstarttime=millis();
    }
    
  }  

  if((millis()-waitingstarttime> waitdelay) && waitingtoplay){
    myDFPlayer.loop(1);
    playing=true;
    playstart=millis();
    waitingtoplay=false;
    
  }

  if((millis()-playstart>playtime)&& playing){
    myDFPlayer.pause();
    playing=false;
    
  }

  if(voldownbutton.isPressed())
  {
    vol--;
    if(vol<0){vol=0;}
    EEPROM.write(0,vol);
    myDFPlayer.volume(vol);
    
  }  
  if(volupButton.isPressed())
  {
    vol++;
    if(vol>30){vol=30;}
    EEPROM.write(0, vol);
    myDFPlayer.volume(vol);
  }  

}
