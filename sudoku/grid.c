/*
 Name : Manos Chatzakis
 AM   : 4238
 eMail: csd4238@csd.uoc.gr
 File : grid.c
 This file contains the implementation of grid.h
 library.
*/

#include "grid.h"

/* update value of i,j to n */
void grid_update_value(Grid_T *g, int i, int j, int n){
    (g->elts[i][j]).val = n;
}

/* return value of i,j */
int grid_read_value(Grid_T g, int i, int j){
    return g.elts[i][j].val;
}

/* set (to 1) or clear (to 0) choice n for elt i,j */
void grid_set_choice(Grid_T *g, int i, int j, int n){
    (g->elts[i][j]).choices.count++;
    (g->elts[i][j]).choices.num[n] = 1;
}
void grid_clear_choice(Grid_T *g, int i, int j, int n){
    /*(g->elts[i][j]).choices.count--;*/
    (g->elts[i][j]).choices.num[n] = 0;
}

/* true if choice n for elt i,j is valid */
int grid_choice_is_valid(Grid_T g, int i, int j, int n){
    
    int index;
    int index_c;

    int R = 3 * (i/3);
    int C = 3 * (j/3);

    /*Check the row*/
    for(index = 0; index<9; index++){
        if(g.elts[i][index].val == n && index!=j){
            return 0;
        }
    }

    /*Check the column*/
    for(index = 0; index<9; index++){
        if(g.elts[index][j].val == n && index!=i){
            return 0;
        }
    }

    /*Check the subgrid*/
    for(index = R; index<R+3; index++){
        for(index_c = C; index_c<C+3; index_c++){
            
            if(index == i && index_c == j){
                continue;
            }
            
            if(n == g.elts[index][index_c].val ){
                return 0;
            }
        }
    }
    
    return 1;
}
/* remove n from choices of elt i,j and adjust count only if n is a
   valid choice for elt i,j */
void grid_remove_choice(Grid_T *g, int i, int j, int n){
    /*if(grid_choice_is_valid(*g,i,j,n)){*/
    if((g->elts[i][j]).choices.num[n] == 1){    
        (g->elts[i][j]).choices.num[n] = 0;
        (g->elts[i][j]).choices.count--;
    }
}

/* return count, set (to 9), or clear (to 0) count for elt i, j */
int grid_read_count(Grid_T g, int i, int j){
    return g.elts[i][j].choices.count;
}
void grid_set_count(Grid_T *g, int i, int j){
    (g->elts[i][j]).choices.count = 9;
}
void grid_clear_count(Grid_T *g, int i, int j){
    (g->elts[i][j]).choices.count = 0;
}

/* return val, set (to 1), or clear (to 0) unique flag for g */
int grid_read_unique(Grid_T g){
    return g.unique;
}
void grid_set_unique(Grid_T *g){
    g->unique = 1;
}
void grid_clear_unique(Grid_T *g){
    g->unique = 0;
}
