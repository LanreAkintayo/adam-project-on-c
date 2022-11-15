#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

int getCaseLength(){
    int noOfCases;

    FILE *fp = fopen("Adam.in", "r" );
    
    // Checking if fp, the pointer to the file returns null.
      if(fp == NULL) {
              perror("Unable to open file!");
          exit(1);
      }

   // Read lines using POSIX function getline
     // This code won't work on Windows 
     char *line = NULL;
     size_t len = 0;

    // Getting the first line containing no of cases 
    // and storing it in a variable
    if(getline(&line, &len, fp) != -1) {
        noOfCases = atoi(line);
    }
  
    fclose(fp);
    free(line); 
    return noOfCases;
    

}

int checkScenarioValidity(char scenario[]) {
    int result;
    regex_t expression;
    
    result = regcomp( &expression, "[^udUD]", 0);

 
    result = regexec( &expression, scenario,
                    0, NULL, 0);

    return result;
}

void readCases(int noOfCases, char (*cases)[100]){

    FILE *fp = fopen("Adam.in", "r");
      if(fp == NULL) {
              perror("Unable to open file!");
          exit(1);
      }

   // Read lines using POSIX function getline
     // This code won't work on Windows
     char *line = NULL;
     size_t len = 0;
    int counter = 0;

    // While we've not gotten to the last line, 
    // getLine should keep on reading.
    while(getline(&line, &len, fp) != -1) {

        // Start to read from the second line If we are on the first line.
        if (counter == 0){
            if(getline(&line, &len, fp) != -1){
                line[strcspn(line, "\n")] = 0;
                strcpy(cases[counter], line); 
            } 
        } else{
            line[strcspn(line, "\n")] = 0;
            strcpy(cases[counter], line); 
        }

        if (counter == noOfCases){
            break;
        }-

        counter++;
    }

    fclose(fp);
    free(line);     
}

int getNoOfSteps(char scenario[]){
    int counter = 0;   

    int result = checkScenarioValidity(scenario);

    if (result == 0){
        counter = -1;
        return counter;
    }

    for (int i = 0; i < strlen(scenario); i++){
        char currentChar = scenario[i];

        if (toupper(currentChar) == 68){
            break;
        }
        counter++;
    }

    return counter;
}

void displayResult(int noOfCases, char (*cases)[100]){
     for (int i = 0; i < noOfCases; i++){
        int noOfSteps = getNoOfSteps(cases[i]);
        int result = checkScenarioValidity(cases[i]);

        if (result == 0){
            printf("\nInvalid steps found in: %s. Step can either be 'U' or 'D'", cases[i]);
        }else{
            printf("\nNo of steps for %s is %d", cases[i], noOfSteps);
        }
        }

}

int main(){
    int noOfCases = getCaseLength();


    char cases[noOfCases][100];

    readCases(noOfCases, cases);

    displayResult(noOfCases, cases);

   

    return 0;
}