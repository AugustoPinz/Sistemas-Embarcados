/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 14, Dobradeira de Peças (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoMovendoM1 = 1;
const int EstadoAvancandoC1 = 2;
const int EstadoAguardandoDobra = 3;
const int EstadoAvancandoC3 = 4;
const int EstadoAguardandoCorte = 5;
const int EstadoAvancandoC2 = 6;
const int EstadoRecuandoCilindros = 7;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS4 = 4;
const int SensorS1 = 5;
const int SensorS3 = 6;
const int SensorS2 = 7;
const int SensorC1Recuado = 8;
const int SensorC2Recuado = 9;
const int SensorC3Recuado = 10;
const int MotorM1 = 11;
const int AtuadorCilindroC1 = 12;
const int AtuadorCilindroC2 = 13;
const int AtuadorCilindroC3 = A0;
const int LampadaLigada = A1;
int EstadoAtual = EstadoAguardandoStart;
unsigned long TempoDobra = 0;
unsigned long TempoCorte = 0;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS4, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorC1Recuado, INPUT_PULLUP);
  pinMode(SensorC2Recuado, INPUT_PULLUP);
  pinMode(SensorC3Recuado, INPUT_PULLUP);
  pinMode(MotorM1, OUTPUT);
  pinMode(AtuadorCilindroC1, OUTPUT);
  pinMode(AtuadorCilindroC2, OUTPUT);
  pinMode(AtuadorCilindroC3, OUTPUT);
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
      TempoDobra = 0;
      TempoCorte = 0;
      if (digitalRead(BotaoStart) == LOW) {
        digitalWrite(LampadaLigada, HIGH);
        digitalWrite(MotorM1, HIGH);
        EstadoAtual = EstadoMovendoM1;
      }
      break;

    case EstadoMovendoM1:
      if (digitalRead(SensorS4) == LOW) {
        digitalWrite(MotorM1, LOW);
        digitalWrite(AtuadorCilindroC1, HIGH);
        EstadoAtual = EstadoAvancandoC1;
      }
      break;

    case EstadoAvancandoC1:
      if (digitalRead(SensorS1) == LOW) {
        TempoDobra = millis();
        EstadoAtual = EstadoAguardandoDobra;
      }
      break;

    case EstadoAguardandoDobra:
      if (millis() - TempoDobra >= 2000) {
        digitalWrite(AtuadorCilindroC3, HIGH);
        EstadoAtual = EstadoAvancandoC3;
      }
      break;

    case EstadoAvancandoC3:
      if (digitalRead(SensorS3) == LOW) {
        TempoCorte = millis();
        EstadoAtual = EstadoAguardandoCorte;
      }
      break;

    case EstadoAguardandoCorte:
      if (millis() - TempoCorte >= 2000) {
        digitalWrite(AtuadorCilindroC2, HIGH);
        EstadoAtual = EstadoAvancandoC2;
      }
      break;

    case EstadoAvancandoC2:
      if (digitalRead(SensorS2) == LOW) {
        digitalWrite(AtuadorCilindroC1, LOW);
        digitalWrite(AtuadorCilindroC2, LOW);
        digitalWrite(AtuadorCilindroC3, LOW);
        EstadoAtual = EstadoRecuandoCilindros;
      }
      break;

    case EstadoRecuandoCilindros:
      if (digitalRead(SensorC1Recuado) == LOW && digitalRead(SensorC2Recuado) == LOW && digitalRead(SensorC3Recuado) == LOW) {
        EstadoAtual = EstadoAguardandoStart;
      }
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(MotorM1, LOW);
  digitalWrite(AtuadorCilindroC1, LOW);
  digitalWrite(AtuadorCilindroC2, LOW);
  digitalWrite(AtuadorCilindroC3, LOW);
  digitalWrite(LampadaLigada, LOW);
}