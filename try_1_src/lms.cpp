/*  lms.cpp - LMS adaptive Wiener filter  */
// test lol
#include "ap_fixed.h"
#include "ap_shift_reg.h"
#include "lms.h"


#define MAX 32 // customize our filter size here

void lms_hw (ap_fixed<16,2> noise_in, ap_fixed<16,2> signal_noise, ap_fixed<16,2>  *output)
{
	// maybe make these all statics? Hardware doesn't destroy variables like software?
	
	static ap_shift_reg<ap_fixed<16,2>, MAX> y; //noise input shift register guy
	static ap_fixed<16,2> h[MAX]; //filter coeff's initialized to zero - static variables initialize to zero, hurray
	static const ap_fixed<16,2> mu = 0.125; // mu is always .125 and should only be defined once
	// perhaps make mu an input to change filter behavior on the fly???
	//ap_fixed<16,2> output = ap_fixed<16,2>(0); //output value
	int p; //defined as zero in the loops
	static ap_fixed<32,2> xhat; // defined as 0.0 in the loop
	
	y.shift(noise_in); //shift in the current input to the top of the shift register

	lms_label0:for (xhat=0.0, p=0; p<MAX-1; p++)
			xhat += y.read(p)*h[p];

	*output = (signal_noise - ap_fixed<16,2>(xhat)); //cast xhat from 32,2 to 16,2

	lms_label1:for (p=0; p<MAX-1; p++)
			h[p] += 2 * mu * (*output) * y.read(p);


}
