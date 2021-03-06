/*
Example for 7x10_R Click

    Date          : Jan 2018.
    Author        : MikroE Team

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - GPIO and SPI bus initialization
- Application Initialization - Driver initialization
- Application Task - (code snippet)
  1. Text scrolling
  2. Counts from 0 to 10
  3. Displays random pixels

*/

#include "Click_7x10_R_types.h"
#include "Click_7x10_R_config.h"

uint8_t mikroe_txt[20] = { ' ', ' ', 'M', 'i', 'k', 'r' , 'o', ' ', 'E', 'l', 'e', 'k', 't', 'r', 'o', 'n', 'i', 'k', 'a', 0};
void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_PWM_PIN, _GPIO_OUTPUT );
    mikrobus_spiInit( _MIKROBUS1, &_C7X10R_SPI_CFG[0] );

    Delay_ms( 100 );
}

void applicationInit()
{
    c7x10r_spiDriverInit( (T_C7X10R_P)&_MIKROBUS1_GPIO, (T_C7X10R_P)&_MIKROBUS1_SPI );
    c7x10r_clearDisplay();
}

void applicationTask()
{
    uint8_t i;
    uint8_t j;
    uint8_t endOp;

// SCROLL PROCEDURE
    endOp = 1;
    c7x10r_drawText( &mikroe_txt[0] );
    c7x10r_scrollEnable( _C7X10R_SPEED_MED );
    while (0 != endOp)
    {
        endOp = c7x10r_refreshDisplay();
        c7x10r_tick();
        Delay_ms( 1 );

    }
    c7x10r_scrollDisable();
    c7x10r_clearDisplay();

// COUNTER PROCEDURE
    for (i = 0; i < 11; i++)
    {
        c7x10r_clearDisplay();
        c7x10r_drawNumber( i );

        for (j = 0; j < 30; ++j)
        {
            c7x10r_refreshDisplay();
            Delay_ms( 1 );
        }
    }
    c7x10r_clearDisplay();

// PIXELS PROCEDURE
    c7x10r_drawPixel( 2, 3 );
    c7x10r_drawPixel( 2, 8 );
    c7x10r_drawPixel( 6, 3 );
    c7x10r_drawPixel( 6, 8 );
    for (i = 0; i < 255; i++)
    {
        c7x10r_refreshDisplay();
        Delay_ms( 1 );
    }
    c7x10r_clearDisplay();
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
        applicationTask();
    }
}