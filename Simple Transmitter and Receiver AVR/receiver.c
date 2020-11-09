/*
 * receiver.c
 *
 * Created: 10/23/2020 9:40:30 AM
 * Author : Ahmed Mohamud
 */ 

#include <avr/io.h>
#include <util/delay.h>
//#include <avr/interrupt.h>
#define F_CPU 16000000  // 16 MHz oscillator.
#define BaudRate 9600
#define MYUBRR (F_CPU / 16 / BaudRate ) - 1






unsigned char serialRead(void)
{
	while( !(UCSR0A & (1 << RXC0)) )
	;
	return UDR0;
}




int setLed(int val)
{
	// Power-up pins when receiving (1) and off when receiving (0)
	if (val == 1) PORTD = 0x10;
	if (val == 0) PORTD = 0x00;
	return 1;
}



void serial_init(unsigned int bittimer)
{
	/* Set the baud rate */
	UBRR0H = (unsigned char) (bittimer >> 8);
	UBRR0L = (unsigned char) bittimer;
	/* set the framing to 8N1 (8 data bits + 1 stop bit (default) */
	UCSR0C = (3 << UCSZ00);
	/* Enable receiver and transmitter */
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	return;
}



int main (void)
{

	// Set Port D7:4 pins as all outputs for the LEDs
	DDRD = 0xF0;
	

	serial_init(MYUBRR);

	while (1)  
	{

		//receive data and if 1 or 0 light or off LEDs
		received = serialRead();
		setLed(received);
		

	} 
	
	return 0;
}

