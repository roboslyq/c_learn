# pthread_create
```c
int pthread_create(pthread_t *tidp,const pthread_attr_t *attr, 
                   (void*)(*start_rtn)(void*),void *arg);
```
>   第一个参数为指向线程标识符的指针。
    第二个参数用来设置线程属性。
    第三个参数是线程运行函数的起始地址。
    最后一个参数是运行函数的参数。

# pthread_exit
```c
void  pthread_exit（void  *retval）;

```
 简述：调用这个函数可以显示得退出线程
 
 void  pthread_exit（void  *retval）;
 
 # pthread_join
 ```c
int pthread_join(pthread_t thread, void **retval);
 
 ```
简述：用来等待一个线程的结束,使一个线程等待另一个线程结束，主要于线程间同步的操作。不使用的话，该线程结束后并不会释放其内存空间，这会导致该线程变成了“僵尸线程”。
thread: 线程标识符，即线程ID，标识唯一线程。
retval: 用户定义的指针
 
 
 # pthread_detach
 
 简述：主线程与子线程分离，子线程结束后，资源自动回收。pthread_join()函数的替代函数。如果tid尚未终止，pthread_detach()不会终止该线程。
 
 int pthread_join(pthread_t thread, void **retval);