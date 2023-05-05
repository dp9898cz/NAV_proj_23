#include <Wire.h> // For the SDA display
#include <Adafruit_GFX.h> // For the SDA display
#include <Adafruit_SSD1306.h> // For the SDA display
#include <Ultrasonic.h> // ultrasonic sensor
#include <RotaryEncoder.h> // Rotation encoder

#define OLED_RESET -1 // For the SDA display
Adafruit_SSD1306 display(OLED_RESET); // init SDA display

#define TRIGGER_PIN 2 // For the ultrasonic sensor
#define ECHO_PIN 4 // For the ultrasonic sensor
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN); // init ultrasonic sensor

#define ROTARY_PIN_A 14 // For the ultrasonic sensor
#define ROTARY_PIN_B 27 // For the ultrasonic sensor
RotaryEncoder *encoder = nullptr; // defined in setup

// for delay control
#define ROTARYSTEPS 20
#define ROTARYMIN 100
#define ROTARYMAX 1000

// for debounce problem control
int delay_rotary = 5;
int last_bounce = 0;

int delay_time = 500;

// interuption function
void checkPosition()
{
  if ((millis() - last_bounce) > delay_rotary) {
    encoder->tick(); // just call tick() to check the state.

    int newPos = encoder->getPosition() * ROTARYSTEPS;

    if (newPos < ROTARYMIN) {
      encoder->setPosition(ROTARYMIN / ROTARYSTEPS);
      newPos = ROTARYMIN;

    } else if (newPos > ROTARYMAX) {
      encoder->setPosition(ROTARYMAX / ROTARYSTEPS);
      newPos = ROTARYMAX;
    } // if

    if (delay_time != newPos) {
      Serial.print("Delay changed: ");
      Serial.println(newPos);
      delay_time = newPos;
  }
    last_bounce = millis();
  }
}

void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // For the SDA display

  encoder = new RotaryEncoder(ROTARY_PIN_A, ROTARY_PIN_B, RotaryEncoder::LatchMode::TWO03);
  encoder->setPosition(25); // half position

  // register interrupt routine
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_A), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ROTARY_PIN_B), checkPosition, CHANGE);
}

void loop() {
  long distance = ultrasonic.read();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.print("Distance: ");
  display.print(distance);
  display.print(" cm");
  display.setCursor(0,10);
  display.print("Delay: ");
  display.print(delay_time);
  display.print(" ms");
  display.display();

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  Serial.println();

  delay(delay_time);
}