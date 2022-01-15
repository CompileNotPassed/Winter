#include "headfile.h"
int16 encoder[4];
uint16 encoderCount;

void getEncoder(){
	encoderCount++;
	encoder[2] = -qtimer_quad_get(QTIMER_1,QTIMER1_TIMER0_C0 );
    encoder[3] = qtimer_quad_get(QTIMER_1,QTIMER1_TIMER2_C2 );
    encoder[1] = qtimer_quad_get(QTIMER_2,QTIMER2_TIMER0_C3 );
    encoder[0] = -qtimer_quad_get(QTIMER_3,QTIMER3_TIMER2_B18);
        
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER0_C0 );
    qtimer_quad_clear(QTIMER_1,QTIMER1_TIMER2_C2 );
    qtimer_quad_clear(QTIMER_2,QTIMER2_TIMER0_C3 );
    qtimer_quad_clear(QTIMER_3,QTIMER3_TIMER2_B18);
}