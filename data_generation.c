#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//rdtsc() written by Guillaume Hetier


//Time measure function (in ticks).
//First part : for 32bits processors
//Second part : for 64bits processors
//Calls rdtsc function in asm
#ifdef __i386
unsigned long rdtsc() {
  unsigned long lo, hi;
        asm( "rdtsc" : "=a" (lo), "=d" (hi) );
        return (lo);
}
#elif defined __amd64
unsigned long rdtsc() {
  unsigned long lo, hi;
        asm( "rdtsc" : "=a" (lo), "=d" (hi) );
        return( lo | (hi << 32) ); //64bits response stored in 2 registers
#endif

int main()
{
    runToFile(10);
}

int basicTest(){

// Basic test function : writes one test results to console

    int s = 2*1024*1024*70;
    int* t = (int*)(malloc(sizeof(int)*s));
    int a;
    long i;
    int time2;


    a=5;
    printf("Début, a : %d\n", a);
    a=5;
    //Access to variable just after previous access
    unsigned long begin = rdtsc();
    a=3;
    unsigned long end = rdtsc();
    printf("Time 1 : %ld\n", end- begin);

    printf("Après premier test a : %d\n", a);
    a=5;
    printf("Avant second test a : %d\n", a);

    for(i=0; i < s/2; i++)
    {
        t[i] = 56234;
        t[s-i] = 78256;
    }


    //Access to variable just after data has been loaded in cache
    begin = rdtsc();
    a=3;
    end = rdtsc();
    time2=end-begin;
    printf("Time 2 : %ld\n", time2);

    printf("A la fin a : %d\n", a);

    free(t);

    a=5;
    printf("Reprise début, a : %d\n", a);
    //Access to variable just after previous access
    a=5;
    begin = rdtsc();
    a=3;
    end = rdtsc();
    printf("Time 3 : %ld\n", end- begin);

    return time2;
}

int runToFile(int count){

// Runs [count] tests and write results to a file to b analyzed with high level language (python/scilab...)

    FILE *output = fopen("cache_test.txt","w");
    int i;
    for (i = 0; i < count; ++i)
    {
        fprintf(output, "%d\n", test());
        printf("%d\n", i);
    }
    fclose(output);
}

int test(){

// Does one single test. Adjust s to your computers memory

    int s = 2*1024*1024*100;
    int* t = (int*)(malloc(sizeof(int)*s));
    long i;
    int time2;
    int a=5;

    for(i=0; i < s/2; i++)
    {
        t[i] = 56234;
        t[s-i] = 78256;
    }


    //Acces à la variable a après ajout de données dans le cache et temps d'attente
    int begin = rdtsc();
    a=3;
    int end = rdtsc();
    time2=end-begin;

    free(t);



    return time2;
}
