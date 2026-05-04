#include <Ultrasonic.h>
Ultrasonic ultrasonic(12, 13);
int distance;
int leds[4] = {9, 8, 7, 6}; 
const int botao = 2; 

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
  }
  pinMode(botao, INPUT_PULLUP);
}
void loop() {
  
  if (digitalRead(botao) == LOW) {
    distance = ultrasonic.read();
    apagarTodosLeds();
    if (distance > 0 && distance <= 10) {
      ligarQuantidadeLeds(4); 
    } 
    else if (distance > 10 && distance <= 20) {
      ligarQuantidadeLeds(3); 
    } 
    else if (distance > 20 && distance <= 30) {
      ligarQuantidadeLeds(2); 
    } 
    else if (distance > 30 && distance <= 40) {
      ligarQuantidadeLeds(1); 
    } 
   
  } 
  else {
    apagarTodosLeds();
  }
  
  delay(100); 
}
void apagarTodosLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(leds[i], LOW);
  }
}
void ligarQuantidadeLeds(int qtd) {
  for (int i = 0; i < qtd; i++) {
    digitalWrite(leds[i], HIGH);
  }
}
}