/***************************************************************************
 *   Copyright (C) 2014 by Edson Borin                                     *
 *   edson@ic.unicamp.br                                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <float.h>  // FLT_MAX
#include <stdio.h>  // printf
#include <stdlib.h> // rand, qsort


/* Matrices dimentions. */
#ifndef ARRAY_SZ
#define ARRAY_SZ 32768
#endif

/* Number of times each kernel will be executed. */
#define RPT 100000

/*------------------------------------------------*/
/* Code to read the wall clock time.              */
#include <sys/time.h>
double mysecond()
{
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

/*------------------------------------------------*/
/* Numeric kernels and data        .              */

/* Matrices. */
int data[ARRAY_SZ];
int result = 0;

/* Kernel name. */
const char* kernel_name = "branch_prediction";

void initialize_array()
{
  unsigned i;
  for (i=0; i<ARRAY_SZ; i++) {
    data[i] = rand() % 256;
  }
}

int compare_int(const void* ap, const void* bp) {
  int* a = (int*) ap;
  int* b = (int*) bp;
  return *a - *b;
}

void sort_array()
{
  qsort(data, ARRAY_SZ, sizeof(int), compare_int);
}

void kernel()
{
  unsigned i;
  unsigned sum = 0;
  for (i=0; i<ARRAY_SZ; i++)
  {
    if (data[i] >= 128)
      sum += data[i];
//      sum += data[i] >=128 ? data[i] : 0;
  }
  result += sum;
}

/* Amount of bytes accessed: 3 (2 reads + 1 write) * ARRAY_SZ * element size (in bytes)  */
double bytes = (ARRAY_SZ*sizeof(int));

/* -----------------------------*/
int main()
{
  unsigned long long k;
  double             band;
  double             t;
  int                i;

  printf("Kernel name     : %s\n",kernel_name);
  printf("# of runs       : %d\n", RPT);
  printf("Array size      : %d\n", (unsigned) ARRAY_SZ);
#ifdef SORT
  printf("Array values    : sorted\n");
#else
  printf("Array values    : unsorted\n");
#endif 

  initialize_array();

  /* --------------------- */
  t = mysecond();
    
#ifdef SORT
  sort_array();
#endif

  /* Run kernel RPT times. */
  for (k=0; k<RPT; k++)
    kernel();

  t = mysecond() - t;
  /* --------------------- */

#define GB (1024*1024*1024)

  band = ((RPT*bytes) / t) / GB;
  printf("Bandwidth GB/s  : %6.4f\n",band);
  printf("Execution time  : %6.4f\n",t);
  printf("Result          : %d\n", result);

  return 0;
}

