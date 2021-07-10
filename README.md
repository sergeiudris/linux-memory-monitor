## lmm

- a linux-specific app that calculates RAM usage for a group of processes
  - uses /proc/processid/pagemap to connect frames (physical memory segments) with pages (virtual memory segments)
  - then filters out 'swapped out', keeping only 'unique' and 'present'
- a one-off elsewhere-useless situational solution
- but made with a pinch of curiosity and effort
- [screenshots](./docs/preview.md)
