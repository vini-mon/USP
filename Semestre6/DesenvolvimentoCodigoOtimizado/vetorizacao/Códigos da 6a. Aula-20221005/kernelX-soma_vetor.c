#ifndef DATATYPE
#define DATATYPE float
#endif

/* Number of times each kernel will be executed. */
#ifndef RPT
#define RPT 1000
#endif

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
DATATYPE mb[ARRAY_SZ];
DATATYPE result;

/* Kernel name. */
const char* kernel_name = "soma_vetor";


void soma_vetor(DATATYPE* a, DATATYPE* end_a, DATATYPE* b, DATATYPE* end_b)
{
    while( (a < end_a) && (b < end_b) )
        *(a++) += *b++;

    // int n = MIN(end_a, end_b)
    while (i < n)
        *(a++) += *b++;
}


void kernel()
{
  soma_vetor(ma, mb);
}

/* Amount of bytes accessed: 2 (2 reads) * ARRAY_SZ * element size (in bytes)  */
double bytes = (2*ARRAY_SZ*sizeof(DATATYPE));

/* -----------------------------*/
int main()
{
  unsigned long long k;
  double	     times[RPT];
  double             mintime = FLT_MAX;
  double             avgtime = 0;
  double             maxtime = 0;
  double             rate, avgrate;
  double             t;
  int                i;

  printf("Kernel name     : %s\n",kernel_name);
  printf("Array datatype  : %s\n", XSTR(DATATYPE));
  printf("# of runs       : %d\n", RPT);
  printf("Arrays size     : %i\n", ARRAY_SZ);

  /* Initialize arrays. */
  for (i=0; i<ARRAY_SZ; i++)
    ma[i] = mb[i] = 2.0;
  
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
  printf("Best Rate GB/s  : %6.2f\n",rate);
  printf("Avg  Rate GB/s  : %6.2f\n",avgrate);
  printf("Avg time        : %6.2f\n",avgtime);
  printf("Min time        : %6.2f\n",mintime);
  printf("Max time        : %6.2f\n",maxtime);
  printf("Product Result  : %f\n", result);

  return 0;
}

