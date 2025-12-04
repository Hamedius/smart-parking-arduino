// Smart Automatic Car Parking System Using Arduino and Proteus Simulation
// Based on project description by Hamed Nahvi & Yasin Shadrouh
// Hardware summary (from report):
//  - Arduino UNO
//  - 4 x IR/PIR sensors for parking slots (digital pins 8–11)
//  - DC motor for gate driven by L293D (control pins 6, 7)
//  - 16x2 LCD (connected on digital pins 0–5 in Proteus simulation)
//
// Assumptions:
//  - Sensor output is LOW when a car is present, HIGH when slot is empty
//  - motorOpenPin HIGH + motorClosePin LOW  => gate opening
//  - motorOpenPin LOW  + motorClosePin HIGH => gate closing
//  - Only one motion command is active at a time (short pulses)
//  - We don't use Serial because pins 0/1 are used by the LCD (Proteus style)

#include <LiquidCrystal.h>

// ---- Pin definitions ----

// LCD pins: rs, en, d4, d5, d6, d7
// NOTE: In the original Proteus simulation, LCD was connected to pins 0–5.
LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

// Parking slot sensors
const int slotSensorPins[4] = {8, 9, 10, 11};

// Motor driver pins (L293D)
const int motorOpenPin  = 6;
const int motorClosePin = 7;

// ---- State variables ----
bool slotOccupied[4] = {false, false, false, false};
int  freeSlots       = 4;   // total number of slots
bool gateClosed      = false; // false = open, true = closed

// Small delay (ms) for motor pulses
const unsigned long GATE_PULSE_TIME = 800;

void setup() {
  // Initialize sensor pins
  for (int i = 0; i < 4; i++) {
    pinMode(slotSensorPins[i], INPUT_PULLUP);
  }

  // Initialize motor pins
  pinMode(motorOpenPin, OUTPUT);
  pinMode(motorClosePin, OUTPUT);
  stopMotor();

  // Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Smart Parking ");
  lcd.setCursor(0, 1);
  lcd.print(" Initializing..");
  delay(1500);
}

void loop() {
  // Read all slot sensors and compute free slots
  updateSlotStatus();

  // Decide gate state
  if (freeSlots == 0 && !gateClosed) {
    closeGate();
  } else if (freeSlots > 0 && gateClosed) {
    openGate();
  }

  // Update LCD with current state
  updateLcd();

  delay(300); // basic refresh delay
}

// ---- Helper functions ----

void updateSlotStatus() {
  int freeCount = 0;

  for (int i = 0; i < 4; i++) {
    int value = digitalRead(slotSensorPins[i]);
    // LOW => car present (slot full), HIGH => slot free
    slotOccupied[i] = (value == LOW);
    if (!slotOccupied[i]) {
      freeCount++;
    }
  }

  freeSlots = freeCount;
}

void updateLcd() {
  lcd.clear();

  // First line: free slots + gate state
  lcd.setCursor(0, 0);
  lcd.print("Free:");
  lcd.print(freeSlots);
  lcd.print(" ");

  if (gateClosed) {
    lcd.print("Gate:C");
  } else {
    lcd.print("Gate:O");
  }

  // Second line: slot states (F = full, O = open)
  lcd.setCursor(0, 1);
  for (int i = 0; i < 4; i++) {
    lcd.print("S");
    lcd.print(i + 1);
    lcd.print(":");
    lcd.print(slotOccupied[i] ? "F" : "O");

    if (i < 3) lcd.print(" ");
  }
}

void openGate() {
  // Pulse motor in "open" direction
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gate Opening...");
  runMotorOpen();
  delay(GATE_PULSE_TIME);
  stopMotor();
  gateClosed = false;
}

void closeGate() {
  // Pulse motor in "close" direction
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Parking is Full!");
  lcd.setCursor(0, 1);
  lcd.print("Gate Closing...");
  runMotorClose();
  delay(GATE_PULSE_TIME);
  stopMotor();
  gateClosed = true;
}

void runMotorOpen() {
  digitalWrite(motorOpenPin, HIGH);
  digitalWrite(motorClosePin, LOW);
}

void runMotorClose() {
  digitalWrite(motorOpenPin, LOW);
  digitalWrite(motorClosePin, HIGH);
}

void stopMotor() {
  digitalWrite(motorOpenPin, LOW);
  digitalWrite(motorClosePin, LOW);
}
