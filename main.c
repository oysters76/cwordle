#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define IS_PERFECT_MATCH 0 
#define IS_HALF_MATCH    1 
#define IS_NOT_MATCH     2
#define MAX              5
#define DEBUG            false //change to true, for debug mode
 
#define MAX_WORD_SIZE    15000 
#define MAX_WORD_LENGTH  10

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"  

char wordlist [MAX_WORD_SIZE][MAX_WORD_LENGTH];   

int get_rand(int max){
    int p = rand() % max;
    return p;
}

int compare_word(char user, char word, char * word_arr, int size){
    if (user == word) return IS_PERFECT_MATCH; 
    for (int i = 0; i < size; i++){
        if (user == word_arr[i]) return IS_HALF_MATCH; 
    }
    return IS_NOT_MATCH;
}

void print_box(const char* color){
    printf("%s█", color);
    printf("%s", ANSI_COLOR_RESET);
}

void print_perfect(){
    print_box(ANSI_COLOR_GREEN); 
}

void print_half_match(){
    print_box(ANSI_COLOR_YELLOW); 
}

void print_not_match(){
    print_box(ANSI_COLOR_RED);
}

void print_wordle_box(int r){
    if (r == IS_PERFECT_MATCH){
        print_perfect(); 
    }else if (r == IS_NOT_MATCH){
        print_not_match(); 
    }else if (r == IS_HALF_MATCH){
        print_half_match(); 
    }
}


int main(void){
    srand(time(NULL)); 
    int size = 0; 
    FILE *file_pointer; 

    file_pointer = fopen("words", "r"); 

    if (file_pointer == NULL){
        printf("Error opening the file\n"); 
        return 1; 
    }

    int i = 0; 
    while (fgets(wordlist[i], sizeof(wordlist[i]), file_pointer) != NULL){
        i++;
    }
    size = i; 
    fclose(file_pointer);

    char * word = wordlist[get_rand(size)]; 
    char user[6];

    if (DEBUG) printf("\nword: %s\n", word);

    for (int i = 0; i < 6; i++){
       scanf("%s",user);
       int all_passed = 1; 
       for (int k = 0; k < 5; k++){
           int r = compare_word(user[k], word[k], word, 5);
           print_wordle_box(r);   
           if (r != IS_PERFECT_MATCH) all_passed = 0;
       }
       if (all_passed == 1){
           printf("\nYou won!\n"); break; 
       }
       printf("\n");
   } 

    return 0; 
}