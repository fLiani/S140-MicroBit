#include "MicroBit.h"

MicroBit uBit;

int main()
{
    MICROBIT_DEBUG_DMESG("Starting");
    // Initialise the micro:bit runtime.
    uBit.init();

    uBit.serial.printf("Hello");
}