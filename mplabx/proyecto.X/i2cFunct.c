#include "i2cFunct.h"


/*
 * Configuración del I2C para su funcionamiento
 * Argumentos:
 * sync_mode : modo de funcionamiento (mirar en i2c.h)
 * slew: velocidad (mirar en i2c.h)
 * baud_clock: valor de configuración dl registro SSPADD
 */
void I2C_open(unsigned char sync_mode, unsigned char slew, unsigned char baud_clock){
    //sync_mode    parameter to config SSPCON register (mode select)
    //slew         parameter to config SSPCON register (slew rate control)
    //baud_clock   parameter to config SSPADD

    CloseI2C();                     //Close I2C if was operating
    OpenI2C(sync_mode,slew);        //Inicialice the I2C mode for sync_mode
    SSPADD = baud_clock;
}

/*
 * Envío de un byte por i2c
 * Argumentos:
 * reg: byte a enviar
 */
void I2C_send(unsigned char reg){

    unsigned char data;
    signed char status;

    data = SSPBUF;  //read any previous stored content in buffer to clear buffer full status
    do
    {
        status = WriteI2C(reg);
        IdleI2C();
        if (status == -1) //check if bus collision happend
        {
            data = SSPBUF; //upon bus collision detection clear the buffer
            SSPCON1bits.WCOL = 0; //clear the bus collision status bit
        }
    }
    while(status!=0); //write until successful communication
}

void init_I2C(){
    I2C_open(MASTER,SLEW_ON,BRG_I2C);
}
