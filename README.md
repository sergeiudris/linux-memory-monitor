## Linux memory monitor

App calculates how much RAM (aka RSS) a process or group of processes (browser, database,etc.) occupies. 

Solves "shared memory multiple times" problem of standard tools.

[Download console version executable](https://github.com/serge-joggen/linux-memory-monitor/releases/download/v0.1/ui_console)


[Download GUI version executable](https://github.com/serge-joggen/linux-memory-monitor/releases/download/v0.1/ui_graphical)


### Run

1. open `Release/ui_graphical/` and copy `ui_graphical` executable file to another directory if you want
2. open terminal (ctrl+alt+t), go to the directory with the executable
3. run commands:
```shell
   $ chmod +x ui_graphical     # grant permissions for every user to access file
   $ sudo ./ui_graphical       # run app as superuser (aka root) - needed to read files in /proc directory
```
*  use same for console version

### Why  

To answer the question how much RAM does a group of processes occupy. 

### How 

Both standard memory tools and this app read /proc interface, but this program goes further: it utilizes
`/proc/processid/pagemap` to connect frames (physical memory segments)  with pages (virtual memory segments),
and then filter them, leaving only unique and present (not swapped out).

https://www.kernel.org/doc/Documentation/vm/pagemap.txt

![Alt text](/gui.png?raw=true "gui")

![Alt text](/console.png?raw=true "console")

### License

Copyright © 2015 serge-joggen  The app  is licensed under [GPL3](http://www.gnu.org/licenses/gpl-3.0.html)
