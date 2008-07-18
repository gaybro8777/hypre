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
 * ConjGrad.h header file.
 *
 *****************************************************************************/

#ifndef _CONJGRAD_H
#define _CONJGRAD_H

void PCG_ParaSails(Matrix *mat, ParaSails *ps, double *b, double *x,
   double tol, int max_iter);
void FGMRES_ParaSails(Matrix *mat, ParaSails *ps, double *b, double *x,
   int dim, double tol, int max_iter);

#endif /* _CONJGRAD_H */
