/*
 * 统计一篇文章中每个单词出现的次数.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash_table.h"

#define MAXWORD 32
#define MYHASHSIZE HASHMSIZE

typedef struct
{
    char *word;
    int num;
}DATA; 

unsigned int hash(const void *data)
{
    unsigned int hashval;
    DATA *d = (DATA *)data;
    char *s = d->word;  //很容易忽略的地方！
    
    for(hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }
    
    return hashval % MYHASHSIZE;
}

int cmp(const void *d1, const void *d2)
{
    DATA *data1 = (DATA *)d1;
    DATA *data2 = (DATA *)d2;
    
    return strcmp(data1->word, data2->word);
}

int main()
{
    char *word;
    DATA *data, *sech;
    
    hashtab_init(MYHASHSIZE, hash, cmp);
    
    while(1)
    {
        if((word = (char *)malloc(1 * MAXWORD)) == NULL)
        {
            perror("malloc() word failed");
            break;
        }
        scanf("%s", word);
        if(!strcmp(word, "quit"))
        {
            break;
        }
        
        if((data = (DATA *)malloc(1 * sizeof(DATA))) == NULL)
        {
            perror("malloc() data failed");
            break;
        }
        data->word = word;
        data->num = 1;
        
        if((sech = (DATA *)hashtab_lookup(data)) == NULL)
        {
            if(!hashtab_insert(data))
            {
                printf("hashtab_insert() failed!\n");
                break;
            }
        }
        else
        {
            sech->num++;
        }
    }
    
    while(data = (DATA *)hashtab_traver())
    {
        printf("%s\t: %d\n", data->word, data->num);
        free(data->word);
        data->word = NULL;
        free(data);
        data = NULL;
    }
    
    hashtab_destroy();
    
    return 0;
}

