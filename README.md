# Anteckningar 2022-02-27
Implementering av arrayer i assembler.
Även implementering av pekare till I/O-register, som i en övningsuppgift ersätter PINB, DDRB samt PORTB
(programmet realiserades utan biblioteket avr/io.h).

Filen "array.asm" innehåller ett program, där en statisk array tilldelas 16 heltal 0 - 15. Varje element
hämtas ett i taget och skrivs till PORTB via en referens.

Filen "io_ptr.c" utgör ett program, där I/O-register PINB, DDRB samt PORTB realiseras via pekare till
motsvarande adresser 0x23 - 0x25 i dataminnet. Dereferensen av dessa pekare (innehållet på respektive)
adress implementeras sedan via makron PINB, DDRB samt PORTB. Därmed fungerar programmet utmärkt utan
inkludering av biblioteket avr/io.h. Datatypen uint8_t realiseras som ett alias till unsigned char
i stället för inkludering av stdint.h (som normalt inkluderas indirekt via avr/io.h).