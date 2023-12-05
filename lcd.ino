#include <LiquidCrystal_I2C.h> // LCD 모듈을 사용하기 위한 라이브러리
#include <Wire.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2); //라이브러리를 이용한 객체 생성, 0x27-모듈주소, 16은 행 2는 열을 나타냅니다.

void setup() {
  lcd.begin();  // LCD 모듈 초기화 
  lcd.backlight();//LCD 백라이트 ON

}
void loop() {
 lcd.setCursor(3,0); // 글자가 출력될 좌표를 설정합니다. LCD상의 커서를 (0,0으로 이동)
 lcd.print("not enough"); //  Hello,BP Lab! 출력
 lcd.setCursor(5,1); // 글자가 출력될 좌표를 설정합니다. LCD상의 커서를 (0,0으로 이동)
 lcd.print("syrup"); 
 delay(00); // 화면에 글자가 보이는 시간을 설정합니다.
 lcd.clear();// LCD화면을 초기화 합니다.
 delay(200);// 초기화 유지 시간을 설정합니다.
}