#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework4.h"
bool charFSM(char rChar);

int main(void)
{
    bool finished;
    char rChar;
    char *response = "\n\n\r2534 is the best course in the curriculum!\r\n\n";

    // TODO: Declare the variables that main uses to interact with your state machine.


    // Stops the Watchdog timer.
    initBoard();
    // TODO: Declare a UART config struct as defined in uart.h.
    //       To begin, configure the UART for 9600 baud, 8-bit payload (LSB first), no parity, 1 stop bit.
    eUSCI_UART_ConfigV1 uartConfig =
    {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,                        // SMCLK Clock Source = 3MHz
        19,                                           // UCBR   = 312
        8,                                            // UCBRF  = 8
        0x55,                                         // UCBRS  = 0x55
        EUSCI_A_UART_NO_PARITY,                       // No Parity
        EUSCI_A_UART_LSB_FIRST,                       // LSB First
        EUSCI_A_UART_ONE_STOP_BIT,                    // One stop bit
        EUSCI_A_UART_MODE,                            // UART mode
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION, // Oversampling
        EUSCI_A_UART_8_BIT_LEN                        // 8-bit
    } ;

    // TODO: Make sure Tx AND Rx pins of EUSCI_A0 work for UART and not as regular GPIO pins.
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1, GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

    // TODO: Initialize EUSCI_A0
    UART_initModule(EUSCI_A0_BASE, &uartConfig);

    // TODO: Enable EUSCI_A0
    UART_enableModule(EUSCI_A0_BASE);
    while (1)
    {
        // TODO: Check the receive interrupt flag to see if a received character is available.
        //       Return 0xFF if no character is available.
        if (UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) == EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)
        {
            rChar = UART_receiveData(EUSCI_A0_BASE);
        }
        else
        {
            rChar = 0xFF;
        }

        // TODO: If an actual character was received, echo the character to the terminal AND use it to update the FSM.
        //       Check the transmit interrupt flag prior to transmitting the character.
        if (rChar != 0xFF)
        {
            finished = charFSM(rChar);
        }
        if (finished == true)
        {
            *response = "\n\n\r2534 is the best course in the curriculum!\r\n\n";
        }
        else
        {
            return 0;
        }


        // TODO: If the FSM indicates a successful string entry, transmit the response string.
        //       Check the transmit interrupt flag prior to transmitting each character and moving on to the next one.
        //       Make sure to reset the success variable after transmission.
        bool UARTCanSend(uint32_t moduleInstance)
        {
            return UART_getInterruptStatus (EUSCI_A0_BASE, EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG) == EUSCI_A_UART_TRANSMIT_INTERRUPT_FLAG;
        }
        void UARTPutString(uint32_t moduleInstance, *response)
        {
            UART_transmitData(EUSCI_A0_BASE, *response);
        }
        return 0;
    }
}

void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

// TODO: FSM for detecting character sequence.
bool charFSM(char rChar)
{
    bool finished = false;
    bool start = false;
    bool step2 = false;
    bool step3 = false;
    if (rChar == 2)
        start = true;
    }
    else
    {
        start = false;
    }

    if (start == true && rChar == 5)
    {
        step2 = true;
    }
    else
    {
        step2 = false;
    }

    if (step2 == true && rChar == 3 && start == false)
    {
        step3 = true;
    }
    else
    {
        step3 = false;
    }

    if (step3 == true && rChar == 4 && step2 == false)
    {
        finished = true;
    }
    else
    {
        finished = false;
    }

    return finished;
}
