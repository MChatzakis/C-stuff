/*
* Manos Chatzakis, csd4238@csd.uoc.gr
*/
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <asm-generic/errno-base.h>

int
is_child(struct task_struct *i){
	struct task_struct *temp_cur;
	temp_cur = i;
	/*NULL comparison is just for safety, as the list is cyclic*/
	while(temp_cur != NULL && temp_cur->pid != 0){
		if(temp_cur->pid == current->pid) return 1;
		temp_cur = temp_cur->parent;
	}
	return 0;
}

asmlinkage long
sys_deadline_sys(int pid, unsigned long deadline, unsigned long computation_time){

	struct task_struct *i;

	printk("Manos Chatzakis csd4238: Called system call set_deadline with args: %d %lu %lu\n",pid,deadline,computation_time);

	if(pid < -1 || deadline <= computation_time) return EINVAL;
	else if(pid == -1 || current->pid == pid){
		(current->d_p).deadline = deadline;
		(current->d_p).computation_time = computation_time;
		//printk("New params set with values (pid,deadline,comp_time) = (%d,%lu,%lu)\n",current->pid,(current->d_p).deadline,(current->d_p).computation_time);
		return 0;
	}
	else{
		/*list_for_each(list,&process->children){
			i = list_entry(list, struct task_struct, sibling);
			if(i->pid == pid){
				(i->d_p).deadline = deadline;
				(i->d_p).computation_time = computation_time;
				return 0;
			}
			i = list_entry(list, struct task_struct, children);
			if(i->pid == pid){
				(i->d_p).deadline = deadline;
				(i->d_p).computation_time = computation_time;
				return 0;
			}
		}*/

		/*Iterates over all processes and finds the process with given pid.
		  If the aforementioned process is child/grandchild ... of the current process,
		  it sets the new deadlines.*/
		for_each_process(i){
			if(i->pid == pid && is_child(i)){
				(i->d_p).deadline = deadline;
                                (i->d_p).computation_time = computation_time;
				//printk("New params set with values (pid,deadline,comp_time) = (%d,%lu,%lu)\n",i->pid,(i->d_p).deadline,(i->d_p).computation_time);
				return 0;
			}
		}
	}

	return EINVAL;
}
