/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 7, Separadora de Peças com Teste de Altura (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoMovendoETestando = 1;
const int EstadoPecaGrande = 2;
const int EstadoPecaPequenaS4 = 3;
const int EstadoDesviandoPequena = 4;
const int EstadoFinalizandoCiclo = 5;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorAltura = 4;
const int SensorS4 = 5;
const int SensorCaixaGrande = 6;
const int SensorCaixaPequena = 7;
const int SensorC1Recuado = 8;
const int SensorC2Recuado = 9;
const int MotorM1 = 10;
const int AtuadorCilindroC1 = 11;
const int AtuadorCilindroC2 = 12;
const int LampadaLigada = 13;
int EstadoAtual = EstadoAguardandoStart;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorAltura, INPUT_PULLUP);
  pinMode(SensorS4, INPUT_PULLUP);
  pinMode(SensorCaixaGrande, INPUT_PULLUP);
  pinMode(SensorCaixaPequena, INPUT_PULLUP);
  pinMode(SensorC1Recuado, INPUT_PULLUP);
  pinMode(SensorC2Recuado, INPUT_PULLUP);
  pinMode(MotorM1, OUTPUT);
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
        digitalWrite(MotorM1, HIGH);
        digitalWrite(AtuadorCilindroC1, HIGH);
        EstadoAtual = EstadoMovendoETestando;
      }
      break;

    case EstadoMovendoETestando:
      if (digitalRead(SensorAltura) == LOW) {
        EstadoAtual = EstadoPecaGrande;
      } else if (digitalRead(SensorS4) == LOW) {
        EstadoAtual = EstadoPecaPequenaS4;
      }
      break;

    case EstadoPecaGrande:
      if (digitalRead(SensorCaixaGrande) == LOW) {
        EstadoAtual = EstadoFinalizandoCiclo;
      }
      break;

    case EstadoPecaPequenaS4:
      digitalWrite(AtuadorCilindroC2, HIGH);
      EstadoAtual = EstadoDesviandoPequena;
      break;

    case EstadoDesviandoPequena:
      if (digitalRead(SensorCaixaPequena) == LOW) {
        EstadoAtual = EstadoFinalizandoCiclo;
      }
      break;

    case EstadoFinalizandoCiclo:
      digitalWrite(MotorM1, LOW);
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
  digitalWrite(AtuadorCilindroC1, LOW);
  digitalWrite(AtuadorCilindroC2, LOW);
  digitalWrite(LampadaLigada, LOW);
}