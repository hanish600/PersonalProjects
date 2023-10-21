#!/bin/bash

# Each process executes a program
# Each process has a parent & parent id
# Each process has a pid, and the owner deterines (e)uid, and the groups (e)gid
# Internally uses fork(clone/copy) and exec
# Pid 1 reserved for init(systemd)

# Niceness determines priority of the process
# Niceness with the lowest value in the range deterines higher priority

# Threads are smaller lightweight processes and share same memory space
# Threads are a piece of a process (process creates threads)
# Threads are faster but limited due to sharing resources and being lightweight
# Also since memory is shared, values can get overwritten

# View processes
ps; # common options -e or -a: every process -u for userlist -l for long format x for register format -f for full

# View detailed information about processes (Can combine with m)
top;
# Better view (Can combine with f5 + m)
htop; # Alternative NetData is an amazing tool

# We can change niceness of a process from -20 to 19
# Set to lowest priority
sudo renice 19 {pid-here};

# These are signal codes for Proccesses
# We can use man pages to learn more
kill -l; # View signals

# Examples include: 
sudo kill 9 {pid-here}; # Signal kill
sudo kill 15 {pid-here}; # Signal terminate
sudo kill 19 {pid-here}; # Signal Stop process
# To kill all user processes:
# use pkill

# To view process files
# Go to /proc/(pid)

# List open files
lsof | head;

# To trace a process
strace man man;

# Find pid of a item
pidof rsyslogd;