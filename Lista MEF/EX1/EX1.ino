/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 1, MEF (Máquina de Estados Finitos)

Autor: Augusto Bredlau Pinz
Data: 13/06/2026
Versão: 1.0

************************************************************************ */

const int MANUAL = 0;
const int AUTOMATICO = 1;
const int BotaoManual = 2;
const int BotaoAuto = 3;
const int BotaoLiga = 4;
const int BotaoDesliga = 5;
const int SensorBaixo = 6;
const int SensorAlto = 7;
const int LedManual = 8;
const int LedAuto = 9;
const int LedBomba = 10;
bool EstadoBomba = LOW;
unsigned long TempoInicioBaixo = 0;
unsigned long TempoInicioAlto = 0;
bool TempoBaixoAtivo = false;
bool TempoAltoAtivo = false;
int ModoAtual = MANUAL;
void setup() {
  pinMode(BotaoManual, INPUT_PULLUP);
  pinMode(BotaoAuto, INPUT_PULLUP);
  pinMode(BotaoLiga, INPUT_PULLUP);
  pinMode(BotaoDesliga, INPUT_PULLUP);
  pinMode(SensorBaixo, INPUT_PULLUP);
  pinMode(SensorAlto, INPUT_PULLUP);
  pinMode(LedManual, OUTPUT);
  pinMode(LedAuto, OUTPUT);
  pinMode(LedBomba, OUTPUT);
}

void loop() {
  if (digitalRead(BotaoManual) == LOW){
    ModoAtual = MANUAL;
    TempoBaixoAtivo = false;
    TempoAltoAtivo = false;
  }
  if (digitalRead(BotaoAuto) == LOW){
    ModoAtual = AUTOMATICO;
    TempoBaixoAtivo = false;
    TempoAltoAtivo = false;
  }
  switch (ModoAtual) {
    
    case MANUAL:
      digitalWrite(LedManual, HIGH);
      digitalWrite(LedAuto, LOW);
      if (digitalRead(BotaoLiga) == LOW) {
        EstadoBomba = HIGH; 
      }
      if (digitalRead(BotaoDesliga) == LOW) {
        EstadoBomba = LOW;
      }
      break;
    case AUTOMATICO:
      digitalWrite(LedManual, LOW);
      digitalWrite(LedAuto, HIGH);
      if (digitalRead(SensorBaixo) == LOW && EstadoBomba == LOW) {
        if (!TempoBaixoAtivo) {
          TempoInicioBaixo = millis();
          TempoBaixoAtivo = true;
        }
        if (millis() - TempoInicioBaixo >= 10000) {
          EstadoBomba = HIGH; 
          TempoBaixoAtivo = false;
        }
      } else {
        TempoBaixoAtivo = false; 
      }
      if (digitalRead(SensorAlto) == LOW && EstadoBomba == HIGH) {
        if (!TempoAltoAtivo) {
          TempoInicioAlto = millis();
          TempoAltoAtivo = true;
        }
        if (millis() - TempoInicioAlto >= 10000) {
          EstadoBomba = LOW;
          TempoAltoAtivo = false;
        }
      } else {
        TempoAltoAtivo = false; 
      }
      break;
  }
  digitalWrite(LedBomba, EstadoBomba);
  delay(50); 
}