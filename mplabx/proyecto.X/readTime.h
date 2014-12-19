/* 
 * File:   readTime.h
 * Author: Verónica
 *
 * Created on 1 de diciembre de 2014, 12:23
 */

#ifndef READTIME_H
#define	READTIME_H

#include "main.h"

void timer0_isr(void);
void startTimer(void);
void endTimer(void);
int gets(void);
int getms(void);
void sets(int seg);
void setms(int ms);


#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* READTIME_H */

