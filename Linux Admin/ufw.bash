#!/bin/bash

sudo apt update;
sudo apt install ufw;
sudo ufw status;
cat /etc/default/ufw;
# If your service is active
sudo ufw disable;
# To reset rules
# These will be backed up
sudo ufw reset;
# Setting incoming and outgoing connections to deny any incoming and allow all outgoing
# by default
sudo ufw default deny incoming;
sudo ufw default allow outgoing;
# stop the systemctl service
sudo systemctl stop ufw;
# allow some rules
sudo ufw allow ssh; # 22
sudo ufw allow https; # 443
sudo ufw allow http; # 80
sudo ufw allow ftp; # 21
sudo ufw allow nfs;
sudo ufw allow samba; 
sudo ufw allow smtp; # smtp
sudo ufw allow smtps; # smtp
sudo ufw allow pop3; # POP 3
sudo ufw allow imaps; # imaps
sudo ufw allow from 10.0.2.15;
# network must be static to ensure connectivity for admin
sudo ufw allow from 10.0.2.15/24 to any port 3389; # rdp
sudo ufw allow from 10.0.2.15 to any port 3306; # mysql
# Deny some rules that are not secure
sudo ufw reject telnet; # 23
sudo ufw deny smtp;
# Note: This redirects the browser to https
sudo ufw reject http;
# restart services
sudo systemctl start ufw; 
sudo ufw enable;
# View rules
sudo ufw status;
# We can delete with:
sudo ufw status numbered;
sudo ufw delete 4; # removes rule 4