//*****************************************************************************
/*
 *  Electrónica Digital 2
 *  Steven Josué Castillo Lou - 17169
 *  LABORATORIO 8: GPIOS --> Semáforo TivaC
 *  Fecha: 13/05/2020
 *  Sección: 12
 *
 */
//*****************************************************************************
//******************** Se importan las Librerias ******************************
#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h" //GPIO Pin Configuration

//*****************************************************************************

int main(void){

    //Se establece el reloj a utilizar
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    //Se habilita el periferico del puerto F --> GPIOF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //Pines de salida para semaforo (LEDS Red:PF_1 , Blue:PF_2  , Green:PF_3) --> LOS PINES 1,2 Y 3 DEL PUERTO F SON LOS LEDS RGB.
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //Pin de entrada (PUSH1 es el SW1:PF_4 o SW2 --> PF_0)
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);  // GPIO_STRENGTH_2MA especifica 2mA de output drive strength //WPU --> Weak pull-up

    while(1){
        // como se establecio la entrada analógica con Weak pull-up --> se activa con 0 el if es decir --> 0 = !(GPIOPinRead())
        if ( !GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) ){

            //Pone en cero los pines de Salida (LEDS R, B, G respectivamente)
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);

            //Enciende el LED verde por 4seg.
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(40000000);

            //Parpadeo LED verde
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(3000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(3000000);


            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(3000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(3000000);


            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(3000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(3000000);


            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(3000000);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            SysCtlDelay(3000000);

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(3000000);

            //Enciende el LED verde y rojo para formar color amarillo
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
            SysCtlDelay(30000000);

            //Apaga led verde y deja LED rojo encendido
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
            SysCtlDelay(30000000);

            //Apaga el LED rojo
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x00);
        }
    }
}

