 /* Assignment 1, Q3
 * Name: Jamie Loebe
 *  Date: 04/14/2019
 * Solution description: This program prompts user for input, then takes that input
 * and puts it into snake case text, and then takes the snake case text and translates
 * it into camelCase text. 
 */


#include <stdio.h>
#include <stdlib.h>

char toUpperCase(char ch){
    return ch - 'a' + 'A'; /* Convert to upper case per ASCII table */
    /*Convert ch to upper case, assuming it is in lower case currently*/
}

char toLowerCase(char ch){
    return ch + 'a' - 'A'; /* Convert to lower case per ASCII table */
    /*Convert ch to lower case, assuming it is in upper case currently*/
}

int isUpperCase(char ch){
    return ch >= 65 && ch <= 90; /* Check if is upper case per ASCII table */
}

int isLowerCase(char ch){
    return ch >= 97 && ch <= 122; /* Check if is lower case per ASCII table */
}

int isNum(char ch){
    return ch >= 48 && ch<= 57; /* Return number per ASCII table */
}

int isChar(char ch){
    return isUpperCase(ch) || isLowerCase(ch); /* Return upper or lower char */
}

int isUnderScore(char ch){
    return ch == '_'; /* Check and return underscore */
}

int isSpecialChar(char ch){
    return (!isUpperCase(ch)) || (!isLowerCase(ch)) || (!isNum(ch)) || (!isUnderScore(ch));
} /* Check and confirm each case to see if special char, and return */

int stringLength(char s[]) {
    /*Return the length of the string*/

    int len;
    for(len = 0; s[len] != '\0';len++); /* Iterate thru entire string, increment length each time */
    return len;
}


int validateString(char *word){
    /* Declare temp pointer */
    char *temp;

    /* Set len equal to the actual length of the string of inputted word */
    int len = stringLength(word);

    temp = (char*) malloc(sizeof(char)*(len+1)); /* Allocate memory for second word */

    // boolean flag anyAlphabetExist = false
    int anyAlphabetExist = 0;

    //boolean flag anySpecialCharacter = false
    int anySpecialCharacter = 0;

    for(int i=0,j=0; i < stringLength(word); i++){


        if (anyAlphabetExist == 0){ /* Loop thru */
            if (isChar(word[i])){
                temp[j] = word[i]; /* Store in temp */
                j++; /* Increment j */
                anyAlphabetExist = 1; /* Set boolean flag to true */
            }
        }

        else{
            if (isChar(word[i])){ /* Check if value is letter */
                temp[j] = word[i]; /* store char in temp */
                j++;
            }
            else{
                if ( anySpecialCharacter == 0){
                    temp[j] = '_'; //add underscore
                    j++;
                    anySpecialCharacter = 1;
                }
            }
        }
    }
    if ( anyAlphabetExist == 0 || anySpecialCharacter == 0){
        return 0;
    }
    else{
        return 1;
    }
}

void firstChange(char* word){
    /* Declare temp pointer */
    char *temp;

    /* Set len equal to the actual length of the string of inputted word */
    int len = stringLength(word);

    temp  = (char*) malloc(sizeof(char)*(len+1)); /* Allocate memory for second word */

    int firstAlphabet = 0; // Boolean flag set to false
    int lastCharAlphbet = 0; // Boolean flag set to false
    int j=0;

    for(int i=0; i < stringLength(word); i++){
        if ( firstAlphabet == 0 && isChar(word[i])){
            if ( isUpperCase(word[i])){ // If letter is upper case
                temp[j] = toLowerCase(word[i]); // Set to lower case and store in temp
            }
            else{
                temp[j] = word[i]; // Store in temp
            }
            j++;
            firstAlphabet = 1; /* Set boolean flags both to true */
            lastCharAlphbet = 1;
        }
        else{
            if(isChar(word[i])){ /* If value is char */
                if ( lastCharAlphbet == 0){
                    temp[j] = '_'; /* Add underscore to temp array */
                    j++;
                }
                if ( isUpperCase(word[i])){
                    temp[j] = toLowerCase(word[i]); /* Set value of i in word array to lower case and assign to temp */
                }
                else{
                    temp[j] = word[i]; /* Store word arraya in temp */
                }
                j++;
                lastCharAlphbet = 1;
            }
            else{
                lastCharAlphbet = 0;
            }
        }
    }
    temp[j] = '\0'; // Add null terminator
    int i;
    for(i = 0; i < stringLength(temp); i++){
        word[i] = temp[i]; /* Iterate thru array and copy  over temp to word */
    }
    word[i] = '\0'; /* Add null terminator */
}


void secondChange(char* word){
    /* Declare temp pointer*/
    char *temp;

    /* Set len equal to the actual length of the string of inputted word */
    int len = stringLength(word);

    temp  = (char*) malloc(sizeof(char)*(len+1)); /* Allocate memory for second word */

    int j=0;
    for(int i=0; i < stringLength(word); i++){
        if (isUnderScore(word[i])){
            /* Incrementing to reach the next letter, skipping the underscore */
            i++;
            temp[j] = toUpperCase(word[i]); /* Convert next letter after underscore to upper case */
            j++;
        }
        else{
            temp[j] = word[i]; /* Add value to temp */
            j++;
        }
    }
    temp[j] = '\0'; /* Add null terminator */

    int i;
    /* copy array of temp into word */
    for(i = 0; i < stringLength(temp); i++){
        word[i] = temp[i];
    }
    word[i] = '\0';
}

void camelCase(char* word){

    if (validateString(word) == 1){ // If string is valid, continue with covnersion */

        firstChange(word);

        secondChange(word);
    }

    else{ /* Invalid string, error */
        char mystring[40] = "Invalid input string";
        int i;
        for(i = 0; i < stringLength(mystring); i++){
            word[i] = mystring[i];
        }
        word[i] = '\0';
    }
}

int main(){
    char word[64];

    printf("Input string: ");
    scanf(" %[^\n]", word); /*Read the string from the keyboard*/
    /*  Source for scanf of string with spaces: stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf */
    printf("String: ");

    /*Call camelCase*/
    camelCase(word);

    /*Print the new string*/
    printf("Converted String : %s\n",word);

    return 0;
}
                                                                             
