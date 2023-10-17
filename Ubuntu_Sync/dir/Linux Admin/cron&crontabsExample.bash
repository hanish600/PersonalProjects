#!/bin/bash

# We can put the minute, hour, day, month, and day of week and the command 
# Alternatively we can set * for every minute, hour, day, month, and day of week
# Recommendations: Use Full Paths


# We can test the first cron job by adding 
# * * * * * ls -lh > myCronJob.txt

# To run cron under a single user
# we can run this through the terminal
crontab -e;


# To run cron under root we use the following:
sudo crontab -u root -e;

# To list single user & root cron jobs
crontab -l;
sudo crontab -u root -l;

# system-wide crontab jobs are found in:
sudo vim /etc/crontab;

# to view jobs that have ran 
cat /var/log/syslog | grep CRON;
