#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Botões
const int btLocalizar = 2;
const int btEmprestimo = 3;
const int btDevolucao = 4;

// LEDs
const int led1 = 5;
const int led2 = 6;
const int led3 = 7;
const int led4 = 8;
const int led5 = 9;

// Sensor (opcional)
const int sensorLivro = A2;

int livro = 1;
bool disponivel = true;

void setup() {

  pinMode(btLocalizar, INPUT_PULLUP);
  pinMode(btEmprestimo, INPUT_PULLUP);
  pinMode(btDevolucao, INPUT_PULLUP);

  pinMode(sensorLivro, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Biblioteca");
  lcd.setCursor(0,1);
  lcd.print("Automatizada");

  delay(2000);

  mostrarLivro();
}

void apagarLeds() {
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
}

void acenderFaixaLivro() {

  apagarLeds();

  if (livro <= 20)
    digitalWrite(led1, HIGH);

  else if (livro <= 40)
    digitalWrite(led2, HIGH);

  else if (livro <= 60)
    digitalWrite(led3, HIGH);

  else if (livro <= 80)
    digitalWrite(led4, HIGH);

  else
    digitalWrite(led5, HIGH);
}

void mostrarLivro() {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Livro: ");
  lcd.print(livro);

  lcd.setCursor(0,1);

  if (disponivel)
    lcd.print("Disponivel");
  else
    lcd.print("Emprestado");

  acenderFaixaLivro();
}

void loop() {

  // Próximo livro (1 a 100)
  if (digitalRead(btLocalizar) == LOW) {

    livro++;

    if (livro > 100)
      livro = 1;

    mostrarLivro();

    delay(300);
  }

  // Empréstimo
  if (digitalRead(btEmprestimo) == LOW) {

    disponivel = false;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Livro ");
    lcd.print(livro);

    lcd.setCursor(0,1);
    lcd.print("Emprestado");

    delay(1000);

    mostrarLivro();
  }

  // Devolução
  if (digitalRead(btDevolucao) == LOW) {

    disponivel = true;

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Livro ");
    lcd.print(livro);

    lcd.setCursor(0,1);
    lcd.print("Devolvido");

    delay(1000);

    mostrarLivro();
  }

  // Sensor de presença
  if (digitalRead(sensorLivro) == LOW)
    disponivel = true;
  else
    disponivel = false;
}
