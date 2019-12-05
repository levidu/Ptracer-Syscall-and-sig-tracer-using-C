Team 13
=======
|Members |Github links|
|--------|------------|
|  Manjusha Vallabhaneni|https://github.com/manjusha1691|
|Levidu Alahakoon|https://github.com/levidu |
|  Amandeep Singh|https://github.com/amansinghammy |
The Progress of the project can be seen in [ProgressUpdate](https://github.com/ualbany-csi402-f19/project-13/blob/master/progress.md)

Documentation 
----------
Video submission link: https://www.screencast.com/t/HTFdRzfi

**Important notes to run our ptracer** 

Due to hardships to make the program with the specified format, we used our own format to make the program run with errors. Please use the following command to run our ptracer in project-13: `ptracer` `command` `[args]` `[-h]` `[-f file]` 
![Screenshot of format that the user should enter](https://content.screencast.com/users/Levidu/folders/ICSI402/media/3d34a8a3-9a1b-42e4-b9e5-ff4bcb81fa4c/Screen%20Shot%202019-12-05%20at%206.47.30%20PM.png)

**Expected outcomes of System calls**

We have managed to complete 10/15 system calls.
  
|syscall# |syscall|comment|
|---------|-------|------|
|0|read|Managed to gather all the actual values for its arguments|
|1|write|Managed to gather all the actual values for its arguments. However, we also get the stdout result. We assume that we failed to pokedata and retrieve it as an empty string|
|2|open|Managed to gather all the actual values of its arguments|
|3|close|Managed to gather all the actual values of its arguments|
|5|fstat|Managed to gather all the actual values of its arguments. However, failed to retrieve the hexadecimals on some arguments|
|6|lseek|Managed to gather all the actual values of its arguments|
|22|pipe|Could not implement the system call|
|32|dup|Managed to gather all the actual values of its arguments|
|33|dups|Managed to gather all the actual values of its arguments|
|39|getpid|We had difficulty on how to retrive the registers for this syscall. Since, all the registers are empty for this syscall|
|56|fork|We failed to retrieve this information in some cases|
|59|execve|In some commits, we managed to get this system call working|
|61|wait4|We failed to retrieve this information|
|231|exit_group|Managed to gather all the actual values for its arguments|

**Technical difficulties we came across**

1. We managed to print the result to a file. However, not in a tabulated format.
2. We failed to convert some regs in long format to hexadecimal. Our `void decToHex(long)` encountered errors.
3. execve, seems to be the most important system call that we should have stressed on. However, this result was not detected by our ptracer.
4. The format that was given to us to run ptracer gave us runs. Thus, our program failed to compile. We put the `command` and its arguments: `[args]` right after `./ptracer`. Like the following -> `ptracer` `command` `[args]` `[-h]` `[-f file]`  

**Conclusion and improvements** 

Quotation marks and spaces were not included or modified as we got the information as it is from the registers. We believe that we could have implemented POKEDATA or a possible method that could have given as a much more similar results like in `strace`. Nevertheless, we successfully manage to retrieve the data in registered and managed to put it in a file that is specified by user arguments.

**Reference**

1. https://nullprogram.com/blog/2018/06/23/
2. http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
3. https://www.linuxjournal.com/article/6100

**Credit**

A source from https://nullprogram.com/blog/2018/06/23/ that was written by Chris Wellons helped us understand how to start this project and basically implement the backbone of ptracer. We thank this source and would hereby like to give credit to the author. It would not have been impossible to get a start if it is not to this source. 
Thank you! 
