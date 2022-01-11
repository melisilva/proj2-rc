# Experiment 4

## Configure Linux Router

### Steps 

1. Connect a cable from tux34/`eth1` to the switch and place it in vlan31 
2. Verify the VLANs on the switch (`show vlan brief`).
3. Configure tux34/`eth1`'s IP address as per the figure (`172.16.31.253/24`).
4. Enable IP forwarding On tux34 .
5. Disable ICMP echo ignore broadcast On tux34 
6. Check the MAC addresses and IP addresses in tux34 for `eth0` and `eth1`.
7. Configure the routes in tux33 and tux32 so that they can reach each other.
           **In tux33**: `# ip route add 172.16.31.0/24 via 172.16.30.254` 
   or `# route add -net 172.16.31.0/24 gw 172.16.30.254 `
           **In tux32**: `# ip route add 172.16.30.0/24 via 172.16.31.253` 
   or `# route add -net 172.16.30.0/24 gw 172.16.31.253`
8. Observe the routes available at the 3 tuxes.
9. Start a capture at tux33.
10. From tux33, `ping` the other network interfaces (`172.16.30.254`, `172.16.31.253`, `172.16.31.1`) and verify if there is connectivity.
11. Stop the capture and save logs.
12. Start a capture in tux34 on both interfaces (in Wireshark select with Ctrl+Click the connections to listen to).
13. Clean the ARP tables in the 3 tuxes.
14. In tux33, `ping` tux32 for a few seconds.
15. Stop the capture in tux34 and save logs.
16. In Wireshark for the last capture, view the packets from each interface using, in the display filter, the test `frame.interface_id == 0`. Replace `0` with the different numbers for the interfaces. You can check which are available seeing in the `Frame/interface id` on a selected packet. See the figure below for an example on a machine (it has different interfaces).

## Configure Cisco Router

Verify that the `GE0` interface of the Cisco Router is connected to the Lab Router.

Verify that the `GE1` interface of the Cisco Router is connected to the Switch.

Configure the Switch's port from 2 to be on the correct VLAN.

Verify the VLANs on the switch.



W=1 in lab I321  					W= 2 in lab I320



1. Modify the configuration file, for IP and forwarding so that:
   - the name of the router reflects your Y: 3.
   - the IP addresses for the interfaces are as indicated in the figure above (see moodle)
   - the route to the network `172.16.30.0/24` goes through tux34 (`172.16.31.253`).
   - The default gateway (to `0.0.0.0`) is as in the figure (through `172.16.W.254`)
2. Modify the configuration file, for NAT so that:
   - The `nat pool ovrld` uses the IP address `172.16.W.Y9`.--> Verify that the interface for this IP address is configured as `outside`.
   - Verify that the interface for the `172.16.31.254` IP address is configured as `inside`.
   - The `access-list 1 permit` has the networks `172.16.30.0/24` and `172.16.31.0/24` (in the access list command the mask is `0.0.0.7`, which is already correct on the file)
3. Configuring the Router:
   - Access the console for configuring the router through the serial port of tuxy???.
   - Enter config mode (see below)
   - Copy-paste the file to the console.
   - Do `show running-config` to check the running configuration
   - Copy the [`running-config` to the `startup-config`](https://www.cisco.com/c/en/us/td/docs/routers/access/1900/software/configuration/guide/Software_Configuration/appendixAcli.html#55329).
4. Checking connectivity:
   - Do a [`ping` from the Cisco Router](https://www.cisco.com/c/en/us/td/docs/routers/access/1900/software/configuration/guide/Software_Configuration/appendixAcli.html#27356) to all tuxes.
   - Do a [`ping` from the Cisco Router](https://www.cisco.com/c/en/us/td/docs/routers/access/1900/software/configuration/guide/Software_Configuration/appendixAcli.html#27356) to `172.16.W.254`.
   - Do a [`ping` from the Cisco Router](https://www.cisco.com/c/en/us/td/docs/routers/access/1900/software/configuration/guide/Software_Configuration/appendixAcli.html#27356) to `104.17.113.188` (in the        Internet).    
5. Configure tux32 and tux34:
   - Set in tux32 and tux34 the default gateway to the Cisco Router (`172.16.30.254`)
             **In tux32 and tux34**: `# ip route add default via 172.16.30.254` 
     or `# route add default gw 172.16.30.254 `
   - Do a `ping` from tux33 to `172.16.W.254`.
   - Do a `ping` from tux33 to `104.17.113.188` (in the Internet).

