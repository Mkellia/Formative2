Q1: Process & File Handling
What it does:

Creates a child process to run a command (e.g. ls) using fork() and execvp()

Parent writes to and reads from a temporary file

System calls are traced using strace

Run it:

./Q1 ls
Q2: Buffered vs Unbuffered Logging
What it does:

Writes 1,000,000 log entries to a file

unbuffered: uses write() → many system calls

buffered: uses fprintf() → fewer system calls

Compared using strace -c and time

Run with strace:

strace -c ./unbuffered  
strace -c ./buffered
Result summary:

Buffered: ~7K system calls, ~0.56 sec

Unbuffered: 1M system calls, ~110 sec

Buffered is faster and more efficient

Q3: Palindrome Counter with Threads
What it does:

Uses 20 threads to count palindromic numbers from 0 to 100,000

Uses a mutex to safely update a shared counter

Run it:

Edit
./Q3
Q4: Multithreaded Log Merger
What it does:

Merges multiple log files into one output file

Each thread reads a file and writes safely to the output using lseek()

Synchronization is handled with a mutex

Run it:

./q4 merged_log.txt file1.txt file2.txt <num_threads>