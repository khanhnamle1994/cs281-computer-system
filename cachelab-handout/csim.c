/* James Le: le_j6 */

#include "cachelab.h"
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Use a struct function to proclaim the data structure of one specific set entry
struct SetEntry
{
    int *valid; // type for 32-bit integer
    long *tag; // type for 64-bit integer
    clock_t *access_time; // type suitable for storing the processor time
};

// This is the global pointer to the cache
struct SetEntry *SetPointer;

void get_opt(int argc, char **argv);
void initCache();
void freeCache();

// The data load operation (L)
void load(void *addr, int size); 
// The data store operation (S) only load when a cache miss occurs
void modify(void *addr, int size); 
// The data modify operation (M) is treated as a load followed by a store to the same address
void store(void *addr, int size);

int  getSetBits(void *addr);
long getTagBits(void *addr);

// Initialize hits, misses, and evictions
int hit_count = 0; 
int miss_count = 0; 
int eviction_count = 0;

// Initialize set index bits, block offset bits, and number of lines per set
int s = 0, E = 0, b = 0;

char *file = NULL;
long clocktime = 0; // Variable is used to record the access time

// Use the getopt function to parse command line arguments.
void get_opt(int argc, char **argv)
{
    int c;

    while ((c = getopt(argc, argv, "s:E:b:t:")) != -1)
    {
        switch (c)
        {
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                file = optarg;
                break;
            default:
                printf("Invalid operation\n");
                exit(0);
        }
    }
}

// Allocate storage for the cache simulator's data structures using the malloc function
void initCache()
{
    int S = (1 << s);
    SetPointer = (struct SetEntry*)malloc(sizeof(struct SetEntry) * S);

    if (!SetPointer) {
	fprintf(stderr, "Memory error!\n");
	exit(0);
    }

    for (int i = 0; i < S; i++)
    {
        SetPointer[i].valid = (int *)malloc(sizeof(int) * E);
	SetPointer[i].tag = (long *)malloc(sizeof(long) * E);
        SetPointer[i].access_time = (clock_t *)malloc(sizeof(clock_t) * E);

        for(int j = 0 ; j < E; j++)
        {
            SetPointer[i].valid[j] = 0;
	    SetPointer[i].tag[j] = 0;
            SetPointer[i].access_time[j] = 0;
        }
    }
}

// Function to return the space left in the cache simulator back to heap
void freeCache()
{
    int S = (1 << s);

    SetPointer = (struct SetEntry*)malloc(sizeof(struct SetEntry) * S);
    for (int i = 0; i < S; i++)
    {
        free(SetPointer[i].valid);
	free(SetPointer[i].tag);
        free(SetPointer[i].access_time);
    }

    free(SetPointer);
}

/* For a Load operation:
	if cache hit:
	     hit_count++
	else:
	     if cache is not full:
		miss_count++
	     else:
		miss_count++
		eviction_count++ */

void load(void *addr, int size)
{
    int setnum = getSetBits(addr);
    printf("setnum = %d, ", setnum);
    struct SetEntry *current_set = &SetPointer[setnum];

    int full = 1;
    int empty_item = 0;         
    int last_item = 0;          
    int last_time = current_set->access_time[0];

    int index;
    for (index = 0; index < E; index++)
    {
        // The entry is not valid, so the cache is not full
        if (current_set->valid[index] == 0)
        {
            full = 0;
            empty_item = index;
        }
        // The entry is valid, so update the access time
	else if (current_set->valid[index] == 1 && getTagBits(addr) == current_set->tag[index])
        {
            current_set->access_time[index] = ++clocktime;
            break;
        }
        // The entry is valid, but the tag is not equal
        else
	{
            if (current_set->access_time[index] < last_time)
            {
                last_item = index;
                last_time = current_set->access_time[index];
            }
        }
    }

    if (index == E) // Cache miss occurs
    {
        miss_count++;
        if (full)   // Cache eviction occurs
        {
            current_set->tag[last_item] = getTagBits(addr);
            current_set->access_time[last_item] = ++clocktime;
            eviction_count++;
        }
        else
        {
            current_set->valid[empty_item] = 1;
            current_set->tag[empty_item] = getTagBits(addr);
            current_set->access_time[empty_item] = ++clocktime;
        }
    }
    else    // Cache hit occurs
    {
        hit_count++;
    }

}

/* For a Store operation:
	if cache hit:
	     hit_count++
	else:
	     load operation */

void store(void *addr, int size)
{
    int setnum = getSetBits(addr);
    printf("setnum = %d, ", setnum);
    struct SetEntry *current_set = &SetPointer[setnum];

    int index;
    for (index = 0; index < E; ++index)
    {
	// Valid entry, so update the access time
        if (current_set->valid[index] == 1 && getTagBits(addr) == current_set->tag[index])
        {
            current_set->access_time[index] = ++clocktime;
            break;
        }
    }

    if (index == E) // Cache miss occurs
    {
        load(addr, size);   // Do a data load operation
    }
    else            // Cache hit occurs
    {
        hit_count++;
    }
}

/* For a Modify operation: do a data load operation, then do a data store operation*/

void modify(void *addr, int size)
{
    int setnum = getSetBits(addr);
    printf("setnum = %d, ", setnum);

    load(addr, size);
    store(addr, size);
}

// get the number of set bits from the address
int  getSetBits(void *addr)
{
    return (int) ( ((long)addr >> b) & ((1 << s) - 1) );
}

// get the number of tag bits from the address
long getTagBits(void *addr)
{
    return (long)((long)addr >> (s + b));
}

// Main Function
int main(int argc, char **argv)
{
    get_opt(argc, argv);
    initCache();

    FILE *fp = fopen(file, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: can't open file!\n");
        exit(0);
    }

    char line_buf[100];
    char op[100];
    
    void *addr;
    int size;

    while (fgets(line_buf, 100, fp) != NULL)
    {
        sscanf(line_buf, "%s %p,%d", op, &addr, &size);
        if (*op == 'L')
        {
            load(addr, size);
        }
        else if (*op == 'S')
        {
            store(addr, size);
        }
        else if (*op == 'M')
        {
            modify(addr, size);
        }
    }

    freeCache();
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
