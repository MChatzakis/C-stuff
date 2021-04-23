#include <pthread.h>
#include <stdio.h>

#include "task_queue.h"

#define TASKS 10

pthread_mutex_t task_lock;
task_queue *tq;

int total_tasks_inserted;
int task_available;

void *producer(void *thread_data);
void *consumer(void *thread_data);

void consume_task(task curr_task);
void create_task(task *curr_task);

int main()
{
  pthread_t producer_t, consumer_t;

  task_available = 0;
  total_tasks_inserted = 0;

  tq = task_queue_init();

  pthread_mutex_init(&task_lock, NULL);

  pthread_create(&producer_t, NULL, producer, NULL);
  pthread_create(&consumer_t, NULL, consumer, NULL);

  pthread_join(producer_t, NULL);
  pthread_join(consumer_t, NULL);

  pthread_exit(NULL);
}

void *producer(void *thread_data)
{
  int inserted;
  int tasks_create;
  task my_task;

  tasks_create = TASKS;
  while (tasks_create--)
  {
    inserted = 0;
    create_task(&my_task);
    while (inserted == 0)
    {
      pthread_mutex_lock(&task_lock);
      if (task_available == 0)
      {
        task_queue_enqueue(tq, my_task);
        printf("Producer -------- Enqueued Task [%d,%d].\n", my_task.id,
               my_task.val);

        total_tasks_inserted++;
        task_available = 1;
        inserted = 1;
      }
      pthread_mutex_unlock(&task_lock);
    }
  }

  pthread_exit(NULL);
}

void *consumer(void *thread_data)
{
  int extracted;
  int tasks_consume;
  task my_task;

  tasks_consume = TASKS;
  while (tasks_consume--)
  {
    extracted = 0;
    while (extracted == 0)
    {
      pthread_mutex_lock(&task_lock);
      if (task_available == 1)
      {
        task_queue_dequeue(tq, &my_task);
        printf("Consumer -------- Dequeued Task [%d,%d].\n", my_task.id,
               my_task.val);
        task_available = 0;
        extracted = 1;
      }
      pthread_mutex_unlock(&task_lock);
    }
    consume_task(my_task);
  }

  pthread_exit(NULL);
}

void consume_task(task curr_task)
{
  // printf("Consumer -------- Processed Task [%d,%d].\n", curr_task.id,
  // curr_task.val);
}

void create_task(task *curr_task)
{
  curr_task->id = total_tasks_inserted;
  curr_task->val = curr_task->id * 10;

  // printf("Producer -------- Created Task [%d,%d].\n", curr_task->id,
  // curr_task->val);
}