/* Name: Jamie Loebe
 * Date: 04/21/2019
 * Class: CS 261
 * Description: This is the program to run the stackapp
 * and check for balanced parentheses
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
 Using stack to check for unbalanced parentheses.
 ***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
 param:     s pointer to a string
 
 */
char nextChar(char* s)
{
    static int i = -1;
    char c;
    ++i;
    c = *(s+i);
    if ( c == '\0' )
        return '\0';
    else
        return c;
}

/* Checks whether the (), {}, and [] are balanced or not
 param:     s pointer to a string
 pre:
 post:
 */
int isBalanced(char* s){
    DynArr *stack = newDynArr(50);
    char next = nextChar(s);
    
    int balanced = 1;

    while(next != '\0')
    {
        if(next == '[' || next == '{' || next == '(')
        {
            pushDynArr(stack, next);
	        next = nextChar(s);
        }
        
        else if(next == ']' || next == '}' || next == ')')
        {
           popDynArr(stack);
           next = nextChar(s);
        }
    }

	balanced = isEmptyDynArr(stack);
	
	freeDynArr(stack);
	
    return balanced;
}

int main(int argc, char* argv[]){
    
    char* s=argv[1];
    int res;
    
    printf("Assignment 2\n");
    
    res = isBalanced(s);
    
    if (res)
        printf("The string %s is balanced\n",s);
    else
        printf("The string %s is not balanced\n",s);
   
    return 0;
}

