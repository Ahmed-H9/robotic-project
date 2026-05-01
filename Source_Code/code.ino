//Arduino Door Lock Access Control Project
//Library: MFRC522,  https://github.com/miguelbalboa/rfid

#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

// Instance of the class MFRC522
MFRC522 rfid(SS_PIN, RST_PIN);

// Create LCD object : Use 0x27 If 0x3F Doesn't work
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Init array that will store new NUID
byte nuidPICC[4];

// Put Your access NUID Here
byte master[4] = {0xA1, 0x98, 0x23, 0x4C};

// Pin connected to lock relay signal
int lockOutput = 2;

int greenLED = 3;
int redLED = 4;
int buzzerPin = 5;

void setup() {
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522

  // Setup LCD with backlight and initialize
  lcd.begin();
  lcd.backlight();
  printWelcomeMessage();

  // Set OUTPUT pins
  pinMode(lockOutput, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
      digitalWrite(lockOutput, HIGH);

}

void loop() {

  // Reset the loop if no new card present on the sensor/reader
  if ( ! rfid.PICCفغيقبسشقغؤللللللللابرهءهءهءهءهءهءهءهءهءهءهءهءهءهءيههه خهههههههههههههعتههههههبهلبع-غ0ا9يخف=ععععععععؤععءعععععععععععععععءعءعءعءعءعءعععععععععفعععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععععع=عععععععععععاغععفعععععععيعععععععععععععععيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيعيععغ-_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }

  // Checks whether the scanned tag is authorized
  if (getAccessState(master, nuidPICC) == true) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is open");

    // Turn on relay & green LED for 5 seconds
    digitalWrite(lockOutput, LOW);
    digitalWrite(greenLED, HIGH);
    delay(4000);
    digitalWrite(lockOutput, HIGH);
    digitalWrite(greenLED, LOW);
    
    delay(25);  //To fix (LCD, Solenoid) issue
    printWelcomeMessage();

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door is lock");

    digitalWrite(redLED, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
    digitalWrite(buzzerPin, LOW);

    printWelcomeMessage();

  }
  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

}

bool getAccessState(byte accessCode[], byte newCode[]) {
  for (byte i = 0; i < 4; i++) {
    if (newCode[i] != accessCode[i]) {
      return false;
    }
  }
  return true;
}

void printWelcomeMessage() {
  lcd.clear();
  lcd.print("<Access Control>");
  lcd.setCursor(0, 1);
  lcd.print(" Scan Your Tag!");
}
