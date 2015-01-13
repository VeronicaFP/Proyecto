/* 
 * File:   accmag.h
 * Author: Verónica
 *
 * Created on 1 de diciembre de 2014, 13:39
 */

#ifndef ACCMAG_H
#define	ACCMAG_H

#include "main.h"

/***ACCELEROMETER***/
/*CTRL_REG_1*/
#define POWER_DOWN     0b00000000 /*Power mode selection: power down*/
#define NORMAL_MODE    0b00100000 /*Power mode selection: normal mode*/
#define LOW_POWER_005  0b01000000 /*Power mode selection: low power: 0.5Hz*/
#define LOW_POWER_01   0b01100000 /*Power mode selection: low power: 1Hz*/
#define LOW_POWER_02   0b10000000 /*Power mode selection: low power: 2Hz*/
#define LOW_POWER_05   0b10100000 /*Power mode selection: low power: 5Hz*/
#define LOW_POWER_10   0b11000000 /*Power mode selection: low power: 10Hz*/

#define CO37_ODR50      0b00000000 /*normal opareation: ODR = 50Hz low power: cutoff 37Hz*/
#define CO74_ODR100     0b00001000 /*normal opareation: ODR = 100Hz low power: cutoff 74Hz*/
#define CO292_ODR400    0b00010000 /*normal opareation: ODR = 400Hz low power: cutoff 292Hz*/
#define CO780_ODR1000   0b00011000 /*normal opareation: ODR = 1kHz low power: cutoff 780Hz*/

/*CTRL_REG_2*/
#define HP_NORMAL_MODE 0b00000000
#define HP_REFERENCE_SIGNAL 0b00100000
#define HP_ON 0b00010000
#define HP_OFF 0b00000000
#define HP_CUT_OFF_64 0b00000011
#define HP_CUT_OFF_32 0b00000010
#define HP_CUT_OFF_16 0b00000001
#define HP_CUT_OFF_8 0b00000000

/*CTRL_REG_4*/
#define CONTINUOUS_UPDATE 0b00000000
#define NOT_CONTINUOUS_UPDATE 0b10000000
#define FS_2g 0b00000000 /*full scale: +-2g*/
#define FS_4g 0b00010000 /*full scale: +-4g*/
#define FS_8g 0b00110000 /*full scale: +-8g*/

/*CTRL_5*/
#define SLEEP_TO_WAKEUP_ON  0b00000011
#define SLEEP_TO_WAKEUP_OFF 0b00000000

/***MAGNETOMETER***/
#define M00075 0b00000000 /*0.75Hz*/
#define M0015  0b00000100 /*1.5Hz*/
#define M003   0b00001000 /*3Hz*/
#define M0075  0b00001100 /*7.5Hz*/
#define M015   0b00010000 /*15Hz*/
#define M030   0b00010100 /*30Hz*/
#define M075   0b00011000 /*75Hz*/
#define M220   0b00011100 /*220Hz*/

#define CONTINUOUS_CONVERSION_MODE  0b00000000
#define SINGLE_CONVERSION_MODE      0b00000001
#define SLEEP_MODE                  0b00000010

void I2C_write_reg_acc(unsigned char reg, unsigned char valor);
void I2C_read_byte_acc(unsigned char reg,unsigned char *rdptr);
void I2C_read_data_acc(unsigned char reg,unsigned char *rdptr);
void data_acc(int *ptr);

void I2C_write_reg_mag(unsigned char reg, unsigned char valor);
void I2C_read_byte_mag(unsigned char reg,unsigned char *rdptr);
void I2C_read_data_mag(unsigned char reg,unsigned char *rdptr);
void data_mag(int *ptr);

void I2C_turn_on_acc(unsigned char mode,unsigned char data_rate,unsigned char full_scale,unsigned char sleep_wakeup);
void I2C_turn_on_mag(unsigned char data_rate,unsigned char mode);
void init_ACC();
void init_MAG();
void stop_ACC();
void stop_MAG();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* ACCMAG_H */

