/*
 Name : Manos Chatzakis
 AM   : 4238
 eMail: csd4238@csd.uoc.gr
 File : sudoku.c
 This file contains the implementation of sudoku.h
 library.
*/

#include "sudoku.h"

/* Read a sudoku grid from stdin and return an object Grid_T
   initialized to these values. The input has the format:

1 2 3 4 5 6 7 8 9
4 5 6 7 8 9 1 2 3
7 8 9 1 2 3 4 5 6
2 3 4 5 6 7 8 9 1
5 6 7 8 9 1 2 3 4
8 9 1 2 3 4 5 6 7
3 4 5 6 7 8 9 1 2
6 7 8 9 1 2 3 4 5
9 1 2 3 4 5 6 7 8

   Each number is followed by a space. Each line is terminated with
   \n. Values of 0 indicate empty grid cells.
*/
Grid_T sudoku_read(void){

    Grid_T newGrid;

    int val;

    int indexROW = 0;
    int indexCOL = 0;

    /*Read the first 81 numbers*/
    while( (scanf("%d",&val)) != EOF ){

        if(val != ' ' && val != '\n'){

            assert(val >=0 && val <= 9);

            newGrid.elts[indexROW][indexCOL].val = val;
            indexCOL++;
        }
        if(indexCOL == 9){
            indexROW = indexROW + 1;
            indexCOL = 0;
        }
        if(indexROW == 9){
            break;
        }
    }

    return newGrid;
}

/* Print all row, col, sub-grid errors/conflicts found in puzzle g;
   some errors may be reported more than once. */
void sudoku_print_errors(Grid_T g){

    int i,j,val;

    /*Iterating the grid to detect input errors (excluding empty spaces)*/
    for(i = 0; i < 9; i++){
        for(j = 0; j<9; j++){
            val = grid_read_value(g,i,j);
            if(val != 0 && !(grid_choice_is_valid(g,i,j,val))){
                printf("Duplicate error at cell (%d,%d) of the grid\n",(i+1),(j+1));
            }
        }
    }   
}

/* Searches for errors(duplicates), excluding cells with no value. */
int sudoku_is_solvable(Grid_T g){
    
    int i,j,val;

    for(i = 0; i < 9; i++){
        for(j = 0; j<9; j++){
            val = grid_read_value(g,i,j);
            if(val != 0 && !(grid_choice_is_valid(g,i,j,val))){
                return 0;
            }
        }
    }   

    return 1;
}

/* Return true iff puzzle g is correct. */
int sudoku_is_correct(Grid_T g){

    int i;
    int j;
    int val;

    for(i = 0; i < 9; i++){
        for(j = 0; j<9; j++){
            val = grid_read_value(g,i,j);
            if(val == 0){
                return 0;
            }
            else if(!(grid_choice_is_valid(g,i,j,val))){
                return 0;
            }
        }
    }   
    return 1;
}

/* Finds and initializes every possible choice for every empty cell of grid g. */
static void sudoku_init_choices(Grid_T *g){

    int i, j, n, val;

    for(i = 0; i<9; i++){
        for(j = 0; j<9; j++){
            
            grid_clear_choice(g,i,j,0); /*Zero is not a choice*/
            grid_clear_count(g,i,j); /*Counts are initializes to 0 at the beggining*/

            val = (g->elts[i][j]).val;
            
            /*If the cell is empty, detect the possible choices*/
            if(val == 0){
                for(n = 1; n<10; n++){
                    if(grid_choice_is_valid(*g,i,j,n)){
                        grid_set_choice(g,i,j,n);
                    }
                    else{
                        grid_clear_choice(g,i,j,n);
                    }
                }
            }
            /*Else clear all the fields*/
            else{

                for(n=0; n<10; n++){
                    /*Delete every choice for non empty cells*/
                    grid_clear_choice(g,i,j,n);
                }
            }
        }
    }
    return;
}

/* Returns true if solution g, as returned by sudoku_solve, has a
   unique choice for each step (no backtracking required). (Note, g
   must have been computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g){
    
    int i,j;

    for(i=0; i<9; i++){
        for(j = 0; j<9; j++){
            if(grid_read_count(g,i,j) != 0){
                return 0;
            }
        }
    }

    return 1;
}

/* Returns true iff grid h has at least one empty cell 
   with just one possible choice. */
int sudoku_has_unique_cell(Grid_T g){
    
    int i,j;
    
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(grid_read_count(g,i,j) == 1){
                return 1;
            }
        }
    }

    return 0;
}

/* Returns true if grid g has empty cells. */
int sudoku_has_empty_cells(Grid_T g){
    
    int i,j;

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            if(grid_read_value(g,i,j) == 0) return 1;
        }
    }

    return 0;
}

/* Returns a (randomly picked) solution for an empty cell of grid g.
   Priority for filling the cells are the ones that have just one 
   possible choice (To avoid non neccessary backtracking). */
static int sudoku_try_next(Grid_T g, int *row, int *col){
    
    int k,val,ch;
    int tmpR, tmpC, tmpV;
    int isFirst = 1;
    srand(getpid());

    /*Check if grid has an empty cell with just one choice*/
    if(sudoku_has_unique_cell(g)){
        
        /*Find the coordinates of the cell*/
        for(*row = 0; *row<9; (*row)++){
            for(*col=0; *col<9; (*col)++){

                val = grid_read_value(g,*row,*col);
                ch  = grid_read_count(g,*row,*col);
                
                if( (val == 0) && (ch == 1) ){
                    
                    for(k=1; k<10; k++){
                        if(g.elts[*row][*col].choices.num[k] == 1) return k;
                    }

                    return 0;
                }
            }
        }
    }

    else{
        for(*row = 0; *row<9; (*row)++){
            for(*col=0; *col<9; (*col)++){
                    
                val = grid_read_value(g,*row,*col);
                
                /*Return a possible choice*/
                if(val == 0){
                
                    /*for(k=1; k<10; k++){
                        //if(grid_choice_is_valid(g,*row,*col,k)) return k;
                        if(g.elts[*row][*col].choices.num[k] == 1) return k;
                   }*/

                    /*If the cell is empty, temporarily store its possible choices count*/

                    if(grid_read_count(g,*row,*col) == 0) return 0;

                    if(isFirst){
                        isFirst = 0;
                        tmpR = *row;
                        tmpC = *col;
                        tmpV = grid_read_count(g,*row,*col);
                    }
                    /*Seeking the empty cell with less possible moves*/
                    else{
                        if(grid_read_count(g,*row,*col) < tmpV){
                            tmpR = *row;
                            tmpC = *col;
                            tmpV = grid_read_count(g,*row,*col);
                        }
                    }
                }
            }
        }

        /*Returning a possible choice for the empty cell with less possible moves*/
        *row = tmpR;
        *col = tmpC;

        k = rand()%10;
                    
        while(g.elts[*row][*col].choices.num[k] == 0){
            k = rand()%10;
        }
                
        return k;

    }
    
    return 0;
}

/* Updates the current value of cell (i,j) of the grid g.
   After the value is updated, the choice is removed from the possible choices,
   and the number of the possible choices left is returned. */
static int sudoku_update_choice(Grid_T *g, int i, int j, int n){
    
    /*Update the value and remove it from the possible choices*/
    grid_update_value(g,i,j,n);
    grid_remove_choice(g,i,j,n);

    return grid_read_count(*g,i,j);
}

/* Removes the choice n from the possible choices of empty cells
   of row i, column n and assossiated box, excluding the cell with 
   coordinates (i,j). */
static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n){
    
    int index,index_c,val;
    
    int R = 3 * (r/3);
    int C = 3 * (c/3);

    /*Eliminate the same choice from the row*/
    for(index = 0; index<9; index++){
        val = (g->elts[r][index]).val;
        if(val == 0 && index != c){
            grid_remove_choice(g,r,index,n);
        }
    }

    /*Eliminate the same choice from the column*/
    for(index = 0; index<9; index++){
        val = (g->elts[index][c]).val;
        if(val == 0 && index != r){
            grid_remove_choice(g,index,c,n);
        }
    }

    /*ELiminate the row from the subgrid*/
    for(index = R; index<R+3; index++){
        for(index_c = C; index_c<C+3; index_c++){
            val = (g->elts[index][index_c]).val;

            if(index == r && index_c == c){
                continue;
            }

            if(val == 0){
                grid_remove_choice(g,index,index_c,n);
            }
        }
    }

    return;
}

/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T g){

    /*A temporary grid to examine the possible solutions*/
    Grid_T fulGrid;

    /*Grid coordinates*/
    int n,row,col;

    /*Find the possible choices for every empty cell of the puzzle*/
    sudoku_init_choices(&g);

    /*Initialize the temporaty grid*/
    fulGrid = g; /*Assignment works for structs*/

    /*Try to solve the puzzle while the grid has empty cells with possible choices*/
    while( (sudoku_has_empty_cells(g)) && ((n = sudoku_try_next(g,&row,&col)) != 0) ){

        /*When the flow reaches here, it means that that a possible choice for the
          cell (i,j) is returned*/

        /*The new choice will be applied temporarily to our official grid.
          If the puzzle with this choice is unsolvable, the value of the cell
          (i,j) is deleted and we try again*/
        if(sudoku_update_choice(&g,row,col,n) == 0){

            /*If the choice returned is the only possible choice for the current
            empty cell, is should be removed from the empty spaces of the same row, col, and box*/
            sudoku_eliminate_choice(&g,row,col,n);
            
        }
        /*If the cell has multiple possible moves, backtrack may be needed.*/
        else{

            /*As backtrack may be needed, we dont have unique choice solution*/
            grid_clear_unique(&g);

            /*Assign the current g version to temporary grid*/
            fulGrid = g;

            /*Solve the puzzle recursively*/
            fulGrid = sudoku_solve(fulGrid); /* = sudoku_solve(g)*/

            /*Return the grid if solved. (This will terminate recursion) */
            if(sudoku_is_correct(fulGrid)) { 
                return fulGrid;
            }

            /*Set the value 0 to try the next possible choice*/
            grid_update_value(&g,row,col,0);
        }   
    }

    /*Retutn the grid, solved or unsolved*/
    return g;

}

/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read().
   In case the output has to be in console, arg should be stderr. */
void sudoku_print(FILE *s, Grid_T g){
    
    int indexROW,indexCOL,val;

    for(indexROW = 0; indexROW < 9; indexROW++){
        
        for(indexCOL = 0; indexCOL < 9; indexCOL++){
            val = g.elts[indexROW][indexCOL].val;
            fprintf(s,"%d ",val);
        }
        fputc('\n',s);
    }

    return;
}

/* Returns an empty grid. */
Grid_T sudoku_generate_empty(void){
    
    int i,j,k;

    Grid_T g;

    grid_set_unique(&g);

    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            
            grid_clear_count(&g,i,j);
            grid_update_value(&g,i,j,0);

            for(k=0; k<10; k++){
                grid_clear_choice(&g,i,j,k);
            }

        }
    }

    return g;
}

/* Generates a fixed and solved grid. */
Grid_T sudoku_generate_fixed(void){

    Grid_T g = sudoku_generate_empty();

    int i,j,count;

    int puzzle[] = {1,2,6,4,5,3,8,7,9,
                    5,7,9,2,8,6,1,3,4,
                    3,4,8,1,7,9,5,2,6,
                    7,5,1,9,4,8,3,6,2,
                    6,3,2,7,1,5,4,9,8,
                    9,8,4,6,3,2,7,5,1,
                    4,6,5,3,2,1,9,8,7,
                    2,1,3,8,9,7,6,4,5,
                    8,9,7,5,6,4,2,1,3 };

    count = 0;

    for(i = 0; i<9; i++){
        for(j=0; j<9; j++){
            grid_update_value(&g,i,j,puzzle[count]);
            count++;
        }
    }

    return g;

}

/* Generates a filled grid using try_next */
static Grid_T sudoku_generate_complete(void){
    
    int row,col,count,n;

    Grid_T genGrid = sudoku_generate_empty();
    Grid_T tmpGrid = sudoku_generate_empty();
    Grid_T fixGrid = sudoku_generate_fixed();

    sudoku_init_choices(&genGrid);

    count = 0;

    grid_set_unique(&genGrid);
    grid_set_unique(&fixGrid);

    /*Generate a complete puzzle*/
    while( (n = sudoku_try_next(genGrid,&row,&col)) != 0 ){
        
        if(sudoku_update_choice(&genGrid,row,col,n) == 0){
            sudoku_eliminate_choice(&genGrid,row,col,n);
        }
        else{
            tmpGrid = sudoku_solve(genGrid);
            if(sudoku_is_correct(tmpGrid)) { return tmpGrid; }
            grid_update_value(&genGrid,row,col,0);
        }
        
        count++;
        if(count == 10){
            return fixGrid;
        }
    }

    return genGrid;
}

/* Generate and return a sudoku puzzle with "approximately" nelts
   elements having non-0 value. The smaller nelts the harder may be to
   generate/solve the puzzle. For instance, nelts=81 should return a
   completed and correct puzzle. */
Grid_T sudoku_generate(int nelts){
    
    int count,row,col,n;

    int elts = 81 - nelts;
    
    Grid_T g = sudoku_generate_complete();
    Grid_T tmp = sudoku_generate_empty();

    srand(getpid());

    row = rand()%9;
    col = rand()%9;

    count = 0;

    /*Till the desired empty cells are created*/
    while(count<elts){

        if((n = grid_read_value(g,row,col)) != 0){
                
                grid_update_value(&g,row,col,0);

                tmp = sudoku_solve(g);

                /*If the solution is unique, procceed to the next random cell*/ 
                if(sudoku_is_correct(tmp) && sudoku_solution_is_unique(tmp)){
                    count++;
                }
                else{
                    grid_update_value(&g,row,col,n);
                }

        }

        row = rand()%9;
        col = rand()%9;
    }

    return g;

}

/* Generate an new puzzle with nelts, without using sudoku_solve
   to check if the output has unique choice solution. */
Grid_T sudoku_generate_simple(int nelts){
    
    int count,row,col;
    int elts = 81 - nelts;
    
    Grid_T g = sudoku_generate_complete();

    srand(getpid());

    row = rand()%9;
    col = rand()%9;

    count = 0;

    while(count<elts){
        
        if(grid_read_value(g,row,col) != 0){
            grid_update_value(&g,row,col,0);
            count++;
        }

        row = rand()%9;
        col = rand()%9;
    }
    

    return g;
}

/* Prints the errors of a filled input grid. */
void sudoku_print_all_errors(Grid_T g){
   
    int i,j,val;
    
    for(i = 0; i < 9; i++){
        for(j = 0; j<9; j++){

            val = grid_read_value(g,i,j);
            
            if(val == 0){
                printf("Cell (%d,%d) is empty.\n",(i+1),(j+1));
            }

            else if(!(grid_choice_is_valid(g,i,j,val))){
                printf("Cell (%d,%d) is invalid.\n",(i+1),(j+1));
            }

        }
    }
}

/* Prints the check outcome for a filled grid g. */
void sudoku_print_check(FILE *s,Grid_T g){
    
    if(sudoku_is_correct(g)){
            fprintf(s,"Puzzle is correct\n");
        }
        else{
            fprintf(s,"Puzzle is not correct:\n");
            sudoku_print_all_errors(g);
        }
    
}

/* Argc is the number of arguments. Argv is the array of arguments. */
int main(int argc, char *argv[]){
    
    Grid_T g;

    int nelts;

    /*Default choice is puzzle solution*/
    if(argc == 1){
        
        /*Take the input*/
        g = sudoku_read();
        
        /*Print the input to console*/
        sudoku_print(stderr,g);
        
        /*If it has errors, return*/
        if(!sudoku_is_solvable(g)){
            sudoku_print_errors(g);
            return 0;
        }

        /*Initialize the choices for the empty spaces*/
        sudoku_init_choices(&g);

        /*Defaulty assume the solution is unique*/
        grid_set_unique(&g);
        
        /*Solve or try to solve the sudoku*/
        g = sudoku_solve(g);

         /*If solution is correct print the output*/
        if(sudoku_is_correct(g)){
            fprintf(stderr,"Puzzle has a ");
            if(grid_read_unique(g)){
               fprintf(stderr,"(unique choice) ");
            }
            fprintf(stderr,"solution:\n");
        }
        else{
            fprintf(stderr,"Puzzle has not solution:\n");
        }

        /*Print the outcome*/
        sudoku_print(stderr,g);
        
    }
    /*Arg -c indicates puzzle check*/
    else if(argc == 2 && strcmp(argv[1],"-c") == 0){
        
        /*Take the input*/
        g = sudoku_read();

        /*Print the input puzzle*/
        sudoku_print(stderr,g);

        /*Print if input is correct or not*/
        sudoku_print_check(stderr,g);
    }
    /*Arg -g generates puzzles*/
    else if(argc >= 2 && strcmp(argv[1],"-g") == 0){

        /*Generate a (non urgently unique) puzzle*/
        if(argc == 3){
            nelts = atoi(argv[2]);
            assert(nelts>=0 && nelts<=81);
            g = sudoku_generate_simple(nelts);    
        }
        /*Generate a unique choice solution puzzle. If nelts is too small,
          unexpected behavior will occur*/
        else if(argc == 4 && (strcmp(argv[3],"-u") == 0)){
            nelts = atoi(argv[2]);
            /*if(nelts < 70) nelts = 70*/
            assert(nelts>=0 && nelts<=81);
            g = sudoku_generate(nelts);
        }
        else{
            fprintf(stderr,"Wrong command line input for generate.\n");
            return 0;
        }
    
        fprintf(stderr,"New Puzzle:\n");
        sudoku_print(stderr,g);

    }else{
        fprintf(stderr,"Wrong command line input.\n");
    }

    return 0;
}
