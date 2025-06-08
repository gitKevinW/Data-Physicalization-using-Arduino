#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN); // Class Library for RFID

//Note: Blue tags have format of 82 0E 82 D4, White tags have format of 04 D1 34 C8 23 02 89

// Pin for LEDs & Buttons
int ResetBtn = 7;

int LED_sodium_1 = 0;
int LED_sodium_2 = 0;
int LED_sodium_3 = 0;
int LED_sodium_4 = 0;
int LED_sodium_5 = 0;

int LED_sugar_1 = 0;
int LED_sugar_2 = 0;
int LED_sugar_3 = 0;
int LED_sugar_4 = 0;
int LED_sugar_5 = 0;

int LED_fiber_1 = 0;
int LED_fiber_2 = 0;
int LED_fiber_3 = 0;
int LED_fiber_4 = 0;
int LED_fiber_5 = 0;

// Flags for loop manipulation
// int start_flag = 0;
// int rest_flag = 0;
// int lock_flag = 0;
// int buzzer_flag = 0;

// Timer variables
// int counter = 0;
// int cache_counter = 0;

// Nutrient variables (In mg)
int sodium = 0; // in mg // How much nutrients user is actually consuming
int fiber = 0; // in g
int sugar = 0; // in g

int rec_sodium = 2300; // in mg // How much nutrients user is needs everyday
int rec_fiber = 30; //in g
int rec_sugar = 30; // in g

// Food Nutrient variables 
int cheese_sodium = 211;
int cheese_sugar = 1;
int cheese_fiber = 0;

int ice_cream_sodium = 0;
int ice_cream_sugar = 0;
int ice_cream_fiber = 0;

int broccoli_sodium = 0;
int broccoli_sugar = 0;
int broccoli_fiber = 0;

int salad_sodium = 0;
int salad_sugar = 0;
int salad_fiber = 0;

int croissant_sodium = 0;
int croissant_sugar = 0;
int croissant_fiber = 0;

int apple_sodium = 0;
int apple_sugar = 0;
int apple_fiber = 0;

int chicken_sodium = 0;
int chicken_sugar = 0;
int chicken_fiber = 0;

int burger_sodium = 0;
int burger_sugar = 0;
int burger_fiber = 0;

int pizza_sodium = 0;
int pizza_sugar = 0;
int pizza_fiber = 0;

int ramen_sodium = 0;
int ramen_sugar = 0;
int ramen_fiber = 0;

int spaghetti_sodium = 0;
int spaghetti_sugar = 0;
int spaghetti_fiber = 0;

int bread_sodium = 0;
int bread_sugar = 0;
int bread_fiber = 0;



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
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Cheese 
    // Update nutrient values

    sodium = sodium + cheese_sodium;
    sugar = sugar + cheese_sugar;
    fiber = fiber + cheese_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Ice Cream
    // Update nutrient values

    sodium = sodium + ice_cream_sodium;
    sugar = sugar + ice_cream_sugar;
    fiber = fiber + ice_cream_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Broccoli
    // Update nutrient values

    sodium = sodium + broccoli_sodium;
    sugar = sugar + broccoli_sugar;
    fiber = fiber + broccoli_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Salad
    // Update nutrient values

    sodium = sodium + salad_sodium;
    sugar = sugar + salad_sugar;
    fiber = fiber + salad_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Croissant
    // Update nutrient values

    sodium = sodium + croissant_sodium;
    sugar = sugar + croissant_sugar;
    fiber = fiber + croissant_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Apple
    // Update nutrient values

    sodium = sodium + apple_sodium;
    sugar = sugar + apple_sugar;
    fiber = fiber + apple_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Chicken
    // Update nutrient values

    sodium = sodium + chicken_sodium;
    sugar = sugar + chicken_sugar;
    fiber = fiber + chicken_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Burger
    // Update nutrient values

    sodium = sodium + burger_sodium;
    sugar = sugar + burger_sugar;
    fiber = fiber + burger_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Pizza
    // Update nutrient values

    sodium = sodium + pizza_sodium;
    sugar = sugar + pizza_sugar;
    fiber = fiber + pizza_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Ramen
    // Update nutrient values

    sodium = sodium + ramen_sodium;
    sugar = sugar + ramen_sugar;
    fiber = fiber + ramen_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Spagetti
    // Update nutrient values

    sodium = sodium + spagetti_sodium;
    sugar = sugar + spagetti_sugar;
    fiber = fiber + spagetti_fiber;

  } 

  if (mfrc522.uid.uidByte[0] == 0xDE && mfrc522.uid.uidByte[1] == 0xAD && mfrc522.uid.uidByte[2] == 0xBE && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF 
  && mfrc522.uid.uidByte[3] == 0xEF && mfrc522.uid.uidByte[3] == 0xEF) { // Bread
    // Update nutrient values

    sodium = sodium + bread_sodium;
    sugar = sugar + bread_sugar;
    fiber = fiber + bread_fiber;

  } 



  mfrc522.PICC_HaltA();  // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}
