#ifndef _TELE_H_
#define _TELE_H_



void doTeleop();
void coneArmControl(const bool moveUp, const bool moveDown, const float multilpier);
float applyCurve(float input, int n);
void wheelControl(int leftXAxis, int leftYAxis, int rightXAxis, int rightYAxis, const float multilpier);
void goalArmControl1(const bool moveUp, const bool moveDown, const float multilpier);
void coneClawControl(const bool open, const bool close, const float multilpier);
void goalArmControl(const bool moveUp, const bool moveDown, const float multilpier);
//void goalClawControl(); // depricated
void pusherControl(const bool open, const bool close, const float multilpier);

#include "Tele.c"

#endif // _TELE_H_
