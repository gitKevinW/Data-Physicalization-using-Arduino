#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

// With words facing the readable way, from right to left: 
// Empty, 5v, CLOCK_PIN, LATCH_PIN, ground, DATA_PIN, 1st LED power, 5v
#define DATA_PIN1 7 //ds pin
#define CLOCK_PIN1 6 //shcp pin
#define LATCH_PIN1 5 //stcp pin

#define DATA_PIN2 4 //ds pin
#define CLOCK_PIN2 3 //shcp pin
#define LATCH_PIN2 2 //stcp pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // Class Library for RFID

// MOSI pin 11, MISO pin 12, SCK pin 13, GND pin GND, RST pin 9, SDA pin 10, 3.3V pin 3.3V

//Note: Blue tags have format of 82 0E 82 D4, White tags have format of 04 D1 34 C8 23 02 89

// Pin for LEDs & Buttons
int ResetBtn = 8;

// Nutrient variables (Sodium: mg, Fiber: g, Sugar: g)
int sodium = 0; // How much nutrients user is actually consuming
int fiber = 0; 
int sugar = 0; 

int sl_sodium = 5; 
int sl_fiber = 5; 
int sl_sugar = 5; 

int l_sodium = 1000; 
int l_fiber = 15; 
int l_sugar = 10; 

int rec_sodium = 1500;
int rec_fiber = 30; 
int rec_sugar = 20; 

int h_sodium = 1900; 
int h_fiber = 50; 
int h_sugar = 35; 

int sh_sodium = 2300; // in mg // How much nutrients is the limit for everyday
int sh_fiber = 70; 
int sh_sugar = 50; 

// Food Nutrient variables (Sources: USDA, FDA)
int cheese_sodium = 180;
int cheese_sugar = 0;
int cheese_fiber = 0;

int ice_cream_sodium = 80;
int ice_cream_sugar = 28;
int ice_cream_fiber = 0;

int broccoli_sodium = 55;
int broccoli_sugar = 2;
int broccoli_fiber = 5;

int salad_sodium = 200;
int salad_sugar = 3;
int salad_fiber = 3;

int croissant_sodium = 210;
int croissant_sugar = 6;
int croissant_fiber = 1;

int apple_sodium = 1;
int apple_sugar = 19;
int apple_fiber = 4;

int chicken_sodium = 1500;
int chicken_sugar = 0;
int chicken_fiber = 1;

int burger_sodium = 800;
int burger_sugar = 7;
int burger_fiber = 2;

int pizza_sodium = 640;
int pizza_sugar = 3;
int pizza_fiber = 2;

int ramen_sodium = 1700;
int ramen_sugar = 1;
int ramen_fiber = 1;

int spaghetti_sodium = 500;
int spaghetti_sugar = 6;
int spaghetti_fiber = 3;

int bread_sodium = 150;
int bread_sugar = 2;
int bread_fiber = 1;

// Async Timer variables
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long second = 200; //In milliseconds

// Global variables to track LED states
byte currentLED1 = 0;  // For sugar and sodium (first shift register)
byte currentLED2 = 0;  // For fiber (second shift register)

void setup() {
  Serial.begin(9600);
  SPI.begin();

  pinMode(DATA_PIN1, OUTPUT);
  pinMode(CLOCK_PIN1, OUTPUT);
  pinMode(LATCH_PIN1, OUTPUT);

  pinMode(DATA_PIN2, OUTPUT);
  pinMode(CLOCK_PIN2, OUTPUT);
  pinMode(LATCH_PIN2, OUTPUT);

  pinMode(ResetBtn, INPUT_PULLUP);

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

  currentLED1 = 0;
  currentLED2 = 0;
  updateLEDs();  // Initialize all LEDs off


}

void loop() {
  
  updateLEDs();  // Continuously update LEDs

  if (digitalRead(ResetBtn) == LOW) {  // Button pressed
    sodium = 0;
    sugar = 0;
    fiber = 0;
    currentLED1 = 0;
    currentLED2 = 0;
    updateLEDs();
    delay(500); // debounce
  }

  if (!mfrc522.PICC_IsNewCardPresent()) {
    delay(50); 
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

  if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0xD1 && mfrc522.uid.uidByte[2] == 0x34 && mfrc522.uid.uidByte[3] == 0xC8 && mfrc522.uid.uidByte[4] == 0x23
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Cheese
    Serial.println("SCANNED CHEESE");
    sodium += cheese_sodium;
    sugar += cheese_sugar;
    fiber += cheese_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x31 && mfrc522.uid.uidByte[2] == 0xCB && mfrc522.uid.uidByte[3] == 0xC9 && mfrc522.uid.uidByte[4] == 0x23
      && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Ice Cream
      Serial.println("SCANNED ICE CREAM");
      sodium += ice_cream_sodium;
      sugar += ice_cream_sugar;
      fiber += ice_cream_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x03 && mfrc522.uid.uidByte[2] == 0x1C && mfrc522.uid.uidByte[3] == 0xF0 && mfrc522.uid.uidByte[4] == 0x20
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Broccoli
    Serial.println("SCANNED BROCCOLI");
    sodium += broccoli_sodium;
    sugar += broccoli_sugar;
    fiber += broccoli_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0xA3 && mfrc522.uid.uidByte[2] == 0xFA && mfrc522.uid.uidByte[3] == 0xDF && mfrc522.uid.uidByte[4] == 0x20
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Salad
    Serial.println("SCANNED SALAD");
    sodium += salad_sodium;
    sugar += salad_sugar;
    fiber += salad_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x91 && mfrc522.uid.uidByte[2] == 0x24 && mfrc522.uid.uidByte[3] == 0xC7 && mfrc522.uid.uidByte[4] == 0x23
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Croissant
    Serial.println("SCANNED CROISSANT");
    sodium += croissant_sodium;
    sugar += croissant_sugar;
    fiber += croissant_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x81 && mfrc522.uid.uidByte[2] == 0x21 && mfrc522.uid.uidByte[3] == 0xC6 && mfrc522.uid.uidByte[4] == 0x23
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Apple
    Serial.println("SCANNED APPLE");
    sodium += apple_sodium;
    sugar += apple_sugar;
    fiber += apple_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0xF3 && mfrc522.uid.uidByte[2] == 0x69 && mfrc522.uid.uidByte[3] == 0xE1 && mfrc522.uid.uidByte[4] == 0x20
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Chicken
    Serial.println("SCANNED CHICKEN");
    sodium += chicken_sodium;
    sugar += chicken_sugar;
    fiber += chicken_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x41 && mfrc522.uid.uidByte[2] == 0x32 && mfrc522.uid.uidByte[3] == 0xC4 && mfrc522.uid.uidByte[4] == 0x23
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Burger
    Serial.println("SCANNED BURGER");
    sodium += burger_sodium;
    sugar += burger_sugar;
    fiber += burger_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x51 && mfrc522.uid.uidByte[2] == 0xD0 && mfrc522.uid.uidByte[3] == 0x7C && mfrc522.uid.uidByte[4] == 0x23
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Pizza
    Serial.println("SCANNED PIZZA");
    sodium += pizza_sodium;
    sugar += pizza_sugar;
    fiber += pizza_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x63 && mfrc522.uid.uidByte[2] == 0xE5 && mfrc522.uid.uidByte[3] == 0xE1 && mfrc522.uid.uidByte[4] == 0x20
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Ramen
    Serial.println("SCANNED RAMEN");
    sodium += ramen_sodium;
    sugar += ramen_sugar;
    fiber += ramen_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x51 && mfrc522.uid.uidByte[2] == 0x48 && mfrc522.uid.uidByte[3] == 0x86 && mfrc522.uid.uidByte[4] == 0x23
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Spaghetti
    Serial.println("SCANNED SPAGHETTI");
    sodium += spaghetti_sodium;
    sugar += spaghetti_sugar;
    fiber += spaghetti_fiber;
  }

  else if (mfrc522.uid.uidByte[0] == 0x04 && mfrc522.uid.uidByte[1] == 0x51 && mfrc522.uid.uidByte[2] == 0x43 && mfrc522.uid.uidByte[3] == 0x81 && mfrc522.uid.uidByte[4] == 0x23
    && mfrc522.uid.uidByte[5] == 0x02 && mfrc522.uid.uidByte[6] == 0x89) { // Bread
    Serial.println("SCANNED BREAD");
    sodium += bread_sodium;
    sugar += bread_sugar;
    fiber += bread_fiber;
  }

  updateNutritionLEDs();
  updateLEDs();

  flashScanIndicator();

  mfrc522.PICC_HaltA();  // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}

void updateNutritionLEDs() {
  // Clear previous nutrition indicators
  currentLED1 &= ~(0B00011111);  // Clear sugar bits (bits 0-4)
  currentLED1 &= ~(0B11100000);  // Clear sodium bits (bits 5-7)
  currentLED2 &= ~(0B00000011);  // Clear sodium bits (bits 0-1)
  currentLED2 &= ~(0B01111100);  // Clear fiber bits (bits 2-6)

  if (sugar < sl_sugar) currentLED1 |= 0B00000001;
  else if (sugar < l_sugar) currentLED1 |= 0B00000010;
  else if (sugar < rec_sugar) currentLED1 |= 0B00000100;
  else if (sugar < h_sugar) currentLED1 |= 0B00001000;
  else currentLED1 |= 0B00010000;

  if (sodium < sl_sodium) currentLED1 |= 0B00100000;
  else if (sodium < l_sodium) currentLED1 |= 0B01000000;
  else if (sodium < rec_sodium) currentLED1 |= 0B10000000;
  else if (sodium < h_sodium) currentLED2 |= 0B00000001;
  else currentLED2 |= 0B00000010;

  if (fiber < sl_fiber) currentLED2 |= 0B00000100;
  else if (fiber < l_fiber) currentLED2 |= 0B00001000;
  else if (fiber < rec_fiber) currentLED2 |= 0B00010000;
  else if (fiber < h_fiber) currentLED2 |= 0B00100000;
  else currentLED2 |= 0B01000000;

}

void updateLEDs() {
  digitalWrite(LATCH_PIN1, LOW);
  shiftOut(DATA_PIN1, CLOCK_PIN1, LSBFIRST, currentLED1);
  digitalWrite(LATCH_PIN1, HIGH);

  digitalWrite(LATCH_PIN2, LOW);
  shiftOut(DATA_PIN2, CLOCK_PIN2, LSBFIRST, currentLED2);
  digitalWrite(LATCH_PIN2, HIGH);
}

void flashScanIndicator() {
  // Save current LED states
  byte prevLED1 = currentLED1;
  byte prevLED2 = currentLED2;

  // Turn off all LEDs
  currentLED1 = 0;
  currentLED2 = 0;
  updateLEDs();

  // Flash the scan indicator LED (only bit 7 of shift register 2)
  digitalWrite(LATCH_PIN2, LOW);
  shiftOut(DATA_PIN2, CLOCK_PIN2, LSBFIRST, 0B10000000);
  digitalWrite(LATCH_PIN2, HIGH);
  delay(500);

  // Restore previous LED states
  currentLED1 = prevLED1;
  currentLED2 = prevLED2;
  updateLEDs();
}
