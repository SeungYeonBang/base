/**
 * MetaSCOPE Service
 *
 * Author: Kyungyin.Kim < kyungyin.kim@medithinq.com >
 * Copyright (c) 2021, MedithinQ. All rights reserved.
 */
#include <unistd.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include <string>

#include "Preprocessing.h"
#include "CircularQueue.h"

static void* producer_proc(void* param)
{
    CircularQueue* queue = (CircularQueue*)param;

    int num = 0;
    while(1)
    {
        getchar();
        queue->push(num++);
    }

    return NULL;
}

static void* consumer_proc(void* param)
{
    CircularQueue* queue = (CircularQueue*)param;
    while(1)
    {
        int d = queue->pop();
        printf("%d\n", d);
    }

    return NULL;
}

typedef struct test
{
    int age = 21;
    std::string name = "test";
}test_t;

#include "Log.h"
int main(UNUSED_PARAM int argc, UNUSED_PARAM char** argv)
{
    CircularQueue queue(5);
/*
    pthread_t producer;
    pthread_t consumer;

    pthread_create(&producer, NULL, producer_proc, &queue);
    pthread_create(&consumer, NULL, consumer_proc, &queue);

    printf("sise : %d", queue.size());

    while(1)
        sleep(1);
*/
/*
    printf("\033[31mdata : %d\n", queue.pop());

    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);
    queue.push(5);
    queue.push(6);

    printf("sise : %d\n", queue.size());

    printf("data : %d\n", queue.pop());
    printf("data : %d\n", queue.pop());

    printf("sise : %d\n", queue.size());

    printf("data : %d\n", queue.pop());

    printf("sise : %d\n", queue.size());
*/
    LOGT("aaaa %d\n", 11);
    LOGD("Debug %d\n", 12);
    LOGI("Info %d\n", 13);
    LOGW("Warning %d\n", 14);
    LOGE("Error %d\n", 15);
    
    test_t test;
    test.age = 19;
    test.name = "eeeee";
    printf("%s\n", __PRETTY_FUNCTION__);
    printf("%s\n", __BASE_FILE__);

    Log::hexDump(&test, sizeof(test_t));

    return 0;
}
