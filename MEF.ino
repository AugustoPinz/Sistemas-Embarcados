int SensorCaixaBaixa = 8;
int SensorCaixaAlta = 9;
int SensorContagemAlta = 10;
int SensorContagemBaixa = 11;
const int botao_start =  2;
const int botao_stop = 3;
int estado = 0;
unsigned long tempo_ant = 0, tempo_atual = 0;
const int IN1 = 8;
const int IN2 = 9;
int ContagemBaixa = 0;
int ContagemAlta = 0;

void setup() {
  pinMode(botao_start, INPUT_PULLUP);
  pinMode(botao_stop, INPUT_PULLUP);
  pinMode(SensorCaixaBaixa, INPUT); 
  pinMode(SensorCaixaAlta, INPUT); 
  pinMode(SensorContagemBaixa, INPUT); 
  pinMode(SensorContagemAlta, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  bool stop = digitalRead(botao_stop);
  if (stop == 0){
    estado = 0;
  }

switch(estado){
  case 0:
    bool start = digitalRead(botao_start);
    if (start == 0){
    estado = 1;
    tempo_ant = millis();
    }
    break;

  case 1:
    tempo_atual = millis();
    if (tempo_atual - tempo_ant > 2000){
      estado = 2;
    }
    break;
  
  case 2:
    int CaixaAlta = digitalRead(SensorCaixaAlta);
    int CaixaBaixa = digitalRead(SensorCaixaBaixa);
    if ((CaixaAlta = HIGH) && (CaixaBaixa = HIGH)){
      estado = 3;
    }
    if ((CaixaAlta = LOW) && (CaixaBaixa = HIGH)){
      estado = 4;
    }
    break;

  case 3: 
    int ContagemCaixaAlta = digitalRead(SensorContagemAlta);
    
    digitalWrite(IN1, LOW);//Anti-horário
    digitalWrite(IN2, HIGH);
    
    if(ContagemCaixaAlta = HIGH){
      estado = 5;
    }
    break;
  
  case 4:
    int ContagemCaixaBaixa = digitalRead(SensorContagemBaixa);
    
    digitalWrite(IN1, HIGH);//Horário
    digitalWrite(IN2, LOW);
    
    if(ContagemCaixaBaixa = HIGH){
      estado = 6;
    }
    break; 

  case 5:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      ContagemAlta ++;
      estado = 1;
    break;

  case 6:
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      ContagemBaixa ++;
      estado = 1;
    break;

  default:
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    estado = 0;
    break;

}
}

