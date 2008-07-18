/*BHEADER**********************************************************************
 * Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * This file is part of HYPRE.  See file COPYRIGHT for details.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License (as published by the Free
 * Software Foundation) version 2.1 dated February 1999.
 *
 * $Revision$
 ***********************************************************************EHEADER*/





/******************************************************************************
 *
 * General structures and values
 *
 *****************************************************************************/

#ifndef HYPRE_GENERAL_HEADER
#define HYPRE_GENERAL_HEADER


/*--------------------------------------------------------------------------
 * Define various flags
 *--------------------------------------------------------------------------*/

#ifndef NULL
#define NULL 0
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif


/*--------------------------------------------------------------------------
 * Define max and min functions
 *--------------------------------------------------------------------------*/

#ifndef max
#define max(a,b)  (((a)<(b)) ? (b) : (a))
#endif
#ifndef min
#define min(a,b)  (((a)<(b)) ? (a) : (b))
#endif

#ifndef round
#define round(x)  ( ((x) < 0.0) ? ((int)(x - 0.5)) : ((int)(x + 0.5)) )
#endif


/*--------------------------------------------------------------------------
 * Define memory allocation routines
 *--------------------------------------------------------------------------*/

#define hypre_TAlloc(type, count) \
((count) ? (type *) malloc((unsigned int)(sizeof(type) * (count))) : NULL)

#define hypre_CTAlloc(type, count) \
((count) ? (type *) calloc((unsigned int)(count), (unsigned int)sizeof(type)) : NULL)

/* note: the `else' is required to guarantee termination of the `if' */
#define hypre_TFree(ptr) if (ptr) free(ptr); else


#endif

