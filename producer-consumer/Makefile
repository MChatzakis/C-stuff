all : task_queue.c task_queue.h prod_cons.c 
	gcc prod_cons.c task_queue.c -o prod-cons.out -pthread

clean:
	rm -f prod-cons.out	