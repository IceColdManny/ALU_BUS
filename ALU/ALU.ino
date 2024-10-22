int EstadoA = 0;
int EstadoB = 0;

int EstadoW = 0;
int EstadoX = 0;
int EstadoY = 0;
int EstadoZ = 0;

void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  EstadoA = digitalRead(2);
  EstadoB = digitalRead(3);
  
  EstadoW = digitalRead(4);
  EstadoX = digitalRead(5);
  EstadoY = digitalRead(6);
  EstadoZ = digitalRead(7);

  int resultado = 0;
  int acarreo = 0;
  bool negativo = false;
  bool indeterminado = false;

  if (EstadoW == 0 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 0) {
    Serial.println("NOP - No operation");
  }
  else if (EstadoW == 0 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 1) {
    resultado = EstadoA ^ EstadoB;
    acarreo = EstadoA && EstadoB;
    Serial.println("Suma");
  }
  else if (EstadoW == 0 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 0) {
    resultado = EstadoA - EstadoB;
    if (resultado < 0) {
      negativo = true;
    }
    Serial.println("Resta");
  }
  else if (EstadoW == 0 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 1) {
    resultado = EstadoA * EstadoB;
    Serial.println("Multiplicacion");
  }
  else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 0 && EstadoZ == 0) {
    if (EstadoB != 0) {
      resultado = EstadoA / EstadoB;
    } else {
      resultado = -1;
      indeterminado = true;
      Serial.println("Error: División por 0");
    }
  }
  else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 0 && EstadoZ == 1) {
    resultado = EstadoA & EstadoB;
    Serial.println("AND");
  }
  else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 1 && EstadoZ == 0) {
    resultado = EstadoA | EstadoB;
    Serial.println("OR");
  }
  else if (EstadoW == 0 && EstadoX == 1 && EstadoY == 1 && EstadoZ == 1) {
    resultado = !EstadoA;
    Serial.println("NOT");
  }
  else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 0) {
    resultado = EstadoA ^ EstadoB;
    Serial.println("XOR");
  }
  else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 0 && EstadoZ == 1) {
    resultado = !(EstadoA ^ EstadoB);
    Serial.println("XNOR");
  }
  else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 0) {
    resultado = !(EstadoA & EstadoB);
    Serial.println("NAND");
  }
  else if (EstadoW == 1 && EstadoX == 0 && EstadoY == 1 && EstadoZ == 1) {
    resultado = !(EstadoA | EstadoB);
    Serial.println("NOR");
  }

  if (!negativo && !indeterminado) {
    digitalWrite(12, resultado);
    digitalWrite(13, acarreo);
  } else {
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  
  digitalWrite(8, negativo ? HIGH : LOW);
  digitalWrite(9, indeterminado ? HIGH : LOW);
  delay(1);

  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  delay(1);
}

