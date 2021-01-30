/*
 * File:   average_calculations.c
 * Author: Ahmed GEE
 *
 * Created on August 21, 2020, 2:04 PM
 */


#include <xc.h>
#include "average_calculations.h"


short get_averageX(short Data)
{
    static short OutPut = 0;
    OutPut = (short)((92 * (long)Data + 8 * (long)OutPut)/100);
    return OutPut;
}
short get_averageY(short Data)
{
    static short OutPut = 0;
    OutPut = (short)((92 * (long)Data + 8 * (long)OutPut)/100);
    return OutPut;
}
short get_averageZ(short Data)
{
    static short OutPut = 0;
    OutPut = (short)((92 * (long)Data + 8 * (long)OutPut)/100);
    return OutPut;
}

short get_average(short Data)
{
    static short OutPut = 0;
    OutPut = (short)((92 * (long)Data + 8 * (long)OutPut)/100);
    return OutPut;
}