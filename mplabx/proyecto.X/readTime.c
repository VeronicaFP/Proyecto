#include "readTime.h"

unsigned int segundos, milisegundos,microsegundos;
//unsigned int timer0=65160; //valor del timer0 para que la interrupción salte cada milisegundo
//unsigned int timer0=5536;
unsigned int timer0 = 65416;
//rutina de interrupción
/*
 * La interrupción salta cada 1e-4 segundos,restaura el valor del timer0
 */

void timer0_isr(){
    INTCONbits.TMR0IF = LOW; //Baja el flag de la interrupción
    WriteTimer0(timer0);
    return;
}
  /*
   * Comenzar el timer
   * Pone la cuenta de segundos y milisegundos a 0, configura en registro de
   * control de interrupciones
   * Abre el timer 0 con 16 bits y preescaler de 32
   * Escribe en el registro del timer 0 el valor necesario para que la
   * interrupción salte cada milisegundo
   */
  void startTimer(){
      segundos = 0;
      milisegundos = 0;
      INTCONbits.GIE =1; //Interrupciones globales (y alta prioridad)
      INTCONbits.PEIE = 1; //Interrupciones perifericos (y baja prioridad)
      INTCONbits.TMR0IE = 1; //Interrupciones timer 0

      //1e-4 seg
      OpenTimer0(TIMER_INT_ON&T0_16BIT&T0_SOURCE_INT&T0_PS_1_1);
      WriteTimer0(timer0);
  }

  /*
   * Desactiva el timer 0
   */
  void endTimer(){
      CloseTimer0();
  }

  /*
   * Devuelve el valor de los segundos
   */
  int gets(){
      return segundos;
  }

  /*
   * Devuelve el valor de los milisegundos
   */
   int getms(){
      return milisegundos;
  }

   void sets(int seg){
       segundos = seg;
   }
   void setms(int ms){
       milisegundos = ms;
   }




