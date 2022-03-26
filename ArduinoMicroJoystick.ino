// --------------------------------------------------------------------------------
// Arduino Micro Power USB Joystick
// This sketch file can be used only with Arduino Micro or Leonardo.
// For more information, visit the original project on Thingiverse.
// https://www.thingiverse.com/thing:4576634
// --------------------------------------------------------------------------------

// ================================================================================
// =============================  Settings and Stuff  =============================
// ================================================================================

// ===== Pin Definitions =====
//Adjust pin numbers here if your joystick is wired differently.

//Hall Effect Sensors
const byte X_PIN = A0;
const byte Y_PIN = A1;

//Buttons
const byte BUTTON_0 = 3;
const byte BUTTON_1 = 6;
const byte BUTTON_2 = 2;
const byte BUTTON_3 = 7;
const byte BUTTON_4 = 5;
const byte BUTTON_5 = 4;

// ===== Axes Settings =====
//Change these settings to adjust trim and limits.
//Calibrating your joystick in Windows achives has the same effect.
//To invert an axis, set INVERT to -1.

//X-Axis
const int X_MIN = 512;
const int X_MAX = 1023;
const int X_TRIM = (X_MAX - X_MIN) / 2;
const int X_INVERT = 1;

//Y-Axis
const int Y_MIN = 512;
const int Y_MAX = 1023;
const int Y_TRIM = (Y_MAX - Y_MIN) / 2;
const int Y_INVERT = 1;

// ===== MISC Settings =====
//General
const int controllerDelay = 100;

//Axes Mapping
const int VALUE_MIN = 0;
const int VALUE_MAX = 1023;

// ===== Including and Setting Up Joystick Library =====
#include <Joystick.h>

Joystick_ Joystick(0x04,JOYSTICK_TYPE_JOYSTICK,
  6, 0,                  //Button Count, Hat Switch Count
  true, true, false,     //X and Y, but no Z Axis
  false, false, false,   //No Rx, Ry, or Rz
  false, false,          //No rudder, no throttle
  false, false, false);  //No accelerator, brake, or steering

// ================================================================================
// ==============================      FIRMWARE      ==============================
// ================================================================================

void setup()
{
  //Initialize Pins
  pinMode(BUTTON_0, INPUT_PULLUP);
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  pinMode(BUTTON_5, INPUT_PULLUP);

  //Initialize Joystick
  Joystick.begin(false); //false = dont send automatically. We will sendState() at the end of the loop.
  Joystick.setXAxisRange(VALUE_MIN, VALUE_MAX);
  Joystick.setYAxisRange(VALUE_MIN, VALUE_MAX);
}

void loop()
{
  ReadButtons();
  ReadAnalogAxes();

  Joystick.sendState();
  delay(controllerDelay);
}

void ReadButtons()
{
  //A LOW pin state means the button is pressed.
  Joystick.setButton(0, !digitalRead(BUTTON_0));
  Joystick.setButton(1, !digitalRead(BUTTON_1));
  Joystick.setButton(2, !digitalRead(BUTTON_2));
  Joystick.setButton(3, !digitalRead(BUTTON_3));
  Joystick.setButton(4, !digitalRead(BUTTON_4));
  Joystick.setButton(5, !digitalRead(BUTTON_5));
}

void ReadAnalogAxes()
{
  int valueX = map(analogRead(X_PIN) + X_TRIM , X_MIN, X_MAX, VALUE_MIN, VALUE_MAX) * X_INVERT;
  Joystick.setXAxis(valueX);
  
  int valueY = map(analogRead(Y_PIN) + Y_TRIM , Y_MIN, Y_MAX, VALUE_MIN, VALUE_MAX) * Y_INVERT;
  Joystick.setYAxis(valueY);
}
