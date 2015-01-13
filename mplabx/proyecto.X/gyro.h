/* 
 * File:   gyro.h
 * Author: Verónica
 *
 * Created on 1 de diciembre de 2014, 12:37
 */

#ifndef GYRO_H
#define	GYRO_H

#include "main.h"
void I2C_read_byte_gyro(unsigned char reg,unsigned char *rdptr);
void I2C_read_data_gyro(unsigned char reg,unsigned char *rdptr);
void I2C_turn_on_gyro(void);
void I2C_write_reg_gyro(unsigned char reg, unsigned char valor);
void init_GYRO(void);
void stop_GYRO();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* GYRO_H */

