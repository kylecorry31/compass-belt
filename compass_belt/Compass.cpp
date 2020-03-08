#include "Compass.h"
void Compass::begin(){
  while(imu_.begin() < 0);
  imu_.setMagCalX(xb_, xs_);
  imu_.setMagCalY(yb_, ys_);
  imu_.setMagCalZ(zb_, zs_);
}

float Compass::getHeading(){
  imu_.readSensor();
  float x = magXFilter_.filter(imu_.getMagX_uT());
  float y = magYFilter_.filter(imu_.getMagY_uT());
  float z = imu_.getMagZ_uT();
  
  float heading = atan2(z, x) * 180 / PI; 

  if (heading < 0){
    heading += 360;  
  }

//  TODO: Set the correct North heading 
//  heading += 90;
//
//  if (heading >= 360){
//    heading -= 360;  
//  }  

  return heading;
}
