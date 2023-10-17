#!/bin/bash

sudo apt update;
sudo apt install nfs-kernel-server;
# start automatically on boot
sudo systemctl enable --now nfs-server;
# create a directory
sudo mkdir -p /media/mynfs;
# put your directory, accepted ip addresse, and options
sudo gedit /etc/exports;
# load exports config
sudo exportfs -arv

sudo apt install nfs-common;
# set a mounting point at an ip address of the nfs server (Can be specified)
sudo mount -t nfs4 ipOfNfsServer:/media/mynfs /media/share
# insert ip_of_nfs_server:/media/mynfs  /media/share    nfs4    defaults,user,exec  0   0
# for permanent solution
sudo gedit /etc/fstab;
# get fstab config
sudo mount -a;