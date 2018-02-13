#ifndef _TELE_H_
#define _TELE_H_



void doTeleop();
void coneArmControl(const bool moveUp, const bool moveDown);
void wheelControl(int leftXAxis, int leftYAxis, int rightXAxis, int rightYAxis);
void goalArmControl1(const bool moveUp, const bool moveDown);
void coneClawControl(const bool open, const bool close);
void goalArmControl(const bool moveUp, const bool moveDown);
//void goalClawControl(); // depricated
void pusherControl(const bool open, const bool close);

#include "Tele.c"

#endif // _TELE_H_
