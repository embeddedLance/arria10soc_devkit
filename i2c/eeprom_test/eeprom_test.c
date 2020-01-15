/***************************************************************************
    copyright            : (C) by 2003-2004 Stefano Barbato
    email                : stefano@codesink.org
    
    Copyright (C) 2011 by Kris Rusocki <kszysiu@gmail.com>
    - usage/strings cleanup
    - misc cleanup: use "static" keyword where appropriate
    - misc cleanup: have confirm_action() return void
    - support custom input and output files
    - support user-defined write cycle time
    - ensure that stdin is a terminal when operating w/o -f
    - do not allow reading data from a terminal w/o -f
    - perform complete input validation before taking action
    - use dedicated exit code when opening I2C device fails

    $Id: eeprog.c,v 1.28 2004/02/29 11:06:41 tat Exp $
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <stdio.h>
#include <fcntl.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "24cXX.h"

#define VERSION 			"0.7.6-tear12"

#define ENV_DEV				"/dev/i2c-0"
#define ENV_I2C_ADDR		0x70
#define WRITE_CYCLE_TIME 	5

static int g_quiet;


static void do_die_if(int b, char* msg, int line, int exitcode)
{
	if(!b)
		return;
	fprintf(stderr, "Error at line %d: %s\n", line, msg);
	//fprintf(stderr, "	sysmsg: %s\n", strerror(errno));
	exit(exitcode);
}

#define die_if(a, msg) die_if3(a, msg, 1)
#define die_if3(a, msg, code) do { do_die_if( a , msg, __LINE__, code); } while(0)



int main(int argc, char** argv)
{
	char ch = '0';
	struct eeprom e;
	int i2c_addr, write_cycle_time;

	char *device;
	int eeprom_type = 0;

	device  = ENV_DEV;
	i2c_addr = ENV_I2C_ADDR;
	write_cycle_time = WRITE_CYCLE_TIME;
	eeprom_type = EEPROM_TYPE_8BIT_ADDR; // default

	die_if3(eeprom_open(device, i2c_addr, eeprom_type, write_cycle_time, &e) < 0, 
			"unable to open eeprom device file "
			"(check that the file exists and that it's readable)",
			2);

	printf("Writing to the EEPROM: %c\n", 'h');
	die_if(eeprom_write_byte(&e, 3, 'h'), "write error");
	die_if((ch = eeprom_read_byte(&e, 3)) < 0, "read error");
	printf("Reading from the EEPROM: %c\n", ch);

	eeprom_close(&e);

	return 0;
}
