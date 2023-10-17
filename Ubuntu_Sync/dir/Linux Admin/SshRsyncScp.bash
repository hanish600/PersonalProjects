#!/bin/bash

# To use ssh use -p if port is different from 22
# Input the name@ip
# Enter the password
sudo ssh -p 22 name@ip;

# To use secure copy use the following:
sudo scp filename name@ip:/directory_to_copy_to;

# rsync should be installed first
# Should be automatically installed in ubuntu
# use -a to sync recursive
# can be used for local host if name@ip:/ is removed
rsync -a /myDirectory name@ip:/directory_to_copy_to;
