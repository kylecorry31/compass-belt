#include "Compass.h"
void Compass::begin(){
  while(imu_.begin() < 0);
  resetCalibration();
}

float raw(float mag, float b, float s){
  return mag / s + b;
}

void Compass::resetCalibration(){
  xb_ = defaultXb_;
  yb_ = defaultYb_;
  zb_ = defaultZb_;
  xs_ = defaultXs_;
  ys_ = defaultYs_;
  zs_ = defaultZs_;
  xMin_ = 1000;
  xMax_ = -1000;
  yMin_ = 1000;
  yMax_ = -1000;
  zMin_ = 1000;
  zMax_ = -1000;
  imu_.setMagCalX(xb_, xs_);
  imu_.setMagCalY(yb_, ys_);
  imu_.setMagCalZ(zb_, zs_);
}

void Compass::activeCalibrate(){
  float x = raw(imu_.getMagX_uT(), xb_, xs_);
  float y = raw(imu_.getMagY_uT(), yb_, ys_);
  float z = raw(imu_.getMagZ_uT(), zb_, zs_);

  xMin_ = min(x, xMin_);
  yMin_ = min(y, yMin_);
  zMin_ = min(z, zMin_);
  xMax_ = max(x, xMax_);
  yMax_ = max(y, yMax_);
  zMax_ = max(z, zMax_);

  xb_ = (xMax_ + xMin_) / 2.0;
  yb_ = (yMax_ + yMin_) / 2.0;
  zb_ = (zMax_ + zMin_) / 2.0;

  xs_ = (xMax_ - xMin_) / 2.0;
  ys_ = (yMax_ - yMin_) / 2.0;
  zs_ = (zMax_ - zMin_) / 2.0;

  imu_.setMagCalX(xb_, xs_);
  imu_.setMagCalY(yb_, ys_);
  imu_.setMagCalZ(zb_, zs_);
}

void Compass::calibrate(){

  resetCalibration();

  for (int i = 0; i < 1000; i++)
  {
    imu_.readSensor();
    float x = raw(imu_.getMagX_uT(), xb_, xs_);
    float y = raw(imu_.getMagY_uT(), yb_, ys_);
    float z = raw(imu_.getMagZ_uT(), zb_, zs_);

    xMin_ = min(x, xMin_);
    yMin_ = min(y, yMin_);
    zMin_ = min(z, zMin_);
    xMax_ = max(x, xMax_);
    yMax_ = max(y, yMax_);
    zMax_ = max(z, zMax_);

    delay(20);
  }

  xb_ = (xMax_ + xMin_) / 2.0;
  yb_ = (yMax_ + yMin_) / 2.0;
  zb_ = (zMax_ + zMin_) / 2.0;

  xs_ = (xMax_ - xMin_) / 2.0;
  ys_ = (yMax_ - yMin_) / 2.0;
  zs_ = (zMax_ - zMin_) / 2.0;

  Serial.println(xb_);
  Serial.println(yb_);
  Serial.println(zb_);
  Serial.println(xs_);
  Serial.println(ys_);
  Serial.println(zs_);
  
  imu_.setMagCalX(xb_, xs_);
  imu_.setMagCalY(yb_, ys_);
  imu_.setMagCalZ(zb_, zs_);
}

float Compass::getHeading(){
  imu_.readSensor();

  if (activeCalibration_){
    activeCalibrate();
    if (millis() - lastCalibrationTime_ >= calibrationResetInverval_){
      resetCalibration();
      Serial.println("CALIBRATION RESET");
      lastCalibrationTime_ = millis();
    }
  }

  float x = magXFilter_.filter(imu_.getMagX_uT());
  float y = imu_.getMagY_uT();
  float z = magYFilter_.filter(imu_.getMagZ_uT());
  
  float heading = atan2(z, x) * 180 / PI; 

  if (heading < 0){
    heading += 360;  
  }

  heading += 90;

  if (heading >= 360){
    heading -= 360;
  }

  return heading;
}
