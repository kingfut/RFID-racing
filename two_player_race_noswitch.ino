/* 
 * All the resources for this project: https://www.hackster.io/Aritro
 * Modified by Aritro Mukherjee
 */
 
 //blue tag UID: B4 9F DA D9
 //white card UID: 60 37 FF A3

#include <SPI.h>          //RFID stuff
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define NOTE_B0  31         //piezo sound stuff
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
int sAudioPin = 5;
int NOTE_SUSTAIN = 120;

int greenLed = 6;   //LED lights
int redLed = 7;

const int switchPin = 4;  
int switchState = 0;      //timer variables
int prevSwitchState = 0; 
unsigned long lapMillis = 0;
unsigned long startMillis = millis();
unsigned long bestMillis = 9999999;
unsigned long currentTime = millis();
float lapTime = 0.00;
float bestLap = 0.00;
boolean firstTrigger = true;
boolean newBest = false;
boolean firstRace = true;

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Prepare to race...");
  Serial.println();
  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(switchPin, INPUT);
  Serial.println("Go!");
  
}

void loop() {
 //unsigned long currentTime = millis();
 switchState = digitalRead(switchPin);
 //startMillis = currentTime; 
  //GO sequence:
 /*if(firstRace == true){
    //play "GO" sound on piezo
    /*tone(sAudioPin,NOTE_A5);
    delay(NOTE_SUSTAIN);
    noTone(sAudioPin);
    digitalWrite(greenLed, HIGH); 
    Serial.println("Go!");*/
   
    
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) 
        {
         return;
        }
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) 
        {
          return;
        }
        //Show UID on serial monitor
        Serial.print("UID tag :");
        String content= "";
        byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++) 
        {
           Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(mfrc522.uid.uidByte[i], HEX);
          content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
          content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        Serial.println();
        //Serial.print("Message : ");
       content.toUpperCase(); 
     
        if (firstRace == true)  { 
          if (content.substring(1) == "B4 9F DA D9") { // player 1 wins
            //lapMillis = currentTime - startMillis;
            lapTime = millis() / 1000.00;
            Serial.println("Player 1 Wins!");
            Serial.print("Your time: ");
            Serial.print(lapTime);
            Serial.println("s");
            digitalWrite (greenLed, HIGH);
            firstRace = false;
            //play win sound
            /*tone(sAudioPin,NOTE_A5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_B5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_C5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_B5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_C5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_D5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_C5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_D5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_E5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_D5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_E5);
            delay(NOTE_SUSTAIN);
            tone(sAudioPin,NOTE_E5);
            delay(NOTE_SUSTAIN);
            noTone(sAudioPin); */
            //firstRace = false; 
                                  }
                        } 
        if (firstRace == true) {
          if (content.substring(1) == "60 37 FF A3"){ // player 2 wins
          //lapMillis = currentTime - startMillis;
          lapTime = currentTime / 1000.00;
          Serial.println("Player 2 Wins!");
          Serial.print("Your time: ");
          Serial.print(lapTime);
          Serial.println("s");
          firstRace = false;
          //play win sound
          /*tone(sAudioPin,NOTE_A5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_B5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_C5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_B5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_C5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_D5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_C5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_D5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_E5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_D5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_E5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_E5);
          delay(NOTE_SUSTAIN);
          noTone(sAudioPin); */
          //firstRace = false;  
              }
          }
  
 //prevSwitchState = switchState;
}

   /*if (content.substring(1) == "B4 9F DA D9"){ // racer rfid
    lapMillis = currentTime - startMillis;
    startMillis = currentTime;
    
    lapTime = lapMillis / 1000.00;
    
    //if first trigger print race started
    if (firstTrigger == true){
      Serial.println("Race Started!    ");
    }
    
    //print if not first trigger
    if (firstTrigger != true){
      //Serial.print("lapTime: ");
      //Serial.println(lapTime);
      //Serial.print("lapMillis: ");
      //Serial.println(lapMillis);
      //print lap time
      //lcd.setCursor(0, 0);
      Serial.print("Time: ");
      Serial.print(lapTime);
      Serial.println("s      ");   
    }
   
        
    //if last lap is better than best lap
    if(lapMillis < bestMillis && firstTrigger != true)
    {
      bestMillis = lapMillis;
      bestLap = lapTime;
      //Serial.print("bestLap: ");
      //Serial.println(bestLap);
      //print best lap time
      //lcd.setCursor(0, 1);
      Serial.print("Best: ");
      Serial.print(bestLap);
      Serial.println("s     ");
      newBest = true;
    }
    
    //beep piezo
    if(newBest == true){
     //winning sound
        //for(uint8_t nLoop = 0;nLoop < 2;nLoop ++)
        {
          tone(sAudioPin,NOTE_A5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_B5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_C5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_B5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_C5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_D5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_C5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_D5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_E5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_D5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_E5);
          delay(NOTE_SUSTAIN);
          tone(sAudioPin,NOTE_E5);
          delay(NOTE_SUSTAIN);
          noTone(sAudioPin);
          newBest = false;
         } 
      }
       else {
          tone(sAudioPin,NOTE_G4);
          delay(250);
          tone(sAudioPin,NOTE_C4);
          delay(500);
          noTone(sAudioPin);
    }
    
    firstTrigger = false;
    Serial.println("----------------"); 
   }

    /*Serial.println("Authorized access");
    Serial.println();
    digitalWrite(greenLed, HIGH);
    delay(3000);
    digitalWrite(greenLed, LOW);
  
 
 else   {
    Serial.println(" Access denied");
    digitalWrite(redLed, HIGH);
    delay(3000);
    digitalWrite(redLed, LOW);
  }
}*/ 
