/*  lms.c - LMS adaptive Wiener filter  */
#include "ap_fixed.h"
#include "ap_shift_reg.h"


#define MAX 16

static ap_shift_reg<ap_fixed<16,2>, MAX> h;
ap_fixed<16,2> mu = .125;
ap_fixed<16,2> xhat = 0;
static ap_shift_reg<ap.fixed<16,2>, MAX> y; //noise input shift register guy


/*double lms(/* filter length M */, /* this is the filter array ( in the function now)*/ h[] , x /* input with noise */, y /* input just noise */, /*xhat, e, mu, init*/)
double /*h[]*/, x, y,/* *xhat */, /* return this e value as output*e, /*mu*/;
int M, *init;
*?
/
lms(ap_fixed<16,2> *e, ap_fixed<16,2> noise_in, ap_fixed<16,2> signal_noise)
{

// output is e, for some reason they use the output as a pointer... *e, or they are passing a pointer to be edited basically
//input is y, 
/*
double mu = ????;
double xhat;
*/

/*

       int p;
       static double w[MAX+1];

       if (*init == 0) {
              for (p=1; p<=M; p++) {
                     w[p] = 0;
                     h[p] = 0;
                     }
              h[0] = 0;
              *init = 1;
              }

       w[0] = y;
*/


int p =0;



       for (*xhat=0, p=0; p<=M; p++)
              *xhat += h[p] * w[p];

       *e = x - *xhat;

       for (p=0; p<=M; p++)
              h[p] += 2 * mu * *e * w[p];

       for (p=M; p>=1; p--)
              w[p] = w[p-1];
}

