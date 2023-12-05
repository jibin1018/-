#include <Wire.h>
#include "HX711.h"
#include "LiquidCrystal_PCF8574.h"

LiquidCrystal_PCF8574 lcd(0x27);

int initialWeight = 5300;    // 무게 비율1
int totalWeight = 0;

int maxWeight = 7500;        // 무게 비율2
int syrupThreshold = 300;    // 시럽이 없다고 판단할 무게 임계값
int backlightDelay = 50;    // 백라이트 딜레이 값

// 아두이노 보드에 연결된 HX711 연결 포트
const int DT_PIN_1 = 6;
const int SCK_PIN_1 = 5;
const int DT_PIN_2 = 10;
const int SCK_PIN_2 = 9;

// 로드셀에 측정된 무게를 g으로 변환
const int scale_factor_master = 324;

HX711 scale_master_1;
HX711 scale_master_2;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(16, 2);
  lcd.setBacklight(255);
  lcd.clear();

  // 초기 무게 설정
  int initialToCurrentRatio = map(initialWeight, 0, maxWeight, 0, 100);
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Total Weight");
  lcd.setCursor(5, 1);
  lcd.print(String(initialToCurrentRatio) + "%");
  delay(2000);

  scale_master_1.begin(DT_PIN_1, SCK_PIN_1);
  scale_master_2.begin(DT_PIN_2, SCK_PIN_2);

  Serial.println("Before setting up the scales (Master):");
  Serial.println(scale_master_1.get_units(5), 0);
  Serial.println(scale_master_2.get_units(5), 0);

  scale_master_1.set_scale(scale_factor_master);
  scale_master_2.set_scale(scale_factor_master);

  scale_master_1.tare();
  scale_master_2.tare();

  Serial.println("After setting up the scales (Master):");
  Serial.println(scale_master_1.get_units(5), 0);
  Serial.println(scale_master_2.get_units(5), 0);
  Serial.println("Readings (Master):");
}

void loop() {
  // Master에서 무게 측정
  int weight_master_1 = scale_master_1.get_units(10) * 0.7246376812;
  int weight_master_2 = scale_master_2.get_units(10) * 0.7246376812;

  totalWeight = weight_master_1 + weight_master_2;

  // 무게가 500g 미만이면 백라이트와 함께 "not enough syrup" 표시
  if (totalWeight < syrupThreshold) {
    lcd.clear();
    lcd.setBacklight(0);
    lcd.setCursor(3, 0);
    lcd.print("not enough");
    lcd.setCursor(5, 1);
    lcd.print("syrup");
    delay(backlightDelay);
    lcd.setBacklight(255);
    delay(backlightDelay);

  } 
  else if (530 < totalWeight && totalWeight < 5300) {
    // 현재 무게에 대한 초기 무게 비율을 계산
    int initialToCurrentRatio = map(totalWeight, 0, initialWeight, 0, 100);

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Total Weight");
    lcd.setCursor(3, 1);
    lcd.print(String(totalWeight) + "g, " + String(initialToCurrentRatio) + "%");

  } 
  else if (totalWeight > 5300) {
    // 현재 무게에 대한 초기 무게 비율을 계산
    int initialToCurrentRatio = map(totalWeight, 0, maxWeight, 0, 100);

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Total Weight");
    lcd.setCursor(3, 1);
    lcd.print(String(totalWeight) + "g, " + String(initialToCurrentRatio) + "%");
  }
  else if (syrupThreshold < totalWeight && totalWeight < 530){

    int initialToCurrentRatio = map(totalWeight, 0, initialWeight, 0, 100);

    lcd.clear();
    lcd.setBacklight(0);
    lcd.setCursor(2, 0);
    lcd.print("Total Weight");
    lcd.setCursor(3, 1);
    lcd.print(String(totalWeight) + "g, " + String(initialToCurrentRatio) + "%");
    delay(backlightDelay);
    lcd.setBacklight(255);
    delay(backlightDelay);

  }


  delay(1000);
}





