#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

//PIN DEFINE
#define PIN_RIGHT_POS 3
#define PIN_RIGHT_NEG 4
#define PIN_LEFT_POS  5
#define PIN_LEFT_NEG  6

//MACROS
#define MOTOR_OFF(x)      digitalWrite(x, LOW)
#define MOTOR_ON(x)       digitalWrite(x, HIGH)
#define MOTOR_INITIATE(x) pinMode(x, OUTPUT)

//ENUM
enum MOTOR__DIR {
  STOP,
  FORWARD,
  BACKWARD,
  RIGHT,
  LEFT
};

MOTOR__DIR MOTOR_DIR_CUR = STOP;
MOTOR__DIR MOTOR_DIR_PRE = STOP;

//VARIABLES
const int MOTOR_PINS[] = {PIN_RIGHT_POS, PIN_RIGHT_NEG, PIN_LEFT_POS, PIN_LEFT_NEG};
int MOTOR_CONTROL_STATE = -1;

//MOTOR DIRECTION LOOP
void MOTOR_LOOP() {
  if (MOTOR_DIR_PRE != MOTOR_DIR_CUR) {
    Serial.print("MOTOR DIRECTION: ");
    if (MOTOR_DIR_CUR == FORWARD) {
      Serial.print("FORWARD");
      MOTOR_OFF(PIN_RIGHT_NEG);
      MOTOR_OFF(PIN_LEFT_NEG);
      MOTOR_ON(PIN_RIGHT_POS);
      MOTOR_ON(PIN_LEFT_POS);
    } else if (MOTOR_DIR_CUR == BACKWARD) {
      Serial.print("BACKWARD");
      MOTOR_OFF(PIN_RIGHT_POS);
      MOTOR_OFF(PIN_LEFT_POS);
      MOTOR_ON(PIN_RIGHT_NEG);
      MOTOR_ON(PIN_LEFT_NEG);
    } else if (MOTOR_DIR_CUR == RIGHT) {
      Serial.print("RIGHT");
      MOTOR_OFF(PIN_RIGHT_POS);
      MOTOR_OFF(PIN_RIGHT_NEG);
      MOTOR_OFF(PIN_LEFT_NEG);
      MOTOR_ON(PIN_LEFT_POS);
    } else if (MOTOR_DIR_CUR == LEFT) {
      Serial.print("LEFT");
      MOTOR_OFF(PIN_RIGHT_NEG);
      MOTOR_OFF(PIN_LEFT_POS);
      MOTOR_OFF(PIN_LEFT_NEG);
      MOTOR_ON(PIN_RIGHT_POS);
    } else {
      Serial.print("STOP");
      //CONSIDER THIS AS STOP
      for (int i = 0; i < (sizeof(MOTOR_PINS) / sizeof(int)); i++) MOTOR_OFF(MOTOR_PINS[i]);
    }
    Serial.println();
    MOTOR_DIR_PRE = MOTOR_DIR_CUR;
  }
}

void MOTOR_PIN_INITIATE() {
  if (MOTOR_CONTROL_STATE != 0) {
    for (int i = 0; i < ((sizeof(MOTOR_PINS) / sizeof(int))); i++) {
      MOTOR_INITIATE(MOTOR_PINS[i]);
      MOTOR_OFF(MOTOR_PINS[i]);
    }
    MOTOR_CONTROL_STATE = 0;
  }
}

#endif
