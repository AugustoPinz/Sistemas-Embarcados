/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 6, Transportadora de Peças (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoMovendoM1 = 1;
const int EstadoAvancandoC1 = 2;
const int EstadoAvancandoC2 = 3;
const int EstadoMovendoM2 = 4;
const int EstadoRecuandoCilindros = 5;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS1 = 4;
const int SensorS2 = 5;
const int SensorS3 = 6;
const int SensorS4 = 7;
const int SensorC1Recuado = 8;
const int SensorC2Recuado = 9;
const int MotorM1 = 10;
const int MotorM2 = 11;
const int AtuadorCilindroC1 = 12;
const int AtuadorCilindroC2 = 13;
const int LampadaLigada = A0;
int EstadoAtual = EstadoAguardandoStart;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(SensorS4, INPUT_PULLUP);
  pinMode(SensorC1Recuado, INPUT_PULLUP);
  pinMode(SensorC2Recuado, INPUT_PULLUP);
  pinMode(MotorM1, OUTPUT);
  pinMode(MotorM2, OUTPUT);
  pinMode(AtuadorCilindroC1, OUTPUT);
  pinMode(AtuadorCilindroC2, OUTPUT);
  pinMode(LampadaLigada, OUTPUT);
  desligarAtuadores();
}

void loop() {
  if (digitalRead(BotaoStop) == LOW) {
    EstadoAtual = EstadoAguardandoStart;
  }

  switch (EstadoAtual) {

    case EstadoAguardandoStart:
      desligarAtuadores();
      if (digitalRead(BotaoStart) == LOW) {
        digitalWrite(LampadaLigada, HIGH);
        EstadoAtual = EstadoMovendoM1;
      }
      break;

    case EstadoMovendoM1:
      digitalWrite(MotorM1, HIGH);
      if (digitalRead(SensorS2) == LOW) {
        digitalWrite(MotorM1, LOW);
        EstadoAtual = EstadoAvancandoC1;
      }
      break;

    case EstadoAvancandoC1:
      digitalWrite(AtuadorCilindroC1, HIGH);
      if (digitalRead(SensorS1) == LOW) {
        EstadoAtual = EstadoAvancandoC2;
      }
      break;

    case EstadoAvancandoC2:
      digitalWrite(AtuadorCilindroC2, HIGH);
      if (digitalRead(SensorS3) == LOW) {
        EstadoAtual = EstadoMovendoM2;
      }
      break;

    case EstadoMovendoM2:
      digitalWrite(MotorM2, HIGH);
      if (digitalRead(SensorS4) == LOW) {
        digitalWrite(MotorM2, LOW);
        EstadoAtual = EstadoRecuandoCilindros;
      }
      break;

    case EstadoRecuandoCilindros:
      digitalWrite(AtuadorCilindroC1, LOW);
      digitalWrite(AtuadorCilindroC2, LOW);
      if (digitalRead(SensorC1Recuado) == LOW && digitalRead(SensorC2Recuado) == LOW) {
        EstadoAtual = EstadoAguardandoStart;
      }
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(MotorM1, LOW);
  digitalWrite(MotorM2, LOW);
  digitalWrite(AtuadorCilindroC1, LOW);
  digitalWrite(AtuadorCilindroC2, LOW);
  digitalWrite(LampadaLigada, LOW);
}