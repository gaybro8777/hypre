#!/bin/sh
#BHEADER**********************************************************************
# Copyright (c) 2008,  Lawrence Livermore National Security, LLC.
# Produced at the Lawrence Livermore National Laboratory.
# This file is part of HYPRE.  See file COPYRIGHT for details.
#
# HYPRE is free software; you can redistribute it and/or modify it under the
# terms of the GNU Lesser General Public License (as published by the Free
# Software Foundation) version 2.1 dated February 1999.
#
# $Revision$
#EHEADER**********************************************************************

#------------------------------------------------------------------------
#   File: BHEADER_update.sh
#   This script is used to replace existing BHEADER/EHEADER information
#   It expects the new information to be in a template file before this script 
#   is run.  This version is written for source code files (using the 
#   BHEAD_code_template) and script/info files (using the BHEAD_file_template).
#   These files can be edited to whatever is needed in the future. 
#
#   This script is run in the directory one level above the linear_solvers 
#   directory.
#
#   Algorithm Used:
#      grep for BHEADER in all sub-directories
#      for each file found
#         read each line of the file
#         if the line contains #BHEADER 
#            set the foundb flag to 1
#            copy the file_template to the temporary output file
#         else if the line contains *BHEADER*
#            set the foundb flag to 1
#            copy the code_template to the temporary output file
#         else if the line contains *EHEADER*
#            set the founde flag to 1
# 
#         when both BHEADER and EHEADER have been found; use PERL to
#           copy the rest of the file to the temporary file        
#
#         remove the original file
#         rename the temporary file to the original name
#
#------------------------------------------------------------------------

hypre_temp_outfile="AAfile.new"

hypre_file_template="BHEAD_file_template"
hypre_code_template="BHEAD_code_template"

filelist=`grep -R -l BHEADER linear_solvers/*`

current_dir=`pwd`

for file in $filelist
do

   echo ""
   echo "Processing file: " $file

   foundb=0
   founde=0
  
   pathname=`dirname $file`
   filename=`basename $file`

   cd $pathname

   while read InputLine
   do
      case $InputLine in
         "#!/bin"*)
               echo $InputLine > $hypre_temp_outfile
               ;;
         "#BHEADER"*)
               foundb=1
               if [ "$pathname" != "$current_dir" ]
               then
                  cp $current_dir/$hypre_file_template .
               fi
               cat $hypre_file_template >> $hypre_temp_outfile
               ;;
         *BHEADER*)
               foundb=1
               if [ "$pathname" != "$current_dir" ]
               then
                  cp $current_dir/$hypre_code_template .
               fi
               cat $hypre_code_template >> $hypre_temp_outfile
               ;;
         *EHEADER*)
               founde=1
               ;;
      esac
   done < $filename               ### done with reading HEADER section of filename

   if [ "$foundb" = "1" -a "$founde" = "1" ]
   then
      perl -e 'while ($line = <>) {if ($line =~ /\*BHEADER|#BHEADER/) {0 while(<> !~ /\*EHEADER|#EHEADER/);} elsif ($line !~ /BHEADER|EHEADER|bin/) {print("$line");}}' $filename >> $hypre_temp_outfile

      rm -rf $filename
      mv $hypre_temp_outfile $filename

   fi

   if [ "$pathname" != "$current_dir" ]
   then
      rm -rf *_template
   fi

   cd $current_dir

done                           ##### done with all filenames 
