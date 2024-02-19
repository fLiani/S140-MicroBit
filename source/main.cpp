#include "MicroBit.h"

MicroBit uBit;

int main()
{
    // Initialise the micro:bit runtime.
    uBit.init();
    MICROBIT_DEBUG_DMESG("Starting");
}