# Experiment 3

## Analyzing the configuration file for a Cisco router

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

##  NAT configuration on the router

1. **Which interface is connected to the Internet?**
      It's *FastEthernet0/1* (ip nat outside).

2. **How many IP addresses are available for *NATing*?**
   One (172.16.254.45).
3. **Is the router using overloading or not?**
   Yes.

## DNS configs

2. There aren't any DNS packets, only *icmp*.

![DNS](screenshots/exp3/1.png)

![DNS](screenshots/exp3/2.png)

![DNS](screenshots/exp3/3.png)

3. The destination address of the DNS query is 10.50.52.1.

![DNS](screenshots/exp3/4.png)

4. Destination was 9.9.9.9.

   ![DNS](screenshots/exp3/5.png)

   ![DNS](screenshots/exp3/6.png)

## Linux Routing

1. The default gateway is 10.0.2.1.

   ![DNS](screenshots/exp3/7.png)

2. Delete the default gateway entry

   ![DNS](screenshots/exp3/8.png)

3. As predicted the DNS server is not reachable, as no default route exists.
   ![DNS](screenshots/exp3/9.png)

4. Add a specific route for `104.17.113.188` to the gateway found on 1 (10.0.2.1) .
   ![DNS](screenshots/exp3/10.png)

5. Wireshark logs with traceroute -n 104.17.113.188 .
   ![DNS](screenshots/exp3/11.png)

6. Wireshark logs with traceroute -n who.int

   ![DNS](screenshots/exp3/12.png)

   - ![DNS](screenshots/exp3/13.png)
   - ![DNS](screenshots/exp3/14.png)
   - ![DNS](screenshots/exp3/15.png)

   

7. ![DNS](screenshots/exp3/16.png)

   

