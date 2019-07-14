Q1: in my experiement, child process is the copy of parent process, so it gain exatly the same variable as parent process before folk(). But after folk(), the variable in the two process are in different address space. So no matter child process or parent process do the change, the variable own by each process will not be affected by another one.

Q2: for the file descriptor opened before fork(), child process can accees it through it. And I find if parent process and child process write to file concurrently, there will be no racing condition.
	Since these two process dose not shared the same file table, which contains the file offset or other file information.
Action: ./hwk2
		 cat normal_file  | grep child | wc -l   


Q3: I use pipe to do the sync of two processes. 


Q4: execlxxx will use list to pass the process and arguments, which may need programer to type into. Which is not like execvxxx, user only need to pass the pointer of vector.
 Besides, although execlp and execvp are so convenient so that user don't need to specify the exact path of program, the will suffer some security problem. The hackers can inject thier path into $PATH. 

Q5: 
	the wait() will return the pid of child which is terminated and wait by parent process. if wait() in child process, the return value will be -1, and corresponding errno indicating no child process to wait.

Q6: In the condition that parent has several child process. I think waitpid() is good at waiting child process in certain PID.

Q7: The printf will not show message in the screen.
