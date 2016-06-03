/*
 *        'hash_table.c'
 *     (C) 2014.4 GordonChen
 * 
 *    此处提供'hash_table.h'中函数的实现.
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"

static NLIST   *hashtab[HASHMSIZE];
static unsigned int hashsize;
static HASHFPTR hashfun;
static CMPFPTR  cmpfun;

static NLIST *lookup(void *data);

int hashtab_init(unsigned int size, HASHFPTR hash, CMPFPTR cmp)
{
    int i;
    
    for(i = 0; i < HASHMSIZE; i++)
    {
        hashtab[i] = NULL;
    }
    
    if(size < 1 || size > HASHMSIZE)
    {
        return -1;
    }
    hashsize = size;
    
    if(hash == NULL || cmp == NULL)
    {
        hashsize = 0;
        return -1;
    }
    hashfun = hash;
    cmpfun = cmp;
    
    return hashsize;    
}

void hashtab_destroy(void)
{
    int i;
    NLIST *np;
    
    for(i = 0; i < HASHMSIZE; i++)
    {
        if(hashtab[i] != NULL)
        {
            np = hashtab[i];
            while(np)
            {
                hashtab[i] = np->next;
                free(np);
                np = hashtab[i];
            }
        }
    }
    
    hashsize = 0;
    hashfun = NULL;
    cmpfun = NULL;
}

static NLIST *lookup(void *data)
{
    NLIST *np;
    unsigned int hashval = hashfun(data);
    
    if(hashval > hashsize - 1)
    {
        printf("PANIC! lookup: hashval(%d) > hashsize(%d) - 1\n",
            hashval, hashsize);
        hashtab_destroy();
        return NULL;
    }
    
    for(np = hashtab[hashval]; np != NULL; np = np->next)
    {
        if(!cmpfun(data, np->data))
        {
            return np;
        }
    }
    return NULL;
}

void *hashtab_lookup(void *data)
{
    NLIST *np = lookup(data);
    if(np == NULL)
    {
        return NULL;
    }
    else
    {
        return np->data;
    }
}

void *hashtab_insert(void *data)
{
    NLIST *newnp;
    unsigned int hashval = hashfun(data);
    
    if(hashval > hashsize - 1)
    {
        printf("PANIC! insert: hashval(%d) > hashsize(%d) - 1\n",
            hashval, hashsize);
        hashtab_destroy();
        return NULL;
    }
    
    if((newnp = (NLIST *)malloc(1 * sizeof(NLIST))) == NULL)
    {
        perror("malloc() newnp failed");
        return NULL;
    }
    newnp->data = data;
    newnp->next = NULL;
    
    if(hashtab[hashval] == NULL)
    {
        hashtab[hashval] = newnp;
    }
    else
    {
        newnp->next = hashtab[hashval];
        hashtab[hashval] = newnp;
    }
    
    return newnp->data;
}

void  *hashtab_delete(void *data)
{
    void *ret;
    NLIST *np, *tmp;
    unsigned int hashval;
    
    if((np = lookup(data)) == NULL)
    {
        return NULL;
    }
    
    hashval = hashfun(data);
    if(hashval > hashsize - 1)
    {
        printf("PANIC! delete: hashval(%d) > hashsize(%d) - 1\n",
            hashval, hashsize);
        hashtab_destroy();
        return NULL;
    }
    
    tmp = hashtab[hashval];
    if(tmp == np)
    {
        hashtab[hashval] = np->next;
    }
    else
    {
        while(tmp->next)
        {
            if(tmp->next == np)
            {
                tmp->next = np->next;
            }
            tmp = tmp->next;
        }
    }
    
    ret = np->data;
    free(np);
    np = NULL;
    
    return ret;
}

void *hashtab_traver(void)
{
    static int cur_hashval = -1;
    static NLIST *cur_np = NULL;
    void *data;
    
    while(!cur_np)
    {
        cur_hashval++;
        cur_np = hashtab[cur_hashval];
        
        if(cur_hashval > hashsize - 1)
        {
            return NULL;
        }
    }
    
    data = cur_np->data;
    cur_np = cur_np->next;
    
    return data;
}

