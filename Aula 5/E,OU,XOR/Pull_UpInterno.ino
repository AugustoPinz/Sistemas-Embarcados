const int pin_botao1 = 2;
const int pin_botao2 = 3;
bool botao1 = false;
bool botao2 = false;
const int led_vermelho = 5;			
const int led_verde = 6;			
const int led_amarelo = 7;			
char led;	

void setup() {
  pinMode(pin_botao1, INPUT_PULLUP);
  pinMode(pin_botao2, INPUT_PULLUP);
  pinMode(led_vermelho, OUTPUT);		
  pinMode(led_verde, OUTPUT);			
  pinMode(led_amarelo, OUTPUT);	
}

void loop() {
  botao1 = digitalRead(pin_botao1);
  botao2 = digitalRead(pin_botao2);
  if (botao1 == LOW  && botao2 == LOW) {
    digitalWrite(led_vermelho, HIGH);
  }
  else {
    digitalWrite(led_vermelho, LOW);
  }

  if (botao1 == LOW || botao2 == LOW) {
    digitalWrite(led_verde, HIGH);
  }
  else {
    digitalWrite(led_verde, LOW);
  }
  if (botao1 == LOW ^ botao2 == LOW) {
    digitalWrite(led_amarelo, HIGH);
  }
  else {
    digitalWrite(led_amarelo, LOW);
  }
}
