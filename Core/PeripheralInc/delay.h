#ifndef __DELAY_H
#define __DELAY_H
#include "os.h"
extern void delay_init(void);
extern void delay_us(uint32_t us);
extern void delay_ms(uint16_t nms);
#endif

