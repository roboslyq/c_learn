//
// Created by luo.yongqian on 2020/4/27.
//

#include <stdio.h>

#define SDS_HDR_VAR(T,s) struct sdshdr##T *sh = (void*)((s)-(sizeof(struct sdshdr##T)));

struct __attribute__ ((__packed__)) sdshdr8 {
    uint8_t len; /* used  表示当前sds的长度(单位是字节),包括'0'终止符，通过len直接获取字符串长度，不需要扫一遍string*/
    uint8_t alloc; /* excluding the header and null terminator 表示已为sds分配的内存大小(单位是字节),(3.2以前的版本用的free是表示还剩free字节可用空间)，不包括'0'终止符*/
    unsigned char flags; /* 3 lsb of type, 5 unused bits 用一个字节表示当前sdshdr的类型，因为有sdshdr有五种类型，所以至少需要3位来
                            表示000:sdshdr5，001:sdshdr8，010:sdshdr16，011:sdshdr32，100:sdshdr64。高5位用不到所以都为0。
                         */
    char buf[]; //sds实际存放的位置(本质是一个char数组)
};
struct __attribute__ ((__packed__)) sdshdr16 {
    uint16_t len; /* used */
    uint16_t alloc; /* excluding the header and null terminator */
    unsigned char flags; /* 3 lsb of type, 5 unused bits */
};

int main(){
    printf("%d \n", sizeof(struct sdshdr8));
    printf("%d \n", sizeof(struct sdshdr16));
    struct sdshdr16 sds16;

    sds16.len = 100;
    sds16.alloc = 90;
    sds16.flags = '3';

    char *p;
    p = & sds16.flags;
    printf("%d",*(p-1)); // 0  -- 90的末位
    printf("%d",*(p-2)); // 90 -- 移2字节，得到完成的90
    printf("%d",*(p-4)); // 100 -- 移4字节，得到完成的90
}