/*BHEADER**********************************************************************
 * Copyright (c) 2007, Lawrence Livermore National Security, LLC.
 * Produced at the Lawrence Livermore National Laboratory.
 * Written by the HYPRE team. UCRL-CODE-222953.
 * All rights reserved.
 *
 * This file is part of HYPRE (see http://www.llnl.gov/CASC/hypre/).
 * Please see the COPYRIGHT_and_LICENSE file for the copyright notice, 
 * disclaimer, contact information and the GNU Lesser General Public License.
 *
 * HYPRE is free software; you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License (as published by the Free Software
 * Foundation) version 2.1 dated February 1999.
 *
 * HYPRE is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS 
 * FOR A PARTICULAR PURPOSE.  See the terms and conditions of the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * $Revision$
 ***********************************************************************EHEADER*/





/******************************************************************************
 *
 * HYPRE_SStructPCG interface
 *
 *****************************************************************************/

#include "headers.h"

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGCreate( MPI_Comm             comm,
                        HYPRE_SStructSolver *solver )
{
   hypre_PCGFunctions * pcg_functions =
      hypre_PCGFunctionsCreate(
         hypre_CAlloc, hypre_SStructKrylovFree, hypre_SStructKrylovCommInfo,
         hypre_SStructKrylovCreateVector,
         hypre_SStructKrylovDestroyVector, hypre_SStructKrylovMatvecCreate,
         hypre_SStructKrylovMatvec, hypre_SStructKrylovMatvecDestroy,
         hypre_SStructKrylovInnerProd, hypre_SStructKrylovCopyVector,
         hypre_SStructKrylovClearVector,
         hypre_SStructKrylovScaleVector, hypre_SStructKrylovAxpy,
         hypre_SStructKrylovIdentitySetup, hypre_SStructKrylovIdentity );

   *solver = ( (HYPRE_SStructSolver) hypre_PCGCreate( pcg_functions ) );

   return 0;
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int 
HYPRE_SStructPCGDestroy( HYPRE_SStructSolver solver )
{
   return( hypre_PCGDestroy( (void *) solver ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int 
HYPRE_SStructPCGSetup( HYPRE_SStructSolver solver,
                       HYPRE_SStructMatrix A,
                       HYPRE_SStructVector b,
                       HYPRE_SStructVector x )
{
   return( HYPRE_PCGSetup( (HYPRE_Solver) solver,
                           (HYPRE_Matrix) A,
                           (HYPRE_Vector) b,
                           (HYPRE_Vector) x ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int 
HYPRE_SStructPCGSolve( HYPRE_SStructSolver solver,
                       HYPRE_SStructMatrix A,
                       HYPRE_SStructVector b,
                       HYPRE_SStructVector x )
{
   return( HYPRE_PCGSolve( (HYPRE_Solver) solver,
                           (HYPRE_Matrix) A,
                           (HYPRE_Vector) b,
                           (HYPRE_Vector) x ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetTol( HYPRE_SStructSolver solver,
                        double              tol )
{
   return( HYPRE_PCGSetTol( (HYPRE_Solver) solver, tol ) );
}
/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetAbsoluteTol( HYPRE_SStructSolver solver,
                        double              tol )
{
   return( HYPRE_PCGSetAbsoluteTol( (HYPRE_Solver) solver, tol ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetMaxIter( HYPRE_SStructSolver solver,
                            int                 max_iter )
{
   return( HYPRE_PCGSetMaxIter( (HYPRE_Solver) solver, max_iter ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetTwoNorm( HYPRE_SStructSolver solver,
                            int                 two_norm )
{
   return( HYPRE_PCGSetTwoNorm( (HYPRE_Solver) solver, two_norm ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetRelChange( HYPRE_SStructSolver solver,
                              int                 rel_change )
{
   return( HYPRE_PCGSetRelChange( (HYPRE_Solver) solver, rel_change ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetPrecond( HYPRE_SStructSolver          solver,
                            HYPRE_PtrToSStructSolverFcn  precond,
                            HYPRE_PtrToSStructSolverFcn  precond_setup,
                            void                        *precond_data )
{
   return( HYPRE_PCGSetPrecond( (HYPRE_Solver) solver,
                                (HYPRE_PtrToSolverFcn) precond,
                                (HYPRE_PtrToSolverFcn) precond_setup,
                                (HYPRE_Solver) precond_data ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetLogging( HYPRE_SStructSolver solver,
                            int                 logging )
{
   return( HYPRE_PCGSetLogging( (HYPRE_Solver) solver, logging ) );
}


/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGSetPrintLevel( HYPRE_SStructSolver solver,
                            int                 level )
{
   return( HYPRE_PCGSetPrintLevel( (HYPRE_Solver) solver, level ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGGetNumIterations( HYPRE_SStructSolver  solver,
                                  int                 *num_iterations )
{
   return( HYPRE_PCGGetNumIterations( (HYPRE_Solver) solver, num_iterations ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGGetFinalRelativeResidualNorm( HYPRE_SStructSolver  solver,
                                              double              *norm )
{
   return( HYPRE_PCGGetFinalRelativeResidualNorm( (HYPRE_Solver) solver, norm ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/

int
HYPRE_SStructPCGGetResidual( HYPRE_SStructSolver  solver,
                              void              **residual )
{
   return( HYPRE_PCGGetResidual( (HYPRE_Solver) solver, residual ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/
int
HYPRE_SStructDiagScaleSetup( HYPRE_SStructSolver solver,
                             HYPRE_SStructMatrix A,
                             HYPRE_SStructVector y,
                             HYPRE_SStructVector x      )
{
  
   return( HYPRE_StructDiagScaleSetup( (HYPRE_StructSolver) solver,
                                       (HYPRE_StructMatrix) A,
                                       (HYPRE_StructVector) y,
                                       (HYPRE_StructVector) x ) );
}

/*--------------------------------------------------------------------------
 *--------------------------------------------------------------------------*/
int
HYPRE_SStructDiagScale( HYPRE_SStructSolver solver,
                        HYPRE_SStructMatrix A,
                        HYPRE_SStructVector y,
                        HYPRE_SStructVector x      )
{
   int ierr = 0;

   int                      nparts= hypre_SStructMatrixNParts(A);

   hypre_SStructPMatrix    *pA;
   hypre_SStructPVector    *px;
   hypre_SStructPVector    *py;
   hypre_StructMatrix      *sA;
   hypre_StructVector      *sx;
   hypre_StructVector      *sy;

   int part, vi;
   int nvars;

   for (part = 0; part < nparts; part++)
   {
      pA = hypre_SStructMatrixPMatrix(A, part);
      px = hypre_SStructVectorPVector(x, part);
      py = hypre_SStructVectorPVector(y, part);
      nvars= hypre_SStructPMatrixNVars(pA);
      for (vi = 0; vi < nvars; vi++)
      {
         sA = hypre_SStructPMatrixSMatrix(pA, vi, vi);
         sx = hypre_SStructPVectorSVector(px, vi);
         sy = hypre_SStructPVectorSVector(py, vi);
         
         HYPRE_StructDiagScale( (HYPRE_StructSolver) solver,
                                (HYPRE_StructMatrix) sA,
                                (HYPRE_StructVector) sy,
                                (HYPRE_StructVector) sx );
      }
   }

   return ierr;
}



