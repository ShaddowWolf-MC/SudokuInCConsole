#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char    pre[] = "| ";
char    post[] = " |";
char    horizontalLine[] = "---------------------------\n";
int     countLines = 1;
char    saveGameNumbers[9][9];


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
    int modifyRow;
    switch (row)
    {
    case 1:
    case 2:
    case 3:
        modifyRow = 0;
        break;
    case 4:
    case 5:
    case 6:
        modifyRow = 3;
        break;
    case 7:
    case 8:
    case 9:
        modifyRow = 6;
    default:
        break;
    }
    return modifyRow;
}

int findColumnBig(int column){ //0 for first block, 3 for seckond, 6 for third
    int modifyCollumn;
    switch (column)
    {
    case 1:
    case 2:
    case 3:
        modifyCollumn = 0;
        break;
    case 4:
    case 5:
    case 6:
        modifyCollumn = 3;
        break;
    case 7:
    case 8:
    case 9:
        modifyCollumn = 6;
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
        return 1;
    }

    if(rowOK(row, input) == 1){
        return 2;
    }

    if(columnOK(column, input) == 1){
        return 3;
    }

    if(blockOK(row, column, input) == 1){
        return 4;
    }

    return 0;
}

void insertNumber(int row, int column, int input){
    saveGameNumbers[row-1][column-1] = input+'0';
}


void main(){
    prepareGamefield();
    if(numberInsertable(5, 5, 5) == 0){
        insertNumber(5, 5, 5);
    }
    buildField();
}