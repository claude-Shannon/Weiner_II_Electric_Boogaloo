/*******************************************************************************
Vendor: Xilinx 
Associated Filename: fir_test.cpp
Purpose: FIR Filter Example for Vivado HLS
Revision History: July 6, 2012 - initial release
                                                
*******************************************************************************
© Copyright 2008 - 2012 Xilinx, Inc. All rights reserved. 

This file contains confidential and proprietary information of Xilinx, Inc. and 
is protected under U.S. and international copyright and other intellectual 
property laws.

DISCLAIMER
This disclaimer is not a license and does not grant any rights to the materials 
distributed herewith. Except as otherwise provided in a valid license issued to 
you by Xilinx, and to the maximum extent permitted by applicable law: 
(1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL FAULTS, AND XILINX 
HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, 
INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, OR 
FITNESS FOR ANY PARTICULAR PURPOSE; and (2) Xilinx shall not be liable (whether 
in contract or tort, including negligence, or under any other theory of 
liability) for any loss or damage of any kind or nature related to, arising under 
or in connection with these materials, including for any direct, or any indirect, 
special, incidental, or consequential loss or damage (including loss of data, 
profits, goodwill, or any type of loss or damage suffered as a result of any 
action brought by a third party) even if such damage or loss was reasonably 
foreseeable or Xilinx had been advised of the possibility of the same.

CRITICAL APPLICATIONS
Xilinx products are not designed or intended to be fail-safe, or for use in any 
application requiring fail-safe performance, such as life-support or safety 
devices or systems, Class III medical devices, nuclear facilities, applications 
related to the deployment of airbags, or any other applications that could lead 
to death, personal injury, or severe property or environmental damage 
(individually and collectively, "Critical Applications"). Customer assumes the 
sole risk and liability of any use of Xilinx products in Critical Applications, 
subject only to applicable laws and regulations governing limitations on product 
liability. 

THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
ALL TIMES.

*******************************************************************************/


#include "fir.h"



ap_fixed<16,2> lms_sw(/*ap_fixed<16,2> *e,*/ ap_fixed<16,2> noise_in, ap_fixed<16,2> signal_noise)
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


int main()
{
	ap_fixed<16,2> input_sw;
	ap_fixed<16,2> input_hw;
	ap_fixed<16,2> output_hw;
	ap_fixed<16,2> output_sw;
	
	//Write the input values
	for(int i = 0; i < RUN_LENGTH; i++){
		input_sw = i;
		input_hw = i;
	}

	//Call to software model of fir
  	lms_sw(input_sw, output_sw);

	//Call to hardware model of fir
	lms_hw(input_hw, output_hw);

	for(int k=0; k < RUN_LENGTH; k++){
		int sw, hw;
		sw = output_sw;
		hw = output_hw;
		if(sw != hw){
			printf("ERROR: k = %d sw = %d hw = %d\n",k,sw,hw);
		      return 1;
		}
	}
	printf("Success! both SW and HW models match.\n");
	return 0;
}

