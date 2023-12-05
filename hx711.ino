#include "HX711.h"
#include "LiquidCrystal_PCF8574.h"

LiquidCrystal_PCF8574 lcd(0x27); 


const int DT_PIN = 6;
const int SCK_PIN = 5;

const int scale_factor = 324; 
HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing the scale");

  scale.begin(DT_PIN, SCK_PIN);
  lcd.begin(16, 2); 
  lcd.setBacklight(255);
  lcd.clear();

  Serial.println("Before setting up the scale:"); 
  
  Serial.println(scale.get_units(5), 0); 

  scale.set_scale(scale_factor);      
  scale.tare();            

  Serial.println("After setting up the scale:"); 

  Serial.println(scale.get_units(5), 0);  

  Serial.println("Readings:");  
}

void loop() {
  
  Serial.println(scale.get_units(10), 0); 
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Weight: ");
  lcd.setCursor(9, 0);
  float weight = scale.get_units(10) * 0.7246376812;

  if(weight<=0){
    weight = 0;
  }
  lcd.print(weight,0);
  lcd.setCursor(13, 0);
  lcd.print("g");
  scale.power_down();            
  delay(500);
  scale.power_up();        
}
