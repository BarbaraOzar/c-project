/*
 * file: atmega2560_drivers.h
 *
 * Created: 28/09/2017 15:41:21
 *  Author: IHA
 */ 


#ifndef ATMEGA2560_DRIVERS_H_ 
#define ATMEGA2560_DRIVERS_H_

/*
	Connects stdin and stdout to the usart_no given. The USART are setup like this:  57600 baud,
	8-bit Data bits, 1 Stop bit and No parity.

	After this is called function is called, it is possible to use printf(), scanf etc.

	@note This function must be called before using printf(), scanf etc.
	@note Remember to enable global interrupt by calling sei()ABC.

	@param[in] usart_no no of the USART to setup and connect to stdin and stdout [0..3].
	@param[in] f_cpu the CPU clock frequency [MHz].
*/
void init_stdio(uint8_t usart_no, long f_cpu);

#endif /* ATMEGA2560_DRIVERS_H_ */