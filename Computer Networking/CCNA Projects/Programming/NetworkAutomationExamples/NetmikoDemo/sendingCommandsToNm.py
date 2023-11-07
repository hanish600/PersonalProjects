from netmiko import ConnectHandler

# This is an example of how to send commands through netmiko on switches and routers

# we can reuse paramiko dict loop for this if needed
device = {
    "device_type":"cisco_xe",
    "host":"10.10.20.175",
    "username":"cisco",
    "password":"cisco"
}
net_connect=ConnectHandler(**device)
# elevate 
net_connect.enable()
command="sh version"
with net_connect:
    output=net_connect.send_command(command)
print(output)

# We can do something like this to execute commands
commands = ["logging buffered 10000"]

with ConnectHandler(**device) as net_connect:
    # This will go to config terminal mode and execute commands
    output =net_connect.send_config_set(commands)
    # This will write to startup config
    output += net_connect.save_config()
print(output)
net_connect.disconnect()