#include <Wire.h>
#include <BH1750.h>
#include <LiquidCrystal.h>
#include <dht.h>
#define DHT11_PIN 10

dht DHT;
int led = 9;
BH1750 lightMeter;
long luxa;
long ygr;
long ther;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){

  Serial.begin(9600);
  pinMode (led,OUTPUT); //led or relay pin
  Wire.begin();
  lightMeter.begin();

}

long metrhsh()
  {
    uint16_t lux;
    lux = lightMeter.readLightLevel();
    return lux;
    delay(100);
  }

void loop() {
  int chk = DHT.read11(DHT11_PIN);
  luxa = metrhsh();
  ther = DHT.temperature - 1; // -1 for correction
  ygr = DHT.humidity + 2; // +2 for correction
  
  Serial.print("Light: ");
  Serial.print(luxa);
  Serial.println(" lx");
  delay(500);
  Serial.print("YGRASIA: ");
  Serial.print(ygr);
  Serial.println(" %");
  delay(500);
  Serial.print("THERMOKRASIA: ");
  Serial.print(ther);
  Serial.print((char)223);
  Serial.println(" C");
  delay(500);
  
  if (luxa < 10)
    {
      digitalWrite(led, HIGH);
      lcd.begin(16, 2);
      lcd.setCursor(0,0);
      lcd.print("Hm: ");
      lcd.setCursor(4,0);
      lcd.print(ygr); 
      lcd.setCursor(6,0);
      lcd.print("%");       
      lcd.setCursor(9,0);
      lcd.print("Lux: ");
      lcd.setCursor(13,0);
      lcd.print(luxa);
      lcd.setCursor(3,1);
      lcd.print("Temp: ");
      lcd.setCursor(9,1);
      lcd.print(ther);
      lcd.setCursor(11,1);
      lcd.print((char)223);
      lcd.setCursor(12,1);
      lcd.print("C");
      delay(500);
    }
  else
    {
      digitalWrite(led, LOW);
      lcd.begin(16, 2);
      lcd.setCursor(0,0);
      lcd.print("Hm: ");
      lcd.setCursor(4,0);
      lcd.print(ygr); 
      lcd.setCursor(6,0);
      lcd.print("%");
      lcd.setCursor(9,0);
      lcd.print("Lux: ");
      lcd.setCursor(13,0);
      lcd.print(luxa);
      lcd.setCursor(3,1);
      lcd.print("Temp: ");
      lcd.setCursor(9,1);
      lcd.print(ther);
      lcd.setCursor(11,1);
      lcd.print((char)223);
      lcd.setCursor(12,1);
      lcd.print("C");
      delay(500);
    }

}
