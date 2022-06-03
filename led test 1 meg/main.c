/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 3/17/2021
Author  : 
Company : 
Comments: 


Chip type               : ATmega164P
Program type            : Application
AVR Core Clock frequency: 1.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#define F_CPU 1000000UL

#include <xc.h>
#include <util/delay.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define _bar0 0
#define _bar1 1
#define _bar2 2
#define _bar3 3
#define _bar4 4
#define _bar5 5
#define _bar6 6
#define _bar7 7
#define _bar8 8

#define _white 0
#define _yellow 1
#define _purple 2
#define _red 3
#define _blue 4
#define _green 5

#define VARB

#ifndef VARB
	#define _T0H 7
	#define _T0L 16
	#define _T1H 14
	#define _T1L 12
#endif
	
#ifdef VARB
	#define _T0H 8
	#define _T0L 17
	#define _T1H 16
	#define _T1L 7
#endif
//#define _delay_us delay_us
//#define _delay_ms delay_ms
// Declare your global variables here

void _delay_s(int s) {
	int i;
	for (i = 1; i <= 20*s; i++) {
		_delay_ms(1000);
	}
}

void passOneA(int port_value) {
	PORTA |= port_value;
    _delay_us(_T1H);
    PORTA = 0;
    _delay_us(_T1L);
}

void passOneC(int port_value) {
    PORTC |= port_value;
    _delay_us(_T1H);
    PORTC = 0;
    _delay_us(_T1L);
}

void passZeroA(int port_value) {
    PORTA |= port_value;
    _delay_us(_T0H);
    PORTA = 0;
    _delay_us(_T0L);
}

void passZeroC(int port_value) {
    PORTC |= port_value;
    _delay_us(_T0H);
    PORTC = 0;
    _delay_us(_T0L);
}

void passResetA() {
    PORTA = 0;
    _delay_us(1020);
}

void passResetC() {
    PORTC = 0;
    _delay_us(1020);
}

void passBar(int8_t bits[], int8_t bar) {
    int i;
    int8_t port_value;
    if (bar < 8) {
        port_value = 1<<bar;
        for (i = 0; i < 144; i++) {
            switch (bits[i]) {
                case 1:
                passOneA(port_value);
                break;
                default:
                passZeroA(port_value);
            }
        }
        passResetA();
    }
    else {
        bar -= 8;
        port_value = 1<<bar;
        for (i = 0; i < 144; i++) {
            switch (bits[i]) {
                case 1:
                passOneC(port_value);
                break;
                default:
                passZeroC(port_value);
            }
        }
        passResetC();
    }
}

void getBitsFromCube(int8_t bar, int8_t cube[], int8_t bits[]) {
    int i;
    int j;
    for (i = bar*6; i <= bar*6+5; i++) {
        if (cube[i] == 0) {
            for (j = (i-bar*6)*24; j <= (i-bar*6)*24+7; j++) {
                bits[j] = 1;
            }
            for (j = (i-bar*6)*24+8; j <= (i-bar*6)*24+7+8; j++) {
                bits[j] = 1;
            }
            for (j = (i-bar*6)*24+16; j <= (i-bar*6)*24+7+16; j++) {
                bits[j] = 1;
            }
        }
        else if (cube[i] == 1) {
            for (j = (i-bar*6)*24; j <= (i-bar*6)*24+7; j++) {
                bits[j] = 1;
            }
            for (j = (i-bar*6)*24+8; j <= (i-bar*6)*24+7+8; j++) {
                bits[j] = 1;
            }
            for (j = (i-bar*6)*24+16; j <= (i-bar*6)*24+7+16; j++) {
                bits[j] = 0;
            }
        }
        else if (cube[i] == 2) {
            for (j = (i-bar*6)*24; j <= (i-bar*6)*24+7; j++) {
                bits[j] = 0;
            }
            for (j = (i-bar*6)*24+8; j <= (i-bar*6)*24+7+8; j++) {
                bits[j] = 1;
            }
            for (j = (i-bar*6)*24+16; j <= (i-bar*6)*24+7+16; j++) {
                bits[j] = 1;
            }
        }
        else if (cube[i] == 3) {
            for (j = (i-bar*6)*24; j <= (i-bar*6)*24+7; j++) {
                bits[j] = 0;
            }
            for (j = (i-bar*6)*24+8; j <= (i-bar*6)*24+7+8; j++) {
                bits[j] = 1;
            }
            for (j = (i-bar*6)*24+16; j <= (i-bar*6)*24+7+16; j++) {
                bits[j] = 0;
            }
        }
        else if (cube[i] == 4) {
            for (j = (i-bar*6)*24; j <= (i-bar*6)*24+7; j++) {
                bits[j] = 0;
            }
            for (j = (i-bar*6)*24+8; j <= (i-bar*6)*24+7+8; j++) {
                bits[j] = 0;
            }
            for (j = (i-bar*6)*24+16; j <= (i-bar*6)*24+7+16; j++) {
                bits[j] = 1;
            }
        }
        else{
            for (j = (i-bar*6)*24; j <= (i-bar*6)*24+7; j++) {
                bits[j] = 1;
            }
            for (j = (i-bar*6)*24+8; j <= (i-bar*6)*24+7+8; j++) {
                bits[j] = 0;
            }
            for (j = (i-bar*6)*24+16; j <= (i-bar*6)*24+7+16; j++) {
                bits[j] = 0;
            }
        }
    }
}

void initCube(int8_t cube[]) {
    cube[0] = 0;
    cube[1] = 0;
    cube[2] = 0;
    cube[6] = 0;
    cube[7] = 0;
    cube[8] = 0;
    cube[12] = 0;
    cube[13] = 0;
    cube[14] = 0;
    cube[3] = 1;
    cube[4] = 1;
    cube[5] = 1;
    cube[9] = 1;
    cube[10] = 1;
    cube[11] = 1;
    cube[15] = 1;
    cube[16] = 1;
    cube[17] = 1;
    cube[18] = 2;
    cube[19] = 2;
    cube[20] = 2;
    cube[24] = 2;
    cube[25] = 2;
    cube[26] = 2;
    cube[30] = 2;
    cube[31] = 2;
    cube[32] = 2;
    cube[21] = 3;
    cube[22] = 3;
    cube[23] = 3;
    cube[27] = 3;
    cube[28] = 3;
    cube[29] = 3;
    cube[33] = 3;
    cube[34] = 3;
    cube[35] = 3;
    cube[36] = 4;
    cube[37] = 4;
    cube[38] = 4;
    cube[42] = 4;
    cube[43] = 4;
    cube[44] = 4;
    cube[48] = 4;
    cube[49] = 4;
    cube[50] = 4;
    cube[39] = 5;
    cube[40] = 5;
    cube[41] = 5;
    cube[45] = 5;
    cube[46] = 5;
    cube[47] = 5;
    cube[51] = 5;
    cube[52] = 5;
    cube[53] = 5;
}

void displayCube(int8_t cube[], int8_t bits[]) {
    getBitsFromCube(0,cube,bits);
    passBar(bits,0);
    getBitsFromCube(1,cube,bits);
    passBar(bits,1);
    getBitsFromCube(2,cube,bits);
    passBar(bits,2);
    getBitsFromCube(3,cube,bits);
    passBar(bits,3);
    getBitsFromCube(4,cube,bits);
    passBar(bits,4);
    getBitsFromCube(5,cube,bits);
    passBar(bits,5);
    getBitsFromCube(6,cube,bits);
    passBar(bits,6);
    getBitsFromCube(7,cube,bits);
    passBar(bits,7);
    getBitsFromCube(8,cube,bits);
    passBar(bits,8);
}

void shiftVector(int8_t dir, int8_t times, int8_t size, int8_t v[]) {
    int i;
    int8_t aux[3];
    
    if (dir >= 0) {
        for (i = 0; i < times; i++) {
            aux[i] = v[i];
        }
        for (i = 0; i < size-times; i++) {
            v[i] = v[i+times];
        }
        for (i = size-times; i < size; i++) {
            v[i] = aux[i-size+times];
        }
    }
    else {
        for (i = size-times; i < size; i++) {
            aux[i-size+times] = v[i];
        }
        for (i = size-1; i >= times; i--) {
            v[i] = v[i-times];
        }
        for (i = 0; i < times; i++) {
            v[i] = aux[i];
        }
    }
}

void doMove(int8_t dir, int8_t move, int8_t cube[]) {
    int i;
    int8_t aux[12];
    int8_t miscari[12];
    
    //invartim in jurul axei x
    if (0 <= move && move <= 2) {
        miscari[0] = 3;
        miscari[1] = 9;
        miscari[2] = 15;
        miscari[3] = 41;
        miscari[4] = 47;
        miscari[5] = 53;
        miscari[6] = 35;
        miscari[7] = 29;
        miscari[8] = 23;
        miscari[9] = 48;
        miscari[10] = 42;
        miscari[11] = 36;
        
        for (i = 0; i < 12; i++) {
            if (i < 3 || i > 8) {
                aux[i] = cube[miscari[i]+move];
            }
            else {
                aux[i] = cube[miscari[i]-move];
            }
        }
        shiftVector(dir,3,12,aux);
        for (i = 0; i < 12; i++) {
            if (i < 3 || i > 8) {
                cube[miscari[i]+move] = aux[i];
            }
            else {
                cube[miscari[i]-move] = aux[i];
            }
        }
        
        if (move == 0) {
            aux[0] = cube[0];
            aux[1] = cube[1];
            aux[2] = cube[2];
            aux[3] = cube[8];
            aux[4] = cube[14];
            aux[5] = cube[13];
            aux[6] = cube[12];
            aux[7] = cube[6];
            shiftVector(dir,2,8,aux);
            cube[0] = aux[0];
            cube[1] = aux[1];
            cube[2] = aux[2];
            cube[8] = aux[3];
            cube[14] = aux[4];
            cube[13] = aux[5];
            cube[12] = aux[6];
            cube[6] = aux[7];
        }
        if (move == 2) {
            aux[0] = cube[18];
            aux[1] = cube[24];
            aux[2] = cube[30];
            aux[3] = cube[31];
            aux[4] = cube[32];
            aux[5] = cube[26];
            aux[6] = cube[20];
            aux[7] = cube[19];
            shiftVector(dir,2,8,aux);
            cube[18] = aux[0];
            cube[24] = aux[1];
            cube[30] = aux[2];
            cube[31] = aux[3];
            cube[32] = aux[4];
            cube[26] = aux[5];
            cube[20] = aux[6];
            cube[19] = aux[7];
        }
    }
    //invartim in jurul axey y
    else if (3 <= move && move <= 5) {
        miscari[0] = 0;
        miscari[1] = 6;
        miscari[2] = 12;
        miscari[3] = 53;
        miscari[4] = 52;
        miscari[5] = 51;
        miscari[6] = 32;
        miscari[7] = 26;
        miscari[8] = 20;
        miscari[9] = 50;
        miscari[10] = 49;
        miscari[11] = 48;
        
        for (i = 0; i < 12; i++) {
            if (i < 3) {
                aux[i] = cube[miscari[i]+move-3];
            }
            else if (6 <= i && i <= 8) {
                aux[i] = cube[miscari[i]-move+3];
            }
            else {
                aux[i] = cube[miscari[i]-(move-3)*6];
            }
        }
        shiftVector(dir,3,12,aux);
        for (i = 0; i < 12; i++) {
            if (i < 3) {
                cube[miscari[i]+move-3] = aux[i];
            }
            else if (6 <= i && i <= 8) {
                cube[miscari[i]-move+3] = aux[i];
            }
            else {
                cube[miscari[i]-(move-3)*6] = aux[i];
            }
        }
        if (move == 3) {
            aux[0] = cube[21];
            aux[1] = cube[22];
            aux[2] = cube[23];
            aux[3] = cube[29];
            aux[4] = cube[35];
            aux[5] = cube[34];
            aux[6] = cube[33];
            aux[7] = cube[27];
            shiftVector(dir,2,8,aux);
            cube[21] = aux[0];
            cube[22] = aux[1];
            cube[23] = aux[2];
            cube[29] = aux[3];
            cube[35] = aux[4];
            cube[34] = aux[5];
            cube[33] = aux[6];
            cube[27] = aux[7];
        }
        if (move == 5) {
            aux[0] = cube[5];
            aux[1] = cube[4];
            aux[2] = cube[3];
            aux[3] = cube[9];
            aux[4] = cube[15];
            aux[5] = cube[16];
            aux[6] = cube[17];
            aux[7] = cube[11];
            shiftVector(dir,2,8,aux);
            cube[5] = aux[0];
            cube[4] = aux[1];
            cube[3] = aux[2];
            cube[9] = aux[3];
            cube[15] = aux[4];
            cube[16] = aux[5];
            cube[17] = aux[6];
            cube[11] = aux[7];
        }
    }
    //invartim in jurul axey z
    else {
        for (i = 0; i < 12; i++) {
            if (i < 6) {
                miscari[i] = i;
            }
            else {
                miscari[i] = i+12;
            }
        }
        
        for (i = 0; i < 12; i++) {
            aux[i] = cube[miscari[i]+(move-6)*6];
        }
        shiftVector(dir,3,12,aux);
        for (i = 0; i < 12; i++) {
            cube[miscari[i]+(move-6)*6] = aux[i];
        }
        
        if (move == 6) {
            aux[0] = cube[36];
            aux[1] = cube[37];
            aux[2] = cube[38];
            aux[3] = cube[44];
            aux[4] = cube[50];
            aux[5] = cube[49];
            aux[6] = cube[48];
            aux[7] = cube[42];
            shiftVector(dir,2,8,aux);
            cube[36] = aux[0];
            cube[37] = aux[1];
            cube[38] = aux[2];
            cube[44] = aux[3];
            cube[50] = aux[4];
            cube[49] = aux[5];
            cube[48] = aux[6];
            cube[42] = aux[7];
        }
        if (move == 8) {
            aux[0] = cube[53];
            aux[1] = cube[47];
            aux[2] = cube[41];
            aux[3] = cube[40];
            aux[4] = cube[39];
            aux[5] = cube[45];
            aux[6] = cube[51];
            aux[7] = cube[52];
            shiftVector(dir,2,8,aux);
            cube[53] = aux[0];
            cube[47] = aux[1];
            cube[41] = aux[2];
            cube[40] = aux[3];
            cube[39] = aux[4];
            cube[45] = aux[5];
            cube[51] = aux[6];
            cube[52] = aux[7];
        }
    }
}

/*
void dumpBits(int bits[]) {
    int i;
    for (i = 0; i < 144; i++) {
        printf("%d ", bits[i]);
    }
    printf("\n");
}
*/

void main(void)
{
    // Declare your local variables here
    int i, j;
    int8_t bits[144];
    int8_t cube[54];
    int8_t moves[60];
    
    initCube(cube);
    
    // Crystal Oscillator division factor: 1
    #pragma optsize-
    CLKPR=(1<<CLKPCE);
    CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
    #ifdef _OPTIMIZE_SIZE_
    #pragma optsize+
    #endif

    // Input/Output Ports initialization
    // Port A initialization
    // Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out
    DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
    // State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0

    // Port B initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T

    // Port C initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=Out
    DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=0

    // Port D initialization
    // Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In
    DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
    // State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: Timer 0 Stopped
    // Mode: Normal top=0xFF
    // OC0A output: Disconnected
    // OC0B output: Disconnected
    TCCR0A=(0<<COM0A1) | (0<<COM0A0) | (0<<COM0B1) | (0<<COM0B0) | (0<<WGM01) | (0<<WGM00);
    TCCR0B=(0<<WGM02) | (0<<CS02) | (0<<CS01) | (0<<CS00);
    TCNT0=0x00;
    OCR0A=0x00;
    OCR0B=0x00;

    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: Timer1 Stopped
    // Mode: Normal top=0xFFFF
    // OC1A output: Disconnected
    // OC1B output: Disconnected
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer1 Overflow Interrupt: Off
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
    TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (0<<CS12) | (0<<CS11) | (0<<CS10);
    TCNT1H=0x00;
    TCNT1L=0x00;
    ICR1H=0x00;
    ICR1L=0x00;
    OCR1AH=0x00;
    OCR1AL=0x00;
    OCR1BH=0x00;
    OCR1BL=0x00;

    // Timer/Counter 2 initialization
    // Clock source: System Clock
    // Clock value: Timer2 Stopped
    // Mode: Normal top=0xFF
    // OC2A output: Disconnected
    // OC2B output: Disconnected
    ASSR=(0<<EXCLK) | (0<<AS2);
    TCCR2A=(0<<COM2A1) | (0<<COM2A0) | (0<<COM2B1) | (0<<COM2B0) | (0<<WGM21) | (0<<WGM20);
    TCCR2B=(0<<WGM22) | (0<<CS22) | (0<<CS21) | (0<<CS20);
    TCNT2=0x00;
    OCR2A=0x00;
    OCR2B=0x00;

    // Timer/Counter 0 Interrupt(s) initialization
    TIMSK0=(0<<OCIE0B) | (0<<OCIE0A) | (0<<TOIE0);

    // Timer/Counter 1 Interrupt(s) initialization
    TIMSK1=(0<<ICIE1) | (0<<OCIE1B) | (0<<OCIE1A) | (0<<TOIE1);

    // Timer/Counter 2 Interrupt(s) initialization
    TIMSK2=(0<<OCIE2B) | (0<<OCIE2A) | (0<<TOIE2);

    // External Interrupt(s) initialization
    // INT0: Off
    // INT1: Off
    // INT2: Off
    // Interrupt on any change on pins PCINT0-7: Off
    // Interrupt on any change on pins PCINT8-15: Off
    // Interrupt on any change on pins PCINT16-23: Off
    // Interrupt on any change on pins PCINT24-31: Off
    EICRA=(0<<ISC21) | (0<<ISC20) | (0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
    EIMSK=(0<<INT2) | (0<<INT1) | (0<<INT0);
    PCICR=(0<<PCIE3) | (0<<PCIE2) | (0<<PCIE1) | (0<<PCIE0);

    // USART0 initialization
    // USART0 disabled
    UCSR0B=(0<<RXCIE0) | (0<<TXCIE0) | (0<<UDRIE0) | (0<<RXEN0) | (0<<TXEN0) | (0<<UCSZ02) | (0<<RXB80) | (0<<TXB80);

    // USART1 initialization
    // USART1 disabled
    UCSR1B=(0<<RXCIE1) | (0<<TXCIE1) | (0<<UDRIE1) | (0<<RXEN1) | (0<<TXEN1) | (0<<UCSZ12) | (0<<RXB81) | (0<<TXB81);

    // Analog Comparator initialization
    // Analog Comparator: Off
    // The Analog Comparator's positive input is
    // connected to the AIN0 pin
    // The Analog Comparator's negative input is
    // connected to the AIN1 pin
    ACSR=(1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
    ADCSRB=(0<<ACME);
    // Digital input buffer on AIN0: On
    // Digital input buffer on AIN1: On
    DIDR1=(0<<AIN0D) | (0<<AIN1D);

    // ADC initialization
    // ADC disabled
    ADCSRA=(0<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (0<<ADPS1) | (0<<ADPS0);

    // SPI initialization
    // SPI disabled
    SPCR=(0<<SPIE) | (0<<SPE) | (0<<DORD) | (0<<MSTR) | (0<<CPOL) | (0<<CPHA) | (0<<SPR1) | (0<<SPR0);

    // TWI initialization
    // TWI disabled
    TWCR=(0<<TWEA) | (0<<TWSTA) | (0<<TWSTO) | (0<<TWEN) | (0<<TWIE);
    
    while (1)   {
        srand(rand());
        initCube(cube);
        displayCube(cube, bits);
        _delay_s(1);
        
        //shuffle the cube
        for (i = 0; i < 60; i++) {
            moves[i] = rand()%9;
            doMove(1,moves[i],cube);
        }
        displayCube(cube,bits);
        _delay_s(1);
        
        //unshuffle the cube
        for (i = 59; i >= 0; i--) {
            doMove(-1,moves[i],cube);
            displayCube(cube,bits);
            _delay_s(1);
        }
        
        _delay_s(30);
    }
}
