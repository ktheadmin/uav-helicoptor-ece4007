/*
* Copyright (c) 2012 Joey Yore
*
* Permission is hereby granted, free of charge, to any person obtaining a 
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation 
* the rights to use, copy, modify, merge, publish, distribute, sublicense, 
* and/or sell copies of the Software, and to permit persons to whom the 
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included 
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR 
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <time.h>
#include <iostream>
#include <math.h>

#ifndef M_PI
    #define M_PI 3.14159265
#endif

using namespace std;

#define MIN(a,b) ((a) < (b)) ? (a) : (b) 
#define MAX(a,b) ((a) > (b)) ? (a) : (b)
#define LIMIT(l,v,u) (MIN(MAX((v),(l)),(u)))
#define ABSV(a)  ((a) < 0) ? -(a) : (a)


struct T_TONDelay {
	bool in;
	bool out;
	double delay;
	time_t start_time;
};


struct T_CharCurvePoint {
	uint16_t x;
	int16_t y;
};

template <typename T>
void swap(T *a, T *b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}


template <typename T, typename U>
U scale(T value, float factor, bool scaleup) {

	long f = factor * 1000;
	U res = 0;

	if(scaleup) {
		res = (U)((((long long)value*f)+500)/1000);
	} else {
		res = (U)((((long long)value*1000))/f);
	}
	
	return res;
}

bool inDeadBand(int64_t valueA, int64_t valueB, int64_t thresh) {
	return ((ABSV(valueA-valueB))< thresh);
}


bool ton_delay(T_TONDelay &ton, bool in) {

	time_t now;
	time(&now);
	
	if(in) {
		if(!ton.in) {
			ton.start_time = now;
			ton.out = false;
		} else {
			ton.out = difftime(now,ton.start_time) >= ton.delay;
		}
	} else {
		ton.out = false;
	}

	ton.in = in;
	return ton.out;

}


bool toff_delay(T_TONDelay &toff, bool in) {

	time_t now;
	time(&now);

	if(!in) {
		if(toff.in) {
			toff.start_time = now;
			toff.out = true;
		} else {
			toff.out = !(difftime(now,toff.start_time) > toff.delay);
		}
	} else {
		toff.out = true;
	}

	toff.in = in;
	return toff.out;
}

//Helper
int16_t interp_2d(T_CharCurvePoint *pt1, T_CharCurvePoint *pt2, uint16_t x) {
	int16_t dx = (int16_t)pt2->x - (int16_t)pt1->x;
	int16_t dy = pt2->y - pt1->y;
	int32_t m = 1000 * ((int32_t)dy) / dx;
	int16_t b = (int16_t)(pt2->y - m * pt2->x / 1000);
	return (int16_t)((m * x) / 1000 + b);
}

int16_t char_curve(T_CharCurvePoint *curve, uint16_t x) {
	T_CharCurvePoint *pt1 = curve;
	T_CharCurvePoint *pt2;

	while(pt1->x < x) {
		++pt1;
	}

	pt2 = pt1 - 1;
	return interp_2d(pt1,pt2,x);
}

double inv_sqrt(double x) {
	double halfx = 0.5*x;
	double y = x;
	long i = *(long *) &y;
	i = 0x5F3759DF - (i >> 1);
	y = *(double *) &i;
	y = y * (1.5 - (halfx * y * y));

	return y;
}

double deg2rad(double deg) {
	return ((deg*M_PI)/180);
}

double rad2deg(double rad) {
	return ((rad*180)/M_PI);
}

#endif
