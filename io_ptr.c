/********************************************************************************
* io_ptr.c: Demonstration av pekare till I/O-register. I detta program inkluderas
*           inte avr/io.h. I st�llet implementeras pekare till I/O-register PINB, 
*           DDRB samt PORTB. Makron med samma namn anv�nds f�r att enkelt skriva
*           respektive l�sa till registret i fr�ga via en dereferens. Datatypen
*           uint8_t realiseras som ett alias till datatypen unsigned char via
*           en typdefinition.
*
*           F�r test av implementeringen ansluts en lysdiod till pin 8 (PORTB0)
*           och en tryckknapp till pin 13 (PORTB5). Polling (avl�sning) av 
*           tryckknappen sker kontinuerligt, d�r nedtryckning medf�r att 
*           lysdioden t�nds, annars h�lls den sl�ckt.
********************************************************************************/

/********************************************************************************
* Typdefinitioner (alias):
********************************************************************************/
typedef unsigned char uint8_t; /* 8-bitars osignerat heltal. */

/********************************************************************************
* Pekare till I/O-register:
*
*   - PINB ligger p� adress 0x23 i dataminnet.
*   - DDRB ligger p� adress 0x24 i dataminnet.
*   - PORTB ligger p� adress 0x25 i dataminnet.
********************************************************************************/
static volatile uint8_t* const pinb = (volatile uint8_t*)(0x23); 
static volatile uint8_t* const ddrb = (volatile uint8_t*)(0x24);  
static volatile uint8_t* const portb = (volatile uint8_t*)(0x25); 

/********************************************************************************
* Makrodefinitioner f�r I/O-register, som m�jligg�r l�sning/skrivning till/fr�n
* refererad minnesadress:
*
*   - PINB �r ekvivalent med *pinb, vilket motsvarar inneh�llet p� adress 0x23.
*   - DDRB �r ekvivalent med *ddrb, vilket motsvarar inneh�llet p� adress 0x24.
*   - PORTB �r ekvivalent med *portb, vilket motsvarar inneh�llet p� adress 0x25.
********************************************************************************/
#define PINB *pinb   /* Motsvarar makrot PINB i avr/io.h. */
#define DDRB *ddrb   /* Motsvarar makrot DDRB i avr/io.h. */
#define PORTB *portb /* Motsvarar makrot PORTB i avr/io.h. */

/********************************************************************************
* Makrodefinitioner f�r I/O-portar:
********************************************************************************/
#define PORTB0 0
#define PORTB1 1
#define PORTB2 2
#define PORTB3 3
#define PORTB4 4
#define PORTB5 5
#define PORTB6 6
#define PORTB7 7

/********************************************************************************
* Makrodefinitioner f�r pinnar:
********************************************************************************/
#define LED1    PORTB0 /* Lysdiod 1 ansluten till pin 8 (PORTB0). */
#define BUTTON1 PORTB5 /* Tryckknapp 1 ansluten till pin 13 (PORTB5). */

/********************************************************************************
* main: Initierar systemet vid start. Vid nedtryckning av BUTTON1 t�nds LED1, 
*       �vrig tid h�lls den sl�ckt.
********************************************************************************/
int main(void)
{
   DDRB = (1 << LED1);
   PORTB = (1 << BUTTON1);

   while (1)
   {
      if (PINB & (1 << BUTTON1))
      {
         PORTB |= (1 << LED1);
      }
      else
      {
         PORTB &= ~(1 << LED1);
      }
   }
   return 0;
}