 #include "main.h"
#define CataKp 0.016
#define CataKd 0

Motor Catapult(CataPort);
Rotation CataRot(CataSensor);

double CTarg = 73500, CPrevErr = 0, CPower = 0;
bool Manual = false, CMoving;
double CPos, catapultError;

//Catapult Pid
void CataControl(void*ignore){
  while(true){
    if(Manual == false){
      CPos = CataRot.get_position()%108000;
     catapultError = CTarg - CPos;
     if((CPrevErr-fabs(catapultError))>90000||fabs(catapultError)<200){CMoving = false;}
     else{CMoving=true;}
     if(catapultError<0){catapultError = 108000-fabs(catapultError);}
     if(CMoving==true){
       CPower = catapultError*CataKp + (catapultError-CPrevErr)*CataKd;
       Catapult.move(CPower);
       CPrevErr = catapultError;
     }
     else{Catapult.move(0);}
     double time = millis();
     }
     delay(5);
     // printf("pos %.2f, targ %.2f, error%.2f, power%.2f\n",CPos,CTarg,catapultError,CPower);
     delay(20);
   }
}

void IntakeControl(double Time);

void CataMove(bool Shoot){
  if(Shoot == true){
    CTarg = 0;
  }
  else{
    CTarg = 67500;
  }
}
