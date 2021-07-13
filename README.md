## Linux memory monitor

App monitors RAM usage of a process or *group* of processes (browser, database,etc.).

Solves "shared memory multiple times" problem of standard tools.

Both standard memory tools and this app read `/proc` interface, but this program goes further: it utilizes
`/proc/processid/pagemap` to connect frames (physical memory segments)  with pages (virtual memory segments),
and then filter them, leaving only unique and present (not swapped out).

https://www.kernel.org/doc/Documentation/vm/pagemap.txt


![Alt text](/gui.png?raw=true "gui")

![Alt text](/console.png?raw=true "console")

### Dev

```shell


$ sudo apt install build-essential
$ sudo apt install qtcreator
$ sudo apt install qt5-default

# open project and 'build'

```