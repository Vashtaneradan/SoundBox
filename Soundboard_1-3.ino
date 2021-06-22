//Bibliotheke
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(12, 13); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);





// globale Variablen definitieon
int LEDblau = 2;
int LEDgruen = 3;
int LEDgelb = 4;
int LEDrot = 5;
int LEDweiss = 6;

int S1blau = 7;
int S2gruen = 8;
int S3gelb = 9;
int S4rot = 10;
int S5weiss = 11;
int S6schlange = A0;
int S7skipedi = A2;

int abspielen = 0;
//


void setup() {
  // put your setup code here, to run once:
  //defintion der Output
  pinMode(LEDblau, OUTPUT);
  pinMode(LEDgruen, OUTPUT);
  pinMode(LEDgelb, OUTPUT);
  pinMode(LEDrot, OUTPUT);
  pinMode(LEDweiss, OUTPUT);

  pinMode(S1blau, INPUT_PULLUP);
  pinMode(S2gruen, INPUT_PULLUP);
  pinMode(S3gelb, INPUT_PULLUP);
  pinMode(S4rot, INPUT_PULLUP);
  pinMode(S5weiss, INPUT_PULLUP);


  //LED-Test
  digitalWrite(LEDblau, HIGH);

  delay(1000);//

  digitalWrite(LEDblau, LOW);




  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //  myDFPlayer.EQ(DFPLAYER_EQ_POP);
  //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
  //  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
  //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
  //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

  //----Set device we use SD as default----
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);

  //----Mp3 control----
  //  myDFPlayer.sleep();     //sleep
  //  myDFPlayer.reset();     //Reset the module
  //  myDFPlayer.enableDAC();  //Enable On-chip DAC
  //  myDFPlayer.disableDAC();  //Disable On-chip DAC
  //  myDFPlayer.outputSetting(true, 15); //output setting, enable the output and set the gain to 15

  //----Mp3 play----
  /*
    myDFPlayer.next();  //Play next mp3
    delay(1000);
    myDFPlayer.previous();  //Play previous mp3
    delay(1000);
    myDFPlayer.play(1);  //Play the first mp3
    delay(1000);
    myDFPlayer.loop(1);  //Loop the first mp3
    delay(1000);
    myDFPlayer.pause();  //pause the mp3
    delay(1000);
    myDFPlayer.start();  //start the mp3 from the pause
    delay(1000);
    myDFPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
    delay(1000);
    myDFPlayer.enableLoopAll(); //loop all mp3 files.
    delay(1000);
    myDFPlayer.disableLoopAll(); //stop loop all mp3 files.
    delay(1000);
    myDFPlayer.playMp3Folder(4); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
    delay(1000);
    myDFPlayer.advertise(3); //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
    delay(1000);
    myDFPlayer.stopAdvertise(); //stop advertise
    delay(1000);
    myDFPlayer.playLargeFolder(2, 999); //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
    delay(1000);
    myDFPlayer.loopFolder(5); //loop all mp3 files in folder SD:/05.
    delay(1000);
    myDFPlayer.randomAll(); //Random play all the mp3.
    delay(1000);
    myDFPlayer.enableLoop(); //enable loop.
    delay(1000);
    myDFPlayer.disableLoop(); //disable loop.
    delay(1000);
  */

  //----Read imformation----
  Serial.println(myDFPlayer.readState()); //read mp3 state
  Serial.println(myDFPlayer.readVolume()); //read current volume
  Serial.println(myDFPlayer.readEQ()); //read EQ setting
  Serial.println(myDFPlayer.readFileCounts()); //read all file counts in SD card
  Serial.println(myDFPlayer.readCurrentFileNumber()); //read current play file number
  Serial.println(myDFPlayer.readFileCountsInFolder(3)); //read file counts in folder SD:/03

  //myDFPlayer.playMp3Folder(1);


}
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Schalrter 2: ");
  Serial.print(analogRead(S7skipedi));
  Serial.print(" | ");

  Serial.print("Schalngenschalter: ");
  Serial.println(analogRead(S6schlange));







  if (digitalRead(S1blau) == 0) {
    digitalWrite (LEDblau, HIGH);


  }
  else
  { digitalWrite (LEDblau, LOW);
  }

  //shwifty
  if (digitalRead(S2gruen) == 0) {
    digitalWrite (LEDgruen, HIGH);
    if (abspielen == 0) {
      abspielen = 1;
      myDFPlayer.playMp3Folder(4);
      //myDFPlayer.play(4);
    }
  }
  else
  { digitalWrite (LEDgruen, LOW);

  }



  if (digitalRead(S3gelb) == 0) {
    digitalWrite (LEDgelb, HIGH);
  }
  else
  { digitalWrite (LEDgelb, LOW);
  }


  if (digitalRead(S4rot) == 0) {
    digitalWrite (LEDrot, HIGH);
  }
  else
  { digitalWrite (LEDrot, LOW);
  }


  if (digitalRead(S5weiss) == 0) {
    digitalWrite (LEDweiss, HIGH);
    if (abspielen == 0) {
      abspielen = 1;
      myDFPlayer.playMp3Folder(3);
      //   myDFPlayer.play(2);
      //      myDFPlayer.playFolder(1, 3); // in Ordner 01/003.mp3
    }
  }
  else
  { digitalWrite (LEDweiss, LOW);
  }

  if (abspielen == 0 && analogRead(S6schlange) > 500) {
    abspielen = 1;
    myDFPlayer.playMp3Folder(1);
    //myDFPlayer.play(1); // Befehl bezieht sich auf die Reihenfolge, in der die Songs auf die SD-Karte kopiert wurden.
  }


  if (abspielen == 0 && analogRead(S7skipedi) > 500) {
    abspielen = 1;
    myDFPlayer.playMp3Folder(2);
    //myDFPlayer.play(4);

  }

  // Diese Bedingung muss um jeden zusätzlichen Schalter ergänzt werden, der Musik abspielen und dadurch auch stoppen soll.
  if (abspielen == 1 && analogRead(S6schlange) < 500 && analogRead(S7skipedi) < 500 && digitalRead(S2gruen) == 1 && digitalRead(S5weiss) == 1) {
    abspielen = 0;
    myDFPlayer.pause();  //pause the mp3
  }

  delay(10);
}
