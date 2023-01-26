#include "main.h"
double encdL = 0, encdR = 0, bearing = 0, encdImu = 0, angle = halfPI;
extern double encdL, encdR, bearing, angle;

void Sensors(void * ignore){
  Motor FL (FLPort);
  Motor ML (MLPort);
  Motor BL (BLPort);
  Motor FR (FRPort);
  Motor MR (MRPort);
  Motor BR (BRPort);
  Imu imu (imuPort);

  while(true){
    if(!imu.is_calibrating()){
      encdL = BL.get_position();
      encdR = BR.get_position();
      encdImu = imu.get_pitch();
      bearing = imu.get_rotation();
      angle = halfPI - bearing * toRad;

    }
    delay(5);
  }
}
