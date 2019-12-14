- app monitors RAM usage of a process or *group* of processes (browser, database,etc.).
- intended to answer "shared memory multiple times" problem/
  - both standard memory tools and this app read `/proc` interface
  - this app uses `/proc/processid/pagemap` to connect frames (physical memory segments)  with pages (virtual memory segments),
  - then filters them, leaving only unique and present (not swapped out)
- some info https://www.kernel.org/doc/Documentation/vm/pagemap.txt
<br/>
<br/>
- dev:
  ```shell


  $ sudo apt install build-essential
  $ sudo apt install qtcreator
  $ sudo apt install qt5-default

  $ git clone https://github.com/sergeiudris/linux-memory-monitor

  # open project and 'build'

  ```