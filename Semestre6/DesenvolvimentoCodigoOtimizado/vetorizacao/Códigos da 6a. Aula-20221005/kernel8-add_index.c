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

// Programa adaptado por Sarita M. Bruschi para o código de soma de um escalar a um vetor

#include <float.h> // FLT_MAX
#include <stdio.h> // printf

/* Matrices dimentions. */
#ifndef ARRAY_SZ
#define ARRAY_SZ 500000
#endif

/* Array data type. */
#ifndef DATATYPE
#define DATATYPE float
#endif

/* Number of times each kernel will be executed. */
#define RPT 1000

/* Useful macros! */
#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))
#define XSTR(s)  STR(s)
#define STR(s)   #s
/*------------------------------------------------*/
/* Code to remove data from the processor caches. */
#define KB (1024)
#define MB (1024 * KB)
#define GB (1024 * MB)
#define LARGEST_CACHE_SZ (16 * MB)
static unsigned char dummy_buffer[LARGEST_CACHE_SZ];
void clean_cache()
{
  unsigned long long i;
  for (i=0; i<LARGEST_CACHE_SZ; i++)
    dummy_buffer[i] += 1;
}

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
DATATYPE ma[ARRAY_SZ];


/* Kernel name. */
const char* kernel_name = "add_index";


void addindex(float *x, int n) 
{
    for (int i = 0; i < n; i++) 
        x[i] = x[i] + i;
}


#if DATATYPE == float
#include <x86intrin.h>

// n a multiple of 4, x is 16-byte aligned

void addindex_vec(float *x, int n) 
{
    __m128 index, x_vec;
    
    for(int i = 0; i < n/4; i++) 
    {
        x_vec= _mm_load_ps(x+i*4);           // load 4 floats
        index = _mm_set_ps(i*4+3, i*4+2, i*4+1, i*4); // create vector with indexes
        x_vec= _mm_add_ps(x_vec, index);     // add the two
        
        _mm_store_ps(x+i*4, x_vec);           // store back
    }
}
#else
#error "inner_prod_vec only works for DATATYPE == float"
#endif


/*void addindex_vec(float *x, int n) 
{
    __m128 index, incr, x_vec;
    index = _mm_set_ps(0, 1, 2, 3);
    incr= _mm_set1_ps(4);
    for(inti = 0; i < n/4; i++) 
    {
        x_vec = _mm_load_ps(x+i*4);         // load 4 floats 
        x_vec = _mm_add_ps(x_vec, index);   // add index
        _mm_store_ps(x+i*4, x_vec);         // store back
        
        index = _mm_add_ps(index, incr);// increment index
    }
*/

void kernel()
{
  addindex(ma, 10);
}


/* Amount of bytes accessed: 2 (2 reads) * ARRAY_SZ * element size (in bytes)  */
double bytes = (2*ARRAY_SZ*sizeof(DATATYPE));


int main()
{
  unsigned long long k;
  double	     times[RPT];
  double             mintime = FLT_MAX;
  double             avgtime = 0;
  double             maxtime = 0;
  double             rate, avgrate, medrate;
  double             t;
  int                i;

  printf("Kernel name     : %s\n",kernel_name);
  printf("Array datatype  : %s\n", XSTR(DATATYPE));
  printf("# of runs       : %d\n", RPT);
  printf("Arrays size     : %i\n", ARRAY_SZ);

  /* Initialize arrays. */
  for (i=0; i<ARRAY_SZ; i++)
    ma[i] = 2.0;
  
  /* Main loop. */
  for (k=0; k<RPT; k++)
  {
#ifndef NOCLEAN
    clean_cache();
#endif
    t = mysecond();
    /* Kernel */
    kernel();
    times[k] = mysecond() - t;
    //printf(" -> %6.2f s\n", times[k]);
  }


  /* Final report */
  for (k=1; k<RPT; k++) 
  /* Discard first iteration (k=1). */
  { 
    avgtime = avgtime + times[k];
    mintime = MIN(mintime, times[k]);
    maxtime = MAX(maxtime, times[k]);
  }

  avgtime = avgtime / (RPT-1);
  rate = (bytes / mintime) / GB;
  avgrate = (bytes / avgtime) / GB;
  medrate = (bytes / times[RPT/2]) / GB;
  printf("Best Rate GB/s  : %6.2f\n",rate);
  printf("Avg  Rate GB/s  : %6.2f\n",avgrate);
  printf("Median Rate GB/s: %6.2f\n",medrate);
  printf("Avg time        : %6.2f\n",avgtime);
  printf("Min time        : %6.2f\n",mintime);
  printf("Max time        : %6.2f\n",maxtime);
  //printf("Product Result  : %f\n", result);


    return 0;
}
