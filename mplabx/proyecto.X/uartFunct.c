#include "uartFunct.h"
int CaracterRx = 0;
void init_UART() {
    CloseUSART(); //turn off usart if was previously on
    // --- configure USART
    unsigned char config = USART_TX_INT_OFF & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX&USART_BRGH_HIGH;
    unsigned int spbrg = 1249; //At 48MHz of oscillator frequency & baud rate of 9600
    OpenUSART(config, spbrg); //API configures USART for desired parameters
    unsigned char baudconfig = BAUD_16_BIT_RATE & BAUD_AUTO_OFF & BAUD_IDLE_TX_PIN_STATE_HIGH&BAUD_IDLE_RX_PIN_STATE_HIGH;
    baudUSART(baudconfig);
    INTCONbits.GIE = 1; //interrupciones globales
    INTCONbits.PEIE = 1; //interrupciones de perifericos
    PIE1bits.RCIE = 1;//permite interrupciones usart en recepción
}
void uart_isr(){
    PIR1bits.RCIF=LOW;
    CaracterRx = ReadUSART();
    while(BusyUSART());
    if (CaracterRx == 83){
        startTimer();
    }else if(CaracterRx == 88){
        endTimer();
    }
    
}

void putiUSART(char *data){
    while(BusyUSART());
    putcUSART(*data);
    *data--;
    while(BusyUSART());
    putcUSART(*data);
}
/*
void uart_isr(){
   CaracterRx=ReadUSART();
   while(BusyUSART());
   putcUSART(CaracterRx);
    switch (CaracterRx){
        case 48:
           LED_GREEN_Off();
            break;
        case 49:
            LED_GREEN_On();
            break;
        case 50:
            LED_RED_Off();
            break;
        case 51:
            LED_RED_On();
            break;
    }
    PIR1bits.RCIF=0;
}
*/