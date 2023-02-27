;********************************************************************************
; array.asm: Implementering av en statisk array, som tilldelas 16 heltal
;             0 - 15 via en subrutin d�pt assign. Iteration sker sedan genom
;             arrayen, d�r varje element h�mtas ett i taget och skrivs till 
;             dataregister PORTB via referens.
;********************************************************************************
.EQU RESET_vect = 0x00 ; Reset-vektor, utg�r programmets startpunkt.

;********************************************************************************
; .CSEG: Kodsegment, lagringsplats f�r programkoden.
;********************************************************************************
.CSEG

;********************************************************************************
; RESET_vect: Programmets startpunkt. Programhopp sker till subrutinen main
;             f�r att starta programmet.
;********************************************************************************
.ORG RESET_vect
   RJMP main

;********************************************************************************
; assign: Fyller statisk array av angiven storlek till bredden med heltal.
;         Start- och stegv�rde kan v�ljas godtyckligt.
;     
;         - [R24:R25]: Referens till arrayen (det f�rsta elementet).
;         - R22      : Arrayens storlek.
;         - R20      : Startv�rde.
;         - R18      : Stegv�rde.
;********************************************************************************
assign:
   MOVW Z, R24
   LDI R16, 0x00
assign_loop:
   CP R16, R22
   BREQ assign_end
   ST Z+, R20
   ADD R20, R18
   INC R16
   RJMP assign_loop
assign_end:
   RET

;********************************************************************************
; write: Itererar genom refererad statisk array, h�mtar varje element en 
;        i taget och skriver till refererad destinationsadress.
;     
;         - [R24:R25]: Referens till arrayen (det f�rsta elementet).
;         - R22      : Arrayens storlek.
;         - [R20:R21]: Referens till destinationsregistret.
;********************************************************************************
write:
   MOVW Z, R24
   MOVW X, R20
   LDI R16, 0x00
write_loop:
   CP R16, R22
   BREQ write_end
   LD R24, Z+
   ST X, R24
   INC R16
   RJMP write_loop
write_end:
   RET

;********************************************************************************
; main: S�tter PORTB0 - PORTB3 till utportar och initierar en statisk array 
;       som rymmer 16 heltal med startadress RAMEND + 1 i dataminnet.
;       Arrayen fylls till bredden med heltal 0 - 15. Arrayens inneh�ll
;       l�ses in element f�r element och skrivs till PORTB.
;********************************************************************************
main:
   LDI R16, 0x0F
   OUT DDRB, R16
   LDI YL, LOW(RAMEND)
   LDI YH, HIGH(RAMEND)

   MOVW R24, Y
   ADIW R24, 1
   LDI R22, 16
   LDI R20, 0
   LDI R18, 1
   RCALL assign

   MOVW R24, Y
   ADIW R24, 1
   LDI R22, 16
   LDI R20, 0x25
   LDI R21, 0x00
   RCALL write

;********************************************************************************
; end: G�r ingenting efter att arrayens samtliga element har skrivits till PORTB.
;********************************************************************************
end:
   RJMP end
