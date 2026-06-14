/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 10, Furadeira de Peças Automática (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoPrendendoPeca = 1;
const int EstadoLigandoFuradeira = 2;
const int EstadoAvancandoC2 = 3;
const int EstadoRecuandoC2 = 4;
const int EstadoSoltandoPeca = 5;
const int BotaoStart = 2;
const int SensorS1 = 3;
const int SensorS2 = 4;
const int SensorS3 = 5;
const int SensorC1Recuado = 6;
const int MotorEsteira = 7;
const int AtuadorCilindroC1 = 8;
const int AtuadorCilindroC2 = 9;
const int MotorFuradeira = 10;
const int LampadaLigada = 11;
int EstadoAtual = EstadoAguardandoStart;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP);
  pinMode(SensorS1, INPUT_PULLUP);
  pinMode(SensorS2, INPUT_PULLUP);
  pinMode(SensorS3, INPUT_PULLUP);
  pinMode(SensorC1Recuado, INPUT_PULLUP);
  pinMode(MotorEsteira, OUTPUT);
  pinMode(AtuadorCilindroC1, OUTPUT);
  pinMode(AtuadorCilindroC2, OUTPUT);
  pinMode(MotorFuradeira, OUTPUT);
  pinMode(LampadaLigada, OUTPUT);