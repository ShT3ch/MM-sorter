#include <Arduino.h>
#include <MD_TCS230.h>
#include <Servo.h>
#include "classifier.h"

#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5
MD_TCS230* ColorSensor;

#define SERVO_MM_PUSH_OUT 7
// Waiting should be less than acting here. Fix push_mm if needed
#define SERVO_MM_PUSH_STATE_WAITING 1000
#define SERVO_MM_PUSH_STATE_ACTING  2000
Servo ServoMMPush;

#define SERVO_GUTTER_OUT 6
#define SERVO_GUTTER_STATE_MIN 1000
#define SERVO_GUTTER_STATE_MAX 2300
#define SERVO_GUTTER_SECTORS_COUNT 6
Servo ServoGutter;

#define MM_ITERATION_DELAY 1000

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");

    pinMode(SERVO_MM_PUSH_OUT, OUTPUT);
    ServoMMPush.attach(SERVO_MM_PUSH_OUT);
    ServoMMPush.write(SERVO_MM_PUSH_STATE_WAITING);
    
    pinMode(SERVO_GUTTER_OUT, OUTPUT);
    ServoGutter.attach(SERVO_GUTTER_OUT);
}

void loop() 
{
    // Initialize color sensor
    ColorSensor = new MD_TCS230(S2_OUT, S3_OUT, S0_OUT, S1_OUT);
    ColorSensor->begin();
    
    // Reading data from color sensor
    sensorData sd;
    ColorSensor->read();
    while (!ColorSensor->available())
        ;
    ColorSensor->getRaw(&sd);
    uint32_t clean = read_clean();
    
    // Call generated classifier to detect m&m color
    int color = make_a_decision((float) sd.value[TCS230_RGB_R], (float) sd.value[TCS230_RGB_G], (float) sd.value[TCS230_RGB_B], (float) clean);
    print_debug_output(&sd, clean, color);
    
    // Delete color sensor. It somehow conflicts with servos and disposing helps
    delete ColorSensor;
    
    // Initialize servos
    ServoMMPush.attach(SERVO_MM_PUSH_OUT);
    ServoGutter.attach(SERVO_GUTTER_OUT);
    
    // White means there is no m&m on sensor
    // Used a color name to simplify python code generator
    if (color != white)
    {
      move_gutter(color);
      delay(100);
      push_mm();
    }
    delay(MM_ITERATION_DELAY);
    
    // Dispose servos
    ServoMMPush.detach();
    ServoGutter.detach();
}

uint32_t read_clean()
{
    ColorSensor->setEnable(true);
    ColorSensor->setFilter(TCS230_RGB_X);
    uint32_t clean = ColorSensor->readSingle();
    ColorSensor->setEnable(false);
    return clean;
}

void push_mm()
{
    Serial.println("Pushing");
    for (int i = SERVO_MM_PUSH_STATE_WAITING; i < SERVO_MM_PUSH_STATE_ACTING; i += 50)
    {
      ServoMMPush.write(i);
      delay(25);
    }
    ServoMMPush.write(SERVO_MM_PUSH_STATE_ACTING);
    delay(25);
    ServoMMPush.write(SERVO_MM_PUSH_STATE_WAITING);
}

void move_gutter(int sector)
{
    int oneSectorLen = (SERVO_GUTTER_STATE_MAX - SERVO_GUTTER_STATE_MIN)/SERVO_GUTTER_SECTORS_COUNT;
    int value = SERVO_GUTTER_STATE_MIN + sector*oneSectorLen;
    ServoGutter.write(value);
    Serial.print("Gutter moves to ");
    Serial.println(value);
}

void print_debug_output(sensorData* sd, uint32_t clean, int color)
{
    Serial.print(sd->value[TCS230_RGB_R]);
    Serial.print(" ");
    Serial.print(sd->value[TCS230_RGB_G]);
    Serial.print(" ");
    Serial.print(sd->value[TCS230_RGB_B]);
    Serial.print(" ");
    Serial.print(clean);
    Serial.print(" ");
    Serial.print(color);
    Serial.println();
}
