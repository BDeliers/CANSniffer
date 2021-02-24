#ifndef CONFIG_H
#define	CONFIG_H

/*   CONFIGURATION BITS   */

// CONFIG1L
#pragma config PLLDIV = 5           // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2   // System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2           // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = ON      // USB Voltage Regulator Enable bit (USB voltage regulator enabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#define _XTAL_FREQ 48000000     // System clock is running at 96MHz / 2 = 48MHz.

// XC8 include
#include <xc.h>

// Std includes
#include <stdint.h>

/*   PINS FRIENDLY NAMES   */
#define DIGITAL_LED_TRIS      TRISAbits.TRISA0
#define DIGITAL_LED_LAT       LATAbits.LATA0
#define DIGITAL_LED_PORT      PORTAbits.RA0

#define DIGITAL_BAT_TRIS      TRISAbits.TRISA3
#define DIGITAL_BAT_LAT       LATAbits.LATA3
#define DIGITAL_BAT_PORT      PORTAbits.RA3


/*   MCP2551 CAN TRANSCIEVER   */
#define MCP2551_INT_TRIS      TRISBbits.TRISB2
#define MCP2551_INT_LAT       LATBbits.LATB2
#define MCP2551_INT_PORT      PORTBbits.RB2

#define MCP2551_RXINT0_TRIS   TRISBbits.TRISB3
#define MCP2551_RXINT0_LAT    LATBbits.LATB3
#define MCP2551_RXINT0_PORT   PORTBbits.RB3

#define MCP2551_RXINT1_TRIS   TRISBbits.TRISB4
#define MCP2551_RXINT1_LAT    LATBbits.LATB4
#define MCP2551_RXINT1_PORT   PORTBbits.RB4

/*   SPI INTERFACE   */
#define SPI_SCK_TRIS          TRISBbits.TRISB1
#define SPI_SCK_LAT           LATBbits.LATB1
#define SPI_SCK_PORT          PORTBbits.RB1

#define SPI_MISO_TRIS         TRISBbits.TRISB0
#define SPI_MISO_LAT          LATBbits.LATB0
#define SPI_MISO_PORT         PORTBbits.RB0

#define SPI_MOSI_TRIS         TRISCbits.TRISC7
#define SPI_MOSI_LAT          LATCbits.LATC7
#define SPI_MOSI_PORT         PORTCbits.RC7

#define SPI_SS_TRIS           TRISAbits.TRISA5
#define SPI_SS_LAT            LATAbits.LATA5
#define SPI_SS_PORT           PORTAbits.RA5


/*   INITIALIZATION FUNCTIONS   */
// Initialize all pins as digital outputs, low
void initPins(void);

// Initialize interrupts
void initInterrupt(void);

#endif	/* CONFIG_H */

