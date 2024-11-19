#include <liblcd/liblcd.h>

int main()
{
    liblcd::LCDDisplay display = liblcd::LCDDisplay();

    display.backlightOn();
    display.blinkOff();
    display.gotoLastLine();
    display.scroll("Hello, how are you?  I hope that you are fine.");
    display.backlightOff();
    display.flashBacklight();
}
