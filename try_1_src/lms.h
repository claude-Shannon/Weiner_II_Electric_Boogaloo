
#include <stdio.h>
#include <stdlib.h>
#include <hls_stream.h>
#include "ap_fixed.h"
#include "ap_shift_reg.h"

#define MAX 32

#define RUN_LENGTH 100


void lms_hw (ap_fixed<16,2> noise_in, ap_fixed<16,2> signal_noise,ap_fixed<16,2>  *output);
