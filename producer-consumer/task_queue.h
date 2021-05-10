struct task
{
    int id;
    int val;
};

struct task_node
{
    struct task t;
    struct task_node *next;
};

struct task_queue
{
    struct task_node *first;
    struct task_node *last;
    size_t size;
};

typedef struct task_node task_node;
typedef struct task task;
typedef struct task_queue task_queue;

task_queue *task_queue_init();

int task_queue_is_empty(task_queue *queue);

void task_queue_enqueue(task_queue *queue, task task);

void task_queue_dequeue(task_queue *queue, task *extracted);

void task_queue_print(task_queue *queue);