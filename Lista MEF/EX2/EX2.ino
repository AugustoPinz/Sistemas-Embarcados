/* ************************************************************************

Colégio SATC
Curso Técnico em Mecatrônica
Disciplina: Sistemas Embarcados
Turma: 3191
Professor: Marcos Antonio Jeremias Coelho

Programa: Exercício 2, Misturador de Tintas Automático (MEF)

Autor: Augusto Bredlau Pinz
Data: 13/06/2026
Versão: 1.3 (Versão Final de Entrega)

************************************************************************ */


const int AguardandoStart = 0;
const int AddIngrediente1 = 1;
const int AddIngrediente2 = 2;
const int MisturandoAquecendo = 3;
const int DrenandoTanque = 4;
const int BotaoStart = 2;    
const int SensorBaixo = 3;  
const int SensorAlto = 4;    
const int BombaIng1 = 5;
const int BombaIng2 = 6;
const int MotorMisturador = 7;
const int ValvulaVapor = 8;
const int ValvulaDrenagem = 9;
const int BombaDrenagem = 10;
int EstadoAtual = AguardandoStart;
unsigned long TempoInicio = 0;
int ContadorCiclos = 0;        
bool ProcessoContado = false;

void setup() {
  pinMode(BotaoStart, INPUT_PULLUP); 
  pinMode(SensorBaixo, INPUT_PULLUP);
  pinMode(SensorAlto, INPUT_PULLUP);
  pinMode(BombaIng1, OUTPUT);
  pinMode(BombaIng2, OUTPUT);
  pinMode(MotorMisturador, OUTPUT);
  pinMode(ValvulaVapor, OUTPUT);
  pinMode(ValvulaDrenagem, OUTPUT);
  pinMode(BombaDrenagem, OUTPUT);
  desligarAtuadores();
}

void loop() {
  
  switch (EstadoAtual) {
    case AguardandoStart:
      desligarAtuadores();
      ProcessoContado = false;
      if (digitalRead(BotaoStart) == HIGH) {
        TempoInicio = millis();
        EstadoAtual = AddIngrediente1;
      }
      break;
    case  AddIngrediente1:
      digitalWrite(BombaIng1, HIGH);
      digitalWrite(BombaIng2, LOW);
      if (millis() - TempoInicio >= 6000) {
        digitalWrite(BombaIng1, LOW);
        EstadoAtual = AddIngrediente2;
      }
      break;
    case AddIngrediente2:
      digitalWrite(BombaIng2, HIGH);
      if (digitalRead(SensorAlto) == LOW) {
        digitalWrite(BombaIng2, LOW);
        TempoInicio = millis(); 
        EstadoAtual = MisturandoAquecendo;
      }
      break;
    case MisturandoAquecendo:
      digitalWrite(MotorMisturador, HIGH);
      digitalWrite(ValvulaVapor, HIGH);
      if (millis() - TempoInicio >= 10000) {
        digitalWrite(MotorMisturador, LOW);
        digitalWrite(ValvulaVapor, LOW);
        EstadoAtual = DrenandoTanque;
      }
      break;
    case DrenandoTanque:
      digitalWrite(ValvulaDrenagem, HIGH);
      digitalWrite(BombaDrenagem, HIGH);
      if (digitalRead(SensorBaixo) == HIGH) {
        digitalWrite(ValvulaDrenagem, LOW);
        digitalWrite(BombaDrenagem, LOW);
        if (!ProcessoContado) {
          ContadorCiclos++;
          ProcessoContado = true;
        }
        EstadoAtual = AguardandoStart; 
      }
      break;
  }
  delay(50); 
}
void desligarAtuadores() {
  digitalWrite(BombaIng1, LOW);
  digitalWrite(BombaIng2, LOW);
  digitalWrite(MotorMisturador, LOW);
  digitalWrite(ValvulaVapor, LOW);
  digitalWrite(ValvulaDrenagem, LOW);
  digitalWrite(BombaDrenagem, LOW);
}