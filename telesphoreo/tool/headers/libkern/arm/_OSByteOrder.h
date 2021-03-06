/*
 * Copyright (c) 2006 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _OS__OSBYTEORDERI386_H
#define _OS__OSBYTEORDERI386_H

#if !defined(__DARWIN_OS_INLINE)
# if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#        define __DARWIN_OS_INLINE static inline
# elif defined(__MWERKS__) || defined(__cplusplus)
#        define __DARWIN_OS_INLINE static inline
# else
#        define __DARWIN_OS_INLINE static __inline__
# endif
#endif

/* Generic byte swapping functions. */

__DARWIN_OS_INLINE
__uint16_t
_OSSwapInt16(
    __uint16_t        _data
)
{
    return ((_data << 8) | (_data >> 8));
}

__DARWIN_OS_INLINE
__uint32_t
_OSSwapInt32(
    __uint32_t        _data
)
{
     uint32_t   tmp = _data;
     __asm volatile ("EOR   %1, %0, %0, ROR #16\n"
                   "BIC   %1, %1, #0xff0000\n"
                   "MOV   %0, %0, ROR #8\n"
                   "EOR   %0, %0, %1, LSR #8\n"
                   : "=r" (_data), "=r" (tmp)
                   : "0" (_data), "1" (tmp));

     return _data;
}

__DARWIN_OS_INLINE
__uint64_t
_OSSwapInt64(
    __uint64_t        _data
)
{
    return (__uint64_t) _OSSwapInt32(_data & 0xffffffff) << 32 | _OSSwapInt32(_data >> 32 & 0xffffff);
}

#endif /* ! _OS__OSBYTEORDERI386_H */
