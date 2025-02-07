#include<stdio.h>

char pre[] = "| ";
char post[] = " |";
char horizontalLine[] = "---------------------------\n";
int countLines = 1;
char saveGameNumbers[9][9];
char lenghtCheck[9];
char fieldCheck[3][3];
char usedNumbers[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};


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

void fillArrayWithHash(){
    int count = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            saveGameNumbers[i][j] = '#';
            count++;
        }
    }
}

void resetUsedNumbers(){
    for (int i = 0; i < 10; i++)
    {
        usedNumbers[i] = '0';
    }    
}


void printTopLine(){
    printf("    a b c   d e f   g h i\n");
}

void printSeperatorLine(){
    printf  ("%s", horizontalLine);
}

void buildField(){
    printTopLine();
    printSeperatorLine();
    for(int i = 1; i < 10; i++){
        generateField1x9(i);
        if((i%3) == 0){
            printSeperatorLine();
        }
    }

}

int checkIfNumberIsAllowedColumn(int input, int column){ //returns -1 if number cannot be placed at this position because it has been used allready, 
                                                            // -2 if there are 2 of the same number in the field and 0 if it is ok

    //check first from top to bottom if number is there allready
    for(int i = 0; i < 9; i++){
        lenghtCheck[i] = saveGameNumbers[i][column]; //copy numbers in this column to the ckeck array
    }
    for(int i = 0; i < 9; i++){
        if(lenghtCheck[i] != '#'){ //check if the Number at this place is still a '#'
            if(usedNumbers[lenghtCheck[i]-48] == '1'){ //if not, check if the number was allready used once in this column
                return -2; //if it was used allready, return that this number cannot be used in this position
            }
            else{
                usedNumbers[lenghtCheck[i]-48] = '1'; //if it has not been used in this collum, continue the ckeck, write that it has been used and continue the ckeck
            }
        }
    }
    if(usedNumbers[input] == '1'){  //if the proposed Number, either by program or by user, has been used in the collum already, reset the used numbers list, then return -1 
                                    // as unusable number
        resetUsedNumbers();
        return -1;
    }
    else if(usedNumbers[input] == '0'){//if the number has not been used, return 0 as sucessfull for continuing checks
        resetUsedNumbers();
        return 0;
    }
    else{
        return usedNumbers[input];
    }
}

int checkIfNumberIsAllowedRow(int input, int row){ //-1 is number is used allready, -2 is double number in playing field error, 0 is ok
    //now from left to right
    for(int i = 0; i < 9; i++){
        lenghtCheck[i] = saveGameNumbers[row][i]; //copy the numbers to the check array again
    }
    for(int i = 0; i < 9; i++){
        if(lenghtCheck[i] != '#'){ //check if the Number at this place is still a '#'
            if(usedNumbers[lenghtCheck[i]-48] == '1'){ //if not, check if the number was allready used once in this row
                return -2; //if it was used allready, return that this number cannot be used in this position
            }
            else{
                usedNumbers[lenghtCheck[i]-48] = '1'; //if it has not been used in this collum, note that it has been used now and continue to check
            }
        }
    }

    if(usedNumbers[input] == '1'){
        resetUsedNumbers();
        return -1;
    }
    else if(usedNumbers[input] == '0'){
        resetUsedNumbers();
        return 0;
    }
    else{
        return usedNumbers[input];
    }

}
int checkIfNumberIsAllowedGrid(int input, int row, int column){
    //now in the 3x3 grid
    //we need to know if it is in the bigger collumn 1, 2 or 3
    //and we need to know if it is in the bigger row 1, 2 or 3
    int modifyCollumn, modifyRow;

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

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; i++){
            fieldCheck[i][j] = saveGameNumbers[i+modifyRow][j+modifyCollumn]; //transfer the data from the game save to the check array
        }
    }


    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; i++){
            if(fieldCheck[i][j] != '#'){ //check if the char at position is not '#'
                if(usedNumbers[(fieldCheck[i][j])-48] == '0'){ //if it has not been used allready, continue
                    usedNumbers[fieldCheck[i][j]] = '1'; //put the info that this number has been used 
                }
                else if (usedNumbers[(fieldCheck[i][j])-48] == '1'){ //check if the number has been if it hasnt been not used
                    return -1; //return that this number cannot be used at this position
                }
                else{
                    printf("Something went wrong, this state should not be reachable. \n This means that in my check, something else then a number was written to the field.\n");
                    return -1;
                }
                
            }
        }
    }
    int count = 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            usedNumbers[count] = fieldCheck[i][j];
            count++;
        }
        
    }
    if(usedNumbers[input] == '1'){
        resetUsedNumbers();
        return -1;
    }
    else if(usedNumbers[input] == '0'){
        resetUsedNumbers();
        return 0;
    }
    else{
        return usedNumbers[input];
    }


    return 0;
    
}

void main(){
    fillArrayWithHash();
    buildField();
}


