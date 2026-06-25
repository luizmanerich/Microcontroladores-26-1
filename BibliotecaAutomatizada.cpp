#include "BibliotecaAutomatizada.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int TOTAL_LIVROS = 100;

byte livros[TOTAL_LIVROS];

int livro = 1;

// Pinos recebidos do .ino
int _btProximo;
int _btAnterior;
int _btEmprestimo;
int _btDevolucao;

int _led1;
int _led2;
int _led3;
int _led4;
int _led5;

void apagarLeds() {

    digitalWrite(_led1, LOW);
    digitalWrite(_led2, LOW);
    digitalWrite(_led3, LOW);
    digitalWrite(_led4, LOW);
    digitalWrite(_led5, LOW);
}

void acenderFaixaLivro() {

    apagarLeds();

    if (livro <= 20)
        digitalWrite(_led1, HIGH);

    else if (livro <= 40)
        digitalWrite(_led2, HIGH);

    else if (livro <= 60)
        digitalWrite(_led3, HIGH);

    else if (livro <= 80)
        digitalWrite(_led4, HIGH);

    else
        digitalWrite(_led5, HIGH);
}

void mostrarLivro() {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Livro:");
    lcd.print(livro);

    lcd.setCursor(0, 1);

    if (livros[livro - 1] == 1)
        lcd.print("Disponivel");
    else
        lcd.print("Emprestado");

    acenderFaixaLivro();
}

void iniciarSistema(
    int btProximo,
    int btAnterior,
    int btEmprestimo,
    int btDevolucao,
    int led1,
    int led2,
    int led3,
    int led4,
    int led5
) {

    _btProximo = btProximo;
    _btAnterior = btAnterior;
    _btEmprestimo = btEmprestimo;
    _btDevolucao = btDevolucao;

    _led1 = led1;
    _led2 = led2;
    _led3 = led3;
    _led4 = led4;
    _led5 = led5;

    pinMode(_btProximo, INPUT_PULLUP);
    pinMode(_btAnterior, INPUT_PULLUP);
    pinMode(_btEmprestimo, INPUT_PULLUP);
    pinMode(_btDevolucao, INPUT_PULLUP);

    pinMode(_led1, OUTPUT);
    pinMode(_led2, OUTPUT);
    pinMode(_led3, OUTPUT);
    pinMode(_led4, OUTPUT);
    pinMode(_led5, OUTPUT);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Biblioteca");

    lcd.setCursor(0, 1);
    lcd.print("Automatizada");

    delay(2000);

    for (int i = 0; i < TOTAL_LIVROS; i++) {

        livros[i] = EEPROM.read(i);

        if (livros[i] > 1) {

            livros[i] = 1;
            EEPROM.write(i, 1);
        }
    }

    mostrarLivro();
}

void executarSistema() {

    // Próximo livro
    if (digitalRead(_btProximo) == LOW) {

        livro++;

        if (livro > 100)
            livro = 1;

        mostrarLivro();

        delay(250);
    }

    // Livro anterior
    if (digitalRead(_btAnterior) == LOW) {

        livro--;

        if (livro < 1)
            livro = 100;

        mostrarLivro();

        delay(250);
    }

    // Empréstimo
    if (digitalRead(_btEmprestimo) == LOW) {

        if (livros[livro - 1] == 1) {

            livros[livro - 1] = 0;

            EEPROM.write(livro - 1, 0);

            lcd.clear();
            lcd.print("Emprestado");

            delay(1000);
        }

        mostrarLivro();
    }

    // Devolução
    if (digitalRead(_btDevolucao) == LOW) {

        livros[livro - 1] = 1;

        EEPROM.write(livro - 1, 1);

        lcd.clear();
        lcd.print("Devolvido");

        delay(1000);

        mostrarLivro();
    }
}
