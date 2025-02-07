#include<stdio.h>
#include<stdlib.h>
#include<time.h>

char    pre[] = "| ";
char    post[] = " |";
char    horizontalLine[] = "---------------------------\n";
int     countLines = 1;
char    saveGameNumbers[9][9];
char    lenghtCheck[9];
char    fieldCheck[3][3];
char    usedNumbers[] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
char    input[] = "0 g 9";
char    columnInChar;
int     columnInInt;
int     rowIn;
int     numberIn;
int     emptyFields = 81;

//graphics section

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

//rule section

int checkIfAlreadyFilled(int row, int column){ //returns 0 if the field is empty, -1 if there is a number in it
    if(saveGameNumbers[row][column] == '#'){
        return 0;
    }
    else{
        return -1;
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
    else{ //if somethin else is in the requested field, give out an error message and return the error 100
        printf("Error while checking the collumn rule \n");
        printf("Error: %s in the requested field, should be 0 or 1 \n", &usedNumbers[input]);
        return 100;
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

    if(usedNumbers[input] == '1'){  //if the proposed Number, either by program or by user, has been used in the collum already, reset the used numbers list, then return -1 
                                    // as unusable number
        resetUsedNumbers();
        return -1;
    }
    else if(usedNumbers[input] == '0'){//if the number has not been used, return 0 as sucessfull for continuing checks
        resetUsedNumbers();
        return 0;
    }
    else{ //if somethin else is in the requested field, give out an error message and return the error 100
        printf("Error: %s in the requested field, should be 0 or 1", &usedNumbers[input]);
        return 100;
    }

}

int checkIfNumberIsAllowedGrid(int input, int row, int column){
    //return codes:     -1 if number may not be used because it is already in this field
    //                   0 if the number may be used
    //                   100 for unexpected error
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
        for(int j = 0; j < 3; j++){
            fieldCheck[i][j] = saveGameNumbers[i+modifyRow][j+modifyCollumn]; //transfer the data from the game save to the check array so if we break anything it isnt as bad^^^^
        }
    }


    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; i++){
            if(fieldCheck[i][j] != '#'){ //check if the char at position is not '#' => Doesnt work right now, still gets to the else part
                if(usedNumbers[(fieldCheck[i][j])-'0'] == '0'){ //if it has not been used allready, continue
                    usedNumbers[fieldCheck[i][j]] = '1'; //put the info that this number has been used 
                }
                else{ 
                    if (usedNumbers[(fieldCheck[i][j])-'0'] == '1'){ //check if the number has been if it hasnt been not used
                        return -1; //return that this number cannot be used at this position
                    }
                    else{
                        printf("Something went wrong, this state should not be reachable. \n This means that in my check, something else then a number was written to the field.\n");
                        printf("In the field %d %d was %s \n", i, j, usedNumbers[fieldCheck[i][j]-'0']);
                        return 100;
                    }
                }
            }
        }
    }
    if(usedNumbers[input] == '1'){ //returns if the requested number has been used already in this block
        resetUsedNumbers();
        return -1;
    }
    else if(usedNumbers[input] == '0'){ //returns if requested number is permitted
        resetUsedNumbers();
        return 0;
    }
    else{ //returns if unexpected error
        resetUsedNumbers();
        printf("Error while checking the Square Rule \n");
        printf("ERROR: founc char %c at requested position, should be 0 or 1", usedNumbers[input]);
        return 100;
    }   
}

//generation section

int fillRandomField(){
    if(emptyFields == 0){
        printf("All fields filled, no more random filling possible");
        return -1;
    }
    int rRow = (rand() % 8) +1;
    int rColumn = (rand() % 8) +1;
    int rInput = (rand() % 8) +1;

    printf("  %d    %d      %d \n row column input \n", rRow, rColumn, rInput);

    if(checkIfAlreadyFilled(rRow, rColumn) == -1){
        fillRandomField();
    }
    else{
        if(checkIfNumberIsAllowedColumn(rInput, rColumn) == 0 && checkIfNumberIsAllowedGrid(rInput, rRow, rColumn) == 0 && checkIfNumberIsAllowedRow(rInput, rRow)){
            saveGameNumbers[rRow][rColumn] == rInput;
            //put stack here
        }
    }


}


//input section

void cleanInputVariables(){ //puts demo inputs into the variables so it is easier to determine wrong or broken inputs
    rowIn = -1;
    columnInChar = '#';
    columnInInt = -1;
    numberIn = -1;
}

void getInputs(){
    cleanInputVariables();
    printf("Please input an answer in the form \"row as a number\" \"column as a char from a to i\" \"your answer as a number\"\n");
    printf("Example: 5 e 8 puts the number 8 at the position 5|e => the middle of the playing field\n");
    scanf("%d %c %d", &rowIn, &columnInChar, &numberIn);
}

int transformColumn(){ //Transforms the letter input for column to an intiger for the grid
    switch (columnInChar){
    case 'a':
        columnInInt = 1;
        break;
    
    case 'b':
        columnInInt = 2;
        break;
    
    case 'c':
        columnInInt = 3;
        break;
    
    case 'd':
        columnInInt = 4;
        break;
    
    case 'e':
        columnInInt = 5;
        break;
    
    case 'f':
        columnInInt = 6;
        break;
    
    case 'g':
        columnInInt = 7;
        break;

    case 'h':
        columnInInt = 8;
        break;

    case 'i':
        columnInInt = 9;
        break;
    
    default:
        columnInInt = -1;
        printf("Please input a valid column. \n Only columns between a and i are valid \n");
        break;
    }
    columnInChar = '#';
}

int validateInputPossible(){ //validates that the input is possible to be tested against the field. Inputs that are outside of this field will be cought here
    if(!(rowIn > 0 && rowIn < 10)){
        printf("Please input a valid row.\n Only rows between 1 and 9 are valid \n");
        return -1;
    }
    else if(!(columnInInt > 0 && columnInInt < 10)){
        printf("Please input a valid column. \n Only columns between a and i are valid \n");
        return -1;
    }
    else if(!(numberIn > 0 && numberIn < 10)){
        printf("Please input a valid solution.\n Only solutions between 1 and 9 are valid \n");
        return -1;
    }
    else{
        return 0;
    }
}

int validateInputnoRulesBroken(int input, int row, int column){ //return 0 = ok, -1 = rule broken, look at console, 100 = other error, uncaught
    if(checkIfNumberIsAllowedGrid(input, row, column) == -1){
        printf("This number has been used in the gridspace already, try another one \n");
        return -1;
    }
    else if(checkIfNumberIsAllowedGrid(input, row, column) == 100){
        printf("Some error has occured");
        return 100;
    }
    else if(checkIfNumberIsAllowedGrid(input, row, column) == 0){
        if(checkIfNumberIsAllowedColumn(input, columnInInt) == -1){
            printf("This number has been used in the column already, try another one \n");
            return -1;
        }
        else if (checkIfNumberIsAllowedColumn(input, columnInInt) == 100){
            printf("Some error has occured");
            return 100;
        }
        else if(checkIfNumberIsAllowedColumn(input, columnInInt)){
            if(checkIfNumberIsAllowedRow(input, row) == -1){
                printf("This number has been used in the column already, try another one \n");
                return -1;
            }
            else if(checkIfNumberIsAllowedRow(input, row) == 100){
                printf("Some error has occured");
                return 100;
            }
            else if(checkIfNumberIsAllowedRow(input, row) == 0){
                return 0;
            }
            else{
                return 100;
            }
        }
        else{
            return 100;
        }
    }
    else{
        return 100;
    }
}

void main(){
    fillArrayWithHash();
    buildField();
    fillRandomField();

    buildField();
}


