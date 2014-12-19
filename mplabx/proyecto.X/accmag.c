#include "accmag.h"

/*
 * Escribir un registro en el acelerómetro
 * Argumentos:
 *  reg:dirección del registro
 *  valor:byte a escribir
 */
void I2C_write_reg_acc(unsigned char reg, unsigned char valor){

    //check for bus idle condition
    IdleI2C();
    //--START I2C--
    StartI2C();

    //--SAD+W---  &&   SAK
        //***write the address of the device for communication***
    I2C_send(ACC_ADDRESS_WRITE);
    //SAK
    //--SUB--     &&   SAK
        //**write the subaddress of the register
    I2C_send(reg);
    //--DATA--    &&   SAK
    //***Send data to write***
    I2C_send(valor);

    StopI2C();

}

/*
 *Leer un byte del acelerómetro
 * Argumentos:
 *  reg:dirección del registro del que se lee
 *  *rdptr: puntero de la variable donde se almacena el valor leído
 */
void I2C_read_byte_acc(unsigned char reg,unsigned char *rdptr){

    //--START I2C--
    IdleI2C();
    StartI2C();
    //--SAD+W---    &&   SAK
        //***write the address of the device for communication***
    I2C_send(ACC_ADDRESS_WRITE);
    //--SUB--       &&   SAK
        //**write the subaddress of the register
    I2C_send(reg);

    //---RESTART I2C COMMUNICATION
    RestartI2C();
    //--SAD+R---   &&    SAK
        //***write the address of the device for communication***
    I2C_send(ACC_ADDRESS_READ);
    // DATA
    //***Recive data form slave***
    while(getsI2C(rdptr,1));

    NotAckI2C();
    while( SSPCON2bits.ACKEN!=0); //wait till ack sequence is complete

    StopI2C();

}

/*
 * Leer datos del acelerómetro
 * ---Los datos del acelerómetro se almacenan en variables de 16 bits
 * ---por tanto es necesario leer dos bytes, están almacenados como
 * ---un dato de 12bits justificado a la izquierda por lo que será
 * ---necesario adaptarlo a una variable de 16bits manteniendo la condición
 * ---de complemento a 2
 * Argumentos:
 *  reg: dirección del registro del que se lee
 *  *rdptr: puntero de la variable donde se almacena el valor leído
 */
void I2C_read_data_acc(unsigned char reg,unsigned char *rdptr){

    //--START I2C--
    IdleI2C();
    StartI2C();
    //--SAD+W---    &&   SAK
        //***write the address of the device for communication***
    I2C_send(ACC_ADDRESS_WRITE);
    //--SUB--       &&   SAK
        //**write the subaddress of the register
    reg = reg|0b10000000;
    I2C_send(reg);

    //---RESTART I2C COMMUNICATION
    RestartI2C();
    //--SAD+R---   &&    SAK
        //***write the address of the device for communication***
    I2C_send(ACC_ADDRESS_READ);
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
    data_acc(rdptr);

}

/*
 * Función interna para realizar el desplazamiento en la lectura de datos del
 * acelerómetro
 */
void data_acc(signed int *ptr){
    *ptr = *ptr >> 4;
}

/*
 * Escribir un registro en el magnetómetro
 * Argumentos:
 *  reg:dirección del registro
 *  valor:byte a escribir
 */
void I2C_write_reg_mag(unsigned char reg, unsigned char valor){

    //check for bus idle condition
    IdleI2C();
    //--START I2C--
    StartI2C();

    //--SAD+W---  &&   SAK
        //***write the address of the device for communication***
    I2C_send(MAG_ADDRESS_WRITE);
    //SAK
    //--SUB--     &&   SAK
        //**write the subaddress of the register
    I2C_send(reg);
    //--DATA--    &&   SAK
    //***Send data to write***
    I2C_send(valor);

    StopI2C();

}

/*
 *Leer un byte del acelerómetro
 * Argumentos:
 *  reg:dirección del registro del que se lee
 *  *rdptr: puntero de la variable donde se almacena el valor leído
 */
void I2C_read_byte_mag(unsigned char reg,unsigned char *rdptr){

    //--START I2C--
    IdleI2C();
    StartI2C();
    //--SAD+W---    &&   SAK
        //***write the address of the device for communication***
    I2C_send(MAG_ADDRESS_WRITE);
    //--SUB--       &&   SAK
        //**write the subaddress of the register
    I2C_send(reg);

    //---RESTART I2C COMMUNICATION
    RestartI2C();
    //--SAD+R---   &&    SAK
        //***write the address of the device for communication***
    I2C_send(MAG_ADDRESS_READ);
    // DATA
    //***Recive data form slave***

    while(getsI2C(rdptr,1));

    NotAckI2C();
    while( SSPCON2bits.ACKEN!=0); //wait till ack sequence is complete

    StopI2C();

}

/*
 * Leer datos del acelerómetro
 * ---Los datos del acelerómetro se almacenan en variables de 16 bits
 * ---por tanto es necesario leer dos bytes, están almacenados como
 * ---un dato de 12bits justificado a la derecha por lo que será
 * ---necesario adaptarlo a una variable de 16bits manteniendo la condición
 * ---de complemento a 2
 * Argumentos:
 *  reg: dirección del registro del que se lee
 *  *rdptr: puntero de la variable donde se almacena el valor leído
 */
void I2C_read_data_mag(unsigned char reg,unsigned char *rdptr){

    //--START I2C--
    IdleI2C();
    StartI2C();
    //--SAD+W---    &&   SAK
        //***write the address of the device for communication***
    I2C_send(MAG_ADDRESS_WRITE);
    //--SUB--       &&   SAK
        //**write the subaddress of the register
    I2C_send(reg);

    //---RESTART I2C COMMUNICATION
    RestartI2C();
    //--SAD+R---   &&    SAK
        //***write the address of the device for communication***
    I2C_send(MAG_ADDRESS_READ);
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
    data_mag(rdptr);

}

/*
 * Adaptación del dato de c2 de 12 bits a c2 de 16bits
 */
void data_mag(signed int *ptr){
    if ((*ptr&0x0800) == (0x0800)){
        *ptr = 0xF000 + *ptr;
    }
}

/*
 * Encendido del acelerómetro
 * Argumentos:
 *  mode: modo de funcionamiento
 *  data_rate: velocidad de los datos
 *  full_scale: rango de datos
 *  sleep_wakeup
 */
void I2C_turn_on_acc(unsigned char mode,unsigned char data_rate,unsigned char full_scale,unsigned char sleep_wakeup){
    I2C_write_reg_acc(LSM303DLM_CTRL_REG1_A,data_rate|mode|0x07);
    //I2C_write_reg_acc(LSM303DLM_CTRL_REG2_A,HP_CUT_OFF_8|HP_NORMAL_MODE|HP_OFF);
    I2C_write_reg_acc(LSM303DLM_CTRL_REG2_A,0);

    I2C_write_reg_acc(LSM303DLM_CTRL_REG4_A,NOT_CONTINUOUS_UPDATE|full_scale);
    I2C_write_reg_acc(LSM303DLM_CTRL_REG5_A,sleep_wakeup);
}

/*
 * Encendido del magnetómetro
 * Argumentos:
 *  mode: modo de funcionamiento
 *  data_rate: velocidad de los datos
 */
void I2C_turn_on_mag(unsigned char data_rate,unsigned char mode){
    I2C_write_reg_mag(LSM303DLM_CRA_REG_M,data_rate);
    I2C_write_reg_mag(LSM303DLM_MR_REG_M,mode);
}

void init_ACC(){
    I2C_turn_on_acc(NORMAL_MODE,CO780_ODR1000,FS_8g,SLEEP_TO_WAKEUP_OFF);
}
void init_MAG(){
    I2C_turn_on_mag(M220, CONTINUOUS_CONVERSION_MODE);
}