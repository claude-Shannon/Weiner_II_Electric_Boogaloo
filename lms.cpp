/*  lms.cpp - LMS adaptive Wiener filter  */
#include "ap_fixed.h"
#include "ap_shift_reg.h"
#include "fir.h"


#define MAX 16





ap_fixed<16,2> lms_hw(/*ap_fixed<16,2> *e,*/ ap_fixed<16,2> noise_in, ap_fixed<16,2> signal_noise)
{
	static ap_shift_reg<ap_fixed<16,2>, 32> y; //noise input shift register guy
	ap_fixed<16,2> output = 0;
	ap_fixed<16,2> mu = .125;
	ap_fixed<16,2> h[32] = {0};



int p =0;

ap_fixed<32,2> xhat;

y.shift(signal_noise); //shift in the current input to the top of the shift register



lms_label0:for (xhat=0.0, p=0; p<31; p++)
	  xhat += y.read(p)*h[p];



output = (signal_noise - ap_fixed<16,2>(xhat));


lms_label1:for (p=0; p<31; p++)
	  h[p] += 2 * mu * output * y.read(p);

return output;


}
