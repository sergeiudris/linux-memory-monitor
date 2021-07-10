# linux-memory-monitor
Program calculates how much RAM (aka RSS) a process or group of processes (browser, database,etc.) uses. Solves "shared memory multiple times" problem of standard tools

-- How to run --

1. open Release/ui_graphical/ and copy ui_graphical executable file to another directory if you want
2. open terminal (ctrl+alt+t), go to the directory with the executable
3. run
   $ chmod +x ui_graphical // grant permissions for every user to access file
   $ sudo ./ui_graphical  // run program as superuser (aka root) - needed to read files in /proc directory

*  use same for console version

-- Why  --

To answer the question how much RAM does a group of processes occupy. 

-- How --

Both standard memory tools and this program read /proc interface, but this program goes further: it utilizes
/proc/processid/pagemap to connect frames (physical memory segments)  with pages (virtual memory segments), and then filter them, leaving only unique and present (not swapped out).

https://www.kernel.org/doc/Documentation/vm/pagemap.txt

Build: will take from existing programs.
Language: clojure.
Runtime: gui binary - JVM, command line binary - GraalVM native image