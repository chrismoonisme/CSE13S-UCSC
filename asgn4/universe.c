#include "universe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//defines a universe struct
//universe is a matrix data type
struct Universe {
    //rows and columns
    uint32_t rows;
    uint32_t cols;
    //matrix
    bool **grid;
    //toroidal toggle
    bool toroidal;
};

//type constructor, returns a matrix
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {

    //allocate memory for the universe data structure
    Universe *universe = (Universe *) malloc(sizeof(Universe));

    //if memory allocation doesnt break
    if (universe) {

        //set value of toroidal;
        universe->toroidal = toroidal;

        //set rows and columns
        universe->rows = rows;
        universe->cols = cols;

        //set up empty matrix (grid)
        universe->grid = (bool **) calloc(rows, sizeof(bool *));
        for (uint32_t r = 0; r < rows; r++) {

            universe->grid[r] = (bool *) calloc(cols, sizeof(bool));
        }

        //return type
        return universe;

    } else {
        //if memory allocation breaks, free and nullify pointers
        free(universe);

        universe = NULL;

        return universe;
    }
}
//delete the universe
void uv_delete(Universe *u) {

    //free all inner arrays in the grid array
    for (uint32_t r = 0; r < u->rows; r++) {

        free(u->grid[r]);
    }

    //free the grid array
    free(u->grid);

    //free the pointer to the universe object and null
    free(u);

    u = NULL;
}

//return rows
uint32_t uv_rows(Universe *u) {

    return u->rows;
}

//return cols
uint32_t uv_cols(Universe *u) {

    return u->cols;
}

//sets the cell at r,c to alive
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {

    //if in bounds of the universe
    if (r <= u->rows && c <= u->cols) {

        u->grid[r][c] = true;
    }
}

//kill cell at r,c
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {

    //if in bounds of the universe
    if (r <= u->rows && c <= u->cols) {

        u->grid[r][c] = false;
    }
}

//return cell status at r,c
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {

    if (r <= u->rows && c <= u->cols) {
        return u->grid[r][c];
    }

    return false;
}

bool uv_populate(Universe *u, FILE *infile) {

    //track line of file
    int line = 0;

    //row/col
    int row;
    int col;

    //loop through the file
    while (!feof(infile)) {

        line++;

        if (line != 1) {

            //get the row/col val
            int error = fscanf(infile, "%d %d", &row, &col);

            //make sure it isnt the end of the file
            if (feof(infile) == true) {
                return true;
            }

            //if there are not two values or the values are outside the bounds, return false;
            if (error != 2 || row > u->rows || col > u->cols) {

                return false;
            }

            //set the cell at row, col to alive
            uv_live_cell(u, row, col);
        }
    }

    return true;
}

uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {

    //tracks live neighbors
    uint32_t n = 0;

    //dont wraparound if toroidal = false
    if (u->toroidal == false) {

        //start
        //u->grid[r][c]
        //left
        //u->grid[r-1][c]
        //right
        //u->grid[r+1][c]
        //up
        //u->grid[r][c+1]
        //down
        //u->grid[r][c-1]

        //check left, if r isnt in the leftmost column
        if (r > 0 && uv_get_cell(u, r - 1, c)) {

            n++;
        }
        //check right
        if (r < u->rows - 1 && uv_get_cell(u, r + 1, c)) {

            n++;
        }
        //up
        if (c < u->cols - 1 && uv_get_cell(u, r, c + 1)) {

            n++;
        }

        //down
        if (c > 0 && uv_get_cell(u, r, c - 1)) {

            n++;
        }

        //diagonals
        if (r > 0 && c > 0 && uv_get_cell(u, r - 1, c - 1)) {

            n++;
        }

        if (r < u->rows - 1 && c < u->cols - 1 && uv_get_cell(u, r + 1, c + 1)) {

            n++;
        }

        if (r > 0 && c < u->cols - 1 && uv_get_cell(u, r - 1, c + 1)) {

            n++;
        }

        if (r < u->rows - 1 && c > 0 && uv_get_cell(u, r + 1, c - 1)) {

            n++;
        }
        //if toroidal, loop around
    } else {

        //rows
        n += uv_get_cell(u, (r + 1) % u->rows, c);

        //cols
        n += uv_get_cell(u, r, (c + 1) % u->cols);

        //diagonals
        n += uv_get_cell(u, (r + 1) % u->rows, (c + 1) % uv_cols(u));

        //wraparound for rows
        if (r == 0) {

            n += uv_get_cell(u, u->rows - 1, c);

            n += uv_get_cell(u, u->rows - 1, (c + 1) % u->cols);

            //just do next
        } else if (r > 0) {

            n += uv_get_cell(u, r - 1, c);

            n += uv_get_cell(u, r - 1, (c + 1) % u->cols);
        }
        //wraparound for cols
        if (c == 0) {

            n += uv_get_cell(u, r, u->cols - 1);

            n += uv_get_cell(u, (r + 1) % u->rows, u->cols - 1);

            //normal
        } else if (c > 0) {

            n += uv_get_cell(u, r, c - 1);

            n += uv_get_cell(u, (r + 1) % u->rows, c - 1);
        }

        if (c == 0 && r == 0) {

            n += uv_get_cell(u, u->rows - 1, u->cols - 1);

        } else if (c == 0 && r > 0) {

            n += uv_get_cell(u, r - 1, u->cols - 1);

        } else if (c > 0 && r == 0) {

            n += uv_get_cell(u, u->rows - 1, c - 1);

        } else if (c > 0 && r > 0) {

            n += uv_get_cell(u, r - 1, c - 1);
        }
    }

    return n;
}

void uv_print(Universe *u, FILE *outfile) {

    for (uint32_t r = 0; r < u->rows; r++) {

        for (uint32_t c = 0; c < u->cols; c++) {

            if (uv_get_cell(u, r, c) == true) {
                fprintf(outfile, "o");
            } else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
}
