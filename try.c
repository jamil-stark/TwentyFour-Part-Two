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


int main(){
    int size;
    char letterChose[2];
    printf("Welcome to the game of TwentyFour Part Two!\nUse each of the four numbers shown exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.");
    chooseText(letterChose);
    lines = changeLevelAndReturnNumberOfLines(letterChose);
    // numbersToUse();
    // char chosen[2] = ["E"];


    // printf("The number of lines in the text file is: %d", lines);
        initArray(size);

       for (i = 0; i < size; i++) {
        for (j = 0; j < 4; j++) {
            printf("%d ", easyArray[i][j]);
        }
        printf("\n");
    }


    return 0;

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