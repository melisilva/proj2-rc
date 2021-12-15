# Experiment 1

## Steps

1. Disconnect the switch from *netlab* and connect *tux* computers

2. Configure *tuxy3* and *tuxy4* to have an IP address and have the network `172.16.Y0.0/24` defined

3. - using `ip addr` and `ip route` commands
   - you can also use respectively `ifconfig` and `route`

4. Take note of the IP and MAC addresses of the network interfaces on both *tuxes*.

5. Use `ping` command to verify connectivity between these computers.

6. - Note that there is no name resolution for the IP addresses defined, so you need to use the IP addresses.
   - You can have a look a [`/etc/hosts`](https://linux.die.net/man/5/hosts).

7. Inspect the forwarding table (`ip route show` or `route –n`) and ARP (`arp –a`) tables

8. Delete ARP table entries in *tuxy3* (`arp –d <ipaddress>`)

9. Start [Wireshark](https://www.wireshark.org/) in `eth0` of *tuxy3* and start capturing packets

10. In *tuxy3*, `ping` *tuxy4* for a few seconds

11. Stop capturing packets

12. Save log and study it at home to answer the questions below.



### Example for steps 2 & 3 (configuração da bancada 2)

Ligar Cabos

```bash
TUX32E0 -> Switch
TUX34E0 -> Switch
```

tux2:

```bash
> ifconfig eth0 up
> ifconfig eth0 172.16.30.1/24
> ifconfig eth0
```

tux4:

```bash
> ifconfig eth0 up
> ifconfig eth0 172.16.30.254/24
> ifconfig eth0 
```

| IP            | MAC               | tux/ether  |
| ------------- | ----------------- | ---------- |
| 172.16.30.1   | 00:21:5a:61:30:63 | tux32 eth0 |
| 172.16.30.254 | 00:21:5a:5a:7d:74 | tux34 eth0 |

### Step 4

tux2:

```bash
ping 172.16.30.254
```

recebe pacotes de 64 bytes desse endereço

tux4:

```bash
ping 172.16.30.1
```

recebe pacotes de 64 bytes desse endereço.

### Step 5

tux2:

```bash
route -n
```

Associa endereço IP a porta para saber por onde mandar.

Neste pc :

- Destination 172.16.20.0
- Iface eth0

```bash
arp -a
```

Associa endereço IP a um Endereço MAC

```bash
< ? (172.16.20.254) at 00:08:54:50:3f:2c [ether] on eth0
```

### Step 6

tux3:

```bash
> arp -d 172.16.20.254
> arp -a [retorna nada]
```

Restantes passos são feitos na aplicação Wireshark.

Não esquecer de tirar fotos de tudo e responder às questões da experiência e guardá-las para colocar no relatório.

### Perguntas

1. Address Resolution Protocol (ARP) is **a procedure for mapping a dynamic IP address to a permanent physical machine address in a local area network (LAN)**. The job of ARP is essentially to translate 32-bit addresses to 48-bit addresses and vice versa.
2. Em tux2, o MAC address era 00:21:5a:61:30:63 e o IP era 172.16.30.1 (configurado por nós). Em tux4, MAC era  00:21:5a:5a:7d:74  e o IP era 