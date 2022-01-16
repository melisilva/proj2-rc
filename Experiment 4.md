# Experiment 4

## Configure Linux Router

### Steps 

1. Connect a cable from tuxy4/`eth1` to the switch and place it in vlan31 
2. Verify the VLANs on the switch (`show vlan brief`).
3. Configure tuxy4/`eth1`'s IP address as per the figure (`172.16.y1.253/24`).
4. Enable IP forwarding On tuxy4 .
5. Disable ICMP echo ignore broadcast On tuxy4 
6. Check the MAC addresses and IP addresses in tuxy4 for `eth0` and `eth1`.
7. Configure the routes in tuxy3 and tuxy2 so that they can reach each other.
           **In tux33**: `# ip route add 172.16.y1.0/24 via 172.16.y0.254` 
   or `# route add -net 172.16.y1.0/24 gw 172.16.y0.254 `
           **In tux32**: `# ip route add 172.16.y0.0/24 via 172.16.y1.253` 
   or `# route add -net 172.16.y0.0/24 gw 172.16.y1.253`
8. Observe the routes available at the 3 tuxes.
9. Start a capture at tuxy3.
10. From tuxy3, `ping` the other network interfaces (`172.16.y0.254`, `172.16.y1.253`, `172.16.y1.1`) and verify if there is connectivity.
11. Stop the capture and save logs.
12. Start a capture in tuxy4 on both interfaces (in Wireshark select with Ctrl+Click the connections to listen to).
13. Clean the ARP tables in the 3 tuxes.
14. In tuxy3, `ping` tuxy2 for a few seconds.
15. Stop the capture in tuxy4 and save logs.
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
   - the route to the network `172.16.y0.0/24` goes through tuxy4 (`172.16.y1.253`).
   - The default gateway (to `0.0.0.0`) is as in the figure (through `172.16.W.254`)
2. Modify the configuration file, for NAT so that:
   - The `nat pool ovrld` uses the IP address `172.16.W.Y9`.--> Verify that the interface for this IP address is configured as `outside`.
   - Verify that the interface for the `172.16.y1.254` IP address is configured as `inside`.
   - The `access-list 1 permit` has the networks `172.16.y0.0/24` and `172.16.y1.0/24` (in the access list command the mask is `0.0.0.7`, which is already correct on the file)
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
   - Set in tux32 and tux34 the default gateway to the Cisco Router (`172.16.y0.254`)
             **In tux32 and tux34**: `# ip route add default via 172.16.y0.254` 
     or `# route add default gw 172.16.y0.254 `
   - Do a `ping` from tux33 to `172.16.W.254`.
   - Do a `ping` from tux33 to `104.17.113.188` (in the Internet).



## Step by step - Linux Router

### Step 1

#### Fazer as ligações dos cabos

##### Ligar Cabos

```
TUX33E0  -> Switch Porta C
TUX32E0  -> Switch Porta L
TUX34E0  -> Switch Porta M
TUX34E1  -> Switch Porta T
```

##### Configurar IP's

tuxy3:

```
> ifconfig eth0 up
> ifconfig eth0 172.16.y0.1/24
> ifconfig eth0 
```

tuxy4:

```
> ifconfig eth0 up
> ifconfig eth0 172.16.y0.254/24
> ifconfig eth0 

> ifconfig eth1 up
> ifconfig eth1 172.16.y1.253/24
> ifconfig eth1 
```

tuxy2:

```
> ifconfig eth0 up
> ifconfig eth0 172.16.y1.1/24
> ifconfig eth0 
```

| IP            | MAC  | tux/ether  |
| ------------- | ---- | ---------- |
| 172.16.y1.1   |      | tuxy2 eth0 |
| 172.16.y0.1   |      | tuxy3 eth0 |
| 172.16.y0.254 |      | tuxy4 eth0 |
| 172.16.y1.253 |      | tuxy4 eth1 |

##### Configurar VLAN's

```
TUXy3S0  -> T3
T4 -> Switch Console
```

Ligas um Cabo `S0`, like TUXy3S0, à porta y3 da prateleira de cima (`T3`) e um cabo da porta `T4` a `switch console` 

Esta secção é para ser feita apenas uma vez, num tux à escolha, a partir do terminal GtkTerm, sem necessidade de alterar cabos.

VLAN 0:

- tux33 eth0 -> port C
- tux34 eth0 -> port M

VLAN 1:

- tux32 eth0 -> port L
- tux34 eth1 -> port T



###### Instruções Detalhadas

Dar login no switch :

```
»enable
»password: ****** (8nortel)
```

Criar VLAN (vlany0) :

```
»configure terminal
»vlan y0
»end
»show vlan id y0
```

Add port C to vlan y0 :

```
»configure terminal
»interface fastethernet 0/C            
»switchport mode access
»switchport access vlan y0
»end
```

Add port M to vlan y0 (Slide 44):

```
»configure terminal
»interface fastethernet 0/M             
»switchport mode access
»switchport access vlan y0
»end
```

Criar VLAN (vlany1):

```
»configure terminal
»vlan y1
»end
»show vlan id y1
```

Add port L to vlan y1 (Slide 44):

```
»configure terminal
»interface fastethernet 0/L            
»switchport mode access
»switchport access vlan y1
»end
```

Add port T to vlan y1 (Slide 44):

```
»configure terminal
»interface fastethernet 0/T            
»switchport mode access
»switchport access vlan y1
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

Passa para o tuxy4 e faz os seguintes comando no terminal

```
echo 1 > /proc/sys/net/ipv4/ip_forward
echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts
```

### Step 2

Caso ainda não o tenhas feito, guarda os valores IP e MAC das portas eth0 e eth1 do tuxy4 (tira uma foto, mais rápido).

### Step 3

  **In tuxy3**: `# ip route add 172.16.y1.0/24 via 172.16.y0.254` 
or `# route add -net 172.16.y1.0/24 gw 172.16.y0.254 `
        **In tuxy2**: `# ip route add 172.16.y0.0/24 via 172.16.y1.253` 
or `# route add -net 172.16.y0.0/24 gw 172.16.y1.253`

Testa pingar o tuxy2 a partir do tuxy3 e o oposto para ver se chegam um ao outro.

```
Em tuxy3:
ping 172.16.y1.1

Em tuxy2:
ping 172.16.y0.1
```

Caso haja erros:

- verifica as routes em cada tux com `route -n`
- verifica se os cabos estão bem inseridos e o GKTERM tem as portas corretas para cada VLAN

### Step 4

Passar para tuxy3. Ligar o WireShark e começar a capturar pacotes na eth0

### Step 5

A partir do tuxy3:

- pingar a eth0 do tuxy4 - `ping 172.16.y0.254`
- pingar a eth1 do tuxy4 - `ping 172.16.y1.253`
- pingar a eth0 do tuxy2 - `ping 172.16.y1.1`

Para cada um verificar a conectividade (vê se recebes pacotes)

### Step 6

Para a captura no tuxy3 e guarda os logs 

### Step 7

- Passar para o tuxy4.
- Ligar duas instâncias de WireShark. Uma para o eth0 e outra para o eth1.
- Começar a capturar na eth0 e começar a capturar na eth1.

### Step 8

- No tuxy4, apagar a tabela ARP e verificar se estão limpas

```
> arp -a [ver quais são os ips que se podem apagar]
> arp -d um dos ips
> arp -a [tem de retornar nada]
```

- Trocar para o tuxy2 e fazer o mesmo
- Trocar para o tuxy3 e fazer o mesmo

### Step 9

No tuxy3 começar a pingar o tuxy2 `ping 172.16.y1.1` e ao fim de 10 pings fazer CTRL+C.

### Step 10

Passar para tuxy4, parar as capturas e guardar os ficheiros 

## Step by step - Cisco Router

### Step 1

Ligar os Cabos (os mesmos que ligaste na primeira parte + cabos GE):

Verify that the `GE0` interface of the Cisco Router is connected to the Lab Router.

Verify that the `GE1` interface of the Cisco Router is connected to the Switch.

### Step 2

No GTKTERM, fazer isto para configurar o router cisco

```
enable
configure terminal
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

Do `show running-config`

Do `copy running-config startup-config`

### Step 3

Configurar os IP's para cada tux (tal como fizeste na primeira para da experiência)

### Step 4

Configurar VLANs (da mesma maneira que fizeste no início da experiência) e adicionar o router à VLAN31 (ter atenção aos cabos, para saber as portas)

### Step 5

Fazer o enable do IP forwarding & disable ICMP echo-ignore-broadcast

### Step 6

Adicionar as routes

**In tux33**: `# ip route add 172.16.31.0/24 via 172.16.30.254` 
or `# route add -net 172.16.31.0/24 gw 172.16.30.254 `
        **In tux32**: `# ip route add 172.16.30.0/24 via 172.16.31.253` 
or `# route add -net 172.16.30.0/24 gw 172.16.31.253`

### Step 7

Testar conectividade entre tux33 e tux32 (para ver que está tudo bem)

### Step 8

From Cisco router, do:

1. ping a todos os tuxes
2. ping 172.16.1.254
3. ping 104.17.113.188

### Step 9

**In tuxy2 and tuxy4**: `# ip route add default via 172.16.30.254` 
or `# route add default gw 172.16.30.254 `

### Step 10

From tux33, do ping 172.16.1.254

From tux33, do ping 104.113.188 
