#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char    pre[] = "| ";
char    post[] = " |";
char    horizontalLine[] = "---------------------------\n";
int     countLines = 1;
char    saveGameNumbers[9][9];
int     tries = 0;
int     errors = 0;
int     problem1, error2, error3, error4 = 0;
char    buildstack[90][9][9];
int     frame = 0; //counter for the buildstack
int     emptyFields = 81;

void putCurrentGameOnStack(){ //puts the current game on the stack
    for(int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
        {
            buildstack[frame][i][j] = saveGameNumbers[i][j];
        }
        
    }
}

void revertToFrame(int Frame){ //reverts the game back to the given frame, pulls the data from the buildstack
    frame = Frame;
    for(int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++)
        {
            saveGameNumbers[i][j] = buildstack[frame][i][j];
        }
    }
}

void generateField1x9(int row){
    printf("%d %s", row, pre); //puts the forthermost part of the gamefield down
    for(int i = 0; i < 9; i++){
        for(int j = 1; j < 4; j++){
            printf("%c ", saveGameNumbers[row-1][(j+i)-1]); //puts down the 3 fields
        }
        printf("| "); //seperator between the fields
        i++;
        i++;
    }
    putchar('\n'); 
}


void prepareGamefield(){ //fills the array savedGameNumbers with the char '0'
    int count = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            saveGameNumbers[i][j] = '0';
            count++;
        }
    }
}

void buildField(){
    printf("    a b c   d e f   g h i\n"); //the letters for the columns
    printf  ("%s", horizontalLine); //the seperator line
    for(int i = 1; i < 10; i++){
        generateField1x9(i);
        if((i%3) == 0){
            printf  ("%s", horizontalLine); //seperator line in between
        }
    }

}

int fieldEmpty(int row, int column){ // 0 if empty, 1 if not
    if(saveGameNumbers[row][column] == '0'){
        return 0;
    }
    else{
        return 1;
    }
}

int rowOK(int row, int input){  //0 if ok, 1 if not
    for(int i = 0; i < 9; i++){
        if(saveGameNumbers[row][i] == input+'0'){
            return 1;
        }
    }
    return 0;
}

int columnOK(int column, int input){  //0 if ok, 1 if not
    for(int i = 0; i < 9; i++){
        if(saveGameNumbers[i][column] == input+'0'){
            return 1;
        }
    }
    return 0;
}

int findRowBig(int row){  //0 for first block, 3 for seckond, 6 for third
    int modifyRow = 0;
    switch (row)
    {
    case 0:
    case 1:
    case 2:
        modifyRow = 0;
        break;
    case 3:
    case 4:
    case 5:
        modifyRow = 3;
        break;
    case 6:
    case 7:
    case 8:
        modifyRow = 6;
        break;
    default:
        break;
    }
    return modifyRow;
}

int findColumnBig(int column){ //0 for first block, 3 for seckond, 6 for third
    int modifyCollumn = 0;
    switch (column)
    {
    case 0:
    case 1:
    case 2:
        modifyCollumn = 0;
        break;
    case 3:
    case 4:
    case 5:
        modifyCollumn = 3;
        break;
    case 6:
    case 7:
    case 8:
        modifyCollumn = 6;
        break;
    default:
        break;
    }
    return modifyCollumn;
}

int blockOK(int row, int column, int input){ //0 if ok, 1 if not
    int bigrow = findRowBig(row);
    int bigcolumn = findColumnBig(column);
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(saveGameNumbers[i+bigrow][j+bigcolumn] == input+'0'){
                return 1;
            }
        }
    }
    return 0;
}

int numberInsertable(int row, int column, int input){ //0 if yes, 1 if field not empty, 2 if row problem, 3 if column problem, 4 if block problem
    row--;
    column--;
    if(fieldEmpty(row, column) == 1){
        problem1++;
        return 1;
    }

    if(rowOK(row, input) == 1){
        error2++;
        return 2;
    }

    if(columnOK(column, input) == 1){
        error3++;
        return 3;
    }

    if(blockOK(row, column, input) == 1){
        error4++;
        return 4;
    }

    return 0;
}

void insertNumber(int row, int column, int input){
    if(emptyFields > 0){
        if(numberInsertable(row, column, input) == 0){
            saveGameNumbers[row-1][column-1] = input+'0';
            frame++;
            putCurrentGameOnStack();
            emptyFields--;
        }
        else{
            printf("Error code %d\n", numberInsertable(row, column, input));
            errors++;
        }
    }   
}

void insertRandom(){

    int rRow = (rand() % 9) +1;
    int rColumn = (rand() % 9) +1;
    int rInput = (rand() % 9) +1;
    insertNumber(rRow, rColumn, rInput);
    tries++;
}

void main(){
    srand(time(NULL));
    prepareGamefield();
    for(int i = 0; i < 20000; i++){
        insertRandom();
    }
    buildField();
    printf("Tries: %d\n", tries);
    printf("Errors: %d\n", errors);
    printf("Empty fields: %d\n", emptyFields);
    printf("Davon %d Feld schon belegt \n%d reihe hat schon die zahl \n%d spalte hat schon die Zahl \n%d kasten hat schon die zahl\n", problem1, error2, error3, error4);
}