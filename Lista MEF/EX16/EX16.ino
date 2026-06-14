/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 16, Classificador de Garrafas por Tamanho (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoMovendoEsteira = 1;
const int EstadoAnaliseSensores = 2;
const int EstadoAlarmeIncompativel = 3;
const int BotoeiraL = 2;
const int BotoeiraD = 3;
const int SensorA = 4;
const int SensorB = 5;
const int SensorC = 6;
const int ChaveP = 7;
const int ChaveM = 8;
const int ChaveG = 9;
const int MotorE = 10;
const int AlarmeAL = 11;
int EstadoAtual = EstadoAguardandoStart;
int TamanhoDetectado = 0;
int TamanhoSelecionado = 0;

void setup() {
  pinMode(BotoeiraL, INPUT_PULLUP);
  pinMode(BotoeiraD, INPUT_PULLUP);
  pinMode(SensorA, INPUT_PULLUP);
  pinMode(SensorB, INPUT_PULLUP);
  pinMode(SensorC, INPUT_PULLUP);
  pinMode(ChaveP, INPUT_PULLUP);
  pinMode(ChaveM, INPUT_PULLUP);
  pinMode(ChaveG, INPUT_PULLUP);
  pinMode(MotorE, OUTPUT);
  pinMode(AlarmeAL, OUTPUT);
  desligarAtuadores();
}

void loop() {
  if (digitalRead(BotoeiraD) == LOW) {
    EstadoAtual = EstadoAguardandoStart;
  }

  switch (EstadoAtual) {

    case EstadoAguardandoStart:
      desligarAtuadores();
      if (digitalRead(BotoeiraL) == LOW) {
        EstadoAtual = EstadoMovendoEsteira;
      }
      break;

    case EstadoMovendoEsteira:
      digitalWrite(MotorE, HIGH);
      digitalWrite(AlarmeAL, LOW);
      if (digitalRead(SensorA) == LOW || digitalRead(SensorB) == LOW || digitalRead(SensorC) == LOW) {
        EstadoAtual = EstadoAnaliseSensores;
      }
      break;

    case EstadoAnaliseSensores:
      if (digitalRead(SensorA) == LOW && digitalRead(SensorB) == LOW && digitalRead(SensorC) == LOW) {
        TamanhoDetectado = 3;
      } else if (digitalRead(SensorA) == LOW && digitalRead(SensorB) == LOW) {
        TamanhoDetectado = 2;
      } else if (digitalRead(SensorA) == LOW) {
        TamanhoDetectado = 1;
      } else {
        TamanhoDetectado = 0;
      }

      if (digitalRead(ChaveP) == LOW) {
        TamanhoSelecionado = 1;
      } else if (digitalRead(ChaveM) == LOW) {
        TamanhoSelecionado = 2;
      } else if (digitalRead(ChaveG) == LOW) {
        TamanhoSelecionado = 3;
      }

      if (TamanhoDetectado > 0) {
        if (TamanhoDetectado == TamanhoSelecionado) {
          EstadoAtual = EstadoMovendoEsteira;
        } else {
          digitalWrite(MotorE, LOW);
          EstadoAtual = EstadoAlarmeIncompativel;
        }
      } else {
        EstadoAtual = EstadoMovendoEsteira;
      }
      break;

    case EstadoAlarmeIncompativel:
      digitalWrite(MotorE, LOW);
      digitalWrite(AlarmeAL, HIGH);
      if (digitalRead(SensorA) == HIGH && digitalRead(SensorB) == HIGH && digitalRead(SensorC) == HIGH) {
        if (digitalRead(BotoeiraL) == LOW) {
          EstadoAtual = EstadoMovendoEsteira;
        }
      }
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(MotorE, LOW);
  digitalWrite(AlarmeAL, LOW);
}