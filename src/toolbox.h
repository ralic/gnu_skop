// Copyright (C) 2007, 2008, 2009 Marc Betoule

// This file is part of SkOP.

// SkOP is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
  
// SkOP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with SkOP.  If not, see <http://www.gnu.org/licenses/>.


/**
 * \file toolbox.h
 * \brief Miscellanous usefull tools
 */    

#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <cmath>
#include <iostream>
#include <QColor>
using namespace std;

const double degr2rad = M_PI/180.0;
const double arcmin2rad = degr2rad/60.0;
const double rad2degr = 180.0/M_PI;
const double rad2arcmin = rad2degr*60.0;

class Vec3{
 public:
  Vec3(){a[0] = a[1] = a[2] = 0;}
  Vec3(double theta, double phi){
    double c = sin(theta);
    a[0] = c * cos(phi);
    a[1] = c * sin(phi);
    a[2] = cos(theta);
  }
  Vec3(double x, double y, double z){
    a[0] = x; a[1] = y;a[2] = z;
  }
  double & operator[](int i){return a[i];}
  Vec3 operator * (double b){
    Vec3 c;
    for(int i = 0 ; i < 3 ; i++)
	c[i]+=a[i]*b;
    return c;
  }
  double operator * (Vec3 b){
    double c;
    for(int i = 0 ; i < 3 ; i++)
	c+=a[i]*b[i];
    return c;
  }

  Vec3 operator + (Vec3 b){
    Vec3 c;
    for(int i = 0 ; i < 3 ; i++)
	c[i] = a[i]+b[i];
    return c;
  }
  Vec3 operator - (Vec3 b){
    Vec3 c;
    for(int i = 0 ; i < 3 ; i++)
	c[i] = a[i]-b[i];
    return c;
  }
  double norm(){
    return sqrt( *this * *this);
  }
  void ang(double & theta, double & phi){
    theta = acos(a[2]/norm());
    phi = atan2(a[1],a[0]);
  }
  double a[3];
};

class Mat3{
  
 public:
  Mat3(){
    for(int i = 0 ; i < 3 ; i++)
      for(int j = 0 ; j < 3 ; j++)
	a[i][j] = 0;
  }
  Mat3(double a1,double a2,double a3,double a4,double a5,double a6,double a7,double a8,double a9){
    a[0][0] = a1;
    a[0][1] = a2;
    a[0][2] = a3;
    a[1][0] = a4;
    a[1][1] = a5;
    a[1][2] = a6;
    a[2][0] = a7;
    a[2][1] = a8;
    a[2][2] = a9;

  }
  void operator = (double * tab){
    for(int i = 0 ; i < 3 ; i++)
      for(int j = 0 ; j < 3 ; j++)
	a[i][j] = tab[3*i+j];
  }
  void operator = (Mat3 b){
    for(int i = 0 ; i < 3 ; i++)
      for(int j = 0 ; j < 3 ; j++)
	a[i][j] = b[i][j];
  }
  double * operator[](int i){return a[i];}
  Mat3 operator * (double b){
    Mat3 c;
    for(int i = 0 ; i < 3 ; i++)
      for(int j = 0 ; j < 3 ; j++)
	c[i][j]+=a[i][j]*b;
    return c;
  }
  Mat3 operator * (Mat3 b){
    Mat3 c;
    for(int i = 0 ; i < 3 ; i++)
      for(int j = 0 ; j < 3 ; j++)
	for(int k = 0 ; k < 3 ; k++)
	  c[i][j]+=a[i][k]*b[k][j];
    return c;
  }
  Vec3 operator * (Vec3 b){
    Vec3 c;
    for(int i = 0 ; i < 3 ; i++)
      for(int j = 0 ; j < 3 ; j++)
	c[i]+=a[i][j]*b[j];
    return c;
  }

  void eulerZXZ(double alpha, double beta, double gamma);
  void eulerZYZ(double alpha, double beta, double gamma);
  double a[3][3];
};

ostream & operator << (ostream &os,  Mat3 & m);
ostream & operator << (ostream &os,  Vec3 & v);

QRgb jet(double value, int alpha = 255);

inline double fmodulo (double v1, double v2){
  return (v1>=0) ? ((v1<v2) ? v1 : fmod(v1,v2)) : (fmod(v1,v2)+v2);
}

#endif
