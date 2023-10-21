#!/bin/bash

# Create a file
touch aFile;

# Create a directory
mkdir aDirectory;

# Add a user
sudo adduser newUser;

# Remove user
sudo deluser newUser;

# Add a group 
sudo addgroup newGroup;

# Remove group
sudo delgroup newGroup;

# can use -r recursion for directories

# binary 4 read + 2 write + 1 execute
# Owner Group Other
# can also use u+rwx or - to remove or add permissions on u(sers) g(roup) o(ther) 
# can also use g=r where = sets equal permissions
sudo chmod 750 aFile;
sudo chmod o+x aFile;
sudo chmod g=r aFile;

# To change owner use chown
# :new_group is not required
sudo chown new_owner:new_group aFile;

# To change group use chgrp
sudo chgrp new_group aFile;

# To work with attributes use chattr (see man pages)
# this command makes a file immutatable(cannot edit)
chattr +i aFile;

# add user to group
# use usermod with -g only to change primary group
sudo usermod -a -G group_names user

# See setfacl and getfacl for greater control
# setfacl and getfacl can get confusing with multiple users, and groups 
# This will add a user not in the basic permissions to allow extra permissions
setfacl -m u:UserNotInPermissions:rwx aFile;
getfacl;

# To view permissions
# s can be used for setuid and setgid for changing permissions to it
# t can be used for allowing only owner permissions
ls -l;

# View attributes
lsattr;

# Current User
whoami;
# All users on system
cat /etc/passwd;
# All groups on system
cat /etc/group;