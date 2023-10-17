#!/bin/bash


sudo apt update;
sudo apt install ntp;
# list ntp servers, create a pool & fudge, and disable monitor and make logs available
# There is also an option to disable rollback to Ubuntu ntp servers
sudo cp /etc/ntp.conf /etc/ntp.conf.bak;
sudo gedit /etc/ntp.conf;
sudo systemctl start ntp;
sudo systemctl status ntp;
# If needed enable through firewall 'firewall-cmd --permanent --add-seervice=ntp'
# and reload firewall-cmd --reload

# check servers
ntpq -p;

# put local ntp server in client
# install and use ntpdate -u {local ntp server} on client
# start ntp on client with systemctl
