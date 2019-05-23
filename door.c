#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<stdint.h>
#define CLR_BIT(PORT,PIN) PORT&=~(1<<PIN)
#define SET_BIT(PORT,PIN) PORT|=(1<<PIN)

int ign=0;
int speed;

int i=0;
int j=0;
int child=0;
	
  int ADC_Read(char channel)							
  {
      ADMUX = 0x40 | (channel & 0x07);//Channel selection
      ADCSRA|=(1<<ADSC);//Set ADSC and Start Analog to digital conversion
      while((ADCSRA  & 1<<ADSC));//wait till ADSC becomes 0						
      _delay_ms(1);									
      return ADC;									
  }


main()
{
    EICRA|=(1<<ISC10);    
  EIMSK|=(1<<INT1)|(1<<INT0);
    SREG|=(1<<7);
  
    ADMUX|=(1<<REFS0);
    ADCSRA|=(1<<ADEN);

    CLR_BIT(DDRD,3); //ignition switch
    SET_BIT(PORTD,3);
   	
  	SET_BIT(DDRB,1);
  	SET_BIT(DDRB,2);
  	CLR_BIT(PORTB,1);
  	CLR_BIT(PORTB,2);
  
   CLR_BIT(DDRB,3);         //keep all LEDs off
   CLR_BIT(PORTB,3);
  
   CLR_BIT(DDRB,4);         //keep all LEDs off
   CLR_BIT(PORTB,4);
  
   CLR_BIT(DDRB,5);         //keep all LEDs off
   CLR_BIT(PORTB,5);
  

  while(1)
  {
     uint8_t Central_lock=0x00;
		Central_lock=PINB;
    speed=ADC_Read(1);
    if(ign==1)
    {
      if((Central_lock&(1<<3))||speed>200)
      {
        SET_BIT(PORTB,1);
  		SET_BIT(PORTB,2);
        if((Central_lock&(1<<4)))
      {
        SET_BIT(PORTB,1);
       SET_BIT(PORTB,2);
        
        /*if((Central_lock&(1<<5)))
        {
            CLR_BIT(PORTB,1);
  			CLR_BIT(PORTB,2);
        }*/
        
      }
      else
      {
        
        if((Central_lock&(1<<5)))
        {
            CLR_BIT(PORTB,1);
  			CLR_BIT(PORTB,2);
        }

      }
      }
      else
      {
         CLR_BIT(PORTB,1);
  		CLR_BIT(PORTB,2);
      }     
    }
    }
    else
    {
      CLR_BIT(PORTB,1);
  		CLR_BIT(PORTB,2);
    }  
  }
}
  ISR(INT1_vect)
{
   ign=!(ign);

}













