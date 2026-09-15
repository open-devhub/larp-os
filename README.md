# TODO list

+ Minimal shell setup with some basic commands (that do not involve filesystem operations such as reading/writing files)
+ Command line arguments, environment variables, exit codes and PATH.
+ System calls and abstraction layer (read below for explanation)
+ File abstraction (also read below)
+ Virtual filesystem
+ Device files (like /dev/urandom, /dev/zero, etc.)
+ Commands that involve filesystem operations and redirection operators (`>` and `>>`)
+ Processes


## what are system calls?
Instead of the user being able to directly do an operation, such as reading a file, instead, it asks the kernel to do it.<br>

This is used in real operating systems as a safety layer, because if every app could directly touch the memory or the storage, it would be much easier for the computer to be hacked<br>

So how does it work?<br>
+ There are multiple system call types, each one has a unique number assigned to it. (i.e. SYS_READ = 0, SYS_WRITE = 1, etc.)
+ When invoking a system call, it goes to the kernel, and the kernel calls the functions that are needed to complete the operation, and then returns an exit code.
+ The user, invokes a system call through an abstraction layer, meaning, all system calls are called by the same function: `systemcall()`
+ The `systemcall()` function can have these arguments:  `(int syscall_number, int arg1, int arg2, int arg3, int arg4)`
+ arg1...arg4 are the arguments that are needed for the operation to complete: For example, reading a file would need 3 arguments: file path, length to read, output buffer. Or, exiting a process, only needs 1 argument, the exit code. So it doesn't matter if the call itself doesn't need exactly 4 arguments.


## what is file abstraction?
In unix-like systems, there are character devices, like /dev/urandom, which seem to have an infinite size. But how can there be a file with infinite size?<br>

The answer is simple: it is not an actual file, it is just made in a way to appear like one.<br>

So if its not an actual file, how can you read from it, as if it is an actual file, using the same functions you would use on a real file?<br>

This is called file abstraction, it is the mechanism where all files (special or not), are read/written using the same exact function.<br>
For example, when calling `fread()` on a file like /dev/urandom, the kernel checks its file type (if its a special file), and if it is, it calls another function depending on the file type.<br>
For the case of /dev/urandom, it calls a function that generates a random number. If it were /dev/zero, it would call a function that generates null bytes.
