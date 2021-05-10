#include <stdio.h>
#include <stdlib.h>

#include "task_queue.h"

struct task_queue *task_queue_init()
{
    struct task_queue *new_queue;
    new_queue = (struct task_queue *)malloc(sizeof(struct task_queue));

    new_queue->first = NULL;
    new_queue->last = NULL;
    new_queue->size = 0;

    return new_queue;
}

int task_queue_is_empty(task_queue *queue)
{
    return (queue->last == NULL);
}

void task_queue_enqueue(task_queue *queue, task task)
{
    task_node *new_task;
    new_task = (task_node *)malloc(sizeof(task_node));

    (new_task->t).id = task.id;
    (new_task->t).val = task.val;
    new_task->next = NULL;

    if (task_queue_is_empty(queue))
    {
        queue->first = new_task;
        queue->last = queue->first;
    }
    else
    {
        (queue->last)->next = new_task;
        queue->last = (queue->last)->next;
    }

    queue->size++;
}

void task_queue_dequeue(task_queue *queue, task *extracted)
{
    task_node *tmp;

    if (task_queue_is_empty(queue))
    {
        extracted->id = -1;
        return;
    }

    extracted->id = (queue->first->t).id;
    extracted->val = (queue->first->t).val;

    tmp = queue->first;
    queue->first = queue->first->next;

    if(queue->first == NULL){
        queue->last = NULL;
    }

    queue->size--;

    free(tmp);
}

void task_queue_print(task_queue *queue)
{
    task_node *curr;
    int counter = 0;

    if (queue == NULL)
    {
        return;
    }

    printf("Queue of %ld tasks:\n", queue->size);

    curr = queue->first;
    while (curr != NULL)
    {
        printf("Task %d : [%d,%d]\n", counter, (curr->t).id, (curr->t).val);

        counter++;
        curr = curr->next;
    }
}