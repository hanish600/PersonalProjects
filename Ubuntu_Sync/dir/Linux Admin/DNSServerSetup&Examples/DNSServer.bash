#!/bin/bash

sudo apt update;
sudo apt install -y bind9;
named -v;
cd /etc/bind;
# view config info
cat /etc/bind/zones.rfc1918;
ls;
hostnamectl status;
sudo vim /etc/hosts # edit with the domain name
sudo cp /etc/bind/named.conf.options named.conf.options.bak;
# edit this file with recursion yes, listen-on {the-ip;}; , allow-transfer{none;};
# forwarders {the-ip;};
sudo vim /etc/bind/named.conf;
sudo cp /etc/bind/named.conf.local named.conf.local.bak;
# add in the 
# zone "domain" IN {
# type master  Alternative you can use the secondary slave types
# file "/etc/bind/db.domain";};

# also add the reverse lookup zone by replacing domain with ip
# start with reverse-ip.in-addr.arpa using the ip address in reverse
sudo gpedit /etc/bind/named.conf.local;
sudo cp db.local db.name.local;
# replace local host with domain name add in some records
sudo gpedit db.name.local;
# Copy with your domain add some records
sudo cp db.127 db.{reverse-ip};
sudo systemctl start named;

# To Permenantly save this DNSServer
cat /etc/resolv.conf;
sudo rm /etc/resolv.conf;
sudo ln -sf /run/systemd/resolve/resolv.conf /etc/resolv/conf;
sudo gedit /etc/resolv.conf; # add nameservers if using older version try /etc/nsswitch.conf

