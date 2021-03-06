#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Provide a command line argument (int)\n");
        exit(EXIT_FAILURE);
    }
#ifdef DEBUG
    printf("Size of int: %ld\n", sizeof(int));
    printf("Size of double: %ld\n", sizeof(double));
#endif

    int step = atoi(argv[1]);
    const int length = 512 * 1024 * 1024;
    int* arr = (int*)malloc(length * sizeof(int));

    double avg = 0.0;
    int times = 5, t = 0;
    for (t=0; t<times; ++t)
    {
        int i=0;
        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (i=0; i<length; i+=step)
        {
            arr[i] *= 3.333;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        long int duration;
        if (end.tv_nsec < start.tv_nsec) /* nano ~ 1e9 */
            duration = 1000000000 + end.tv_nsec - start.tv_nsec;
        else
            duration = end.tv_nsec - start.tv_nsec;
#ifdef DEBUG
        printf("iter=%d, step=%d, duration(micro)%ld\n", iter, step, duration / 1000);
#endif
        duration /= 1000000; /* miliseconds */
        avg += duration;
    }
    printf("%d %f\n", step, avg / times);

    free(arr);
    exit(EXIT_SUCCESS);
}
