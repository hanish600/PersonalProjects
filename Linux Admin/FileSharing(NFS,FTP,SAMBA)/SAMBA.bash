#!/bin/bash 

# Installing SAMBA
sudo apt update;
sudo apt install -y samba;
#sudo systemctl status smbd;

# Backing up samba
cd /etc/samba;
ls;
sudo mv smb.conf smb.conf.bak

# Stop Samba to edit
sudo systemctl stop smbd;
#sudo systemctl status smbd;

# Edit smb file
touch smb.conf
echo "[global]" > smb.conf;
echo "server string = File Server" >> smb.conf;
echo "workgroup = WORKGROUP" >> smb.conf;
echo "security = user" >> smb.conf;
echo "map to guest = bad user" >> smb.conf; 
echo "name resolve order" = "bcast host" >> smb.conf;
echo "include = /etc/samba/shares.conf" >> smb.conf;

# edit share paths and user + group
touch shares.conf;
echo "[Public Files]" > share.conf;
echo "path = /share/public_files" >> share.conf;
echo "force user = smbuser" >> share.conf;
echo "force group = smbgroup" >> share.conf;
echo "create mask = 0664" >> share.conf;
echo "force create mode = 0664" >> share.conf;
echo "directory mask = 0775" >> share.conf;
echo "force directory mode = 0775" >> share.conf;
echo "public = yes" >> share.conf;
echo "writable = yes" >> share.conf;

# Create the share path & edit permissions
sudo mkdir -p /share/public_files;
ls -l;
sudo groupadd --system smbgroup;
cat /etc/group;

# We don't want a new home directory or shell here although it can be created
sudo useradd --system --no-create-home --group smbgroup -s /bin/false smbuser;
cat /etc/passwd;
sudo chown -R smbuser:smbgroup /share;
ls -l /share;
sudo chmod -R g+w /share;

sudo systemctl start smbd;
