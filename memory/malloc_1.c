//
// Created by robos on 2020/5/2.
//

#include <stdio.h>  /* printf, scanf, NULL */
#include <stdlib.h>  /* malloc, free, rand, system */
void malloc_lyq(void){
    int i,n;
    char * buffer;
    printf("请输入字符串长度：");
    scanf("%d",&i);

    buffer = (char *)malloc(i+1); // 字符串最后包含 \0
    if(buffer == NULL) exit(1); // 判断是否分配成功
    // 随机生成字符串
    for(n=0; n<i; n++){
        buffer[n] = rand()%26+'a';
    }
    buffer[i]='\0';
    printf ("随机生成的字符串为：%s\n",buffer);
    free(buffer);  // 释放内存空间
//    system("pause");
}

