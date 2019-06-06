/*/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Jamie Loebe
 * Date: June 1st, 2019
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}

int hashFunction2(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += (i + 1) * key[i];
    }
    return r;
}

/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink)); /* Malloc memory for new link in HT*/
    link->key = malloc(sizeof(char) * (strlen(key) + 1)); /*Malloc memory for new link with size of string */
    strcpy(link->key, key); /* Copy in key passed in */
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * param map
 * param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * param map
 */
void hashMapCleanUp(HashMap* map)
{
    // FIXME: implement
    int i;
    for(i = 0 ; i < map->capacity ; i++) /* Loop thru map until capacity */
    {
        if(map->table[i] != NULL)
        {
            HashLink *temp,*prev;
            prev = map->table[i];
            while(prev != NULL)
            {
                temp = prev->next;
                hashLinkDelete(prev);
                prev = temp;
            }
        }
    }
    map->size = 0;
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * param map
 * param key
 * return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    // FIXME: implement
    int val = HASH_FUNCTION(key) % map->capacity;
    if(val >= map->capacity)
    {
        return NULL;
    }
    else
    {
        HashLink *temp = map->table[val];
        while(temp != NULL)
        {
            if(strcmp(temp->key,key) == 0)
                return &(temp->value);
            temp = temp->next;
        }
    }
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity (double of the old capacity). After allocating the new table,
 * all of the links need to rehashed into it because the capacity has changed.
 *
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 *
 * @param map
 * @param capacity The new number of buckets.
 */
HashMap* resizeTable(HashMap* map, int capacity)
{
    // FIXME: implement
    HashMap *newMap = hashMapNew(capacity);
    int i;
    for(i = 0 ; i < map->capacity ; i++)
    {
        if(map->table[i] != NULL)
        {
            HashLink *temp = map->table[i];
            while(temp != NULL)
            {
                hashMapPut(newMap,temp->key,temp->value);
                temp = temp->next;
            }
        }
    }
    
    hashMapDelete(map);
    return newMap;
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 *
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    // FIXME: implement
    int index = HASH_FUNCTION(key) % map->capacity;
    
    HashLink *temp = map->table[index];
    HashLink *newNode = hashLinkNew(key,value,NULL);
    
    if(temp == NULL)
        map->table[index] = newNode;
    else
    {
        while(temp->next != NULL)
        {
            if(strcmp(key,temp->key) == 0)
            {
                temp->value = value;
                return;
            }
            temp = temp->next;
        }
        if(strcmp(key,temp->key) == 0)
        {
            temp->value = value;
            return;
        }
        temp->next = newNode;
    }
    map->size = map->size + 1;
}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    // FIXME: implement
    if(hashMapContainsKey(map,key))
    {
        int index = HASH_FUNCTION(key) % map->capacity;
        if(strcmp(map->table[index]->key,key) == 0)
            map->table[index] = map->table[index]->next;
        else
        {
            HashLink *temp = map->table[index];
            while(temp != NULL && strcmp(temp->next->key,key) != 0)
                temp = temp->next;
            
            if(strcmp(temp->next->key,key) == 0)
            {
                HashLink *h = temp->next;
                temp->next = temp->next->next;
                hashLinkDelete(h);
            }
        }
        map->size = map->size - 1;
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    int index = HASH_FUNCTION(key) % map->capacity;;
    if(index >=  map->capacity)
        return 0;
    
    HashLink *temp = map->table[index];
    
    if(temp != NULL)
    {
        while(temp != NULL)
        {
            if(strcmp(key,temp->key) == 0)
                return 1;
            temp = temp->next;
        }
    }
    
    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    int cnt = 0;
    int i;
    for(i = 0 ; i < map->capacity ; i++)
        if(map->table[i] == NULL)
            cnt++;
    return cnt++;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    // FIXME: implement
    return (float)hashMapSize(map)/(float)hashMapCapacity(map);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    // FIXME: implement
    int i;
    for(i = 0 ; i < map->capacity ; i++)
    {
        printf("\n Bucket[%d] => ", i);
        HashLink *temp = map->table[i];
        while (temp != NULL)
        {
            printf("(%s,%d) -> ", temp->key, temp->value);
            temp = temp->next;
        }
    }

}

