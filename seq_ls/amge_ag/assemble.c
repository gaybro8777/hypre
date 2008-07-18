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




/*****************************************************************************
 * element matrices stored in format:
 *  i_element_chord,
 *  j_element_chord,
 *  a_element_chord; 
 *
 * here, chord = (i_dof, j_dof) directed pair of indices
 *  for which A(i_dof, j_dof) \ne 0; A is the global assembled matrix;
 * 
 * i_chord_dof, j_chord_dof;
 *
 * builds (global) aseembled matrix:
 *        hypre_CSRMatrix A;
 ****************************************************************************/
#include "headers.h" 
int hypre_AMGeMatrixAssemble(hypre_CSRMatrix     **A_pointer,

			     int *i_element_chord,
			     int *j_element_chord,
			     double *a_element_chord,

			     int *i_chord_dof, 
			     int *j_chord_dof,

			     int num_elements, 
			     int num_chords,
			     int num_dofs)

{
  int ierr = 0;
  int i,j;

  hypre_CSRMatrix     *A;

  int *i_dof_dof, *j_dof_dof;
  int dof_counter, dof_dof_counter;
  
  int *i_chord_element, *j_chord_element;
  double *a_chord_element;
  double *chord_data;


  chord_data = hypre_CTAlloc(double, num_chords);

  for (i=0; i < num_chords; i++)
    chord_data[i] = 0.e0;

  for (i=0; i<num_elements; i++)
    for (j=i_element_chord[i]; j < i_element_chord[i+1]; j++)
      chord_data[j_element_chord[j]]+= a_element_chord[j];


  i_dof_dof = hypre_CTAlloc(int, num_dofs+1);
  j_dof_dof = hypre_CTAlloc(int, num_chords);

  dof_dof_counter = 0;
  dof_counter = -1;
  for (i=0; i < num_chords; i++)
    {
      if (j_chord_dof[i_chord_dof[i]] > dof_counter)
	{
	  dof_counter++;
	  i_dof_dof[dof_counter] = dof_dof_counter;
	}

      j_dof_dof[dof_dof_counter] = j_chord_dof[i_chord_dof[i]+1];
      dof_dof_counter++;
    }

  i_dof_dof[num_dofs] = dof_dof_counter;

  /*
  printf("assembled matrix: ============================================\n");
  for (i=0; i < num_dofs; i++)
    for (j=i_dof_dof[i]; j < i_dof_dof[i+1]; j++)
      printf("entry(%d,%d): %e\n", i, j_dof_dof[j], chord_data[j]);
	  
      */

  A = hypre_CSRMatrixCreate(num_dofs, num_dofs, 
			    i_dof_dof[num_dofs]);

  hypre_CSRMatrixData(A) = chord_data;
  hypre_CSRMatrixI(A) = i_dof_dof;
  hypre_CSRMatrixJ(A) = j_dof_dof;

  *A_pointer = A;

  return ierr;

}

