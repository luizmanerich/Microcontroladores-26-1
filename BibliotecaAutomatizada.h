#ifndef BIBLIOTECAAUTOMATIZADA_H
#define BIBLIOTECAAUTOMATIZADA_H

#include <Arduino.h>

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
);

void executarSistema();

#endif
