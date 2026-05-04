int botao = 3;
void setup() {
 pinMode(botao, INPUT);
 Serial.begin(115200);
 
 while(digitalRead(botao) == LOW){
 Serial.println("Aguardando botão...");
 delay(500);
 }
 Serial.println("Botão pressionado");
}
void loop() {
}
