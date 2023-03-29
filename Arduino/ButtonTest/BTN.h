#ifndef BTN_h
#define BTN_h

class Button{
  private:
  int lastState;
  bool* control;

  // for debouncing
  unsigned long debounceDuration = 50; // in milliseconds
  unsigned long timeSinceStateChange = 0; // in milliseconds

  public:
  const static int PRESSED = 1;
  const static int NOT_PRESSED = 0;

  int pin;
  Button(int pin);
  Button(int pin, bool* control);
  bool getState();
  bool isPressed();

  void update();
  void update(bool &x);
};

#endif