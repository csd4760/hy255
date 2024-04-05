#include "grid.h"
#include <assert.h>

/* update value of i,j to n */
void grid_update_value(Grid_T *g, int i, int j, int n){
    assert(g);
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);
    assert(n>-1 && n<=9);
    g->elts[i][j].val = n;
}
/* return value of i,j */
int grid_read_value(Grid_T g, int i, int j){
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);
    return g.elts[i][j].val;
}

/* set (to 1) or clear (to 0) choice n for elt i,j */
void grid_set_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);
    assert(n>-1 && n<=9);

    g->elts[i][j].choices.num[n] = 1;    
}
void grid_clear_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);
    assert(n>-1 && n<=9);

    g->elts[i][j].choices.num[n] = 0;
}
/* true if choice n for elt i,j is valid */
int grid_choice_is_valid(Grid_T g, int i, int j, int n){
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);
    assert(n>-1 && n<=9);

    return g.elts[i][j].choices.num[n];
}
/* remove n from choices of elt i,j and adjust count only if n is a
   valid choice for elt i,j */
void grid_remove_choice(Grid_T *g, int i, int j, int n){
    assert(g);
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);
    assert(n>-1 && n<=9);

    if(grid_choice_is_valid(*g, i, j, n)){
        g->elts[i][j].choices.count--;
    }
    grid_clear_choice(g, i, j, n);
}

/* return count, set (to 9), or clear (to 0) count for elt i, j */
int grid_read_count(Grid_T g, int i, int j){
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);
    
    return g.elts[i][j].choices.count;
}
void grid_set_count(Grid_T *g, int i, int j){
    assert(g);
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);

    g->elts[i][j].choices.count = 9;
}
void grid_clear_count(Grid_T *g, int i, int j){
    assert(g);
    assert(i>-1 && i<9);
    assert(j>-1 && j<9);

    g->elts[i][j].choices.count = 0;
}

/* return val, set (to 1), or clear (to 0) unique flag for g */
int grid_read_unique(Grid_T g){
    return  g.unique;
}
void grid_set_unique(Grid_T *g){
    assert(g);

        g->unique = 1;
}
void grid_clear_unique(Grid_T *g){
    assert(g);
    
    g->unique = 0;
}
