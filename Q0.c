/* CS261- Assignment 1 - Q.0*/
/* Name: Jamie Loebe
 * Date: 04/14/2019
 * Solution Description: This program assigns a random number between 1-10
 * to integer x, and proceeds to call fooA and fooB and print out the 
 * subsequent changes made to x.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fooA(int* iptr){
    printf("Value of iptr: %d \n", *iptr); /* Print value pointed to by iptr */
    printf("Addressof iptr: %p \n", (void*)iptr); /* Print address of iptr */

    *iptr += 5; /* Add 5 to integer pointed to by iptr */

    printf("Address after adding 5: %p \n", &iptr); /* Print address of iptr */

    int c=5;
}

void fooB(int* jptr){
    printf("Value of jptr: %d \n", *jptr); /* Print value pointed to by jptr */
    printf("Address of jptr: %p \n", (void*)jptr); /* Print address pointed to by jptr */

    *jptr--; /* Subtract 1 from address of jptr */

    printf("New addrress of jptr: %p \n", &jptr); /* Print address of jptr */
}



int main() {
    srand(time(NULL));

    int x = rand() % 10 + 1; /* Assigned x a random integer between 1-10 */

    printf("Value of X: %d \n", x); /* Prints value of integer x */
    printf("Address of X: %p \n", &x); /* Prints address of integer x */

    fooA(&x);

    printf("Value of X: %i \n", x);
    /* Yes, the value in 'X' is now different. This is because we used a pointer in the function, and thus actually passed the actual value into the function, implemented the code using the actual value from 'main', and then returned the new value from 'fooA' back into main. We were not using a copt of the value, but the actual value itself */

    fooB(&x);

    printf("Value of X: %d \n", x); /* Prints value of integer x */
    printf("Address of X: %p \n", &x); /* Prints address of integer x */

	/* 5.) Value is same but address is different, as we changed address pointed to by jptr, but we did not change the value */
    return 0;
}
