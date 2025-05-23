/* $Id: wingettimeofday.c,v 1.7 2023/04/23 10:46:42 nanard Exp $ */
/* libnatpmp
Copyright (c) 2007-2013, Thomas BERNARD
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
    * The name of the author may not be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#ifdef _WIN32
#if defined(_MSC_VER)

#else
#include <sys/time.h>
#endif

void __stdcall GetSystemTimeAsFileTime(FILETIME*);

int natpmp_gettimeofday(struct timeval* p, void* tz /* IGNORED */) {
  union {
   long long ns100; /*time since 1 Jan 1601 in 100ns units */
   FILETIME ft;
  } _now;

	if(!p)
		return -1;
  GetSystemTimeAsFileTime( &(_now.ft) );
  p->tv_usec =(long)((_now.ns100 / 10LL) % 1000000LL );
  p->tv_sec = (long)((_now.ns100-(116444736000000000LL))/10000000LL);
  return 0;
}
#endif

