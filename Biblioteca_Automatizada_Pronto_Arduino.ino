#include "BibliotecaAutomatizada.h"

// =====================
// PINAGEM
// =====================

const int btProximo    = 2;
const int btAnterior   = 3;
const int btEmprestimo = 5;
const int btDevolucao  = 6;

const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 10;
const int led5 = 11;

// =====================

void setup() {

    iniciarSistema(
        btProximo,
        btAnterior,
        btEmprestimo,
        btDevolucao,
        led1,
        led2,
        led3,
        led4,
        led5
    );
}

void loop() {

    executarSistema();
}
