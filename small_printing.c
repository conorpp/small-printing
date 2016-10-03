/*
 * Copyright (c) 2016, Conor Patrick
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the FreeBSD Project.
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

#include "small_printing.h"


// Painfully lightweight printing routines
void putf(char c)
{
    fputc(c,stderr);
}


void dump_hex(uint8_t* hex, uint8_t len)
{
	uint8_t i;
	for (i=0 ; i < len ; i++)
	{
		if (hex[i]<0x10)
		{
			putf('0');
		}
		s_putb(hex[i]);
	}
	s_prints("\r\n");
}


void s_prints(const char* d)
{
	while(*d)
	{
		putf(*d++);
	}
}

static void int2str_reduce_n(char ** snum, uint32_t copy, uint8_t n)
{
    do
    {
        copy /= n;
    }while(copy);
}


static const char * __digits = "0123456789abcdef";
static char __int2str_buf[9];

static void int2str_map_n(char ** snum, uint32_t i, uint8_t n)
{
    do
    {
        *--*snum = __digits[i % n];
        i /= n;
    }while(i);
}

#define dint2str(i)     __int2strn(i,10)
#define xint2str(i)     __int2strn(i,16)

char * __int2strn(int32_t i, uint8_t n)
{
    char * snum = __int2str_buf;
    if (i<0) *snum++ = '-';
    int2str_reduce_n(&snum, i, n);
    *snum = '\0';
    int2str_map_n(&snum, i, n);
    return snum;
}

void s_putd(uint32_t i)
{
	s_prints(dint2str((int32_t)i));
}

void s_putx(uint32_t i)
{
	s_prints(xint2str(i));
}

static void put_space()
{
	s_prints(" ");
}
static void put_line()
{
	s_prints("\r\n");
}

void s_printd(const char * tag, uint8_t c, ...)
{
	va_list args;
	s_prints(tag);
    va_start(args,c);
    while(c--)
    {
        s_putd((int32_t)va_arg(args, int32_t));

    }
    put_line();
    va_end(args);
}

void s_printl(const char * tag, uint8_t c, ...)
{
    va_list args;
    s_prints(tag);
    va_start(args,c);
    while(c--)
    {
        s_putl(va_arg(args, int32_t));
        s_prints(" ");
    }
    put_line();
    va_end(args);
}

void s_printx(const char * tag, uint8_t c, ...)
{
    va_list args;
    s_prints(tag);
    va_start(args,c);
    while(c--)
    {
        s_putx((int32_t)va_arg(args, uint32_t));
        s_prints(" ");
    }
    put_line();
    va_end(args);
}

void s_printb(const char * tag, uint8_t c, ...)
{
	va_list args;
    s_prints(tag);
    va_start(args,c);
    while(c--)
    {
        s_putb(va_arg(args, uint32_t));
        put_space();
    }
    put_line();
    va_end(args);
}

void s_printlx(const char * tag, uint8_t c, ...)
{
    va_list args;
    s_prints(tag);
    va_start(args,c);
    while(c--)
    {
        s_putlx(va_arg(args, int32_t));
        put_space();
    }
    put_line();
    va_end(args);
}



