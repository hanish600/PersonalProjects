# This file is about learning python sockets
import socket
import sys
import argparse
from binascii import hexlify
# Get host
def printBasicInfo():
    host=socket.gethostname()
    ip=socket.gethostbyname(host)
    print("Host: ", host,'\n', \
          "IP: ",ip,'\n')
printBasicInfo()

# View capabilities, remote_host IPv6 and IPv4
print("Dualstack Platform: ", \
      socket.has_dualstack_ipv6(),'\n')
print("Google's IP: ", \
      socket.getaddrinfo("google.com",443,proto=socket.IPPROTO_TCP)[0][4][0], \
      " OR ",
      socket.gethostbyname("google.com"))
print('\n')

# Attempt remote host
def tryPyHost():
    remote_host = "www.pytgo.org"
    try:
        print("IP address of python:", \
              socket.gethostbyname(remote_host))
    except socket.error as err:
        return err
print("Error msg: ",tryPyHost(), '\n')

# Convert address to bytes, bytes to address
def convertipv4():
    for ip_address in ['127.0.0.1','192.168.0.1']:
        packedIP=socket.inet_aton(ip_address)
        unpackedIP=socket.inet_ntoa(packedIP)
        print("Packed IP Address: ",hexlify(packedIP),'\n',\
              "Unpacked IP Address: ",unpackedIP,'\n',sep='')
convertipv4()

# View the different port services
# Parameters: protocol='tcp'/'udp', portsArray=[port_num]
def servicePorts(proto='tcp',portsArr=[]):
    portsArr=[443,53,993,2525,21,22,23,109,25,110,3389]
    for port in portsArr:
        print("Port: ",port," => service: ",\
              socket.getservbyport(port,proto),'\n')
servicePorts()

# Convert data to network and host byte order
# long uses 32 bit short uses 16 bit
# Parameters: data(int)
def conversions(data):
    print("Network to host long: ",socket.ntohl(data), \
          '\n',"Host to network long: ",socket.htonl(data), \
          '\n',"Network to host short: ",socket.ntohs(data), \
          '\n',"Host to network short: ",socket.htons(data), '\n',sep='')
conversions(1234)

# Set a socket timeout timer
# Parameters: time(seconds)
def socket_timeout(time):
    # Use Address family, and TCP
    sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    print("default:",sock.gettimeout(),'\n')
    sock.settimeout(time)
    print("new socket timeout:",sock.gettimeout(),'\n')

socket_timeout(120)
    
