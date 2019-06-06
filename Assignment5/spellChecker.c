#include "hashMap.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    char *buf = nextWord(file);
    while(buf != NULL)
    {
        hashMapPut(map,buf,0);
        free(buf);
        buf = nextWord(file);
    }
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXME: implement
    HashMap* map = hashMapNew(10000);
    
    FILE* file = fopen("dictionary.txt", "r");
    clock_t timer = clock();
    loadDictionary(file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);
        
        if (strcmp(inputBuffer, "quit") == 0)
        {
            quit = 1;
            continue;
        }

        int i;
        for( i = 0 ; i < strlen(inputBuffer) ; i++)
            inputBuffer[i] = tolower(inputBuffer[i]);

        if(hashMapContainsKey(map,inputBuffer))
            printf("The inputted word \"%s\" is spelled correctly\n",inputBuffer);
        else
        {
            printf("The inputted word \"%s\" is not spelled correctly\nDid you mean ?\n",inputBuffer);
            int index = HASH_FUNCTION(inputBuffer) % map->capacity;
            int cnt = 0,i=0;
            while(cnt != 5)
            {
                HashLink *temp = map->table[index+i];
                while(temp != NULL)
                {
                    printf("%s\n", temp->key);
                    temp = temp->next;
                    cnt++;
                    if(cnt == 5) break;
                }
                i++;
            }
        }
    }
    
    hashMapDelete(map);
    return 0;
}

