#define DELAY_LEVEL 1150
#define DELAY_LEVEL_TO_TARGET_OK 2500
#define DELAY_TARGET 30

//Uso de Define no lugar de variaveis economiza memoria, pois a troca e feita durante compilacao, como se fosse hard coded.
#define PIN_START 53

#define PIN_N1     22 // nível 1 -  Vermelho 
#define PIN_N2     24 // nível 2 -  Vermelho 
#define PIN_N3     26 // nível 3 -  Vermelho
#define PIN_N4     28 // nível 4 -  Vermelho
#define PIN_N5     30 // nível 5 -  Vermelho
#define PIN_N6     32 // nível 6 -  Vermelho
#define PIN_N7     34 // nível 7 -  Vermelho
#define PIN_N8     36 // nível 8 -  Vermelho
#define PIN_N9     38 // nível 9 -  Vermelho
#define PIN_N10    40 // nível 10 - Vermelho
#define PIN_N11    42 // nível 11 - Vermelho
#define PIN_N12    44 // nível 12 - Vermelho
#define PIN_N13    46 // nível 13 - Vermelho
#define PIN_N14    48 // nível 14 - Vermelho
#define PIN_N15    50 // nível 15 - Vermelho
#define PIN_N16    52 // nível 16 - Vermelho
#define PIN_N17    23 // nível 17 - Vermelho
#define PIN_N18    25 // nível 18 - Amarelo
#define PIN_N19    27 // nível 19 - Amerelo
#define PIN_N20    29 // nível 20 - Amarelo
#define PIN_N21    31 // nível 21 - Amarelo
#define PIN_N22    33 // nível 22 - Verde
#define PIN_N23    35 // nível 23 - Verde
#define PIN_N24    37 // nível 24 - Verde
#define PIN_N25    39 // nível 25 - Azul

#define PIN_R1  43
#define PIN_R2  45
#define PIN_R3  47

int levels[] = {PIN_N1,
                PIN_N2,
                PIN_N3,
                PIN_N4,
                PIN_N5,
                PIN_N6,
                PIN_N7,
                PIN_N8,
                PIN_N9,
                PIN_N10,
                PIN_N11,
                PIN_N12,
                PIN_N13,
                PIN_N14,
                PIN_N15,
                PIN_N16,
                PIN_N17,
                PIN_N18,
                PIN_N19,
                PIN_N20,
                PIN_N21,
                PIN_N22,
                PIN_N23,
                PIN_N24,
                PIN_N25
               };

int lastState = LOW;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
bool isTargetOK = true;// Atingiu (True) a meta ou não atingiu (False)
int result = 90; //% final (Pastor Eli passa esse valor)
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void startPanel() {
  Serial.println("STARTED");
  int target = result / 4;
  Serial.println("SUBINDO");
  for (int i = 0; i < target; i++) {
    digitalWrite(levels[i], true);
    delay(DELAY_LEVEL);
  }
  Serial.println("SUBIU");
  digitalWrite(PIN_R1, true);
  digitalWrite(PIN_R2, true);
  digitalWrite(PIN_R3, true);
  if (isTargetOK == true) {
    Serial.println("VAI PRA DANCINHA");
    delay(DELAY_LEVEL_TO_TARGET_OK);
    targetOk();
  }
}

void resetPanel() {
  for (int i = 0; i < 25; i++) {
    digitalWrite(levels[i], false);
    delay(1);
  }
  digitalWrite(PIN_R1, false);
  digitalWrite(PIN_R2, false);
  digitalWrite(PIN_R3, false);
}

void targetOk() {
  resetPanel();
  Serial.println("DANCANDO");
  while (true) {
    digitalWrite(PIN_R1, true);
    digitalWrite(PIN_R2, true);
    digitalWrite(PIN_R3, true);
    for (int i = 0; i <=24; i++) {
      if (i == 0) {
        digitalWrite(levels[0], true);
      } else {
        digitalWrite(levels[i], true);
        digitalWrite(levels[i - 1], false);
      }
      delay(DELAY_TARGET);
    }
    digitalWrite(PIN_R1, false);
    digitalWrite(PIN_R2, false);
    digitalWrite(PIN_R3, false);
    for (int i = 24; i >= 0; i--) {
      if (i == 24) {
        digitalWrite(levels[24], true);
      } else {
        digitalWrite(levels[i], true);
        digitalWrite(levels[i + 1], false);
      }
      delay(DELAY_TARGET);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_START, INPUT);

  pinMode(PIN_N1, OUTPUT);
  pinMode(PIN_N2, OUTPUT);
  pinMode(PIN_N3, OUTPUT);
  pinMode(PIN_N4, OUTPUT);
  pinMode(PIN_N5, OUTPUT);
  pinMode(PIN_N6, OUTPUT);
  pinMode(PIN_N7, OUTPUT);
  pinMode(PIN_N8, OUTPUT);
  pinMode(PIN_N9, OUTPUT);
  pinMode(PIN_N10, OUTPUT);
  pinMode(PIN_N11, OUTPUT);
  pinMode(PIN_N12, OUTPUT);
  pinMode(PIN_N13, OUTPUT);
  pinMode(PIN_N14, OUTPUT);
  pinMode(PIN_N15, OUTPUT);
  pinMode(PIN_N16, OUTPUT);
  pinMode(PIN_N17, OUTPUT);
  pinMode(PIN_N18, OUTPUT);
  pinMode(PIN_N19, OUTPUT);
  pinMode(PIN_N20, OUTPUT);
  pinMode(PIN_N21, OUTPUT);
  pinMode(PIN_N22, OUTPUT);
  pinMode(PIN_N23, OUTPUT);
  pinMode(PIN_N24, OUTPUT);
  pinMode(PIN_N25, OUTPUT);

  pinMode(PIN_R1, OUTPUT);
  pinMode(PIN_R2, OUTPUT);
  pinMode(PIN_R3, OUTPUT);

  resetPanel();
}

void loop() {
  Serial.println(digitalRead(PIN_START));
  int state = digitalRead(PIN_START);
  if (state != lastState) {
    Serial.println("APERTOU");
    lastState = state;
    if (state == HIGH) {
      Serial.println("START");
      startPanel();
    }
  }
}
