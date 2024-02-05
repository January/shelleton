Shelleton
==========
A basic, Bash-inspired Unix shell that I made. It's not very complex, but it does everything you would expect a shell to do. It can:
- Run executables
- Search your `PATH` for executables if the executable you want is not present in that directory
- Perform background and foreground execution
- Perform I/O redirection using `<`, `>`, and `>>`
- Utilize pipes
- Ignore comments (anything prefixed with `#` will be ignored by Shelleton)
- Read/write environment variables

And there are a few commands built in:

- `echo`: Prints the string given to it as an argument. Can read from environment variables.
- `export`: Sets the value of an environment variable.
- `pwd`: Prints the full path of the working directory.
- `cd`: Change the working directory.
- `jobs`: Print all currently running background processes.
- `kill`: Terminate a process using the provided POSIX signal number and process ID.
- `quit`/`exit`: Leave Shelleton.

I may add more commands and features at some point in the near future, but it's not a high priority for me right now.

Also, the name "Shelleton" stuck because when I started making this, it was around Halloween, which is often symbolized by skeletons, and I thought that since this shell was light and basic but structurally sound, it could perhaps be compared to a skeleton.