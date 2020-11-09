/*
 * transmitter.c
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



unsigned char serialCheckTxReady(void)
{
	return( UCSR0A & 0x20 ) ;  // nonzero if transmit register is ready to receive new data.
}




void serialWrite(unsigned char DataOut)
{
	while (serialCheckTxReady() == 0)  // while NOT ready to transmit
	{;;}
	UDR0 = DataOut;
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


	serial_init(MYUBRR);

	while (1)  
	{
		serialWrite(1);
		_delay_ms(750); //delay just so we can see the receiver LEDs on and off

		serialWrite(0);
		_delay_ms(750);

		
	} 
	
	return 0;
}

