#include "ap_fixed.h"
#include "ap_shift_reg.h"
#include "lms.h"

#define MAX 32
void lms_sw(ap_fixed<16,2> noise_in, ap_fixed<16,2> signal_noise, ap_fixed<16,2>  *output)
{
	// maybe make these all statics? Hardware doesn't destroy variables like software?

	static ap_shift_reg<ap_fixed<16,2>, MAX> y; //noise input shift register guy
	static ap_fixed<16,2> h[MAX]; //filter coeff's initialized to zero - static variables initialize to zero, hurray
	static const ap_fixed<16,2> mu = .125; // mu is always .125 and should only be defined once
	// perhaps make mu an input to change filter behavior on the fly???
	//ap_fixed<16,2> output = ap_fixed<16,2>(0); //output value
	int p; //defined as zero in the loops
	static ap_fixed<32,2> xhat; // defined as 0.0 in the loop

	y.shift(noise_in); //shift in the current input to the top of the shift register

	for (xhat=0.0, p=0; p<MAX-1; p++)
			xhat += y.read(p)*h[p];

	*output = (signal_noise - ap_fixed<16,2>(xhat)); //cast xhat from 32,2 to 16,2

	for (p=0; p<MAX-1; p++)
			h[p] += 2 * mu * (*output) * y.read(p);

}


ap_fixed<16,2> input_sw;
ap_fixed<16,2> input_hw;
ap_fixed<16,2> input_sw_noise;
ap_fixed<16,2> input_hw_noise;
ap_fixed<16,2> *output_hw;
ap_fixed<16,2> *output_sw;
ap_fixed<16,2> sw, hw;


int main()
{

	ap_fixed<16,2> input_sw;
	ap_fixed<16,2> input_hw;
	ap_fixed<16,2> input_sw_noise;
	ap_fixed<16,2> input_hw_noise;
	ap_fixed<16,2> *output_hw;
	ap_fixed<16,2> *output_sw;
	ap_fixed<16,2> sw, hw;

	
	//Write the input values
	for(int i = 0; i < RUN_LENGTH; i++){
		input_sw = ap_fixed<16,2>(0.01*i);
		input_hw = ap_fixed<16,2>(0.01*i);
		input_sw_noise = ap_fixed<16,2>(0.01*(i+2));
		input_hw_noise = ap_fixed<16,2>(0.01*(i+2));


	//Call to software model of fir
  	lms_sw(input_sw, input_sw_noise, output_sw);

	//Call to hardware model of fir
	lms_hw(input_hw, input_hw_noise, output_hw);


	sw = *output_sw;
	hw = *output_hw;
	if(sw != hw){
		printf("ERROR: i = %d\n",i);
		     return 1;
	}
	}
	printf("Success! both SW and HW models match.\n");
	return 0;

}

