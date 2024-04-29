#include "setup.hpp"

void setup () {
    Serial.begin (115200);

    lcd.init ();
    lcd.backlight ();
    delay (100);
    lcd.setCursor (0,0);
    lcd.print ("   ENSMASTEEL   ");
}

void loop () {
    // comTEE.receive ();
    // if (comTEE.retrieve (&teensy_msg)) {
    //     switch (teensy_msg.id) {
    //         case LCD_CLEAR:
    //             lcd.clear ();
    //             break;
    //         case LCD_PRINT:
    //             lcd.setCursor (0, 1);
    //             lcd.print ("oui");
    //             break;
    //     }
    // }
    delay(1000);
    Serial.println("hello");
    
}
