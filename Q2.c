/* CS261- Assignment 1 - Q2
  Name: Jamie Loebe
  Date: 04/14/2019
  Solution description: This program swaps the addresses of 2 pointer variables,
  and prints the appropriate values returned by the function foo().
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo(int* a, int* b, int c){

    printf("Before swap: x = %d, y = %d, z = %d \n", *a, *b, c);
    int *temp; /* Declare pointer temp to hold values */

    temp = a; /* Put value of a in temp */
    a = b; /* Put value of b in a */
    b = temp;  /* Put value of a, which is now in temp, into b */

    c -= 1; /* Decrement the value of c by 1 */
    printf("After swap: x = %d, y = %d, z = %d \n", *a, *b, c);

    return c;
}

int randNum(int *a, int *b, int *c)
{
    *a = rand() % 10 + 0;
    *b = rand() % 10 + 0;
    *c = rand() % 10 + 0;

    return *a, *b, *c;
}

int main(){

    srand(time(NULL));
    int x, y, z; /* Declare three integers x, y, and z */

    randNum(&x, &y, &z); /* This function initializes x, y and z to random values
    between 0-10 */

    printf("%d %d %d \n", x, y, z); /* Print values of x, y, and z */
    printf("%d %d %d \n", x, y, z, foo(&x, &y, z)); /* Perform swap with function foo(), pass in x, y and z as parameters
    and print the new values from foo */
    printf("%d %d %d \n", x, y, z); /* Print values of x, y and z */

    return 0;
}
    /* 4a.) Yes, the return value is different. This is because the foo() function decremented c(z) by 1, and then returned this decremented value. Thus, we are changing the actual value itself, and not just a copy of said value */
    /* 4b.) No, and this is because the swapped values are local in scope. Thus, the values being swapped were local in terms of the function itself, and we not returned back into main */
