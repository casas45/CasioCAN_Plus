/**
 * @file display.h
 * 
 * @brief Header file for display functionalities.
*/
#ifndef DISPLAY_H__
#define DISPLAY_H__

#include "hel_lcd.h"

#define UPSET_ASCII_NUM         48u     /*!< Value to convert a number to it's ascii value */
#define MONTH_N_CHARACTERS      4u      /*!< Number of characters in months array */
#define N_MONTHS                12u     /*!< Number of months */
#define WDAY_N_CHARACTERS       2u      /*!< Number of characters in wday array */
#define N_WDAYS                 7u      /*!< Number of week days */
#define LCD_CHARACTERS          16u     /*!< Number of characters in a line of the LCD */
#define OFFSET_ARRAY            1u      /*!< Offset to get the correct value of wday or months array */
#define TWO_THOUSANDS           2000u   /*!< 2000 years to add to the year that will be in the LCD */

void Display_InitTask( void );

#endif