#ifndef Compass_H
#define Compass_H

#include <Wire.h>
#include <Arduino.h>
#include <MPU9250.h>
#include <KalmanFilter.h>

class Compass {
  private:
    float xb_ = -19.4;
    float yb_ = 10.01;
    float zb_ = -7.59;
    float xs_ = 1.12;
    float ys_ = 0.67;
    float zs_ = 1.66;
    MPU9250 imu_ {Wire, 0x68};
    KalmanFilter magXFilter_ {15, 15, 0, 0.05};
    KalmanFilter magYFilter_ {15, 15, 0, 0.05};
  public:
    void begin();
    float getHeading();  
};

#endif
