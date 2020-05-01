//
// Created by luo.yongqian on 2020/4/26.
//
#include <stdio.h>
#include <pthread.h>

//定义一个结构体类型
typedef struct {
    int val1;
    int val2;
} ADD_VAL;

int *p;

// 定义线程处理的具体任务
void *async_add(void *args){
    ADD_VAL val = *(ADD_VAL *)args;
    printf("async args : %d  %d \n" ,val.val1,val.val2);
    printf("thread_id: %d \n ",pthread_self());
    int res = val.val1 + val.val2;
    return (void*)"OK";
}

int *p;
int add(int val1,int val2){
    ADD_VAL *val;
    printf("input %d  , %d  \n",val1,val2);
    printf("thread_id: %d \n ",pthread_self());
    val -> val1 = val1;
    val -> val2 = val2;
    pthread_t  pid;
    int  ret;
    void *retval;
    ret = pthread_create(&pid,NULL,async_add,val);
    if(ret<0)
    {
        printf("pthread_create error,ret=%d\n",ret);
        return -1;
    }
    pthread_join(pid,&retval);
    printf("res: %s \n",(char*)retval);

    return 0;
}