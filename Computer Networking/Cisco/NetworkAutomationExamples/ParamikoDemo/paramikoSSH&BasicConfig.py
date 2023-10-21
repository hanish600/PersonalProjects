import paramiko
from getpass import getpass # Can be used as input to hide password in terminal

# This is an example of how to send commands through paramiko on switches and routers

# Create device list
devices = {
    "iosxe-R1":{
        "ip":"10.10.20.175",
        "username":"cisco",
        "password":"cisco",
        "port":"22"
    },
    "iosxe-R2":{
        "ip":"10.10.20.176",
        "username":"cisco",
        "password":"cisco",
        "port":"22"
    },
    "iosxe-SW1":{
        "ip":"10.10.20.177",
        "username":"cisco",
        "password":"cisco",
        "port":"22"
    },
    "iosxe-SW2":{
        "ip":"10.10.20.178",
        "username":"cisco",
        "password":"cisco",
        "port":"22"
    }
}

# connect devices to python paramiko
def make_connect(host,usr,pwd,port):
    ssh=paramiko.SSHClient()
    ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ssh.connect(hostname=host,port=port,username=usr,password=pwd,look_for_keys=False,allow_agent=False)
    return ssh

command="sh run\n"

# Store output of sessions into collection
collection=[]

for device in devices:
    print(f"Execution is on device: {devices[device]['ip']}\n\n")
    session=make_connect(devices[device]["ip"],
                         devices[device]["username"],
                         devices[device]["password"],
                         devices[device]["port"])
    stdin, stdout,stderr = session.exec_command(command)
    output = stdout.readlines()
    splits = ' '.join(map(str,output))
    collection.append(splits)

# print devices obtained in paramiko

for device in range(0,len(collection)):
    print("Showing Results for: ",list(devices.keys())[device],'\n')
    print(collection[device])
    print('\n','\n')

# turn on logging for all
for device in devices:
    print(f"Execution is on device: {devices[device]['ip']}\n\n")
    session=make_connect(devices[device]["ip"],
                         devices[device]["username"],
                         devices[device]["password"],
                         devices[device]["port"])
    commands="conf t\n \logging on\n"
    stdin,stdout,stderr=session.exec_command(commands)