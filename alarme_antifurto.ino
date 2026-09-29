// Alarme antifurto com sensor PIR HC-SR501 e 2 buzzers ATIVOS
// Botao arma/desarma. Se armado e detectar movimento: buzzers + LED vermelho.

const int PIR = 2;
const int BOTAO = 4;
const int BUZZER1 = 8;
const int BUZZER2 = 11;
const int LED_VERMELHO = 9;
const int LED_VERDE = 10;

bool armado = false;
bool ultimoBotao = HIGH;

void setup() {
  pinMode(PIR, INPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  // Aquecimento do sensor PIR (30 s). LED vermelho fica piscando.
  for (int i = 0; i < 30; i++) {
    digitalWrite(LED_VERMELHO, HIGH);
    delay(500);
    digitalWrite(LED_VERMELHO, LOW);
    delay(500);
  }
  digitalWrite(LED_VERDE, HIGH); // comeca desarmado
}

void loop() {
  bool botao = digitalRead(BOTAO);
  if (botao == LOW && ultimoBotao == HIGH) {
    armado = !armado;
    desligaBuzzers();
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, !armado);
    if (armado) {
      digitalWrite(BUZZER1, HIGH); // bip curto avisando que armou
      delay(200);
      digitalWrite(BUZZER1, LOW);
      delay(5000);                 // 5 s para voce sair da frente do sensor
    }
    delay(50); // debounce
  }
  ultimoBotao = botao;

  if (armado && digitalRead(PIR) == HIGH) {
    disparaAlarme();
  }
}

void disparaAlarme() {
  // Toca ate o botao ser apertado para desarmar
  while (digitalRead(BOTAO) == HIGH) {
    digitalWrite(BUZZER1, HIGH);
    digitalWrite(BUZZER2, LOW);
    digitalWrite(LED_VERMELHO, HIGH);
    delay(200);
    digitalWrite(BUZZER1, LOW);
    digitalWrite(BUZZER2, HIGH);
    digitalWrite(LED_VERMELHO, LOW);
    delay(200);
  }
  desligaBuzzers();
  digitalWrite(LED_VERMELHO, LOW);
  armado = false;
  digitalWrite(LED_VERDE, HIGH);
  ultimoBotao = LOW; // evita rearmar imediatamente
  delay(300);
}

void desligaBuzzers() {
  digitalWrite(BUZZER1, LOW);
  digitalWrite(BUZZER2, LOW);
}
