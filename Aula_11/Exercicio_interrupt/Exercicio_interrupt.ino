const int ledPin = 9;
const int BotaoLigar = 2;//InterruptPinA
const int BotaoDesligar = 3;//InterruptPinB
volatile bool state = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(BotaoLigar, INPUT_PULLUP);
  pinMode(BotaoDesligar, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BotaoLigar), ligar, FALLING);
  attachInterrupt(digitalPinToInterrupt(BotaoDesligar), desligar, FALLING);
}

void loop() {
  digitalWrite(ledPin, state);
}


void ligar() {
  state = HIGH;
}
void desligar() {
  state = LOW;
}