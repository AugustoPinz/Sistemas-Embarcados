/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 3, Envasamento e Coroamento de Garrafas (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */
const int EstadoEspera = 0; 
const int EstadoEsteiraM1 = 1; 
const int EstadoCoroamentoDESC = 2; 
const int EstadoCoroamentoAguarda = 3; 
const int EstadoCoroamentoSub = 4; 
const int EstadoAlarmeFalha = 5; 
const int BotaoStart = 2;   
const int BotaoStop = 3;   
const int SensorST1 = 4;   
const int SensorSP1 = 5;   
const int SensorST2 = 6;   
const int SensorSR = 7;   
const int SensorSA = 8;   
const int MotorM1 = 9;  
const int MotorCRDescer = 10; 
const int MotorCRSubir = 11; 
const int AlarmeFT = 12; 
const int AlarmeFC = 13; 
int EstadoAtual = EstadoEspera; 
unsigned long TempoCR = 0;
int ContadorGarrafas = 0;
bool GarrafaEmP2 = false; 

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorST1, INPUT_PULLUP);
  pinMode(SensorSP1, INPUT_PULLUP);
  pinMode(SensorST2, INPUT_PULLUP);
  pinMode(SensorSR, INPUT_PULLUP);
  pinMode(SensorSA, INPUT_PULLUP);
  pinMode(MotorM1, OUTPUT);
  pinMode(MotorCRDescer, OUTPUT);
  pinMode(MotorCRSubir, OUTPUT);
  pinMode(AlarmeFT, OUTPUT);
  pinMode(AlarmeFC, OUTPUT);
  desligarAtuadores();
}

void loop() {
  if (digitalRead(BotaoStop) == LOW) {
    EstadoAtual = EstadoEspera;
  }
  if (digitalRead(SensorST1) == HIGH && EstadoAtual != EstadoAlarmeFalha) {
    digitalWrite(AlarmeFT, HIGH); 
    digitalWrite(MotorM1, LOW);   
    if (EstadoAtual == EstadoEsteiraM1) {
      EstadoAtual = EstadoEspera;  
    }
  } else {
    digitalWrite(AlarmeFT, LOW); 
  }
  if (ContadorGarrafas >= 24 && EstadoAtual != EstadoAlarmeFalha) {
    EstadoAtual = EstadoEspera;
  }
  switch (EstadoAtual) {
    
    case EstadoEspera:
      desligarAtuadores();
      if (digitalRead(BotaoStart) == LOW) {
        if (ContadorGarrafas >= 24) {
          ContadorGarrafas = 0;
        }
        if (digitalRead(SensorST1) == LOW) { 
          EstadoAtual = EstadoEsteiraM1;
        }
      }
      break;
    case EstadoEsteiraM1:
      digitalWrite(MotorM1, HIGH);
      digitalWrite(MotorCRDescer, LOW);
      digitalWrite(MotorCRSubir, LOW);
      if (digitalRead(SensorSP1) == LOW) {
        digitalWrite(MotorM1, LOW); 
        EstadoAtual = EstadoCoroamentoDESC;
      }
      break;
    case EstadoCoroamentoDESC:
      digitalWrite(MotorCRDescer, HIGH);
      if (digitalRead(SensorSA) == LOW) {
        digitalWrite(MotorCRDescer, LOW);
        TempoCR = millis(); 
        EstadoAtual = EstadoCoroamentoAguarda;
      }
      break;
    case EstadoCoroamentoAguarda:
      if (millis() - TempoCR >= 2000) {
        EstadoAtual = EstadoCoroamentoSub;
      }
      break;
      
    case EstadoCoroamentoSub:
      digitalWrite(MotorCRSubir, HIGH);
      if (digitalRead(SensorSR) == LOW) {
        digitalWrite(MotorCRSubir, LOW);
        if (GarrafaEmP2) {
          if (digitalRead(SensorST2) == HIGH) { 
            EstadoAtual = EstadoAlarmeFalha;
            break; 
          } else {
            ContadorGarrafas++; 
          }
        }
        GarrafaEmP2 = true; 
        EstadoAtual = EstadoEsteiraM1;
      }
      break;
    case EstadoAlarmeFalha:
      desligarAtuadores();
      digitalWrite(AlarmeFC, HIGH); 
      if (digitalRead(BotaoStart) == LOW) {
        digitalWrite(AlarmeFC, LOW);
        GarrafaEmP2 = false; 
        EstadoAtual = EstadoEsteiraM1; 
      }
      break;
  }
  delay(50); 
}
void desligarAtuadores() {
  digitalWrite(MotorM1, LOW);
  digitalWrite(MotorCRDescer, LOW);
  digitalWrite(MotorCRSubir, LOW);
}