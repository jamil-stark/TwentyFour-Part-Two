#include <stdio.h> 
#define MAX_LINES 100
#define MAX_NUMS 4

int main(){
    printf("Welcome to the game of TwentyFour Part Two!\nUse each of the four numbers shown exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.");
    chooseText();
    char textx[10][20] = numbersToUse();

    return 0;

}

void chooseText(){
    printf("\nChoose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\nYour choice --> ");
}

char numbersToUse(){
    FILE *file = fopen("easy.txt", "r");
    if (file == NULL) {
    printf("File did not open successfully.\n");
    return 1;
    char sentences[10][20]; // assuming maximum 100 sentences, each of length up to 1000 characters
    int i = 0;
    while (fgets(sentences[i], 20, file) != NULL) {
        i++;
    }
    return sentences;
}



}