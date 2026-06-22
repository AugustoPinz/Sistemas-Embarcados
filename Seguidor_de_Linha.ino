#define S1 A0
#define S2 A1
#define S3 A2
#define S4 A3
#define S5 A4

// motor direito ligado no out1 e out2
#define EN_DIR 9
#define IN_DIR1 8
#define IN_DIR2 7

// motor esquerdo ligado no out3 e out4
#define EN_ESQ 10
#define IN_ESQ1 11
#define IN_ESQ2 12

int velBase = 180;      // velocidade para andar reto
int velCurvaLeve = 130; // velocidade para curvas leves
int velCurvaForte = 80; // velocidade para curvas mais fechadas

void setup() {

  // configura os sensores
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);

  // configura os pinos da ponte h
  pinMode(EN_DIR, OUTPUT);
  pinMode(IN_DIR1, OUTPUT);
  pinMode(IN_DIR2, OUTPUT);

  pinMode(EN_ESQ, OUTPUT);
  pinMode(IN_ESQ1, OUTPUT);
  pinMode(IN_ESQ2, OUTPUT);
}

void loop() {

  // le os cinco sensores
  int s1 = digitalRead(S1);
  int s2 = digitalRead(S2);
  int s3 = digitalRead(S3);
  int s4 = digitalRead(S4);
  int s5 = digitalRead(S5);

  // linha branca = 1
  // fundo preto = 0

  if (s3 == 1) {
    // segue reto
    frente(velBase, velBase);
  }

  else if (s2 == 1) {
    // faz uma curva leve para a esquerda
    frente(velCurvaLeve, velBase);
  }

  else if (s1 == 1) {
    // faz uma curva mais forte para a esquerda
    frente(velCurvaForte, velBase);
  }

  else if (s4 == 1) {
    // faz uma curva leve para a direita
    frente(velBase, velCurvaLeve);
  }

  else if (s5 == 1) {
    // faz uma curva mais forte para a direita
    frente(velBase, velCurvaForte);
  }

  else {
    // para se perder a linha
    parar();
  }
}

// controla os dois motores
void frente(int velEsq, int velDir) {

  digitalWrite(IN_ESQ1, HIGH);
  digitalWrite(IN_ESQ2, LOW);
  analogWrite(EN_ESQ, velEsq);

  digitalWrite(IN_DIR1, HIGH);
  digitalWrite(IN_DIR2, LOW);
  analogWrite(EN_DIR, velDir);
}

// para os motores
void parar() {
  analogWrite(EN_ESQ, 0);
  analogWrite(EN_DIR, 0);
}