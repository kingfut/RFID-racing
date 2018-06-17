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

//deleted piezo sound information

int greenLed = 6;   //LED lights
int redLed = 7;

const int switchPin = 4;  
int switchState = 0;      //timer variables
int prevSwitchState = 0; 
unsigned long lapMillis = 0;
unsigned long startTime = 0;
unsigned long bestMillis = 9999999;
unsigned long currentTime = millis();
unsigned long raceTime = 0;
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
  //Serial.println("Go!");
  
}

void loop() {
 //unsigned long currentTime = millis();
 switchState = digitalRead(switchPin);
  if (switchState != prevSwitchState  && switchState == HIGH){
   Serial.println("Go!");
   startTime = millis();
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
            raceTime = (currentTime - startTime);
            lapTime = raceTime / 1000.00;
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
