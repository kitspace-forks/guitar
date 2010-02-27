#include <ctype.h>
#include <stdio.h>

#include <avr/io.h>
#include <avr/pgmspace.h>

#include "uart.h"
#include "adc.h"

FILE uart_str;

int main(void)
{
	uart_init();
	uart_str= FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
	stdout = stdin = &uart_str;
	
	//b1, b2, b3=led,solar,ac
	//buttons b6, b7, b4 center, e2, e3
	DDRB =0b00001110;
	PORTB=0b11010000;
	PORTE=0b00001100;
	
	int choice;
	
	clear();
	
	printf("===LED Lighting System===\n");
	printf(" made by Alex and Andrew\n");
	printf("=========================\n");
	printf("\n");
	

menu:
	printf("=System State=\n");
	printf("Battery Voltage: "); printfloat(voltage()); printf("V\n");
	printf("LEDs: %s\n",state(PB1));
	printf("AC charger: %s\n",state(PB3));
	printf("Solar panels: %s\n",state(PB2));
		
	printf("\n");
	
	printf("==Main Menu==\n");
	printf("0. Refresh\n");
	printf("1. Toggle LEDs\n");
	printf("2. Toggle AC charger\n");
	printf("3. Toggle Solar panels\n");
	printf("4. Continiously Monitor Battery State\n");
	printf("9. Print Credits\n");
	printf("Pick an option: ");
	scanf("%d", &choice);
	switch(choice)
	{
		case 0:
			break;
			
		case 1:
			toggle(PB1);
			break;
		
		case 2:
			toggle(PB3);
			break;
		
		case 3:
			toggle(PB2);
			break;
		
		case 4:
			printf("\n=Battery Monitor=\n");
			printf("Press enter to refresh, press 0 to exit.\n");
			printf("Voltage\n");
			int i;
			double volts;
			int n=3;
			if(bol_state(PB3)) n=16; //charger on
			do
			{
				volts=0;
				for(i=0;i<n;i++)
				{
					volts+=voltage();
					_delay_ms(250);
				}
				volts/=n;
				printfloat(volts);
				printf("V");
			}
			while(uart_getchar(stdin)!='0');
			clear();
			break;
						
		case 9:
			clear();
			printf("===LED Lighting System===\n");
			printf("Design: Alex Stan & Andrew Rossignol\n");
			printf("Hardware: Alex Stan & Andrew Rossignol\n");
			printf("Theory: Andrew Rossignol\n");
			printf("Programming: Alex Stan\n");
			printf("Thanks to LEDs and AVR Butterfly Demo Boards!\n");
			printf("\n\n");
			
			uart_getchar(stdin);
			clear();
			
			goto menu;
			
			break;
			
		default:
			printf("Invalid choice! Try again.\n\n\n");
			goto menu;
	}
	clear();
	goto menu;
}
