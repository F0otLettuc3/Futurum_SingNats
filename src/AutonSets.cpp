#include "main.h"

Motor FL(FLPort);
Motor ML(MLPort);
Motor BL(BLPort);
Motor FR(FRPort);
Motor MR(MRPort);
Motor BR(BRPort);
Motor Intake(IntakePort);
ADIDigitalOut Expansion(ExpansionPort);

void red1 (){

  double start = millis();
  Expansion.set_value(HIGH);
  baseMove(-4);
  Intake.move(-127);
  baseMove(-4);
  waitBase(500);
  delay(200);
  Intake.move(0);
  delay(100);
  baseMove(5);
  waitBase(1000);
  baseTurn(42);
  waitBase(1000);
  baseMove(64);
  waitBase(3000);
  baseTurn(-57);
  waitBase(1500);
  CataMove(true);
  delay(700);
  CataMove(false);
  delay(500);
  baseTurn(-135);
  waitBase(2000);
  Intake.move(127);
  baseMove(-57);
  waitBase(1500);
  baseTurn(-90);
  waitBase(2000);
  baseMove(-14);
  delay(500);
  Intake.move(0);
//
  printf("Time %.2f", start );

}

void red2 (){
}

void blue1 (){
}

void blue2 (){
}

void skills (){

  baseTurn(180);
}
