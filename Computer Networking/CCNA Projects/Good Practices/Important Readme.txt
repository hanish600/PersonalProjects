### Some Good Tips for Live Networks ###

1. Set logins and secret passwords for all devices
2. Use portfast for all non-router/switch devices that connect to a router or switch
3. Use cdp & PAgP for cisco devices, but lldp & LACP for non-cisco devices
4. Use mst for non-cisco devices
5. Set up any redudndancy links with etherchannels(cisco devices)
6. It is good to set etherchannels as p2p instead of shared for performance
7. Avoid using telnet and use ssh instead
8. Make backups and always save run to start config and avoid using write command in case of config register difference
9. Avoid vtp as it can cause new devices added to mess up the network and can cause problems
10. L3 switch routing has great performance benefits over a L3 router(Might be different today), but is limited in features
11. Set up login banners to prevent hackers
12. Use bpduguard