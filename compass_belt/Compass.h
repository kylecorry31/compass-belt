#ifndef Compass_H
#define Compass_H

#include <Wire.h>
#include <Arduino.h>
#include <MPU9250.h>
#include <KalmanFilter.h>

class Compass {
  private:
    float xb_;
    float yb_;
    float zb_;
    float xs_;
    float ys_;
    float zs_;
    float defaultXb_ = 32.87;
    float defaultYb_ = 53.86;
    float defaultZb_ = 2.67;
    float defaultXs_ = 25.37;
    float defaultYs_ = 7.98;
    float defaultZs_ = 31.43;
    float xMin_ = 1000;
    float xMax_ = -1000;
    float yMin_ = 1000;
    float yMax_ = -1000;
    float zMin_ = 1000;
    float zMax_ = -1000;
    bool activeCalibration_ = false;
    long calibrationResetInverval_ = 1000L * 60L * 60L; // 1 Hour
    long lastCalibrationTime_ = 0L;
    MPU9250 imu_ {Wire, 0x68};
    KalmanFilter magXFilter_ {15, 15, 0, 0.05};
    KalmanFilter magYFilter_ {15, 15, 0, 0.05};
  public:
    void begin();
    float getHeading();
    void activeCalibrate();
    void resetCalibration();  
    void calibrate();
};

#endif
