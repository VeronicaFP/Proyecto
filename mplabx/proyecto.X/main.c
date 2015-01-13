/* 
 * File:   newmain.c
 * Author: Verónica
 *
 * Created on 1 de diciembre de 2014, 11:53
 */

#include "main.h"

signed char temperature = 0;
signed int acc_x, acc_y, acc_z;
signed int gyr_x, gyr_y, gyr_z;
char buf[10];
char enter[] = "\n";
char mid[] = "+";
char x[] = "X", y[] = "Y", z[] = "Z";
char start[] = "#";
char end[] = "~";

/*
 *
 */
void readData() {
    I2C_read_data_acc(LSM303DLM_OUT_X_L_A, &acc_x);
    I2C_read_data_acc(LSM303DLM_OUT_Y_L_A, &acc_y);
    I2C_read_data_acc(LSM303DLM_OUT_Z_L_A, &acc_z);
    //I2C_read_data_gyro(L3G4200D_OUT_TEMP, &temperature);
    //I2C_read_data_gyro(L3G4200D_OUT_X_L, &gyr_x);
    //I2C_read_data_gyro(L3G4200D_OUT_Y_L, &gyr_y);
    //I2C_read_data_gyro(L3G4200D_OUT_Z_L, &gyr_z);

}

void main() {
    TRISC = 0b00000000; // portC : output
    LATC = 0b00000000; // portC = 0
    init_UART();
    init_I2C();
    //init_GYRO();
    init_ACC();
    LED_RED_On();
    LED_GREEN_On();

    while (1) {
    };

}

void putintUSART( char *data)
{
    while(BusyUSART());
    putcUSART(*(data+1));
    while(BusyUSART());
    putcUSART(*data);

}

void imprimir() {
    while(BusyUSART());
    WriteUSART(35);
    while(BusyUSART());
    WriteUSART(88);
    while(BusyUSART());
    itoa(buf, acc_x, 10);
    putsUSART(&buf);
    //putintUSART(&acc_x);
    while(BusyUSART());
    WriteUSART(43);
    while(BusyUSART());
    WriteUSART(89);
    while(BusyUSART());
    //putintUSART(&acc_y);
    itoa(buf, acc_y, 10);
    putsUSART(&buf);
    while(BusyUSART());
    WriteUSART(43);
    while(BusyUSART());
    WriteUSART(90);
    while(BusyUSART());
    //putintUSART(&acc_z);
    itoa(buf, acc_z, 10);
    putsUSART(&buf);
    while(BusyUSART());
    WriteUSART(43);
    while(BusyUSART());
    WriteUSART(33);
    //itoa(buf, temperature, 10);
    //  putsUSART(&buf);
    //  putsUSART(&mid);
    //putsUSART(&start);
    //itoa(buf, acc_x, 10);
    //putintUSART(&acc_x);
    //putsUSART(&mid);
    //itoa(buf, acc_y, 10);
    //putsUSART(&buf);
    //putsUSART(&mid);
    //itoa(buf, acc_z, 10);
    //putsUSART(&buf);
    //putsUSART(&mid);
    //putsUSART(&end);
    //putsUSART(&enter);

}

void interrupt Interruption() {
    //Timer interruption
    if (INTCONbits.PEIE & PIR1bits.RCIF) {
        uart_isr();
    } else {
        if (INTCONbits.TMR0IE & INTCONbits.TMR0IF) {
            timer0_isr();
            readData();
            imprimir();
        }
    }
}