#include "gyro.h"

/*
 * Lectura de un byte del giroscopo
 * Argumentos:
 * reg: dirección del registro del que vamos a leer el byte
 * *rdptr: puntero con la dirección de la variable donde se almacena el valor leído
 * (Se sigue el protocolo especificado en el datasheet del giroscopo)
 */
void I2C_read_byte_gyro(unsigned char reg,unsigned char *rdptr){

    //--START I2C--
    IdleI2C();
    StartI2C();
    //--SAD+W---    &&   SAK
        //***write the address of the device for communication***
    I2C_send(GYR_ADDRESS_WRITE);
    //--SUB--       &&   SAK
        //**write the subaddress of the register
    I2C_send(reg);

    //---RESTART I2C COMMUNICATION
    RestartI2C();
    //--SAD+R---   &&    SAK
        //***write the address of the device for communication***
    I2C_send(GYR_ADDRESS_READ);
    // DATA
    //***Recive data form slave***
    //
    while(getsI2C(rdptr,1));

    NotAckI2C();
    while( SSPCON2bits.ACKEN!=0); //wait till ack sequence is complete

    StopI2C();

}

/*
 * Lectura de datos del giroscopo
 * El formato de los datos recogidos por el giroscopo es de un valor c2 de 16bits
 * Argumentos:
 *  reg: dirección del registro al que se va a acceder para leer
 *  *rdptr: puntero con la dirección de la variable dond se va a almacenar el
 *          el valor leído
 */
void I2C_read_data_gyro(unsigned char reg,unsigned char *rdptr){

    //--START I2C--
    IdleI2C();
    StartI2C();
    //--SAD+W---    &&   SAK
        //***write the address of the device for communication***
    I2C_send(GYR_ADDRESS_WRITE);
    //--SUB--       &&   SAK
        //**write the subaddress of the register
    reg = reg|0b10000000;
    I2C_send(reg);

    //---RESTART I2C COMMUNICATION
    RestartI2C();
    //--SAD+R---   &&    SAK
        //***write the address of the device for communication***
    I2C_send(GYR_ADDRESS_READ);
    // DATA
    //***Recive data from slave***
    while(getsI2C(rdptr,1));
    //MAK
    AckI2C();
    //DATA
    //***Recive data from slave***
    while(getsI2C(rdptr+1,1));
    //NMAK
    NotAckI2C();
    while( SSPCON2bits.ACKEN!=0); //wait till ack sequence is complete
    //STOP
    StopI2C();

}

/*
 * Encendido del giroscopo
 * Por defecto el giroscopo está en off, para proceder a la toma de datos
 * es necesario encenderlo
 */
void I2C_turn_on_gyro(void){
    // En el registro de control 1 se establece el output data rate, el ancho
    // de banda, se activa el giroscopo y los ejes que funcionan
    I2C_write_reg_gyro(L3G4200D_CTRL_REG1,0x0F); //0F: ODR = 100Hz Cutoff = 12.5
                                                 // Activos ejes: x, y , z

    // En el registro de control 4 se configura la actualización del bloque de
    // datos, el modo big o little endian y el valor del fullscale
    I2C_write_reg_gyro(L3G4200D_CTRL_REG4,0x20);//20: actualización continua
                                                // big endian, 2000dps, modo normal
}
void I2C_write_reg_gyro(unsigned char reg, unsigned char valor){

    //check for bus idle condition
    IdleI2C();
    //--START I2C--
    StartI2C();

    //--SAD+W---  &&   SAK
        //***write the address of the device for communication***
    I2C_send(GYR_ADDRESS_WRITE);
    //SAK
    //--SUB--     &&   SAK
        //**write the subaddress of the register
    I2C_send(reg);
    //--DATA--    &&   SAK
    //***Send data to write***
    I2C_send(valor);

    StopI2C();

}
void init_GYRO(){
    I2C_turn_on_gyro();
}
