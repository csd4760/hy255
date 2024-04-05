#include "sudoku.h"
#include "grid.h"
#include <assert.h>

Grid_T sudoku_read(void){
    int i, j, n, choice;
    Grid_T g;
    for (i=0; i<9; i++){
        for (j=0; j<9; j++){
            scanf("%d", &n);
            grid_update_value(&g, i, j, n);
            if(grid_read_value(g, i, j) == 0){
                for ( choice = 1; choice < 10; choice++){
                    grid_set_choice(&g, i, j, choice);
                }
                grid_set_count(&g, i, j);
            }
        }
    }
    return g;
}

/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g){
    assert(s!=NULL);
    int i, j;
    for (i=0; i<9; i++){
        for (j=0; j<9; j++){
            fprintf(s, "%d ", g.elts[i][j]);
        }
        fprintf(s, "\n");
    }
}

int checkonerow(Grid_T g, int i){
    int j, k;
    for(j=0; j<9; j++){
        for(k=0; k<9; k++){
            if(grid_read_value(g, i, j) == grid_read_value(g, k, j) && grid_read_value(g, k, j) !=0){
                printf("Conflict found in row %d and collumn %d", k, j);
                return k;
            }
        }
    }
    return 0;
}

int checkrows(Grid_T g){
    int i, flag = 0;
    for(i=0; i<9; i++){
        if(checkonerow(g, i) != 0){
            flag = 1;
        }
    }
    if(flag == 1){
        return 1;
    }
    return 0;
}
/*na kanw antistoixa me to check rows kai ta alla*/

void checkcol(Grid_T g){
    int i, j, k;
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            for(k=0; k<9; k++){
                if(grid_read_value(g, i, j) == grid_read_value(g, i, k)){
                    printf("Error:\n Invalid collumn: %d", j);
                }
            }
        }
    }
    return 0;
}

void checkbox(Grid_T g){
    int i, j, k, l, m, n;
    for(i=0; i<9; i=i+3){
        for(j=0; j<9; j=j+3){
            for(k=i; k<3+i; k++){
                for(l=j; l<3+j; j++){
                    for(m=i; m<3+i; m++){
                        for(n=j; n<3+j; n++){
                            if(grid_read_value(g, k, l) == grid_read_value(g, m, n)){
                                printf("Error:\n Invalid box: %d", i);
                            }
                        }
                    }
                }
            }
        }
    }
}
/*na valw na kanie ola ta print sthn void*/

/* Print all row, col, sub-grid errors/conflicts found in puzzle g;
   some errors may be reported more than once. */
void sudoku_print_errors(Grid_T g){
    if( checkrows(g)== 0 && checkcol(g)==0 && checkbox(g)==0){
        printf("Sudoku is correct!\n");
    }
}

int checksudoku(Grid_T g){
    int i,j,k;

    for (i = 0; i < 9; i++){
        for (j = 0; j < 9; j++)
        {
            if (grid_read_value(g, i, j) == 0)
            {
                for (k = 1; k < 10; k++)
                {
                    grid_update_value(&g, i, j, k);
                    if (!sudoku_is_correct(g))
                    {
                        grid_remove_choice(&g, i, j, k);
                    }
                } 
                grid_update_value(&g, i, j, 0);
            }
            
        }
        
    }
}

/* Return true iff puzzle g is correct. */
int sudoku_is_correct(Grid_T g){
    int i, j, n;
    checksudoku(g);
}

int find_zero(Grid_T g, int i){
    int j;
    for (j = 0; j < 9; j++){
        if (grid_read_value(g, i, j) == 0){
            return j;
        }
    }
    return 0;
}
    
int sudoku_update(Grid_T *g){
    int i, j = 0, k, choice;
    for (i = 0; i < 9; i++){
        j = find_zero(g, i);
        if(j!=0){
            break;
        }
    }
    if(i == 9){
        return 0;
    }
    if(grid_read_count( g,  i,  j)== 0){
        return -1;
    }
    for(k =1; k<10; k++){
        if(grid_choice_is_valid( g,  i,  j,  k) == 1){
            choice = k;
            break;
        }
    }
    grid_update_value(&g, i, j, k);
    sudoku_update(g);
}


/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T g){

}

/* Returns true if solution g, as returned by sudoku_solve, has a
   unique choice for each step (no backtracking required). (Note, g
   must have been computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g){
    return grid_read_unique(g);
}

/* Generate and return a sudoku puzzle with "approximately" nelts
   elements having non-0 value. The smaller nelts the harder may be to
   generate/solve the puzzle. For instance, nelts=81 should return a
   completed and correct puzzle. If unique=1 the puzzle must have a
   unique choice at each step of finding the solution. */
Grid_T sudoku_generate(int nelts, int unique);