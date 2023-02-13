#include "universe.h"

#include <inttypes.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hi:to:n:s"
//file name
char *name;
//toroidal toggle
bool toroidal = false;
//generations
uint32_t g = 100;
//screen toggle
bool screen = true;

int main(int argc, char **argv) {

    //file pointer, default stdin
    FILE *file = stdin;
    FILE *out = stdout;

    int opt = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {

        switch (opt) {

        //help message
        case 'h': {

            printf("SYNOPSIS\n");
            printf("    Conway's Game of Life\n\n");
            printf("USAGE\n");
            printf("    ./life_amd64 tsn:i:o:h\n\n");
            printf("OPTIONS\n");
            printf("    -t             Create your universe as a toroidal");
            printf("    -s             Silent - do not use animate the evolution");
            printf("    -n {number}    Number of generations [default: 100]");
            printf("    -i {file}      Input file [default: stdin]");
            printf("    -o {file}      Output file [default: stdout]");

            return 1;
        }

        //toggle toroidal
        case 't': {
            toroidal = true;
            break;
        }

        //toggle toroidal
        case 's': {
            screen = false;
            break;
        }

        //set generations
        case 'n': {
            g = strtoul(optarg, NULL, 10);
            break;
        }

        //set input file
        case 'i': {

            //get the name of the file
            name = optarg;

            //open the file
            file = fopen(name, "r");
            break;
        }

        //set output file
        case 'o': {

            //get the name of the file
            name = optarg;

            //open the file
            out = fopen(name, "w");
            break;
        }
        }
    }

    //--run code--

    //if any file is invalid, error
    if (file == NULL || out == NULL) {

        printf("Malformed input\n");
        return 1;
    }

    int rows;
    int cols;

    //get first pair
    fscanf(file, "%d %d", &rows, &cols);

    //create the universes
    Universe *u = uv_create(rows, cols, toroidal);

    Universe *u2 = uv_create(rows, cols, toroidal);

    //populate matrix with file, if a pair of numbers in the file is invalid, error
    if (uv_populate(u, file) == false) {

        printf("Malformed Input\n");
        return 1;
    }

    //loop through generations
    for (uint32_t i = 0; i < g; i++) {

        //if screen is toggled
        if (screen == true) {

            initscr();

            curs_set(FALSE);

            clear();

            //loop through cells
            //must use uv_rows() not u->rows
            for (uint32_t j = 0; j < uv_rows(u); j++) {

                for (uint32_t k = 0; k < uv_cols(u); k++) {

                    //if the cell is alive print an o, else, a space
                    if (uv_get_cell(u, j, k) == true) {

                        mvprintw(j, k, "o");

                    } else {

                        mvprintw(j, k, " ");
                    }
                }
            }

            //refresh and sleep
            refresh();

            usleep(50000);
        }
        //run the census and kill/revive cells accordingly
        for (uint32_t l = 0; l < uv_rows(u); l++) {

            for (uint32_t m = 0; m < uv_cols(u); m++) {

                //has 2 or three neighbors, then survives
                if (uv_get_cell(u, l, m) == true
                    && (uv_census(u, l, m) == 3 || uv_census(u, l, m) == 2)) {

                    uv_live_cell(u2, l, m);

                    //dead but has 3 neighbors, revives
                } else if (uv_get_cell(u, l, m) == false && uv_census(u, l, m) == 3) {

                    uv_live_cell(u2, l, m);

                    //live, but has too many/too little neighbors, dies
                } else {

                    uv_dead_cell(u2, l, m);
                }
            }
        }
        //swap universes
        Universe *temp = u;

        u = u2;

        u2 = temp;
    }
    //end
    if (screen == true) {

        endwin();
    }
    //print
    uv_print(u, out);

    //free and close
    uv_delete(u);
    uv_delete(u2);
    fclose(file);
    fclose(out);

    return 0;
}
