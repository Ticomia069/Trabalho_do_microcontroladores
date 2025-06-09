#include <Servo.h>
#include <LiquidCrystal.h>

// Pinos
const int potPin = A0;
const int servoPin = 9;
const int ledVerde = 6;
const int ledAmarelo = 7;
const int ledVermelho = 8;
const int botaoPin = 10;

int potValue = 0;
float tensao = 0.0;
Servo servo;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP); // Puxado para HIGH internamente

  servo.attach(servoPin);
  lcd.begin(16, 2);
  lcd.print("Monitor Agua");
  delay(1500);
  lcd.clear();
}

void loop() {
  potValue = analogRead(potPin);
  tensao = (potValue * 5.0) / 1023.0;

  // Controle dos LEDs baseado no valor do potenciômetro
  if(potValue < 341) {           // Baixo nível
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, LOW);
  } else if(potValue < 682) {    // Médio nível
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, HIGH);
    digitalWrite(ledVermelho, LOW);
  } else {                       // Alto nível
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledAmarelo, LOW);
    digitalWrite(ledVermelho, HIGH);
  }

  // Controle do Servo Motor conforme potenciômetro
  int angulo = map(potValue, 0, 1023, 0, 180);
  servo.write(angulo);

  // Exibir no LCD
  lcd.setCursor(0, 0);
  lcd.print("Pot: ");
  lcd.print(potValue);
  lcd.setCursor(0, 1);
  lcd.print("V: ");
  lcd.print(tensao, 2);
  lcd.print("V   ");

  // Verifica Botão
  if(digitalRead(botaoPin) == LOW) { // Pressionado
    servo.write(0); // Reset Servo
    lcd.clear();
    lcd.print("Resetado!");
    delay(1000);
    lcd.clear();
  }

  delay(200);
}
