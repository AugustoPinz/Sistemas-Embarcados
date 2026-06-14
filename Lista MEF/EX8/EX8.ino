/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 8, Separadora de Peças por Material (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoAguardandoPecaS1 = 1;
const int EstadoMovendoAteAnalise = 2;
const int EstadoSeparandoMaterial1 = 3;
const int EstadoSeparandoMaterial2 = 4;
const int EstadoRecuandoAtuadores = 5;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS1 = 4;
const int SensorMaterial1 = 5;
const int SensorMaterial2 = 6;
const int SensorC1Recuado = 7;
const int SensorC2Recuado = 8;
const int MotorEsteira = 9;
const int AtuadorCilindroC1 = 10;
const int AtuadorCilindroC2 = 11;
const int LampadaLigada = 12;
int EstadoAtual = EstadoAguardandoStart;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorMaterial1, INPUT_PULLUP);
  pinMode(SensorMaterial2, INPUT_PULLUP);
  pinMode(SensorC1Recuado, INPUT_PULLUP);
  pinMode(SensorC2Recuado, INPUT_PULLUP);
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
        EstadoAtual = EstadoAguardandoPecaS1;
      }
      break;

    case EstadoAguardandoPecaS1:
      if (digitalRead(SensorS1) == LOW) {
        digitalWrite(MotorEsteira, HIGH);
        EstadoAtual = EstadoMovendoAteAnalise;
      }
      break;

    case EstadoMovendoAteAnalise:
      if (digitalRead(SensorMaterial1) == LOW) {
        digitalWrite(MotorEsteira, LOW);
        digitalWrite(AtuadorCilindroC1, HIGH);
        EstadoAtual = EstadoSeparandoMaterial1;
      } else if (digitalRead(SensorMaterial2) == LOW) {
        digitalWrite(MotorEsteira, LOW);
        digitalWrite(AtuadorCilindroC2, HIGH);
        EstadoAtual = EstadoSeparandoMaterial2;
      }
      break;

    case EstadoSeparandoMaterial1:
      digitalWrite(AtuadorCilindroC1, LOW);
      EstadoAtual = EstadoRecuandoAtuadores;
      break;

    case EstadoSeparandoMaterial2:
      digitalWrite(AtuadorCilindroC2, LOW);
      EstadoAtual = EstadoRecuandoAtuadores;
      break;

    case EstadoRecuandoAtuadores:
      if (digitalRead(SensorC1Recuado) == LOW && digitalRead(SensorC2Recuado) == LOW) {
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