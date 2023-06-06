.include "/sdcard/Download/digital-design/trunk/assembly/setup/codes/m328Pdef.inc"

sbi DDRB, 5 ;set pin 13 as output pin (DDRB pin 5)

ldi r16, 0b00000101 
out TCCR0B, r16 

clr r18 

ldi r20,0b00100000 

loop:
 eor r18, r20  ;change the output of LED
 out PORTB, r18 
 ldi r19, 0b01000000   
 rcall PAUSE  
 rjmp loop
 
PAUSE: ;this is delay
lp2:   ;loop runs 64 times
        IN r16, TIFR0
        ldi r17, 0b00000010
        AND r16, r17 ;need second bit
        BREQ PAUSE 
        OUT TIFR0, r17

 dec r19
 brne lp2
 ret
