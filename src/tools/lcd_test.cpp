#include <liblcd/liblcd.h>

int main()
{
    liblcd::LCDDisplay display = liblcd::LCDDisplay();

    display.write("\x1b[L+");
    display.write("\x1b[Lb");
    display.write("\r");
    display.scroll("Hello, how are you?  I hope that you are fine.");
    display.write("\x1b[L-");
    display.write("\x1b[L*");
}
