#import "BTN.h"
#import "LED.h"

bool myBool = false;

Button button(12, &myBool); // add switch var
LED led(LED_BUILTIN);
LED btnLight(11);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  led.set(myBool);
  btnLight.set(myBool);

  // update buttons (buttons have to be updated)
  button.update();
}
