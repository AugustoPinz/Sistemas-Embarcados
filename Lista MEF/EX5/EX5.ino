/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 5, Cortadora de Chapas (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoPosicionandoSimultaneo = 1;
const int EstadoAvancandoCilindro = 2;
const int EstadoRecuandoCilindro = 3;
const int EstadoAvançandoProximaCaixa = 4;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS2 = 4;
const int SensorS3 = 5;
const int SensorFimCursoAvançado = 6;
const int SensorFimCursoRecuado = 7;
const int MotorEsteiraChapa = 8;
const int MotorEsteiraCaixa = 9;
const int AtuadorCilindroC1 = 10;
const int LampadaLigada = 11;
int EstadoAtual = EstadoAguardandoStart;
int ContadorCortes = 0;
bool ChapaPosicionada = false;
bool CaixaPosicionada = false;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(SensorFimCursoAvançado, INPUT_PULLUP);
  pinMode(SensorFimCursoRecuado, INPUT_PULLUP);
  pinMode(MotorEsteiraChapa, OUTPUT);
  pinMode(MotorEsteiraCaixa, OUTPUT);
  pinMode(AtuadorCilindroC1, OUTPUT);
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
      ContadorCortes = 0;
      ChapaPosicionada = false;
      CaixaPosicionada = false;
      if (digitalRead(BotaoStart) == LOW) {
        digitalWrite(LampadaLigada, HIGH);
        EstadoAtual = EstadoPosicionandoSimultaneo;
      }
      break;

    case EstadoPosicionandoSimultaneo:
      if (digitalRead(SensorS2) == LOW) {
        ChapaPosicionada = true;
        digitalWrite(MotorEsteiraChapa, LOW);
      } else if (!ChapaPosicionada) {
        digitalWrite(MotorEsteiraChapa, HIGH);
      }

      if (digitalRead(SensorS3) == LOW) {
        CaixaPosicionada = true;
        digitalWrite(MotorEsteiraCaixa, LOW);
      } else if (!CaixaPosicionada) {
        digitalWrite(MotorEsteiraCaixa, HIGH);
      }

      if (ChapaPosicionada && CaixaPosicionada) {
        EstadoAtual = EstadoAvancandoCilindro;
      }
      break;

    case EstadoAvancandoCilindro:
      digitalWrite(AtuadorCilindroC1, HIGH);
      if (digitalRead(SensorFimCursoAvançado) == LOW) {
        EstadoAtual = EstadoRecuandoCilindro;
      }
      break;

    case EstadoRecuandoCilindro:
      digitalWrite(AtuadorCilindroC1, LOW);
      if (digitalRead(SensorFimCursoRecuado) == LOW) {
        ContadorCortes++;
        if (ContadorCortes >= 5) {
          EstadoAtual = EstadoAvançandoProximaCaixa;
        } else {
          ChapaPosicionada = false;
          EstadoAtual = EstadoPosicionandoSimultaneo;
        }
      }
      break;

    case EstadoAvançandoProximaCaixa:
      if (digitalRead(SensorS3) == HIGH) {
        digitalWrite(MotorEsteiraCaixa, HIGH);
      }
      if (digitalRead(SensorS3) == LOW && digitalWrite(MotorEsteiraCaixa, HIGH)) {
        digitalWrite(MotorEsteiraCaixa, LOW);
        EstadoAtual = EstadoAguardandoStart;
      }
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(MotorEsteiraChapa, LOW);
  digitalWrite(MotorEsteiraCaixa, LOW);
  digitalWrite(AtuadorCilindroC1, LOW);
  digitalWrite(LampadaLigada, LOW);
}