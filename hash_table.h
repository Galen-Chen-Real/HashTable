/*
 *        'hash_table.h'
 *     (C) 2014.4 GordonChen
 *
 *     此处提供HASH表相关函数原形定义. 以下简述其用法:
 *  (1)使用HASH表前需要先调用hashtab_init() 初始化HASH表,参数分别为HASH表最大表项、
 * HASH算法函数(用以产生HASH值并要求返回值为正且比最大表项小) 以及判断两数据是否相同的
 * 比较函数(要求相同时返回0); 初始化成功返回最大表项数值.
 *  (2)现在可以调用hashtab_lookup() 查询数据是否存在于HASH表中; 调用hashtab_insert()
 * 往HASH表中插入一个数据(注意此函数不考虑数据重复的问题,如需考虑重复情况需用户自己先调用
 * hashtab_lookup() 判断再决定是否插入); 调用hashtab_delete() 删除HASH表中指定的数据,
 * 如果数据存在并且删除成功则返回此数据,此返回值非常有用,它可让用户进一步释放而不会导致内存泄
 * 漏(因为HASH表中所存的数据是用户真实数据的指针); 通过重复调用hashtab_traver() 可以遍历
 * HASH表中所有的数据,遍历结束返回NULL,再次调用则从头开始,以此类推.
 *  (3)HASH表使用完毕后,如果用户不想导致内存泄漏,就必须先通过hashtab_traver() 的返回值
 * 自己依次释放用户真实数据,然后再使用hashtab_destroy() 来销毁HASH表以便重新使用或者只是
 * 单纯的释放不使用的内存.
 * 
 */
#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

//最大hash表项
#define HASHMSIZE 101

//链表节点类型
typedef struct nlist
{
    struct nlist *next;
    void *data;
}NLIST;

//比较函数指针类型
typedef int (*CMPFPTR)(const void *, const void *);
//hash算法函数指针类型
typedef unsigned int (*HASHFPTR)(const void *);

//初始化hash表;成功返回hashsize,失败返回-1.
int  hashtab_init(unsigned int hashsize, HASHFPTR hash, CMPFPTR cmp);
//销毁hash表
void hashtab_destroy(void);
//查找;成功返回查找到的data,失败返回NULL.
void *hashtab_lookup(void *data);
//插入;成功返回插入的data,失败返回NULL.
void *hashtab_insert(void *data);
//删除;成功返回data,失败返回NULL.
void *hashtab_delete(void *data);
//遍历;成功返回data,遍历结束返回NULL.
void *hashtab_traver(void);

#endif

