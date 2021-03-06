/*
 * S_SEGMENT.h
 *
 * Created: 12/11/2020 12:54:43 PM
 *  Author: Amrha
 */ 


#ifndef S_SEGMENT_H_
#define S_SEGMENT_H_

#include "S_SEGMENT_CONFIG.h"
#include "STD_TYPES.h"

void initialize_S_SEGMENT();
void turn_ON_S_SEGMENT_1();
void turn_ON_S_SEGMENT_2();
void turn_ON_S_SEGMENT_DOT();
void show_ON_S_SEGMENT(uint8_t value);
void turn_OFF_S_SEGMENT_1();
void turn_OFF_S_SEGMENT_2();
void turn_OFF_S_SEGMENT_DOT();


#endif /* S_SEGMENT_H_ */
