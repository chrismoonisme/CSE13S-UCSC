//include standard libraries
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//include written files
#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"

//include stats struct definition
#include "stats.h"

//command line options
#define OPTIONS "Hsqn:p:r:ahb"

//initialize seed
uint64_t seed = 13371453;

//intialize array size
uint32_t size = 100;

//initialize number of printed values
uint32_t elements = 100;

//array scrambler
void scramble(uint32_t *arr, uint64_t seed, uint32_t size) {

    srandom(seed);

    for (uint32_t i = 0; i < size; i++) {

        uint32_t val = random() & 0x3fffffff;

        arr[i] = val;
    }
}

//main
int main(int argc, char **argv) {

    Set options = set_empty();

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        //help message (also runs on defualt, no option)
        case 'H': {

            //insert 1 into the set
            options = set_insert(options, 1);
            break;
        }

        //run all option
        case 'a': {

            options = set_insert(options, 2);
            options = set_insert(options, 3);
            options = set_insert(options, 4);
            options = set_insert(options, 5);
            break;
        }

        //shellsort option
        case 's': {

            //insert 2 into the set
            options = set_insert(options, 2);
            break;
        }

        //quicksort option
        case 'q': {

            //insert 3 into the set
            options = set_insert(options, 3);
            break;
        }

        //heapsort option
        case 'h': {

            //insert 4 into the set
            options = set_insert(options, 4);
            break;
        }

        //mergesort option
        case 'b': {

            //insert 5 into the set
            options = set_insert(options, 5);
            break;
        }

        //set array length
        case 'n': {

            int val = strtoul(optarg, NULL, 10);

            //set array size
            if (val > 0) {

                size = val;

            } else {

                return 1;
            }
            break;
        }

        //set elements to be printed
        case 'p': {

            int val = strtoul(optarg, NULL, 10);

            elements = val;

            break;
        }

        //set seed
        case 'r': {

            int val = strtoul(optarg, NULL, 10);

            seed = val;

            break;
        }
        }
    }

    //check if printed elements is larger than the array size, if so, reduce to size
    if (elements > size) {
        elements = size;
    }

    //create stats struct
    Stats stats;

    //allocate memory for the array
    uint32_t *arr = (uint32_t *) malloc(size * sizeof(uint32_t));

    //run shell if set contains 2
    if (set_member(options, 2) == true) {

        //fill up array with random values, using the scramble function from above
        scramble(arr, seed, size);

        shell_sort(&stats, arr, size);

        //print
        printf(
            "Shell Sort, %i elements, %lu moves, %lu compares", size, stats.moves, stats.compares);

        for (uint32_t i = 0; i < elements; i++) {

            if (i % 5 == 0) {

                printf("\n");
            }

            printf("%13" PRIu32, arr[i]);
        }

        printf("\n");
    }

    //run mergesort if set contains 5
    if (set_member(options, 5) == true) {

        //fill up array with random values, using the scramble function from above
        scramble(arr, seed, size);

        batcher_sort(&stats, arr, size);

        //print
        printf("Batcher Sort, %i elements, %lu moves, %lu compares", size, stats.moves,
            stats.compares);

        for (uint32_t i = 0; i < elements; i++) {

            if (i % 5 == 0) {

                printf("\n");
            }

            printf("%13" PRIu32, arr[i]);
        }

        printf("\n");
    }

    //run heapsort if set contains 4
    if (set_member(options, 4) == true) {

        //fill up array with random values, using the scramble function from above
        scramble(arr, seed, size);

        heap_sort(&stats, arr, size);

        //print
        printf(
            "Heap Sort, %i elements, %lu moves, %lu compares", size, stats.moves, stats.compares);

        for (uint32_t i = 0; i < elements; i++) {

            if (i % 5 == 0) {

                printf("\n");
            }

            printf("%13" PRIu32, arr[i]);
        }

        printf("\n");
    }
    //quicksort
    if (set_member(options, 3) == true) {

        //fill up array with random values, using the scramble function from above
        scramble(arr, seed, size);

        quick_sort(&stats, arr, size);

        //print
        printf(
            "Quick Sort, %i elements, %lu moves, %lu compares", size, stats.moves, stats.compares);

        for (uint32_t i = 0; i < elements; i++) {

            if (i % 5 == 0) {

                printf("\n");
            }

            printf("%13" PRIu32, arr[i]);
        }

        printf("\n");
    }

    //run help statement if empty set (no options inputed) or 4 is in the set (-H option)
    if (options == set_empty() || set_member(options, 1) == 1) {

        printf("SYNOPSIS\n");
        printf("   A collection of comparison-based sorting algorithms.\n");
        printf("\nUSAGE\n");
        printf("   ./sorting [-Hasbhq] [-n length] [-p elements] [-r seed]\n");
        printf("\nOPTIONS\n");
        printf("   -H              Display program help and usage.\n");
        printf("   -a              Enable all sorts.\n");
        printf("   -b              Enable Batcher Sort.\n");
        printf("   -h              Enable Heap Sort.\n");
        printf("   -q              Enable Quick Sort.\n");
        printf("   -s              Enable Shell Sort.\n");
        printf("   -n length       Specify number of array elements (default: 100).\n");
        printf("   -p elements     Specify number of elements to print (default: 100).\n");
        printf("   -r seed         Specify random seed (default: 13371453).\n");

        return 1;
    }

    //free array memory
    free(arr);

    return 0;
}
