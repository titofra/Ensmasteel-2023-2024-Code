#include "setup.hpp"

Servo clawL, clawR;
Communication<msg_ardtee> comTeensy (&Serial1);
msg_ardtee msg;

void setup () {
  Serial.begin(115200);
  Serial1.begin(115200);

  clawL.attach (PIN_PWM_CLAW_L);
  clawR.attach (PIN_PWM_CLAW_R);
  clawL.write (0);
  clawR.write (180);
}

void loop () {
    if(comTeensy.retrieve (&msg)){
        switch (msg.id) {
            case OPEN_CLAWS :
                clawL.write(25);
                clawR.write(155);
                break;
            case CLOSE_CLAWS :
                clawL.write(0);
                clawR.write(180);
                break;
        }
    }
}