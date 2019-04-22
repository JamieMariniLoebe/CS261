/* CS261- Assignment 1 - Q.1*/
/* Name: Jamie Loebe
 * Date: 04/14/2019
 * Solution description: This program dynamically allocates memory for 10 students, and
 * prints out the IDs and scores for each student. The scores and IDs are randomly allocated
 * to the variables ID and score. The program then also prints out the minimum, maximum and average 
 * scores before deallocating memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
    int id;
    int score;
};

struct student* allocate()
{
    int n = 10; /* Initialize n to 10, the number of students */
    struct student* students = malloc(n * sizeof(struct student)); /* Use malloc to dynamically allocate
                                                                   memory for 10 students */
    return students; /* Return students pointer */
}

void generate(struct student* students)
{

    for(int i=0; i<10; i++) // Loop thru
    {
        students[i].id = rand() % 10 + 1; /* Generate random number between 1-10 for ID */
    }
    printf(" \n"); /* Print new line */

    /* for(int i=0; i<10; i++)
    {
        int temp = students[i].id;
        int randNum = rand() % 10 + 1; Incorrect code, still gives repetitive numbers and includes 0.
        
        students[i].id = students[randNum].id;
        students[randNum].id = temp;
        
    } */

    for(int i=0; i<10; i++)
    {
        students[i].score = rand() % (100 + 0); /* Loop thru, generate scores between 0-100 */
    }
}

void output(struct student* students){
    printf("ID   Score \n"); /* Print header */
    for (int i=0; i<10; i++) /* Loop thru */
    {
        printf("%d    %d \n", students[i].id, students[i].score); /* Print ID and Score, then new line */
    }
}

void summary(struct student* students){

    int min = 100; /* Initialize min to 100 */
    int max = 0; /* Initialize max to 0 */
    float sum = 0.00; /* Initialize sum to 0 */

    for(int i=0; i<10; i++)
    {
        sum += students[i].score; /* Add current/next score to sum */

        if(students[i].score < min)
        {
            min = students[i].score; /* Set min equal to new lowest score */
        }

        if(students[i].score > max)
        {
            max = students[i].score; /* Set max equal to new highest score */
        }
    }

    float average = sum/10; /* Divide sum by 10, total of students, to obtain score average */

    printf("Min = %d \n", min); /* Print min */
    printf("Max = %d \n", max); /* Print max */
    printf("Average = %.2f \n", average); /* Print average */

}

void deallocate(struct student* stud){
    free(stud); /* Free allocated memory */
}

int main(){
    srand(time(NULL));

    struct student* stud = NULL;

    stud = allocate();

    generate(stud);

    output(stud);

    summary(stud);

    deallocate(stud);

    return 0;
}
