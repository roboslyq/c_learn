//
// Created by luo.yongqian on 2020/4/26.
//
#include <stdio.h>
#include <pthread.h>

void *  async_add(void *args){
    int i = *(int *)args;
    printf("args : %d \n" ,i);
    return (void*)"OK";
}

int add(int val1,int val2){
    pthread_t  pid;
    int a = 10;
    int  ret;
    void* cal_res;
    ret = pthread_create(&pid,NULL,async_add,&a);
    pthread_join(ret,&cal_res);
    printf("res: %d \n",*(char *)cal_res);
}