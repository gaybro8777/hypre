/******************************************************************************
 * Copyright 1998-2019 Lawrence Livermore National Security, LLC and other
 * HYPRE Project Developers. See the top-level COPYRIGHT file for details.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR MIT)
 ******************************************************************************/

#include "_hypre_parcsr_ls.h"
#include "_hypre_utilities.hpp"

#if defined(HYPRE_USING_CUDA) || defined(HYPRE_USING_HIP)

__global__ void hypre_BoomerAMGBuildDirInterp_getnnz( HYPRE_Int nr_of_rows, HYPRE_Int *S_diag_i, HYPRE_Int *S_diag_j, HYPRE_Int *S_offd_i, HYPRE_Int *S_offd_j, HYPRE_Int *CF_marker, HYPRE_Int *CF_marker_offd, HYPRE_Int num_functions, HYPRE_Int *dof_func, HYPRE_Int *dof_func_offd, HYPRE_Int *P_diag_i, HYPRE_Int *P_offd_i);

__global__ void hypre_BoomerAMGBuildDirInterp_getcoef( HYPRE_Int nr_of_rows, HYPRE_Int *A_diag_i, HYPRE_Int *A_diag_j, HYPRE_Real *A_diag_data, HYPRE_Int *A_offd_i, HYPRE_Int *A_offd_j, HYPRE_Real *A_offd_data, HYPRE_Int *Soc_diag_j, HYPRE_Int *Soc_offd_j, HYPRE_Int *CF_marker, HYPRE_Int *CF_marker_offd, HYPRE_Int num_functions, HYPRE_Int *dof_func, HYPRE_Int *dof_func_offd, HYPRE_Int *P_diag_i, HYPRE_Int *P_diag_j, HYPRE_Real *P_diag_data, HYPRE_Int *P_offd_i, HYPRE_Int *P_offd_j, HYPRE_Real *P_offd_data, HYPRE_Int *fine_to_coarse );

__global__ void hypre_BoomerAMGBuildDirInterp_getcoef_v2( HYPRE_Int nr_of_rows, HYPRE_Int *A_diag_i, HYPRE_Int *A_diag_j, HYPRE_Real *A_diag_data, HYPRE_Int *A_offd_i, HYPRE_Int *A_offd_j, HYPRE_Real *A_offd_data, HYPRE_Int *Soc_diag_j, HYPRE_Int *Soc_offd_j, HYPRE_Int *CF_marker, HYPRE_Int *CF_marker_offd, HYPRE_Int num_functions, HYPRE_Int *dof_func, HYPRE_Int *dof_func_offd, HYPRE_Int *P_diag_i, HYPRE_Int *P_diag_j, HYPRE_Real *P_diag_data, HYPRE_Int *P_offd_i, HYPRE_Int *P_offd_j, HYPRE_Real *P_offd_data, HYPRE_Int *fine_to_coarse );

/*---------------------------------------------------------------------------
 * hypre_BoomerAMGBuildDirInterp
 *--------------------------------------------------------------------------*/

HYPRE_Int
hypre_BoomerAMGBuildDirInterpDevice( hypre_ParCSRMatrix   *A,
                                     HYPRE_Int            *CF_marker,
                                     hypre_ParCSRMatrix   *S,
                                     HYPRE_BigInt         *num_cpts_global,
                                     HYPRE_Int             num_functions,
                                     HYPRE_Int            *dof_func,
                                     HYPRE_Int             debug_flag,
                                     HYPRE_Real            trunc_factor,
                                     HYPRE_Int             max_elmts,
                                     HYPRE_Int             interp_type,
                                     hypre_ParCSRMatrix  **P_ptr)
{
   MPI_Comm                comm     = hypre_ParCSRMatrixComm(A);
   hypre_ParCSRCommPkg    *comm_pkg = hypre_ParCSRMatrixCommPkg(A);
   hypre_ParCSRCommHandle *comm_handle;

   hypre_CSRMatrix *A_diag      = hypre_ParCSRMatrixDiag(A);
   HYPRE_Real      *A_diag_data = hypre_CSRMatrixData(A_diag);
   HYPRE_Int       *A_diag_i    = hypre_CSRMatrixI(A_diag);
   HYPRE_Int       *A_diag_j    = hypre_CSRMatrixJ(A_diag);

   hypre_CSRMatrix *A_offd      = hypre_ParCSRMatrixOffd(A);
   HYPRE_Real      *A_offd_data = hypre_CSRMatrixData(A_offd);
   HYPRE_Int       *A_offd_i    = hypre_CSRMatrixI(A_offd);
   HYPRE_Int       *A_offd_j    = hypre_CSRMatrixJ(A_offd);
   HYPRE_Int        num_cols_A_offd = hypre_CSRMatrixNumCols(A_offd);
   //   HYPRE_BigInt   *col_map_offd_A = hypre_ParCSRMatrixColMapOffd(A);

   HYPRE_Int        n_fine = hypre_CSRMatrixNumRows(A_diag);

   hypre_CSRMatrix *S_diag   = hypre_ParCSRMatrixDiag(S);
   HYPRE_Int       *S_diag_i = hypre_CSRMatrixI(S_diag);
   HYPRE_Int       *S_diag_j = hypre_CSRMatrixJ(S_diag);

   hypre_CSRMatrix *S_offd   = hypre_ParCSRMatrixOffd(S);
   HYPRE_Int       *S_offd_i = hypre_CSRMatrixI(S_offd);
   HYPRE_Int       *S_offd_j = hypre_CSRMatrixJ(S_offd);

   hypre_ParCSRMatrix *P;
   HYPRE_Int          *tmp_map_offd_h = NULL;

   HYPRE_Int       *CF_marker_dev = NULL;
   HYPRE_Int       *CF_marker_offd = NULL;
   HYPRE_Int       *dof_func_offd = NULL;
   HYPRE_Int       *dof_func_dev = NULL;

   hypre_CSRMatrix *P_diag;
   hypre_CSRMatrix *P_offd;
   HYPRE_Real      *P_diag_data;
   HYPRE_Int       *P_diag_i;
   HYPRE_Int       *P_diag_j;
   HYPRE_Real      *P_offd_data;
   HYPRE_Int       *P_offd_i;
   HYPRE_Int       *P_offd_j;
   HYPRE_Int        P_diag_size, P_offd_size;

   HYPRE_Int       *fine_to_coarse_d;
   HYPRE_Int       *fine_to_coarse_h;
   HYPRE_BigInt     total_global_cpts;
   HYPRE_Int        num_cols_P_offd = 0;

   HYPRE_Int        i;
   HYPRE_Int        j;
   HYPRE_Int        start;
   HYPRE_Int        my_id;
   HYPRE_Int        num_procs;
   HYPRE_Int        num_sends;
   HYPRE_Int        index;
   HYPRE_Int       *int_buf_data;

   HYPRE_Real       wall_time;  /* for debugging instrumentation  */

   HYPRE_MemoryLocation memory_location = hypre_ParCSRMatrixMemoryLocation(A);

   hypre_MPI_Comm_size(comm, &num_procs);
   hypre_MPI_Comm_rank(comm,&my_id);

   if (my_id == (num_procs -1))
   {
      total_global_cpts = num_cpts_global[1];
   }
   hypre_MPI_Bcast( &total_global_cpts, 1, HYPRE_MPI_BIG_INT, num_procs-1, comm);

   if (!comm_pkg)
   {
      hypre_MatvecCommPkgCreate(A);
      comm_pkg = hypre_ParCSRMatrixCommPkg(A);
   }
   if (debug_flag == 4)
   {
      wall_time = time_getWallclockSeconds();
   }

   ///* 0. Assume CF_marker has been allocated in device memory */
   //   CF_marker_host = hypre_CTAlloc(HYPRE_Int,  n_fine, HYPRE_MEMORY_HOST);
   //   hypre_TMemcpy( CF_marker_host, CF_marker, HYPRE_Int, n_fine, HYPRE_MEMORY_HOST, HYPRE_MEMORY_DEVICE );
   /* 0. Assume CF_marker has been allocated in host memory */
   //   CF_marker_host = CF_marker;
   CF_marker_dev = hypre_TAlloc(HYPRE_Int,  n_fine, HYPRE_MEMORY_DEVICE);
   hypre_TMemcpy( CF_marker_dev, CF_marker, HYPRE_Int, n_fine, HYPRE_MEMORY_DEVICE, HYPRE_MEMORY_HOST );

   /* 1. Communicate CF_marker to/from other processors */
   if (num_cols_A_offd)
   {
      CF_marker_offd = hypre_TAlloc(HYPRE_Int, num_cols_A_offd, HYPRE_MEMORY_DEVICE);
   }

   num_sends = hypre_ParCSRCommPkgNumSends(comm_pkg);
   int_buf_data = hypre_TAlloc(HYPRE_Int, hypre_ParCSRCommPkgSendMapStart(comm_pkg, num_sends), HYPRE_MEMORY_HOST);
   index = 0;
   for (i = 0; i < num_sends; i++)
   {
      start = hypre_ParCSRCommPkgSendMapStart(comm_pkg, i);
      for (j = start; j < hypre_ParCSRCommPkgSendMapStart(comm_pkg, i+1); j++)
      {
         int_buf_data[index++] = CF_marker[hypre_ParCSRCommPkgSendMapElmt(comm_pkg,j)];
      }
   }

   comm_handle = hypre_ParCSRCommHandleCreate_v2(11, comm_pkg, HYPRE_MEMORY_HOST, int_buf_data,
                                                 HYPRE_MEMORY_DEVICE, CF_marker_offd);
   hypre_ParCSRCommHandleDestroy(comm_handle);

   if (num_functions > 1)
   {
      /* 2. Communicate dof_func to/from other processors */
      if (num_cols_A_offd > 0)
      {
         dof_func_offd = hypre_TAlloc(HYPRE_Int, num_cols_A_offd, HYPRE_MEMORY_DEVICE);
      }

      index = 0;
      for (i = 0; i < num_sends; i++)
      {
         start = hypre_ParCSRCommPkgSendMapStart(comm_pkg, i);
         for (j=start; j < hypre_ParCSRCommPkgSendMapStart(comm_pkg, i+1); j++)
         {
            int_buf_data[index++] = dof_func[hypre_ParCSRCommPkgSendMapElmt(comm_pkg,j)];
         }
      }
      comm_handle = hypre_ParCSRCommHandleCreate_v2(11, comm_pkg, HYPRE_MEMORY_HOST, int_buf_data,
                                                    HYPRE_MEMORY_DEVICE, dof_func_offd);
      hypre_ParCSRCommHandleDestroy(comm_handle);

      dof_func_dev = hypre_TAlloc(HYPRE_Int, n_fine, HYPRE_MEMORY_DEVICE);
      hypre_TMemcpy(dof_func_dev, dof_func, HYPRE_Int, n_fine, HYPRE_MEMORY_DEVICE, HYPRE_MEMORY_HOST);
   }

   if (debug_flag == 4)
   {
      wall_time = time_getWallclockSeconds() - wall_time;
      hypre_printf("Proc = %d     Interp: Comm 1 CF_marker =    %f\n", my_id, wall_time);
      fflush(NULL);
   }

   /* 3. Figure out the size of the interpolation matrix, P, i.e., compute P_diag_i and P_offd_i */
   /*    Also, compute fine_to_coarse array: When i is a coarse point, fine_to_coarse[i] will hold a  */
   /*    corresponding coarse point index in the range 0..n_coarse-1 */
   P_diag_i = hypre_TAlloc(HYPRE_Int, n_fine+1, memory_location);
   P_offd_i = hypre_TAlloc(HYPRE_Int, n_fine+1, memory_location);

   dim3 bDim = hypre_GetDefaultCUDABlockDimension();
   dim3 gDim = hypre_GetDefaultCUDAGridDimension(n_fine, "warp", bDim);

   HYPRE_CUDA_LAUNCH( hypre_BoomerAMGBuildDirInterp_getnnz, gDim, bDim,
                      n_fine, S_diag_i, S_diag_j, S_offd_i, S_offd_j,
                      CF_marker_dev, CF_marker_offd, num_functions,
                      dof_func_dev, dof_func_offd, P_diag_i, P_offd_i);

   /* The scans will transform P_diag_i and P_offd_i to the CSR I-vectors */
   hypreDevice_IntegerExclusiveScan(n_fine+1, P_diag_i);
   hypreDevice_IntegerExclusiveScan(n_fine+1, P_offd_i);

   fine_to_coarse_d = hypre_TAlloc(HYPRE_Int, n_fine, HYPRE_MEMORY_DEVICE);
   /* The scan will make fine_to_coarse[i] for i a coarse point hold a
    * coarse point index in the range from 0 to n_coarse-1 */
   HYPRE_THRUST_CALL( exclusive_scan,
                      thrust::make_transform_iterator(CF_marker_dev,          is_nonnegative<HYPRE_Int>()),
                      thrust::make_transform_iterator(CF_marker_dev + n_fine, is_nonnegative<HYPRE_Int>()),
                      fine_to_coarse_d,
                      HYPRE_Int(0) ); /* *MUST* pass init value since input and output types diff. */

   /* 4. Compute the CSR arrays P_diag_j, P_diag_data, P_offd_j, and P_offd_data */
   /*    P_diag_i and P_offd_i are now known, first allocate the remaining CSR arrays of P */
   hypre_TMemcpy(&P_diag_size, &P_diag_i[n_fine], HYPRE_Int, 1, HYPRE_MEMORY_HOST, memory_location);
   hypre_TMemcpy(&P_offd_size, &P_offd_i[n_fine], HYPRE_Int, 1, HYPRE_MEMORY_HOST, memory_location);

   P_diag_j    = hypre_TAlloc(HYPRE_Int,  P_diag_size, memory_location);
   P_diag_data = hypre_TAlloc(HYPRE_Real, P_diag_size, memory_location);

   P_offd_j    = hypre_TAlloc(HYPRE_Int,  P_offd_size, memory_location);
   P_offd_data = hypre_TAlloc(HYPRE_Real, P_offd_size, memory_location);

   if (interp_type == 3)
   {
      HYPRE_CUDA_LAUNCH( hypre_BoomerAMGBuildDirInterp_getcoef, gDim, bDim,
                         n_fine, A_diag_i, A_diag_j, A_diag_data,
                         A_offd_i, A_offd_j, A_offd_data,
                         hypre_ParCSRMatrixSocDiagJ(S),
                         hypre_ParCSRMatrixSocOffdJ(S),
                         CF_marker_dev, CF_marker_offd,
                         num_functions, dof_func_dev, dof_func_offd,
                         P_diag_i, P_diag_j, P_diag_data,
                         P_offd_i, P_offd_j, P_offd_data,
                         fine_to_coarse_d );
   }
   else
   {
      HYPRE_CUDA_LAUNCH( hypre_BoomerAMGBuildDirInterp_getcoef_v2, gDim, bDim,
                         n_fine, A_diag_i, A_diag_j, A_diag_data,
                         A_offd_i, A_offd_j, A_offd_data,
                         hypre_ParCSRMatrixSocDiagJ(S),
                         hypre_ParCSRMatrixSocOffdJ(S),
                         CF_marker_dev, CF_marker_offd,
                         num_functions, dof_func_dev, dof_func_offd,
                         P_diag_i, P_diag_j, P_diag_data,
                         P_offd_i, P_offd_j, P_offd_data,
                         fine_to_coarse_d );
   }

   /* !!!! Free them here */
   /*
   hypre_TFree(hypre_ParCSRMatrixSocDiagJ(S), HYPRE_MEMORY_DEVICE);
   hypre_TFree(hypre_ParCSRMatrixSocOffdJ(S), HYPRE_MEMORY_DEVICE);
   */

   HYPRE_THRUST_CALL(replace, CF_marker_dev, CF_marker_dev + n_fine, -3, -1);

   /* 5. Construct the result as a ParCSRMatrix. At this point, P's column indices */
   /*    are defined with A's enumeration of columns */

   P = hypre_ParCSRMatrixCreate(comm,
                                hypre_ParCSRMatrixGlobalNumRows(A),
                                total_global_cpts,
                                hypre_ParCSRMatrixColStarts(A),
                                num_cpts_global,
                                0,
                                P_diag_size,
                                P_offd_size);

   P_diag = hypre_ParCSRMatrixDiag(P);
   hypre_CSRMatrixData(P_diag) = P_diag_data;
   hypre_CSRMatrixI(P_diag)    = P_diag_i;
   hypre_CSRMatrixJ(P_diag)    = P_diag_j;

   P_offd = hypre_ParCSRMatrixOffd(P);
   hypre_CSRMatrixData(P_offd) = P_offd_data;
   hypre_CSRMatrixI(P_offd)    = P_offd_i;
   hypre_CSRMatrixJ(P_offd)    = P_offd_j;

   hypre_ParCSRMatrixOwnsRowStarts(P) = 0;

   hypre_CSRMatrixMemoryLocation(P_diag) = memory_location;
   hypre_CSRMatrixMemoryLocation(P_offd) = memory_location;

   /* 6. Compress P, removing coefficients smaller than trunc_factor * Max, and */
   /*    make sure no row has more than max_elmts elements */

   if (trunc_factor != 0.0 || max_elmts > 0)
   {
      hypre_BoomerAMGInterpTruncationDevice(P, trunc_factor, max_elmts);

      P_offd_i    = hypre_CSRMatrixI(P_offd);
      P_offd_j    = hypre_CSRMatrixJ(P_offd);
      P_offd_size = hypre_CSRMatrixNumNonzeros(P_offd);
      /* hypre_TMemcpy(&P_offd_size, &P_offd_i[n_fine], HYPRE_Int, 1, HYPRE_MEMORY_HOST, memory_location); */
   }

   /* 7. Translate P_offd's column indices from the values inherited from A_offd to a 0,1,2,3,... enumeration, */
   /*    and construct the col_map array that translates these into the global 0..c-1 enumeration */
   if (P_offd_size)
   {
      /* Array P_marker has length equal to the number of A's offd columns+1, and will */
      /* store a translation code from A_offd's local column numbers to P_offd's local column numbers */
      /* Example: if A_offd has 6 columns, locally 0,1,..,5, and points 1 and 4 are coarse points, then
         P_marker=[0,1,0,0,1,0,0], */

      /* First,  set P_marker[i] to 1 if A's column i is also present in P, otherwise P_marker[i] is 0 */
      HYPRE_Int *P_marker = hypre_TAlloc(HYPRE_Int, num_cols_A_offd, HYPRE_MEMORY_DEVICE);
      HYPRE_Int *P_colids = hypre_TAlloc(HYPRE_Int, hypre_max(P_offd_size, num_cols_A_offd), HYPRE_MEMORY_DEVICE);

      hypre_TMemcpy(P_colids, P_offd_j, HYPRE_Int, P_offd_size, HYPRE_MEMORY_DEVICE, memory_location);
      /* sort and unique */
      HYPRE_THRUST_CALL(sort, P_colids, P_colids + P_offd_size);
      HYPRE_Int *new_end = HYPRE_THRUST_CALL(unique, P_colids, P_colids + P_offd_size);

      num_cols_P_offd = new_end - P_colids;

      HYPRE_THRUST_CALL(fill_n, P_marker, num_cols_A_offd, 0);
      hypreDevice_ScatterConstant(P_marker, num_cols_P_offd, P_colids, 1);

      /* Because P's columns correspond to P_marker[i]=1 (and =0 otherwise), the scan below will return  */
      /* an enumeration of P's columns 0,1,... at the corresponding locations in P_marker. */
      /* P_marker[num_cols_A_offd] will contain num_cols_P_offd, so sum reduction above could  */
      /* have been replaced by reading the last element of P_marker. */
      HYPRE_THRUST_CALL(exclusive_scan, P_marker, P_marker + num_cols_A_offd, P_colids);
      /* Example: P_marker becomes [0,0,1,1,1,2] so that P_marker[1]=0, P_marker[4]=1  */

      /* Do the re-enumeration, P_offd_j are mapped, using P_marker as map  */
      HYPRE_THRUST_CALL(gather, P_offd_j, P_offd_j + P_offd_size, P_colids, P_offd_j);

      /* Create and define array tmp_map_offd. This array is the inverse of the P_marker mapping, */
      /* Example: num_cols_P_offd=2, tmp_map_offd[0] = 1, tmp_map_offd[1]=4  */
      /* P_colids is large enough to hold */
      new_end = HYPRE_THRUST_CALL(copy_if,
                                  thrust::make_counting_iterator(0),
                                  thrust::make_counting_iterator(num_cols_A_offd),
                                  P_marker,
                                  P_colids,
                                  thrust::identity<HYPRE_Int>());
      hypre_assert(new_end - P_colids == num_cols_P_offd);

      tmp_map_offd_h = hypre_TAlloc(HYPRE_Int, num_cols_P_offd, HYPRE_MEMORY_HOST);
      hypre_TMemcpy(tmp_map_offd_h, P_colids, HYPRE_Int, num_cols_P_offd, HYPRE_MEMORY_HOST, HYPRE_MEMORY_DEVICE);

      hypre_TFree(P_colids, HYPRE_MEMORY_DEVICE);
      hypre_TFree(P_marker, HYPRE_MEMORY_DEVICE);
   }

   /* 8. P_offd_j now has a 0,1,2,3... local column index enumeration. */
   /*    tmp_map_offd contains the index mapping from P's offd local columns to A's offd local columns.*/
   /*    Below routine is in parcsr_ls/par_rap_communication.c. It sets col_map_offd in P, */
   /*    comm_pkg in P, and perhaps more members of P ??? */

   fine_to_coarse_h = hypre_TAlloc(HYPRE_Int, n_fine, HYPRE_MEMORY_HOST);
   hypre_TMemcpy(fine_to_coarse_h, fine_to_coarse_d, HYPRE_Int, n_fine, HYPRE_MEMORY_HOST, HYPRE_MEMORY_DEVICE);

   hypre_ParCSRMatrixColMapOffd(P) = hypre_CTAlloc(HYPRE_BigInt, num_cols_P_offd, HYPRE_MEMORY_HOST);
   hypre_CSRMatrixNumCols(P_offd)  = num_cols_P_offd;

   hypre_GetCommPkgRTFromCommPkgA(P, A, fine_to_coarse_h, tmp_map_offd_h);

   *P_ptr = P;

   hypre_TFree(CF_marker_dev,    HYPRE_MEMORY_DEVICE);
   hypre_TFree(CF_marker_offd,   HYPRE_MEMORY_DEVICE);
   hypre_TFree(dof_func_offd,    HYPRE_MEMORY_DEVICE);
   hypre_TFree(dof_func_dev,     HYPRE_MEMORY_DEVICE);
   hypre_TFree(int_buf_data,     HYPRE_MEMORY_HOST);
   hypre_TFree(fine_to_coarse_d, HYPRE_MEMORY_DEVICE);
   hypre_TFree(fine_to_coarse_h, HYPRE_MEMORY_HOST);
   hypre_TFree(tmp_map_offd_h,   HYPRE_MEMORY_HOST);

   return hypre_error_flag;
}


/*-----------------------------------------------------------------------*/
 __global__ void
hypre_BoomerAMGBuildDirInterp_getnnz( HYPRE_Int  nr_of_rows,
                                      HYPRE_Int *S_diag_i,
                                      HYPRE_Int *S_diag_j,
                                      HYPRE_Int *S_offd_i,
                                      HYPRE_Int *S_offd_j,
                                      HYPRE_Int *CF_marker,
                                      HYPRE_Int *CF_marker_offd,
                                      HYPRE_Int  num_functions,
                                      HYPRE_Int *dof_func,
                                      HYPRE_Int *dof_func_offd,
                                      HYPRE_Int *P_diag_i,
                                      HYPRE_Int *P_offd_i)
{
   /*-----------------------------------------------------------------------*/
   /* Determine size of interpolation matrix, P

      If A is of size m x m, then P will be of size m x c where c is the
      number of coarse points.

      It is assumed that S have the same global column enumeration as A

      Input: nr_of_rows         - Number of rows in matrix (local in processor)
             S_diag_i, S_diag_j - CSR representation of S_diag
             S_offd_i, S_offd_j - CSR representation of S_offd
             num_function  - Number of degrees of freedom per grid point
             dof_func      - vector of length nr_of_rows, indicating the degree of freedom of vector element.
             dof_func_offd - vector over ncols of A_offd, indicating the degree of freedom.

      Output: P_diag_i       - Vector where P_diag_i[i] holds the number of non-zero elements of P_diag on row i.
              P_offd_i       - Vector where P_offd_i[i] holds the number of non-zero elements of P_offd on row i.
              fine_to_coarse - Vector of length nr_of_rows.
                               fine_to_coarse[i] is set to 1 if i is a coarse pt.
                               Eventually, fine_to_coarse[j] will map A's column j
                               to a re-enumerated column index in matrix P.
    */
   /*-----------------------------------------------------------------------*/

   HYPRE_Int i = hypre_cuda_get_grid_warp_id<1,1>();

   if (i >= nr_of_rows)
   {
      return;
   }

   HYPRE_Int p, q, dof_func_i;
   HYPRE_Int jPd = 0, jPo = 0;
   HYPRE_Int lane = hypre_cuda_get_lane_id<1>();

   if (lane == 0)
   {
      p = read_only_load(CF_marker + i);
   }
   p = __shfl_sync(HYPRE_WARP_FULL_MASK, p, 0);

   /*--------------------------------------------------------------------
    *  If i is a C-point, interpolation is the identity.
    *--------------------------------------------------------------------*/
   if (p >= 0)
   {
      if (lane == 0)
      {
         P_diag_i[i] = 1;
         P_offd_i[i] = 0;
      }
      return;
   }

   /*--------------------------------------------------------------------
    *  If i is an F-point, interpolation is from the C-points that
    *  strongly influence i.
    *--------------------------------------------------------------------*/
   if (num_functions > 1 && dof_func != NULL)
   {
      if (lane == 0)
      {
         dof_func_i = read_only_load(&dof_func[i]);
      }
      dof_func_i = __shfl_sync(HYPRE_WARP_FULL_MASK, dof_func_i, 0);
   }

   /* diag part */
   if (lane < 2)
   {
      p = read_only_load(S_diag_i + i + lane);
   }
   q = __shfl_sync(HYPRE_WARP_FULL_MASK, p, 1);
   p = __shfl_sync(HYPRE_WARP_FULL_MASK, p, 0);

   for (HYPRE_Int j = p + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q); j += HYPRE_WARP_SIZE)
   {
      if (j < q)
      {
         const HYPRE_Int col = read_only_load(&S_diag_j[j]);
         if ( read_only_load(&CF_marker[col]) > 0 && (num_functions == 1 || read_only_load(&dof_func[col]) == dof_func_i) )
         {
            jPd++;
         }
      }
   }
   jPd = warp_reduce_sum(jPd);

   /* offd part */
   if (lane < 2)
   {
      p = read_only_load(S_offd_i + i + lane);
   }
   q = __shfl_sync(HYPRE_WARP_FULL_MASK, p, 1);
   p = __shfl_sync(HYPRE_WARP_FULL_MASK, p, 0);

   for (HYPRE_Int j = p + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q); j += HYPRE_WARP_SIZE)
   {
      if (j < q)
      {
         const HYPRE_Int tmp = read_only_load(&S_offd_j[j]);
         const HYPRE_Int col = tmp;
         if ( read_only_load(&CF_marker_offd[col]) > 0 && (num_functions == 1 || read_only_load(&dof_func_offd[col]) == dof_func_i) )
         {
            jPo++;
         }
      }
   }
   jPo = warp_reduce_sum(jPo);

   if (lane == 0)
   {
      P_diag_i[i] = jPd;
      P_offd_i[i] = jPo;
   }
}

/*-----------------------------------------------------------------------*
 *-----------------------------------------------------------------------*/
 __global__ void
hypre_BoomerAMGBuildDirInterp_getcoef( HYPRE_Int   nr_of_rows,
                                       HYPRE_Int  *A_diag_i,
                                       HYPRE_Int  *A_diag_j,
                                       HYPRE_Real *A_diag_data,
                                       HYPRE_Int  *A_offd_i,
                                       HYPRE_Int  *A_offd_j,
                                       HYPRE_Real *A_offd_data,
                                       HYPRE_Int  *Soc_diag_j,
                                       HYPRE_Int  *Soc_offd_j,
                                       HYPRE_Int  *CF_marker,
                                       HYPRE_Int  *CF_marker_offd,
                                       HYPRE_Int   num_functions,
                                       HYPRE_Int  *dof_func,
                                       HYPRE_Int  *dof_func_offd,
                                       HYPRE_Int  *P_diag_i,
                                       HYPRE_Int  *P_diag_j,
                                       HYPRE_Real *P_diag_data,
                                       HYPRE_Int  *P_offd_i,
                                       HYPRE_Int  *P_offd_j,
                                       HYPRE_Real *P_offd_data,
                                       HYPRE_Int  *fine_to_coarse )
{
   /*-----------------------------------------------------------------------*/
   /* Compute interpolation matrix, P

      Input: nr_of_rows - Number of rows in matrix (local in processor)
             A_diag_i, A_diag_j, A_diag_data - CSR representation of A_diag
             A_offd_i, A_offd_j, A_offd_data - CSR representation of A_offd
             S_diag_i, S_diag_j - CSR representation of S_diag
             S_offd_i, S_offd_j - CSR representation of S_offd
             CF_marker          - Coarse/Fine flags for indices (rows) in this processor
             CF_marker_offd     - Coarse/Fine flags for indices (rows) not in this processor
             num_function  - Number of degrees of freedom per grid point
             dof_func      - vector over nonzero elements of A_diag, indicating the degree of freedom
             dof_func_offd - vector over nonzero elements of A_offd, indicating the degree of freedom
             fine_to_coarse - Vector of length nr_of_rows-1.

      Output: P_diag_j         - Column indices in CSR representation of P_diag
              P_diag_data      - Matrix elements in CSR representation of P_diag
              P_offd_j         - Column indices in CSR representation of P_offd
              P_offd_data      - Matrix elements in CSR representation of P_diag
   */
   /*-----------------------------------------------------------------------*/

   HYPRE_Int i = hypre_cuda_get_grid_warp_id<1,1>();

   if (i >= nr_of_rows)
   {
      return;
   }

   HYPRE_Int lane = hypre_cuda_get_lane_id<1>();

   HYPRE_Int k, dof_func_i;

   if (lane == 0)
   {
      k = read_only_load(CF_marker + i);
   }
   k = __shfl_sync(HYPRE_WARP_FULL_MASK, k, 0);

   /*--------------------------------------------------------------------
    *  If i is a C-point, interpolation is the identity.
    *--------------------------------------------------------------------*/
   if (k > 0)
   {
      if (lane == 0)
      {
         const HYPRE_Int ind = read_only_load(&P_diag_i[i]);
         P_diag_j[ind]       = read_only_load(&fine_to_coarse[i]);
         P_diag_data[ind]    = 1.0;
      }

      return;
   }

   /*--------------------------------------------------------------------
    *  Point is f-point, use direct interpolation
    *--------------------------------------------------------------------*/
   if (num_functions > 1 && dof_func != NULL)
   {
      if (lane == 0)
      {
         dof_func_i = read_only_load(&dof_func[i]);
      }
      dof_func_i = __shfl_sync(HYPRE_WARP_FULL_MASK, dof_func_i, 0);
   }

   HYPRE_Real diagonal = 0.0, sum_N_pos = 0.0, sum_N_neg = 0.0, sum_P_pos = 0.0, sum_P_neg = 0.0;

   /* diag part */
   HYPRE_Int p_diag_A, q_diag_A, p_diag_P, q_diag_P;
   if (lane < 2)
   {
      p_diag_A = read_only_load(A_diag_i + i + lane);
      p_diag_P = read_only_load(P_diag_i + i + lane);
   }
   q_diag_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_A, 1);
   p_diag_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_A, 0);
   q_diag_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_P, 1);
   p_diag_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_P, 0);

   k = p_diag_P;
   for (HYPRE_Int j = p_diag_A + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_diag_A); j += HYPRE_WARP_SIZE)
   {
      HYPRE_Int col, sum, pos;
      HYPRE_Int is_SC = 0; /* if is a Strong-C */
      HYPRE_Complex val;

      if (j < q_diag_A)
      {
         col = read_only_load(&A_diag_j[j]);

         if (i == col)
         {
            diagonal = read_only_load(&A_diag_data[j]);
         }
         else if ( num_functions == 1 || read_only_load(&dof_func[col]) == dof_func_i )
         {
            val = read_only_load(&A_diag_data[j]);

            if (val > 0.0)
            {
               sum_N_pos += val;
            }
            else
            {
               sum_N_neg += val;
            }

            is_SC = read_only_load(&Soc_diag_j[j]) > -1 && read_only_load(&CF_marker[col]) > 0;

            if (is_SC)
            {
               if (val > 0.0)
               {
                  sum_P_pos += val;
               }
               else
               {
                  sum_P_neg += val;
               }
            }
         }
      }

      pos = warp_prefix_sum(lane, is_SC, sum);

      if (is_SC)
      {
         P_diag_data[k + pos] = val;
         P_diag_j[k + pos] = read_only_load(&fine_to_coarse[col]);
      }
      k += sum;
   }

   hypre_device_assert(k == q_diag_P);

   /* offd part */
   HYPRE_Int p_offd_A, q_offd_A, p_offd_P, q_offd_P;
   if (lane < 2)
   {
      p_offd_A = read_only_load(A_offd_i + i + lane);
      p_offd_P = read_only_load(P_offd_i + i + lane);
   }
   q_offd_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_A, 1);
   p_offd_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_A, 0);
   q_offd_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_P, 1);
   p_offd_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_P, 0);

   k = p_offd_P;
   for (HYPRE_Int j = p_offd_A + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_offd_A); j += HYPRE_WARP_SIZE)
   {
      HYPRE_Int col, sum, pos;
      HYPRE_Int is_SC = 0; /* if is a Strong-C */
      HYPRE_Complex val;

      if (j < q_offd_A)
      {
         col = read_only_load(&A_offd_j[j]);

         if ( num_functions == 1 || read_only_load(&dof_func_offd[col]) == dof_func_i )
         {
            val = read_only_load(&A_offd_data[j]);

            if (val > 0.0)
            {
               sum_N_pos += val;
            }
            else
            {
               sum_N_neg += val;
            }

            is_SC = read_only_load(&Soc_offd_j[j]) > -1 && read_only_load(&CF_marker_offd[col]) > 0;

            if (is_SC)
            {
               if (val > 0.0)
               {
                  sum_P_pos += val;
               }
               else
               {
                  sum_P_neg += val;
               }
            }
         }
      }

      pos = warp_prefix_sum(lane, is_SC, sum);

      if (is_SC)
      {
         P_offd_data[k + pos] = val;
         P_offd_j[k + pos] = col;
      }
      k += sum;
   }

   hypre_device_assert(k == q_offd_P);

   diagonal  = warp_allreduce_sum(diagonal);
   sum_N_pos = warp_allreduce_sum(sum_N_pos);
   sum_N_neg = warp_allreduce_sum(sum_N_neg);
   sum_P_pos = warp_allreduce_sum(sum_P_pos);
   sum_P_neg = warp_allreduce_sum(sum_P_neg);

   HYPRE_Complex alfa = 1.0, beta = 1.0;

   if (sum_P_neg)
   {
      alfa = sum_N_neg / (sum_P_neg * diagonal);
   }

   if (sum_P_pos)
   {
      beta = sum_N_pos / (sum_P_pos * diagonal);
   }

   for (HYPRE_Int j = p_diag_P + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_diag_P); j += HYPRE_WARP_SIZE)
   {
      /* if (P_diag_data[j] > 0.0)
            P_diag_data[j] *= -beta;
         else
            P_diag_data[j] *= -alfa; */
      if (j < q_diag_P)
      {
         P_diag_data[j] *= (P_diag_data[j] > 0.0) * (alfa-beta) - alfa;
      }
   }

   for (HYPRE_Int j = p_offd_P + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_offd_P); j += HYPRE_WARP_SIZE)
   {
      /* if (P_offd_data[indp]> 0)
            P_offd_data[indp] *= -beta;
         else
            P_offd_data[indp] *= -alfa; */
      if (j < q_offd_P)
      {
         P_offd_data[j] *= (P_offd_data[j] > 0.0) * (alfa-beta) - alfa;
      }
   }
}

/*-----------------------------------------------------------------------*
 *-----------------------------------------------------------------------*/
 __global__ void
hypre_BoomerAMGBuildDirInterp_getcoef_v2( HYPRE_Int   nr_of_rows,
                                          HYPRE_Int  *A_diag_i,
                                          HYPRE_Int  *A_diag_j,
                                          HYPRE_Real *A_diag_data,
                                          HYPRE_Int  *A_offd_i,
                                          HYPRE_Int  *A_offd_j,
                                          HYPRE_Real *A_offd_data,
                                          HYPRE_Int  *Soc_diag_j,
                                          HYPRE_Int  *Soc_offd_j,
                                          HYPRE_Int  *CF_marker,
                                          HYPRE_Int  *CF_marker_offd,
                                          HYPRE_Int   num_functions,
                                          HYPRE_Int  *dof_func,
                                          HYPRE_Int  *dof_func_offd,
                                          HYPRE_Int  *P_diag_i,
                                          HYPRE_Int  *P_diag_j,
                                          HYPRE_Real *P_diag_data,
                                          HYPRE_Int  *P_offd_i,
                                          HYPRE_Int  *P_offd_j,
                                          HYPRE_Real *P_offd_data,
                                          HYPRE_Int  *fine_to_coarse )
{
   /*-----------------------------------------------------------------------*/
   /* Compute interpolation matrix, P

      Input: nr_of_rows - Number of rows in matrix (local in processor)
             A_diag_i, A_diag_j, A_diag_data - CSR representation of A_diag
             A_offd_i, A_offd_j, A_offd_data - CSR representation of A_offd
             S_diag_i, S_diag_j - CSR representation of S_diag
             S_offd_i, S_offd_j - CSR representation of S_offd
             CF_marker          - Coarse/Fine flags for indices (rows) in this processor
             CF_marker_offd     - Coarse/Fine flags for indices (rows) not in this processor
             num_function  - Number of degrees of freedom per grid point
             dof_func      - vector over nonzero elements of A_diag, indicating the degree of freedom
             dof_func_offd - vector over nonzero elements of A_offd, indicating the degree of freedom
             fine_to_coarse - Vector of length nr_of_rows-1.

      Output: P_diag_j         - Column indices in CSR representation of P_diag
              P_diag_data      - Matrix elements in CSR representation of P_diag
              P_offd_j         - Column indices in CSR representation of P_offd
              P_offd_data      - Matrix elements in CSR representation of P_diag
   */
   /*-----------------------------------------------------------------------*/

   HYPRE_Int i = hypre_cuda_get_grid_warp_id<1,1>();

   if (i >= nr_of_rows)
   {
      return;
   }

   HYPRE_Int lane = hypre_cuda_get_lane_id<1>();

   HYPRE_Int k, dof_func_i;

   if (lane == 0)
   {
      k = read_only_load(CF_marker + i);
   }
   k = __shfl_sync(HYPRE_WARP_FULL_MASK, k, 0);

   /*--------------------------------------------------------------------
    *  If i is a C-point, interpolation is the identity.
    *--------------------------------------------------------------------*/
   if (k > 0)
   {
      if (lane == 0)
      {
         const HYPRE_Int ind = read_only_load(&P_diag_i[i]);
         P_diag_j[ind]       = read_only_load(&fine_to_coarse[i]);
         P_diag_data[ind]    = 1.0;
      }

      return;
   }

   /*--------------------------------------------------------------------
    *  Point is f-point, use direct interpolation
    *--------------------------------------------------------------------*/
   if (num_functions > 1 && dof_func != NULL)
   {
      if (lane == 0)
      {
         dof_func_i = read_only_load(&dof_func[i]);
      }
      dof_func_i = __shfl_sync(HYPRE_WARP_FULL_MASK, dof_func_i, 0);
   }

   HYPRE_Real diagonal = 0.0, sum_F = 0.0;

   /* diag part */
   HYPRE_Int p_diag_A, q_diag_A, p_diag_P, q_diag_P;
   if (lane < 2)
   {
      p_diag_A = read_only_load(A_diag_i + i + lane);
      p_diag_P = read_only_load(P_diag_i + i + lane);
   }
   q_diag_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_A, 1);
   p_diag_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_A, 0);
   q_diag_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_P, 1);
   p_diag_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_diag_P, 0);

   k = p_diag_P;
   for (HYPRE_Int j = p_diag_A + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_diag_A); j += HYPRE_WARP_SIZE)
   {
      HYPRE_Int col, sum, pos;
      HYPRE_Int is_SC = 0; /* if is a Strong-C */
      HYPRE_Complex val;

      if (j < q_diag_A)
      {
         col = read_only_load(&A_diag_j[j]);

         if (i == col)
         {
            diagonal = read_only_load(&A_diag_data[j]);
         }
         else if ( num_functions == 1 || read_only_load(&dof_func[col]) == dof_func_i )
         {
            val = read_only_load(&A_diag_data[j]);
            if (read_only_load(&Soc_diag_j[j]) > -1)
            {
               if (read_only_load(&CF_marker[col]) > 0)
               {
                  is_SC = 1;
               }
               else
               {
                  sum_F += val;
               }
            }
            else
            {
               diagonal += val;
            }
         }
      }

      pos = warp_prefix_sum(lane, is_SC, sum);

      if (is_SC)
      {
         P_diag_data[k + pos] = val;
         P_diag_j[k + pos] = read_only_load(&fine_to_coarse[col]);
      }
      k += sum;
   }

   hypre_device_assert(k == q_diag_P);

   /* offd part */
   HYPRE_Int p_offd_A, q_offd_A, p_offd_P, q_offd_P;
   if (lane < 2)
   {
      p_offd_A = read_only_load(A_offd_i + i + lane);
      p_offd_P = read_only_load(P_offd_i + i + lane);
   }
   q_offd_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_A, 1);
   p_offd_A = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_A, 0);
   q_offd_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_P, 1);
   p_offd_P = __shfl_sync(HYPRE_WARP_FULL_MASK, p_offd_P, 0);

   k = p_offd_P;
   for (HYPRE_Int j = p_offd_A + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_offd_A); j += HYPRE_WARP_SIZE)
   {
      HYPRE_Int col, sum, pos;
      HYPRE_Int is_SC = 0; /* if is a Strong-C */
      HYPRE_Complex val;

      if (j < q_offd_A)
      {
         col = read_only_load(&A_offd_j[j]);

         if ( num_functions == 1 || read_only_load(&dof_func_offd[col]) == dof_func_i )
         {
            val = read_only_load(&A_offd_data[j]);
            if (read_only_load(&Soc_offd_j[j]) > -1)
            {
               if (read_only_load(&CF_marker_offd[col]) > 0)
               {
                  is_SC = 1;
               }
               else
               {
                  sum_F += val;
               }
            }
            else
            {
               diagonal += val;
            }
         }
      }

      pos = warp_prefix_sum(lane, is_SC, sum);

      if (is_SC)
      {
         P_offd_data[k + pos] = val;
         P_offd_j[k + pos] = col;
      }
      k += sum;
   }

   hypre_device_assert(k == q_offd_P);

   diagonal  = warp_allreduce_sum(diagonal);
   sum_F     = warp_allreduce_sum(sum_F);

   HYPRE_Complex beta = sum_F / (q_diag_P - p_diag_P + q_offd_P - p_offd_P);

   for (HYPRE_Int j = p_diag_P + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_diag_P); j += HYPRE_WARP_SIZE)
   {
      /* if (P_diag_data[j] > 0.0)
            P_diag_data[j] *= -beta;
         else
            P_diag_data[j] *= -alfa; */
      if (j < q_diag_P)
      {
         P_diag_data[j] = -(P_diag_data[j] + beta) / diagonal;
      }
   }

   for (HYPRE_Int j = p_offd_P + lane; __any_sync(HYPRE_WARP_FULL_MASK, j < q_offd_P); j += HYPRE_WARP_SIZE)
   {
      /* if (P_offd_data[indp]> 0)
            P_offd_data[indp] *= -beta;
         else
            P_offd_data[indp] *= -alfa; */
      if (j < q_offd_P)
      {
         P_offd_data[j] = -(P_offd_data[j] + beta) / diagonal;
      }
   }
}

#endif // defined(HYPRE_USING_CUDA) || defined(HYPRE_USING_HIP)
