#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN); // Class Library for RFID

//Note: Blue tags have format of 82 0E 82 D4, White tags have format of 04 D1 34 C8 23 02 89

// Pin for LEDs & Buttons
// int ResetBtn = 7;
// int LED1 = 9;
// int LED2 = 8;

// Flags for loop manipulation
// int start_flag = 0;
// int rest_flag = 0;
// int lock_flag = 0;
// int buzzer_flag = 0;

// Timer variables
// int counter = 0;
// int cache_counter = 0;

// Nutrient variables
int sodium = 0;
int fiber = 0;
int sugar = 0;

// Async Timer variables
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long second = 200; //In milliseconds

void setup() {
  Serial.begin(9600);
  SPI.begin();

  Serial.println("Initializing RFID reader..."); // Debug for RFID
  mfrc522.PCD_Init();
  byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
  Serial.print("Firmware version: 0x");
  Serial.println(version, HEX);

  if (version == 0x00 || version == 0xFF) { // Debug for RFID
    Serial.println("ERROR: RFID module not detected. Check wiring.");
  } else {
    Serial.println("RFID module is working!");
  }

}

void loop() {

  //TODO: Implement LED status --> Make sure to keep it above mfrc522.PICC_IsNewCardPresent() & mfrc522.PICC_ReadCardSerial() statements

  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if (!mfrc522.PICC_ReadCardSerial()) { 
    return;
  }

  Serial.print("Card UID: "); // Prints card that is registered into serial monitor
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Change this to what the actual UID of the tag is, and duplicate if necessary 
    // Update nutrient values
  } 



  mfrc522.PICC_HaltA();  // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}
