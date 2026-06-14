/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 15, Controle de Segurança de Prensa Bimanual (MEF)

Autor: Augusto Bredlau Pinz
Data: 14/06/2026
Versão: 1.0

************************************************************************ */

const int EstadoAguardandoStart = 0;
const int EstadoSincronizacaoBimanual = 1;
const int EstadoPrensagemAtiva = 2;
const int EstadoAguardandoRetornoMao = 3;
const int EstadoBloqueioManobra = 4;
const int BotaoOperarioA = 2;
const int BotaoOperarioB = 3;
const int ContatorPrensaR = 4;
int EstadoAtual = EstadoAguardandoStart;
unsigned long TempoSincronismo = 0;
unsigned long TempoRetornoMao = 0;

void setup() {
  pinMode(BotaoOperarioA, INPUT_PULLUP);
  pinMode(BotaoOperarioB, INPUT_PULLUP);
  pinMode(ContatorPrensaR, OUTPUT);
  desligarAtuadores();
}

void loop() {
  switch (EstadoAtual) {

    case EstadoAguardandoStart:
      desligarAtuadores();
      if (digitalRead(BotaoOperarioA) == LOW || digitalRead(BotaoOperarioB) == LOW) {
        TempoSincronismo = millis();
        EstadoAtual = EstadoSincronizacaoBimanual;
      }
      break;

    case EstadoSincronizacaoBimanual:
      if (digitalRead(BotaoOperarioA) == LOW && digitalRead(BotaoOperarioB) == LOW) {
        digitalWrite(ContatorPrensaR, HIGH);
        EstadoAtual = EstadoPrensagemAtiva;
      } else if (millis() - TempoSincronismo > 3000) {
        EstadoAtual = EstadoBloqueioManobra;
      }
      break;

    case EstadoPrensagemAtiva:
      if (digitalRead(BotaoOperarioA) == HIGH || digitalRead(BotaoOperarioB) == HIGH) {
        digitalWrite(ContatorPrensaR, LOW);
        TempoRetornoMao = millis();
        EstadoAtual = EstadoAguardandoRetornoMao;
      }
      break;

    case EstadoAguardandoRetornoMao:
      if (digitalRead(BotaoOperarioA) == LOW && digitalRead(BotaoOperarioB) == LOW) {
        digitalWrite(ContatorPrensaR, HIGH);
        EstadoAtual = EstadoPrensagemAtiva;
      } else if (millis() - TempoRetornoMao > 3000) {
        EstadoAtual = EstadoBloqueioManobra;
      }
      break;

    case EstadoBloqueioManobra:
      desligarAtuadores();
      if (digitalRead(BotaoOperarioA) == HIGH && digitalRead(BotaoOperarioB) == HIGH) {
        EstadoAtual = EstadoAguardandoStart;
      }
      break;
  }
  delay(50);
}

void desligarAtuadores() {
  digitalWrite(ContatorPrensaR, LOW);
}