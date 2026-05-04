const int sensores[4] = {A0, A1, A2, A3};

void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int leitura = analogRead(sensores[i]);
    
    Serial.print("Sensor");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(leitura);
    Serial.print(" ");
  }
  
  Serial.println(); 
  delay(500);       
}
