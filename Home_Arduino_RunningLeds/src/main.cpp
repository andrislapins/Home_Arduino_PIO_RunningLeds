#include <Arduino.h>

int number_of_leds      = 9;
int led_pins[]          = {3, 4, 5, 6, 7, 8, 9, 10, 11};
int delay_between_blips = 200;

int button_pin          = 12;
int button_state        = 0;

int direction           = 0;

int interrupt_pin       = 2;
int interrupt_mode      = RISING;

void change_direction() {
  direction = !direction;
}

void running_leds_right() {
  for (int i = number_of_leds - 1; i >= 0; i--) {
    digitalWrite(led_pins[i], HIGH);
    delay(delay_between_blips);
    digitalWrite(led_pins[i], LOW);
  }
}

void running_leds_left() {
  for (int i = 0; i < number_of_leds; i++) {
    digitalWrite(led_pins[i], HIGH);
    delay(delay_between_blips);
    digitalWrite(led_pins[i], LOW);
  }
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < number_of_leds; i++) {
    pinMode(led_pins[i], OUTPUT);
  }

  pinMode(button_pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(interrupt_pin), change_direction, interrupt_mode);
}

void loop() {
  if (direction) {
    running_leds_right();
  } else {
    running_leds_left();
  }
}