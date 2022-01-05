# Experiment 3

## Analyzing the Configuration File for a Cisco Router

1. ##### Router Name:

   gnu-rtrl

2. ##### Ethernet Ports available and of what type (fast-ethernet, gigabit, etc.)

   There's two Ethernet Ports available: FastEthernet0/0 & FastEthernet0/1

3. ##### Configured IP addresses and netmask of ports

   From FastEthernet0/0: 172.16.30.1 255.255.255.0

   From FastEthernet0/1: 172.16.254.45 255.255.255.0

4. **Configured Routes**

```
ip route 0.0.0.0 0.0.0.0 172.16.254.1
ip route 172.16.40.0 255.255.255.0 172.16.30.2
```



##  NAT configuration on the router

1. **Which interface is connected to the Internet?**
   It's *FastEthernet0/1* (ip nat outside).
2. **How many IP addresses are available for *NATing*?**
   One (172.16.254.45).
3. **Is the router using overloading or not?**
   Yes.

​        

