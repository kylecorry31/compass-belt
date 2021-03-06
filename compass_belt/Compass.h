#ifndef Compass_H
#define Compass_H

#include <Wire.h>
#include <Arduino.h>
#include <MPU9250.h>
#include <KalmanFilter.h>

class Compass {
  public:
    Compass(float declination);
    void begin();
    float getHeading();
    void activeCalibrate();
    void resetCalibration();  
    void calibrate();
  private:
    float xb_;
    float yb_;
    float zb_;
    float xs_;
    float ys_;
    float zs_;
    float defaultXb_ = 34.83;
    float defaultYb_ = 62.37;
    float defaultZb_ = 1.38;
    float defaultXs_ = 22.33;
    float defaultYs_ = 4.12;
    float defaultZs_ = 22.21;
    float xMin_ = 1000;
    float xMax_ = -1000;
    float yMin_ = 1000;
    float yMax_ = -1000;
    float zMin_ = 1000;
    float zMax_ = -1000;
    float declination_ = 0;
    bool activeCalibration_ = false;
    long calibrationResetInverval_ = 1000L * 60L * 60L; // 1 Hour
    long lastCalibrationTime_ = 0L;
    MPU9250 imu_ {Wire, 0x68};
    KalmanFilter magXFilter_ {15, 15, 0, 0.05};
    KalmanFilter magYFilter_ {15, 15, 0, 0.05};
};

#endif
