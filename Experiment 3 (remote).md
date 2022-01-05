# Experiment 3

### Analyzing the configuration file for a Cisco router

1. ##### Router name:

   gnu-rtrl

2. ##### Ethernet Ports available and of what type (fast-ethernet, gigabit, etc.)

   There's two Ethernet Ports available: FastEthernet0/0 & FastEthernet0/1

3. ##### Configured IP addresses and netmask of ports

​        From FastEthernet0/0: 172.16.30.1 255.255.255.0

​        From FastEthernet0/1: 172.16.254.45 255.255.255.0

#####    4. Configured routes

```
ip route 0.0.0.0 0.0.0.0 172.16.254.1
ip route 172.16.40.0 255.255.255.0 172.16.30.2
```

###  NAT configuration on the router

a. Which interface is connected to the Internet? It's FastEthernet0/1 (ip nat outside)

b. How many IP addresses are available for *NATing*? 172.16.254.45

c. Is the router using overloading or not? Yes

### 

​        

