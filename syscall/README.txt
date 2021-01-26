Name: Manos Chatzakis
AM  : 4238
Mail: csd4238@csd.uoc.gr

HY345 - Assignment 3

For this assignment we create an additional system call, which sets computation deadlines for different processes.
As every process should be able to change the params of his children/grandchildren etc.. the algorithm works as follows:

1) Using "for_each_process" macro, we iterate each process running.
2) If the process has the same pid as the pid given, we check if this process is a child/grandchild of the current process, using the parent list.
3) If the process with selected pid is actually child/grandchild etc.. of the current process (the calling process) the fields are changed and 0 is returned.
4) If deadline<=computation_time, or pid<-1 or pid is not a child/current or if it does not exist, EINVAL is returned (22). 
