/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 11, Pasteurizadora de Peças (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoAguardandoPecaS1 = 1;
const int EstadoMovendoAteS2 = 2;
const int EstadoAquecendoR1 = 3;
const int EstadoMovendoAteS3 = 4;
const int EstadoResfriandoV1 = 5;
const int EstadoMovendoAteS4 = 6;
const int BotaoStart = 2;
const int BotaoStop = 3;
const int SensorS1 = 4;
const int SensorS2 = 5;
const int SensorS3 = 6;
const int SensorS4 = 7;
const int MotorEsteira = 8;
const int ResistenciaR1 = 9;
const int VentoinhaV1 = 10;
const int LampadaLigada = 11;
int EstadoAtual = EstadoAguardandoStart;
unsigned long TempoAquecimento = 0;
unsigned long TempoResfriamento = 0;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(BotaoStop, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(SensorS4, INPUT_PULLUP);
  pinMode(MotorEsteira, OUTPUT);
  pinMode(ResistenciaR1, OUTPUT);
  pinMode(VentoinhaV1, OUTPUT);
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
      TempoAquecimento = 0;
      TempoResfriamento = 0;
      if (digitalRead(BotaoStart) == LOW) {
        digitalWrite(LampadaLigada, HIGH);
        EstadoAtual = EstadoAguardandoPecaS1;
      }
      break;

    case EstadoAguardandoPecaS1:
      if (digitalRead(SensorS1) == LOW) {
        digitalWrite(MotorEsteira, HIGH);
        EstadoAtual = EstadoMovendoAteS2;
      }
      break;

    case Estado