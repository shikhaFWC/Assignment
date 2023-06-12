#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>


const uint8_t GRAY_CODE[8] = {0b000, 0b001, 0b011, 0b010, 0b110, 0b111, 0b101, 0b100};

#define LED_Q0_PIN PD2
#define LED_Q1_PIN PD3
#define LED_Q2_PIN PD4
#define LED_D1_PIN PD5


int main(void) 
{
  static uint8_t counter = 0; //initialize the couner to 0

  DDRD=0b00111100; //Defining pin 2,3,4,5 as output
  DDRB=0b00100000; //Defining pin 13 as output
  
  PORTD=0b11000000;
  PORTB=0b00000011;
  
  DDRD |= (1 << LED_Q0_PIN) | (1 << LED_Q1_PIN) | (1 << LED_Q2_PIN) | (1 << LED_D1_PIN);
 
  while(1)
  {
  
  PORTB = ((1 <<  PB5)); //set the LED high at pin13
  _delay_ms(500);


uint8_t counter = (counter + 1) % 8; //update the counter

  
//calculating the values for Q0,Q1,Q2 and D1
  bool Q0 = (GRAY_CODE[counter] & 0b001) >> 0;
  bool Q1 = (GRAY_CODE[counter] & 0b010) >> 1;
  bool Q2 = (GRAY_CODE[counter] & 0b100) >> 2;

  bool D1 = (!Q2 && Q0) || (Q1 && !Q0);

     
 PORTD =  (Q0 << LED_Q0_PIN) | (Q1 << LED_Q1_PIN) | (Q2 << LED_Q2_PIN) | (D1 << LED_D1_PIN);

     
  PORTB = ((0 <<  PB5));
  _delay_ms(500);
  
  }
  
  return 0;
  }
