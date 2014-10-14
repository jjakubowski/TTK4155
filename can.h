/*
 * can.h
 *
 *  Created on: 14 paŸ 2014
 *      Author: Jakub
 */

#ifndef CAN_H_
#define CAN_H_

typedef struct{
	unsigned int id;
	uint8_t length;
	uint8_t data[8];
} can_message_t;

#endif /* CAN_H_ */
