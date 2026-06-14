/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 9, Abastecedora de Peças (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoAlimentandoCaixa = 1;
const int EstadoMovendoAteS2 = 2;
const int EstadoEnchendoCaixa = 3;
const int EstadoRetornandoAlimentador = 4;
const int EstadoAguardandoRetirada = 5;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS1 = 4;
const int SensorS2 = 5;
const int SensorS3 = 6;
const int SensorS4 = 7;
const int MotorEsteira = 8;
const int AtuadorCilindroC1 = 9;
const int AtuadorCilindroC2 = 10;
const int LampadaLigada = 11;
int EstadoAtual = EstadoAguardandoStart;
unsigned long TempoEnchimento = 0;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(SensorS4, INPUT_PULLUP);
  pinMode(MotorEsteira, OUTPUT);
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
        digitalWrite(MotorEsteira, HIGH);
        digitalWrite(AtuadorCilindroC1, HIGH);
        EstadoAtual = EstadoAlimentandoCaixa;
      }
      break;

    case EstadoAlimentandoCaixa:
      if (digitalRead(SensorS1) == LOW) {
        digitalWrite(AtuadorCilindroC1, LOW);
        EstadoAtual = EstadoMovendoAteS2;
      }
      break;

    case EstadoMovendoAteS2:
      if (digitalRead(SensorS2) == LOW) {
        digitalWrite(MotorEsteira, LOW);
        digitalWrite(AtuadorCilindroC2, HIGH);
        EstadoAtual = EstadoEnchendoCaixa;
      }
      break;

    case EstadoEnchendoCaixa:
      if (digitalRead(SensorS3) == LOW) {
        if (TempoEnchimento == 0) {
          TempoEnchimento = millis();
        }
        if (millis() - TempoEnchimento >= 6000) {
          digitalWrite(AtuadorCilindroC2, LOW);
          digitalWrite(MotorEsteira, HIGH);
          TempoEnchimento = 0;
          EstadoAtual = EstadoRetornandoAlimentador;
        }
      }
      break;

    case EstadoRetornandoAlimentador:
      if (digitalRead(SensorS4) == LOW) {
        digitalWrite(MotorEsteira, LOW);
        EstadoAtual = EstadoAguardandoRetirada;
      }
      break;

    case EstadoAguardandoRetirada:
      if (digitalRead(SensorS4) == HIGH) {
        EstadoAtual = EstadoAguardandoStart;
      }
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(MotorEsteira, LOW);
  digitalWrite(AtuadorCilindroC1, LOW);
  digitalWrite(AtuadorCilindroC2, LOW);
  digitalWrite(LampadaLigada, LOW);
}