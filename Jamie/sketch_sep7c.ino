#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <ezButton.h>
ezButton playButton(2);
ezButton volupButton(4);
ezButton voldownbutton(3);
int vol = 10;
bool playing = true;
int playtime =10000;//ten seconds
int playstart;
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
  myDFPlayer.volume(vol); 
  myDFPlayer.EQ(0); 
  myDFPlayer.play(1);
  myDFPlayer.loop(1);
  playButton.setDebounceTime(50);
  voldownbutton.setDebounceTime(50);
  playstart=millis();
  
  volupButton.setDebounceTime(50);
}

void loop() {
  // put your main code here, to run repeatedly:
  playButton.loop();
  volupButton.loop();
  voldownbutton.loop();
  if(playButton.isPressed())
  {
    Serial.println(playing);
    if(!playing){
      myDFPlayer.loop(1);
      playing=true;
      playstart=millis();
    }
    else{
      myDFPlayer.stop();
      playing = false;
    }
  }  
  if(voldownbutton.isPressed())
  {
    vol--;
    if(vol<0){vol=0;}
    myDFPlayer.volume(vol);
    
  }  
  if(volupButton.isPressed())
  {
    vol++;
    if(vol>30){vol=30;}
    myDFPlayer.volume(vol);
  }  
  if(millis()-playstart>playtime){
    myDFPlayer.stop();
    playing=false;
    
  }

}
