#!/bin/bash

sudo apt update;
sudo apt install -y vsftpd;
sudo service vsftpd status;

# do local_enable=YES and write_enable=YES to enable local users and ftp uploading
# restrict users to their home directory using chroot_local_user=YES
# generate home directory with sub_token and the directory to change to with local_root by
# adding user_sub_token=$USER and local_root=/home/$USER/ftp
# set ports with pasv_min_port= and pasv_max_port=
# allow only local database with userlist_enable=YES, userlist_file=/etc/vsftpd.userlist,
# and userlist_deny=NO
sudo gedit /etc/vsftpd.conf;

# create a directory and change permissions
sudo mkdir /home/example/ftp;
sudo chown example:example /home/example/ftp;

# allow ftp access by listing it in the database
echo "example" >> /etc/vsftpd.userlist

# We can add in a key using openssl
sudo openssl req -x509 -nodes -days 3650 -newkey rsa:2048 -keyout /etc/ss/private/vsftpd.pem -out /etc/ssl/private/vsftpd.pem

# replace certificates in vsftpd.conf
# use rsa_cert_file=/etc/ssl/private/vsftpd.pem
# rsa_private_key=/etc/ssl/private/vsftpd.pem
# ssl_enable=YES
# also allow the ssl created by adding
# allow_anon_ssl=NO
# force_local_data_ssl=YES
# force_local_logins_ssl=YES
sudo gedit /etc/vsftpd.conf;

# start the service
sudo systemctl start vsftpd;