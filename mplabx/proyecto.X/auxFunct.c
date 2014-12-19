#include "auxFunct.h"
/*
 * retardo de x milisegundos (x múltiplos de 10)
 * Argumentos:
 * x: milisegundos
 */
void x_delay_ms(int x) {
    int cont = x/10;
    while (cont > 0){
        __delay_ms(10);
        cont --;
    }
}
