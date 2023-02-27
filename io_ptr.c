/********************************************************************************
* io_ptr.c: Demonstration av pekare till I/O-register. I detta program inkluderas
*           inte avr/io.h. I stället implementeras pekare till I/O-register PINB, 
*           DDRB samt PORTB. Makron med samma namn används för att enkelt skriva
*           respektive läsa till registret i fråga via en dereferens. Datatypen
*           uint8_t realiseras som ett alias till datatypen unsigned char via
*           en typdefinition.
*
*           För test av implementeringen ansluts en lysdiod till pin 8 (PORTB0)
*           och en tryckknapp till pin 13 (PORTB5). Polling (avläsning) av 
*           tryckknappen sker kontinuerligt, där nedtryckning medför att 
*           lysdioden tänds, annars hålls den släckt.
********************************************************************************/

/********************************************************************************
* Typdefinitioner (alias):
********************************************************************************/
typedef unsigned char uint8_t; /* 8-bitars osignerat heltal. */

/********************************************************************************
* Pekare till I/O-register:
*
*   - PINB ligger på adress 0x23 i dataminnet.
*   - DDRB ligger på adress 0x24 i dataminnet.
*   - PORTB ligger på adress 0x25 i dataminnet.
********************************************************************************/
static volatile uint8_t* const pinb = (volatile uint8_t*)(0x23); 
static volatile uint8_t* const ddrb = (volatile uint8_t*)(0x24);  
static volatile uint8_t* const portb = (volatile uint8_t*)(0x25); 

/********************************************************************************
* Makrodefinitioner för I/O-register, som möjliggör läsning/skrivning till/från
* refererad minnesadress:
*
*   - PINB är ekvivalent med *pinb, vilket motsvarar innehållet på adress 0x23.
*   - DDRB är ekvivalent med *ddrb, vilket motsvarar innehållet på adress 0x24.
*   - PORTB är ekvivalent med *portb, vilket motsvarar innehållet på adress 0x25.
********************************************************************************/
#define PINB *pinb   /* Motsvarar makrot PINB i avr/io.h. */
#define DDRB *ddrb   /* Motsvarar makrot DDRB i avr/io.h. */
#define PORTB *portb /* Motsvarar makrot PORTB i avr/io.h. */

/********************************************************************************
* Makrodefinitioner för I/O-portar:
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
* Makrodefinitioner för pinnar:
********************************************************************************/
#define LED1    PORTB0 /* Lysdiod 1 ansluten till pin 8 (PORTB0). */
#define BUTTON1 PORTB5 /* Tryckknapp 1 ansluten till pin 13 (PORTB5). */

/********************************************************************************
* main: Initierar systemet vid start. Vid nedtryckning av BUTTON1 tänds LED1, 
*       övrig tid hålls den släckt.
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