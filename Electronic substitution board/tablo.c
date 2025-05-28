//Mehran khodaei

#include <mega16.h>
#include <delay.h>
#include <stdlib.h>

#asm
.equ __lcd_port=0x1B
#endasm
#include <lcd.h>

void main(void)
{
    int PlayerIN = 50, PlayerOUT = 50;
    int TedadTavizTeam1 = 0, TedadTavizTeam2 = 0;
    char str[10];

    unsigned char anode_seg[]={0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
    int a, b, c, d;

    // PORTA >>> LCD 4*20
    DDRB = 0x00;
    DDRC = 0xFF;
    DDRD = 0xFF;

    lcd_init(20);

    while(1)
    {
        UP:
        
        
lcd_clear();
lcd_gotoxy(1, 0); lcd_puts("Select Your Team :");
lcd_gotoxy(0, 1); lcd_puts("Team 1    OR    Team 2");

while(1)
{
    if(PINB.0)
    {
        TedadTavizTeam1++;

        lcd_clear();
        lcd_gotoxy(2, 0); lcd_puts("You Select Team1");

        if(TedadTavizTeam1 <= 3)
        {
            lcd_gotoxy(0, 1); lcd_puts("Tedad Taviz Team1= ");
            itoa(TedadTavizTeam1 - 1, str); lcd_puts(str);
        }
        else if(TedadTavizTeam1 > 3)
        {
            lcd_gotoxy(2, 1); lcd_puts("Tedad Taviz Team1");
            lcd_gotoxy(6, 2); lcd_putsf("is Full");
            delay_ms(1000);
            goto UP;
        }

        delay_ms(1000);
        goto SelectNumber;
    }
    else if(PINB.1)
    {
        TedadTavizTeam2++;

        lcd_clear();
        lcd_gotoxy(2, 0); lcd_putsf("You Select Team2");
    if(TedadTavizTeam2==3){lcd_gotoxy(0,1);lcd_puts("Tedad Taviz Team2= ");itoa(TedadTavizTeam2-1,str);lcd_puts(str);}
    else if(TedadTavizTeam2>3)
    {
        lcd_gotoxy(2,1);lcd_putsf("Tedad Taviz Team2");
        lcd_gotoxy(6,2);lcd_putsf("is Full");
        delay_ms(1000);
        goto UP;
    }

    delay_ms(1000);
    goto SelectNumber;
    }
}

SelectNumber:
delay_ms(1000);
lcd_clear();

lcd_gotoxy(0,0);lcd_putsf("Number PlayerIN is");
while(PINB.2==0)
{
    if(PINB.0){PlayerIN++; if(PlayerIN>99)PlayerIN=1; delay_ms(300);}
    else if(PINB.1){PlayerIN--; if(PlayerIN<1)PlayerIN=99; delay_ms(300);}
    
    itoa(PlayerIN,str);
    lcd_gotoxy(8,1);lcd_puts(str);lcd_putsf(" ");
}

delay_ms(500);

lcd_gotoxy(0,2);lcd_putsf("Number PlayerOUT is");
while(PINB.2==0)
{
    if(PINB.0){PlayerOUT++; if(PlayerOUT>99)PlayerOUT=1; delay_ms(300);}
    else if(PINB.1){PlayerOUT--; if(PlayerOUT<1)PlayerOUT=99; delay_ms(300);}
    
    itoa(PlayerOUT,str);
    lcd_gotoxy(8,3);lcd_puts(str);lcd_putsf(" ");
}

delay_ms(500);
a=PlayerIN/10;
b=PlayerIN%10;

c=PlayerOUT/10;
d=PlayerOUT%10;

while(PINB.2==0)
{
    // ãÑÈæØ Èå äãÇíÔ ÈÇÒí˜ä æÑæÏí
    PORTD.0=1;
    PORTC=anode_seg[a];
    delay_ms(1);
    PORTD.0=0;

    PORTD.1=1;
    PORTC=anode_seg[b];
    delay_ms(1);
    PORTD.1=0;

    PORTD.2=1;
    PORTC=0x3F;
    delay_ms(1);
    PORTD.2=0;

    PORTD.3=1;
    PORTC=0x3F;
    delay_ms(1);
    PORTD.3=0;
// ÈÇÒí˜ä ÎÑæÌí
 PORTD.4=1;
 PORTC=anode_seg[c];
 delay_ms(1);
 PORTD.4=0;
 
 PORTD.5=1;
 PORTC=anode_seg[d];
 delay_ms(1);
 PORTD.5=0;
 }
 }
 }