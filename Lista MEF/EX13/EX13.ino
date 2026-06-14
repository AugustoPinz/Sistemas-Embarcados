/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 13, Transportadora de Peças com Limite (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoAguardandoPecaS1 = 1;
const int EstadoMovendoM1 = 2;
const int EstadoMovendoM2 = 3;
const int EstadoLimiteAtingido = 4;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS1 = 4;
const int SensorS2 = 5;
const int SensorS3 = 6;
const int MotorM1 = 7;
const int MotorM2 = 8;
const int LampadaLigada = 9;
const int LampadaLimite = 10;
int EstadoAtual = EstadoAguardandoStart;
int ContadorCiclos = 0;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(MotorM1, OUTPUT);
  pinMode(MotorM2, OUTPUT);
  pinMode(LampadaLigada, OUTPUT);
  pinMode(LampadaLimite, OUTPUT);
  desligarAtuadores();
}

void loop() {
  if (digitalRead(BotaoStop) == LOW) {
    if (EstadoAtual == EstadoLimiteAtingido) {
      ContadorCiclos = 0;
      digitalWrite(LampadaLimite, LOW);
    }
    EstadoAtual = EstadoAguardandoStart;
  }

  switch (EstadoAtual) {

    case EstadoAguardandoStart:
      desligarAtuadores();
      if (digitalRead(BotaoStart) == LOW && ContadorCiclos < 5) {
        digitalWrite(LampadaLigada, HIGH);
        EstadoAtual = EstadoAguardandoPecaS1;
      }
      break;

    case EstadoAguardandoPecaS1:
      if (digitalRead(SensorS1) == LOW) {
        digitalWrite(MotorM1, HIGH);
        EstadoAtual = EstadoMovendoM1;
      }
      break;

    case EstadoMovendoM1:
      if (digitalRead(SensorS2) == LOW) {
        digitalWrite(MotorM1, LOW);
        digitalWrite(MotorM2, HIGH);
        EstadoAtual = EstadoMovendoM2;
      }
      break;

    case EstadoMovendoM2:
      if (digitalRead(SensorS3) == LOW) {
        digitalWrite(MotorM2, LOW);
        ContadorCiclos++;
        
        if (ContadorCiclos >= 5) {
          digitalWrite(LampadaLigada, LOW);
          digitalWrite(LampadaLimite, HIGH);
          EstadoAtual = EstadoLimiteAtingido;
        } else {
          EstadoAtual = EstadoAguardandoStart;
        }
      }
      break;

    case EstadoLimiteAtingido:
      desligarAtuadores();
      digitalWrite(LampadaLimite, HIGH);
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(MotorM1, LOW);
  digitalWrite(MotorM2, LOW);
  digitalWrite(LampadaLigada, LOW);
}