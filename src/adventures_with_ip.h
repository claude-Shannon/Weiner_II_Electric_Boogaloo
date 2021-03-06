/*
 * adventures_with_ip.h
 *
 * Main header file.
 */

#ifndef ADVENTURES_WITH_IP_H_
#define ADVENTURES_WITH_IP_H_

/* ---------------------------------------------------------------------------- *
 * 								Header Files									*
 * ---------------------------------------------------------------------------- */
#include <stdio.h>
#include <xil_io.h>
#include <sleep.h>
#include "xiicps.h"
#include <xil_printf.h>
#include <xparameters.h>
#include "xgpio.h"
#include "xuartps.h"
#include "stdlib.h"

/* ---------------------------------------------------------------------------- *
 * 							Custom IP Header Files								*
 * ---------------------------------------------------------------------------- */


#include "audio.h"
#include "xnco_baby.h" //new shit
#include "xnco_mom.h" //also new shit
#include "xlms_hw.h" //also also new shit

/* ---------------------------------------------------------------------------- *
 * 							Prototype Functions									*
 * ---------------------------------------------------------------------------- */
void menu();
void mom_beat();
void baby_beat();
void both_beat();
void filter();
unsigned char gpio_init();
void lms_init(void *InstancePtr);
void mom_init(void *InstancePtr);
void baby_init(void *InstancePtr);


/* ---------------------------------------------------------------------------- *
 * 						Redefinitions from xparameters.h 						*
 * ---------------------------------------------------------------------------- */
//#define NCO_ID XPAR_NCO_0_DEVICE_ID

//shorten ID for MOM_NCO
#define MOM_ID XPAR_NCO_MOM_0_DEVICE_ID
//Shorten ID for baby_nco
#define BABY_ID XPAR_NCO_BABY_0_DEVICE_ID

//LMS ID shorten

#define LMS_ID XPAR_LMS_HW_0_DEVICE_ID

// dont need this stuff as our LMS block is now AXI lite just like the old NCO

//#define LMS_LOC XPAR_LMS_PCORE_0_BASEADDR
//#define LMS_X LMS_LOC + x_k__Data_lms_pcore
//#define LMS_D LMS_LOC + d_k__Data_lms_pcore
//#define LMS_E LMS_LOC + e_k__Data_lms_pcore
//#define LMS_STROBE LMS_LOC + IPCore_Strobe_lms_pcore

//UART shorten
#define UART_BASEADDR XPAR_PS7_UART_1_BASEADDR

//#define BUTTON_SWITCH_BASE XPAR_GPIO_1_BASEADDR
//#define LED_BASE XPAR_LED_CONTROLLER_0_S00_AXI_BASEADDR
//#define BUTTON_SWITCH_ID XPAR_GPIO_1_DEVICE_ID

//digital mute ID
#define AUDIO_ENABLE_ID XPAR_AXI_GPIO_0_DEVICE_ID

/* ---------------------------------------------------------------------------- *
 * 							Define GPIO Channels								*
 * ---------------------------------------------------------------------------- */
//#define BUTTON_CHANNEL 1
//#define SWITCH_CHANNEL 2

/* ---------------------------------------------------------------------------- *
 * 							Audio Scaling Factor								*
 * ---------------------------------------------------------------------------- */
#define SCALE 7

/* ---------------------------------------------------------------------------- *
 * 							Global Variables									*
 * ---------------------------------------------------------------------------- */
XIicPs Iic;
//XGpio Gpio; // Gpio instance for buttons and switches
XGpio Gpio_audio_enable; // GPIO instance for digital mute
XNco_baby baby;
XNco_mom mom;
XLms_hw lms;


#endif /* ADVENTURES_WITH_IP_H_ */
