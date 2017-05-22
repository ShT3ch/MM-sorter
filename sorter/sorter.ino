#include <Arduino.h>
#include <MD_TCS230.h>
#include "classifier.h"
#include <Servo.h>

#define  S0_OUT  2
#define  S1_OUT  3
#define  S2_OUT  4
#define  S3_OUT  5
MD_TCS230* ColorSensor;

#define SDataPush_OUT 7
#define SDisp_OUT 6

Servo servo_data_push;
Servo servo_disp;

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");

//    sensorData whiteCalibration;

//    whiteCalibration.value[TCS230_RGB_R] = 113240;
//    whiteCalibration.value[TCS230_RGB_G] = 106330;
//    whiteCalibration.value[TCS230_RGB_B] = 132540;

//    sensorData blackCalibration;
//    blackCalibration.value[TCS230_RGB_R] = 29100;
//    blackCalibration.value[TCS230_RGB_G] = 30150;
//    blackCalibration.value[TCS230_RGB_B] = 35660;

    ColorSensor = new MD_TCS230(S2_OUT, S3_OUT, S0_OUT, S1_OUT);
    ColorSensor->begin();
//    ColorSensor->setDarkCal(&blackCalibration);
//    ColorSensor->setWhiteCal(&whiteCalibration);

    pinMode(SDataPush_OUT, OUTPUT);
    pinMode(SDisp_OUT, OUTPUT);
    servo_data_push.attach(SDataPush_OUT);
    servo_disp.attach(SDisp_OUT);
    servo_data_push.write(1000);
}

void loop() 
{
    sensorData rgb;
    ColorSensor->read();
    while (!ColorSensor->available())
        ;
    ColorSensor->getRaw(&rgb);
    ColorSensor->setEnable(true);
    ColorSensor->setFilter(TCS230_RGB_X);
   uint32_t x = ColorSensor->readSingle();
    ColorSensor->setEnable(false);
    int color = make_a_decision((float) rgb.value[TCS230_RGB_R], (float) rgb.value[TCS230_RGB_G], (float) rgb.value[TCS230_RGB_B], (float) x);
    print_rgb(&rgb, x, color);

    delete ColorSensor;
    servo_data_push.attach(SDataPush_OUT);
    servo_disp.attach(SDisp_OUT);
    //int color = yellow;
    if (color != white)
    {
      
    //for (int i = 0; i < 5; i++)
      move_dispenser(color);
      push_data();
      
    }
    //set_rgb_led(&rgb);
    delay(1000);
    servo_data_push.detach();
    servo_disp.detach();
    ColorSensor = new MD_TCS230(S2_OUT, S3_OUT, S0_OUT, S1_OUT);
    ColorSensor->begin();
}

void push_data()
{
  //Serial.println("Pushing");
  for (int i = 1000; i < 2000; i += 50)
  {
    servo_data_push.write(i);
    delay(25);
  }
  servo_data_push.write(1000);
  delay(250);
}

void move_dispenser(int sector)
{
  int min = 1000;
  int max = 2300;
  int sectorsCount = 6;
  int value = min+sector*((max - min)/sectorsCount);
  servo_disp.write(value);
  Serial.print("Dispensing ");
  Serial.println(value);
  delay(500);
}

void print_rgb(sensorData* sd, uint32_t clean, int color)
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

//void set_rgb_led(colorData* sd)
//{
 //   analogWrite(R_OUT, 255 - sd->value[TCS230_RGB_R]);
  //  analogWrite(G_OUT, 255 - sd->value[TCS230_RGB_G]);
  //  analogWrite(B_OUT, 255 - sd->value[TCS230_RGB_B]);
//}
