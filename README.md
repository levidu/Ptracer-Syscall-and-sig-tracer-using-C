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

