#include<LiquidCrystal.h>
LiquidCrystal lcd (2, 3, 4, 5, 6, 8);
#include  "HX711.h"
#define DOUT  12
#define CLK  13
#define MOTOR_A 11
#define MOTOR_B 10
HX711 scale(DOUT, CLK);
float calibration_factor = -96650;
void setup() {

  pinMode(MOTOR_A, OUTPUT);
  pinMode(MOTOR_B, OUTPUT);

  scale.set_scale();
  scale.tare();
}

void loop() {
  Serial.begin(9600);
  lcd.print("WELCOME");
  delay(500);
  lcd.clear();
  if (Serial.available()) {
    char data = Serial.read();

    if (data == 'n') {

      lcd.print("PRESSING....");
      delay(5000);
      lcd.clear();
      digitalWrite(MOTOR_A, HIGH);
      digitalWrite(MOTOR_B, LOW);
      while (!Serial.available() && data == 'n') {
        scale.set_scale(calibration_factor + 2);
        lcd.print("Reading: ");
        lcd.print(scale.get_units(), 3);
        lcd.println(" kg");
        delay(500);
        lcd.clear(); //hea deh loop aly 3ayz atl3 mnha lam ade ay 7aga tanya 8er l n

      }
      delay(5000);
      lcd.clear();
    }



    if (data == 'f') {
      lcd.print("PRESS IS OFF");
      delay(5000);
      lcd.clear();
      digitalWrite(MOTOR_A, LOW);
      digitalWrite(MOTOR_B, HIGH);


    }

    if ( data == 's') {

      lcd.print("THE PRESS IS Off");
      digitalWrite(MOTOR_A, LOW);
      digitalWrite(MOTOR_B, LOW);
    }

  }

}
