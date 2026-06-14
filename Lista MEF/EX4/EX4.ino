Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 4, Seletora de Peças (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoEstabilizando = 1;
const int EstadoLeituraSensores = 2;
const int EstadoSeparandoAlta = 3;
const int EstadoSeparandoBaixa = 4;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS1 = 4;
const int SensorS2 = 5;
const int SensorS3 = 6;
const int SensorS4 = 7;
const int MotorEsteira = 8;
const int AtuadorPeca = 9;
const int LampadaLigada = 10;
int EstadoAtual = EstadoAguardandoStart;
unsigned long TempoEstabilizar = 0;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(SensorS4, INPUT_PULLUP);
  pinMode(MotorEsteira, OUTPUT);
  pinMode(AtuadorPeca, OUTPUT);
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
        digitalWrite(AtuadorPeca, HIGH);
        digitalWrite(LampadaLigada, HIGH);
        digitalWrite(MotorEsteira, HIGH);
        TempoEstabilizar = millis();
        EstadoAtual = EstadoEstabilizando;
      }
      break;

    case EstadoEstabilizando:
      digitalWrite(AtuadorPeca, LOW);
      if (millis() - TempoEstabilizar >= 2000) {
        EstadoAtual = EstadoLeituraSensores;
      }
      break;

    case EstadoLeituraSensores:
      if (digitalRead(SensorS3) == LOW && digitalRead(SensorS4) == LOW) {
        EstadoAtual = EstadoSeparandoAlta;
      } else {
        EstadoAtual = EstadoSeparandoBaixa;
      }
      break;

    case EstadoSeparandoAlta:
      if (digitalRead(SensorS1) == LOW) {
        EstadoAtual = EstadoAguardandoStart;
      }
      break;

    case EstadoSeparandoBaixa:
      if (digitalRead(SensorS2) == LOW) {
        EstadoAtual = EstadoAguardandoStart;
      }
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(MotorEsteira, LOW);
  digitalWrite(AtuadorPeca, LOW);
  digitalWrite(LampadaLigada, LOW);
}