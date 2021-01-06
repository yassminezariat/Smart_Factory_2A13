#include "SPI.h"
#include "MFRC522.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20,4);

String str;


MFRC522 rfid(10,9);

MFRC522::MIFARE_Key key;

void setup() {
    SPI.begin();
    rfid.PCD_Init();
    Serial.begin(9600);
    lcd.init();
}

void loop() {
  
  if(Serial.available()){
    str=Serial.readString();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print(str);
    delay(3000);
    lcd.clear();
  }   
  
          if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

  //Serial.print("Tap card key: ");
  Serial.println(strID);

  if (strID.indexOf("") >= 0) {
    
        
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
