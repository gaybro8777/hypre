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
 * Header info for the hypre_DistributedMatrix structures
 *
 *****************************************************************************/

#ifndef HYPRE_PETSC_MAT_SOLVER_PILUT_SOLVER_TYPES_HEADER
#define HYPRE_PETSC_MAT_SOLVER_PILUT_SOLVER_TYPES_HEADER

typedef void *HYPRE_PETScMatPilutSolver;

/* Have to include PETSc since PETSc types appear in prototypes */
#include "sles.h"

#endif
