const int pinoPot = A0;          // Sensor de Nível
const int pinoBotaoA = 2;        // Início (Pull-up interno)
const int pinoBotaoB = 3;        // Emergência (Pull-up interno)
const int ledValvula = 9;        // Válvula de Enchimento (PWM)
const int ledExecucao = 4;       // Ciclo em Execução
const int ledCheio = 5;          // Galão Cheio
const int ledAlarme = 6;         // Emergência/Falha

//Variáveis de Tempo (millis)
unsigned long tempoAnteriorAlarme = 0;
const int intervaloAlarme = 100; // Pisca a cada 100ms

//Variáveis de Estado do Sistema
bool cicloAtivo = false;
bool emergênciaAtiva = false;

void setup() {
  pinMode(pinoPot, INPUT);
  pinMode(ledValvula, OUTPUT);
  pinMode(ledExecucao, OUTPUT);
  pinMode(ledCheio, OUTPUT);
  pinMode(ledAlarme, OUTPUT);
  pinMode(pinoBotaoA, INPUT_PULLUP);
  pinMode(pinoBotaoB, INPUT_PULLUP);
}

void loop() {
  int nivel = analogRead(pinoPot);
  unsigned long tempoAtual = millis();

  // Verificação de Emergência (Botão B)
  // Lógica de segurança NR-12: se pressionado, aborta tudo.
  if (digitalRead(pinoBotaoB) == LOW) {
    emergênciaAtiva = true;
    cicloAtivo = false;
  } else {
    emergênciaAtiva = false;
    digitalWrite(ledAlarme, LOW); // Desliga o alarme se o botão for solto
  }

  //Alarme (Piscar LED 4 com millis)
  if (emergênciaAtiva) {
    // Desliga saídas críticas imediatamente
    analogWrite(ledValvula, 0);
    digitalWrite(ledExecucao, LOW);
    
    if (tempoAtual - tempoAnteriorAlarme >= intervaloAlarme) {
      tempoAnteriorAlarme = tempoAtual;
      digitalWrite(ledAlarme, !digitalRead(ledAlarme));
    }
  }

  //Condição de Partida (Botão A + Galão Vazio + Sem Emergência)
  if (!cicloAtivo && !emergênciaAtiva) {
    if (digitalRead(pinoBotaoA) == LOW && nivel < 50) {
      cicloAtivo = true;
      digitalWrite(ledCheio, LOW); // Apaga indicador de cheio 
    }
  }

  // Enchimento
  if (cicloAtivo && !emergênciaAtiva) {
    digitalWrite(ledExecucao, HIGH);

    if (nivel <= 819) { // Até 80% (80% de 1023 = 819)
      analogWrite(ledValvula, 255); // Vazão Máxima (100%)
    } 
    else if (nivel > 819 && nivel <= 1000) { // Entre 80% e 98%
      analogWrite(ledValvula, 76); // Vazão Reduzida (30% de 255 = 76)
    } 
    else if (nivel > 1000) { // Atingiu 98%
      finalizarCiclo();
    }
  }
}

// Função para organizar a finalização
void finalizarCiclo() {
  cicloAtivo = false;
  analogWrite(ledValvula, 0);
  digitalWrite(ledExecucao, LOW);
  digitalWrite(ledCheio, HIGH);
}