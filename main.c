#include <stdio.h>
#define MAX_LINES 100
#define MAX_NUMS 4
FILE *fp;
int count = 1;
char c;
int easyArray [100][4];
int mediumArray [100][4];
int hardArray [100][4];
int i,j;
int lines;
int valueToUseInFileName = 0;
int randomNumber, num1, num2, num3, num4;


int main(){
    srand(1);
    int size;

    char letterChose[2];
    printf("Welcome to the game of TwentyFour Part Two!\nUse each of the four numbers shown exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.");
    chooseText(letterChose); //Prompt User to enter letter for difficulty.
    lines = changeLevelAndReturnNumberOfLines(letterChose); // call the function which returns number of lines corresponding with the selected difficulty.
    initArray(lines); //Set the array values.
    selectRandomNumbers();
    printNumbersToUse();



    return 0;

}


void printNumbersToUse(){
    printf("The numbers to use are: %d, %d, %d, %d", num1, num2, num3, num4);
}


void chooseText(char* letterChose){
    printf("\nChoose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\nYour choice --> ");
    scanf("%s", letterChose);  
}


int changeLevelAndReturnNumberOfLines(char letterToCompare[2]){
    int linecount = 0;
      if (strcmp(letterToCompare, "M") == 0){
        valueToUseInFileName = 1; //changed such that we keep track of level chose.
        linecount = countNumberOfLines("medium (1).txt");
        
        
    }
    else if (strcmp(letterToCompare, "H") == 0){
        valueToUseInFileName = 2;
       linecount = countNumberOfLines("hard.txt");
       
       
    }
    else{
        valueToUseInFileName = 0;
        linecount = countNumberOfLines("easy.txt");
        
        
    }
    
    return linecount;
}




int countNumberOfLines(char filename[20]){

    count = 1;
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }
    fclose(fp);

    return count;
}



void initArray(int size){
    if (valueToUseInFileName == 1){
         fp = fopen("medium (1).txt", "r");
    }
    else if (valueToUseInFileName == 2){
         fp = fopen("hard.txt", "r");
    }
    else
    {
         fp = fopen("easy.txt", "r");
    }
    
   
    if (fp == NULL) {
        printf("Error opening file.");
        return 1;
    }

        for (i = 0; i < size; i++) {
        for (j = 0; j < 4; j++) {
            fscanf(fp, "%d", &easyArray[i][j]);
        }
    }

}


void selectRandomNumbers(){
    randomNumber = rand() % lines; //generate a radndom number between 0 and size of identified file.
    printf("Random number: %d \n", randomNumber);
    num1 = easyArray[randomNumber][0];
    num2 = easyArray[randomNumber][1];
    num3 = easyArray[randomNumber][2];
    num4 = easyArray[randomNumber][3];
    
}