/* 
 * File:   i2cFunct.h
 * Author: Verónica
 *
 * Created on 1 de diciembre de 2014, 12:35
 */

#ifndef I2CFUNCT_H
#define	I2CFUNCT_H

#include "main.h"
void I2C_open(unsigned char sync_mode, unsigned char slew, unsigned char baud_clock);
void I2C_send(unsigned char reg);
void init_I2C();
#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* I2CFUNCT_H */

