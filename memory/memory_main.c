//
// Created by robos on 2020/5/2.
/**
 * 0、C语言动态内存管理和动态内存分配:
 *      (1) malloc（）、calloc（）分配新的内存区域。
 *      (2) realloc（）调整已分配的内存区域。
 *      (3) free（）释放已分配的内存区域。
 *      上述所有函数都声明在头文件 stdlib.h 中。对象在内存中所占空间的大小是以字节数量为单位计算的。
 *      许多头文件（包括 stdlib.h）专门定义了类型 size_t 用来保存这种内存空间的相关信息。
 *      例如，sizeof 运算符以类型 size_t 返回字节数量。
 * 1、动态内存分配
 *      两个内存分配函数 malloc（）和 calloc（）的参数不一样：
 *      void*malloc(size_t size);
 *      函数 malloc（）分配连续的内存区域，其大小不小于 size。当程序通过 malloc（）获得内存区域时，内存中的内容尚未决定。
 *      void*calloc(size_t count，size_t size);
 *      函数 calloc（）分配一块内存区域，其大小至少是 count_size。换句话说，上述语句分配的空间应足够容纳一个具有 count 个元素的数组，每个元素占用 size 个字节。而且，calloc（）会把内存中每个字节都初始化为 0
 *      两个函数都返回 void 指针，这种指针被称为无类型指针（typeless pointer）。返回指针的值是所分配内存区域中第一个字节的地址，当分配内存失败时，返回空指针。
 *
 * 2、程序中 malloc 等内存分配函数的使用次数一定要和 free 相等，并一一配对使用。
 *      绝对要避免“malloc 两次 free 一次”或者“malloc 一次 free 两次”等情况。
 * 3、对于内存释放还必须保证只释放动态分配的内存，即不能用 free 来释放非 malloc、realloc、calloc 与 aligned_alloc 等
 *   内存分配函数分配的内存空间。
 *   与此同时，也不要将指针变量进行自增或者自减操作，使其指向动态分配的内存空间中间的某个位置，然后直接释放，这样也有可能引起未知的错误。
 * 4、在 free 之后必须为指针赋一个新值在使用指针进行动态内存分配操作时，在指针 p 被 free 释放之后，指针变量本身并没有被删除。
 *    如果这时候没有将指针 p 置为 NULL，会让人误以为 p 是个合法的指针而在以后的程序中错误使用它
 * 5、“free(p)”释放的是指针变量 p 所指向的内存，而不是指针变量 p 本身。指针变量 p 并没有被释放，仍然指向原来的存储空间。
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void malloc_lyq();
void malloc_0(void);

#define MAX_BUF_SIZE 100
int main(void)
{
    malloc_lyq();
    malloc_0();
    return 0;
}


void malloc_0(void) {
    printf("print: \n");
    char * p = NULL;
    /*内存申请*/
    p = (char *)malloc(10);
    if(p == NULL) exit(1); // 判断是否分配成功
    /*内存初始化*/
//    memset(p, '\0', MAX_BUF_SIZE);
//    strcpy(p, "hello");
    p[0] = 'c';
    p[1] = '\0';
    printf("print: %s \n",p);
    /*释放内存*/
    if (p != NULL)
    {
        free(p);
        /*在free之后给指针存储一个新值*/
        p = NULL;
    }
    if (p != NULL)
    {
        /*发生错误*/
        strcpy(p, "world");
    }
}