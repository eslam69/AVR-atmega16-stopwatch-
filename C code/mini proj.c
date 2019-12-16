/* a project if digital clock using atmega16 timer1 and
 * a decoder
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


unsigned short sec_u = 0 ;
unsigned char sec_tenth = 0 ;
unsigned char minutes_u = 0 ;
unsigned char minutes_tenth = 0 ;
unsigned char hours_u = 0 ;
unsigned char hours_tenth = 0 ;

unsigned char pause = 0;

ISR(TIMER1_COMPA_vect)
{

 if ( !(pause==1) ){
   sec_u++ ;
  if (10 == sec_u)
  {
	  sec_tenth++ ;
	  sec_u = 0 ;
  }

  if (6==sec_tenth && 0==sec_u )
  {
	  minutes_u++ ;
	  sec_u =0 ;
	  sec_tenth =0 ;
  }
 if  (10==minutes_u)
 {
	 minutes_tenth++ ;
	 minutes_u = 0 ;
 }
 if (6==minutes_tenth && 0==minutes_u)
 {
	 hours_u++ ;
	 minutes_u =0 ;
	 minutes_tenth =0 ;

 }

 if(10==hours_u)
 {
   hours_tenth++ ;
   hours_u =0 ;

 }
 if(10==hours_tenth && 10==hours_u && 10 ==minutes_u && 10 ==minutes_tenth )
 {
	 sec_u = 0 ;
	sec_tenth = 0 ;
	minutes_u = 0 ;
	minutes_tenth = 0 ;
	hours_u = 0 ;
	 hours_tenth = 0 ;
 }

}

}

ISR(INT0_vect)
{
	     sec_u = 0 ;
		sec_tenth = 0 ;
		minutes_u = 0 ;
		minutes_tenth = 0 ;
		hours_u = 0 ;
		 hours_tenth = 0 ;
}

ISR(INT1_vect)
{
   pause = 1;

}
ISR(INT2_vect)
{
	 pause = 0;
}

void Timer1_CTC_Init(void)
{
	SREG   &= ~(1<<7);
	TCNT1 = 0;
	TIMSK  |=(1<<OCIE1A ) ;
	OCR1A = 1000 ;
    TCCR1B = (1<<CS12) | (1<<CS10) | (1<<WGM12)  ;
	SREG  |= (1<<7);
}


void INT0_reset_Init(void)
{
	SREG  &= ~(1<<7);
	DDRD  &= (~(1<<PD2));
	PORTD |= (1<<PD2);

	GICR  |= (1<<INT0);
	MCUCR |= (1<<ISC01);
	SREG  |= (1<<7);
}

void INT1_pause_Init(void)
{
	SREG  &= ~(1<<7);
	DDRD  &= (~(1<<PD3));
	GICR  |= (1<<INT1);
	MCUCR |= (1<<ISC00) | (1<<ISC01);
	SREG  |= (1<<7);
}

void INT2_start_Init(void)
{
	SREG   &= ~(1<<7);
	DDRB   &= (~(1<<PB2));
	PORTB  |= (1<<PB2) ;      // INTERNAL PULL UP ENABLE
	PINB   &=~(1<<PB2) ;

	GICR |= (1<<INT2);
	MCUCSR |= (1<<ISC2);
	SREG   |= (1<<7);
}

int main (void)
{

 DDRC |= 0x0F ; // decoder connected to first 4 pins in port c
 PORTC &= 0xF0 ; //initialize the lcd with zeros
 DDRA |= 0X3F;
 PORTA &= ~(0X3F);

 Timer1_CTC_Init() ;
 INT0_reset_Init() ;
 INT1_pause_Init() ;
 INT2_start_Init() ;

 while(1)
  {


	 PORTA = (1<<0);
	 PORTC = (PORTC & 0xF0) | (sec_u & 0x0F  ) ;
	 _delay_us(5) ;

	 PORTA = (1<<1);
	 PORTC = (PORTC & 0xF0) | (sec_tenth & 0x0F  ) ;
	  _delay_ms(5) ;

	  PORTA = (1<<2);
	 PORTC = (PORTC & 0xF0) | (minutes_u & 0x0F  ) ;
	  _delay_ms(5) ;

	  PORTA = (1<<3);
	 PORTC = (PORTC & 0xF0) | (minutes_tenth & 0x0F  ) ;
	  _delay_ms(5) ;

	  PORTA = (1<<4);
	 PORTC = (PORTC & 0xF0) | (hours_u & 0x0F  ) ;
	  _delay_ms(5) ;

	  PORTA = (1<<5);
	PORTC = (PORTC & 0xF0) | (hours_tenth & 0x0F  ) ;
	  _delay_ms(5) ;

  }

 }
