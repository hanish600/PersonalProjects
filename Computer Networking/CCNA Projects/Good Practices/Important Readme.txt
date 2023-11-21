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
10. Seperate broadcast and collision domains with vlans,switches and routers to add performance and security
11. Set up login banners to prevent hackers
12. Use bpduguard
13. Use Key Chains
14. Auto-summary is inaccurate and should be disabled and manual summary should be used.
15. Summarization reduces memory, improves bandwidth(less to advertise), improves cpu(less checking)
16. EIGRP unequal costs can be optimized with variance tuning (Use AD/FD)
17. Set exec-timeouts for security
18. Use ssh version 2 (instead of the default version 1)
19. Set minimum password length using the security command 
20. Set failed login timeouts using the login command
21. Use Patch Panels & block 110 (Don't replace those expensive switch ports)
22. Use descriptions and acl remarks