/*
 * byteorder.h
 * Handling of endian byte orders
 * Copyright (C) 2005 Christopher Han
 */
#ifndef BYTEORDER_H
#define BYTEORDER_H

/*
 * The swabbing stuff looks backwards, but the files
 * are _originally_ little endian (win32 x86).
 * So in this case little endian is the standard while
 * big endian is the exception.
 */

#if defined(__linux__)
#include <byteswap.h>

#if __BYTE_ORDER == __BIG_ENDIAN
#define swabword(w)	(bswap_16(w))
#define swabdword(w)	(bswap_32(w))
/* 
   My brother tells me that a C compiler must store floats in memory
   by a particular standard, except for the endianness; hence, this
   will work on all C compilers. 
 */
static inline float swabfloat(float w) {
	char octets[4];
	char ret_octets[4];
	float ret;

	memcpy(octets, &w, 4);

	ret_octets[0] = octets[3];
	ret_octets[1] = octets[2];
	ret_octets[2] = octets[1];
	ret_octets[3] = octets[0];

	memcpy(&ret, ret_octets, 4);

	return ret;
}
#else
#define swabword(w)	(w)
#define swabdword(w)	(w)
#define swabfloat(w)	(w)
#endif

#elif defined(__FreeBSD__)

#include <sys/endian.h>

#define swabword(w)	(htole16(w))
#define swabdword(w)	(htole32(w))
static inline float swabfloat(float w) {
	/* compile time assertion to validate sizeof(long) == sizeof(float) */
	typedef sizeof_long_equals_sizeof_float[sizeof(long) == sizeof(float) ? 1 : -1];
	return swabdword(*(long*)&w);
}

#else

// empty versions for win32
#define swabword(w)	(w)
#define swabdword(w)	(w)
#define swabfloat(w)	(w)

#endif


#endif
