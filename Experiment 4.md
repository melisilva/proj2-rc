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
   - Access the console for configuring the router through the serial port (Check to see if a tux is already connected to the Router's serial port.  If not connect the serial port of the router to one of the tuxes serial  port (see the [NetLab Network](https://moodle.up.pt/mod/page/view.php?id=89375) if needed))
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



## Step by step - Linux Router

### Step 1

#### Fazer as ligações dos cabos

##### Ligar Cabos

```
TUX33E0  -> Switch Porta 1 
TUX32E0  -> Switch Porta 2
TUX34E0  -> Switch Porta 3
TUX34E1  -> Switch Porta 4
```

##### Configurar IP's

tux33:

```
> ifconfig eth0 up
> ifconfig eth0 172.16.30.1/24
> ifconfig eth0 
```

tux34:

```
> ifconfig eth0 up
> ifconfig eth0 172.16.30.254/24
> ifconfig eth0 

> ifconfig eth1 up
> ifconfig eth1 172.16.31.253/24
> ifconfig eth1 
```

tux32:

```
> ifconfig eth0 up
> ifconfig eth0 172.16.31.1/24
> ifconfig eth0 
```

| IP            | MAC  | tux/ether  |
| ------------- | ---- | ---------- |
| 172.16.31.1   |      | tux32 eth0 |
| 172.16.30.1   |      | tux33 eth0 |
| 172.16.30.254 |      | tux34 eth0 |
| 172.16.31.253 |      | tux34 eth1 |

##### Configurar VLAN's

```
TUX33S0  -> T3
T4 -> Switch Console
```

Ligas um Cabo `S0`, like TUX33S0, à porta 33 da prateleira de cima (`T3`) e um cabo da porta `T4` a `switch console` e fazes como em [exp2](https://github.com/Ca-moes/RCOM/issues/63)

Esta secção é para ser feita apenas uma vez, num tux à escolha, a partir do terminal GtkTerm, sem necessidade de alterar cabos.

VLAN 0:

- tux33 eth0 -> port 1
- tux34 eth0 -> port 3

VLAN 1:

- tux32 eth0 -> port 13
- tux34 eth1 -> port 14



###### Instruções Detalhadas

Dar login no switch (slide 48):

```
»enable
»password: ****** (deve ser 8nortel, olha para a prateleira e confirma)
```

Criar VLAN (vlan30) (Slide 44):

```
»configure terminal
»vlan 30
»end
»show vlan id 30
```

Add port 1 to vlan 30 (Slide 44):

```
»configure terminal
»interface fastethernet 0/1            
»switchport mode access
»switchport access vlan 30
»end
```

Add port 3 to vlan 30 (Slide 44):

```
»configure terminal
»interface fastethernet 0/3             
»switchport mode access
»switchport access vlan 30
»end
```

Criar VLAN (vlan31) (Slide 44):

```
»configure terminal
»vlan 31
»end
»show vlan id 31
```

Add port 13 to vlan 31 (Slide 44):

```
»configure terminal
»interface fastethernet 0/13             
»switchport mode access
»switchport access vlan 31
»end
```

Add port 14 to vlan 31 (Slide 44):

```
»configure terminal
»interface fastethernet 0/14            
»switchport mode access
»switchport access vlan 31
»end
```

No final verificar se está tudo correto com:

```
»show vlan
```

Também podes verificar com:

```
»show running-config interface fastethernet 0/1
»show interfaces fastethernet 0/1 switchport
```

testar com números de portas diferentes

##### Enable IP forwarding & Disable ICMP echo-ignore-broadcast

Passa para o tux34 e faz os seguintes comando no terminal

```
echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts
```

### Step 2

Caso ainda não o tenhas feito, guarda os valores IP e MAC das portas eth0 e eth1 do tux34.

### Step 3

  **In tux33**: `# ip route add 172.16.31.0/24 via 172.16.30.254` 
or `# route add -net 172.16.31.0/24 gw 172.16.30.254 `
        **In tux32**: `# ip route add 172.16.30.0/24 via 172.16.31.253` 
or `# route add -net 172.16.30.0/24 gw 172.16.31.253`

Testa pingar o tux32 a partir do tux33 e o oposto para ver se chegam um ao outro.

```
Em tux33:
ping 172.16.31.1

Em tux32:
ping 172.16.30.1
```

Caso haja erros:

- verifica as routes em cada tux com `route -n` para ficarem [desta forma](https://imgur.com/a/IxWSdWm):

### Step 4

Fazer `route -n` em cada 1 dos 3 tuxs

### Step 5

Passar para tux33. Ligar o WireShark e começar a capturar pacotes na eth0

### Step 6

A partir do tux33:

- pingar a eth0 do tux34 - `ping 172.16.30.254`
- pingar a eth1 do tux34 - `ping 172.16.31.253`
- pingar a eth0 do tux32 - `ping 172.16.31.1`

Para cada um verificar a conectividade

### Step 7

Para a captura no tux33 e guardar logs como `exp3_step7.pcapng`

### Step 8

- Passar para o tux34.
- Ligar duas instâncias de WireShark. Uma para o eth0 e outra para o eth1.
- Começar a capturar na eth0 e começar a capturar na eth1.

### Step 9

- No tux34, apagar a tabela ARP e verificar se estão limpas

```
> arp -a [ver quais são os ips que se podem apagar]
> arp -d um dos ips
> arp -a [tem de retornar nada]
```

- Trocar para o tux32 e fazer o mesmo
- Trocar para o tux33 e fazer o mesmo

### Step 10

No tux33 começar a pingar o tux32 `ping 172.16.31.1` e ao fim de 10 pings fazer CTRL+C.

### Step 11

Passar para tux34, parar as capturas e guardar os ficheiros como: `exp3_step11_eth0.pcapng` e `exp3_step11_eth1.pcapng`



## Step by step - Cisco Router

### Step 1

Do router>`enable`

router# configure terminal

Enter this info (one per line):

```
!
version 12.4
service timestamps debug datetime msec
service timestamps log datetime msec
service password-encryption
!
hostname gnu-rtr3
!
boot-start-marker
boot-end-marker
!
! card type command needed for slot/vwic-slot 0/0
logging message-counter syslog
logging buffered 51200 warnings
enable secret 5 $1$u53Q$vBawpP8.1YpCT6ypap1zX.
!
no aaa new-model
dot11 syslog
ip source-route
!
!
!
!
ip cef
no ip domain lookup
no ipv6 cef
!
multilink bundle-name authenticated
!
!
!
!
!
username root privilege 15 secret 5 $1$8AFR$bNAYevxPFjXFExpnZI2fj.
username cisco password 7 02050D480809
archive
 log config
  hidekeys
! 
!
!
!
!
!
!
!
interface FastEthernet0/0
 description $ETH-LAN$$ETH-SW-LAUNCH$$INTF-INFO-FE 0$
 ip address 172.16.31.254 255.255.255.0
 ip nat inside
 ip virtual-reassembly
 duplex auto
 speed auto
!
interface FastEthernet0/1
 ip address 172.16.1.39 255.255.255.0
 ip nat outside
 ip virtual-reassembly
 duplex auto
 speed auto
!
ip forward-protocol nd
ip route 0.0.0.0 0.0.0.0 172.16.1.254
ip route 172.16.30.0 255.255.255.0 172.16.31.253
ip http server
ip http access-class 23
ip http authentication local
ip http secure-server
ip http timeout-policy idle 60 life 86400 requests 10000
!
!
ip nat pool ovrld 172.16.1.39 172.16.1.39 prefix-length 24
ip nat inside source list 1 pool ovrld overload
!
access-list 1 permit 172.16.30.0 0.0.0.7
access-list 1 permit 172.16.31.0 0.0.0.7
!
!
!
!
!
!
control-plane
!
!
!
line con 0
 login local
line aux 0
line vty 0 4
 access-class 23 in
 privilege level 15
 login local
 transport input telnet ssh
line vty 5 15
 access-class 23 in
 privilege level 15
 login local
 transport input telnet ssh
!
scheduler allocate 20000 1000
end
```

End with CTRL + Z

router(config)# exit

Do `show running-config`

Do `copy running-config startup-config`

```
conf t
interface gigabitethernet 0/0 
ip address 172.16.31.254 255.255.255.0
no shutdown
ip nat inside
exit
interface gigabitethernet 0/1
ip address 172.16.1.39 255.255.255.0
no shutdown
ip nat outside
exit
ip nat pool ovrld 172.16.1.39 172.16.1.39 prefix 24
ip nat inside source list 1 pool ovrld overload
access-list 1 permit 172.16.30.0 0.0.0.7
access-list 1 permit 172.16.31.0 0.0.0.7
ip route 0.0.0.0 0.0.0.0 172.16.1.254
ip route 172.16.30.0 255.255.255.0 172.16.3y1.253
end
```



### Step 2

From Cisco router, do:

1. ping 172.16.31.254
2. ping 172.16.1.254
3. ping 104.17.113.188

### Step 3

**In tuxy2 and tuxy4**: `# ip route add default via 172.16.30.254` 
or `# route add default gw 172.16.30.254 `

From tux33, do ping 172.16.1.254

From tux33, do ping 104.113.188



**Notas para segunda parte da experiência**

1. Ligar cabos

2. Configurar router cisco

3. Configurar IP's

4. Configurar VLANs--->adicionar router à VLAN31 (ter atenção aos cabos)

5. Fazer o enable do IP forwarding & disable ICMP echo-ignore-broadcast

6. Adicionar as routes

   **In tux33**: `# ip route add 172.16.31.0/24 via 172.16.30.254` 
   or `# route add -net 172.16.31.0/24 gw 172.16.30.254 `
           **In tux32**: `# ip route add 172.16.30.0/24 via 172.16.31.253` 
   or `# route add -net 172.16.30.0/24 gw 172.16.31.253`

7. Testar conectividade entre tux33 e tux32 (para ver que está tudo bem)

8. Adicionar default routes

   **In tux32 and tux34**: `# ip route add default via 172.16.30.254` 
   or `# route add default gw 172.16.30.254 `

9. Fazer os pings

   
