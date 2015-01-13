#include "readTime.h"

unsigned int timer0 = 59536;//Valor de carga del timer0 para interrupci�n cada 500us
//unsigned int timer0 = 53536;//1ms
//unsigned int timer0 = 5536;
//rutina de interrupci�n
/*
 * La interrupci�n salta cada 500us segundos,restaura el valor del timer0
 */

void timer0_isr(){
    INTCONbits.TMR0IF = LOW; //Baja el flag de la interrupci�n
    WriteTimer0(timer0);//Carga el timer0
    return;
}
  /*
   * Comenzar el timer
   * Pone la cuenta de segundos y milisegundos a 0, configura en registro de
   * control de interrupciones
   * Abre el timer 0 con 16 bits y preescaler de 32
   * Escribe en el registro del timer 0 el valor necesario para que la
   * interrupci�n salte cada milisegundo
   */
  void startTimer(){
      INTCONbits.GIE =1; //Interrupciones globales
      INTCONbits.PEIE = 1; //Interrupciones perifericos
      INTCONbits.TMR0IE = 1; //Interrupciones timer 0
      OpenTimer0(TIMER_INT_ON&T0_16BIT&T0_SOURCE_INT&T0_PS_1_1);
      WriteTimer0(timer0);
  }

  /*
   * Desactiva el timer 0
   */
  void endTimer(){
      CloseTimer0();
  }




