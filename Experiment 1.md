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



### Steps 2 & 3 (bancada 3)

Não era possível usarmos o tux33 pois ainda estava com as configurações do primeiro projeto.

Ligar Cabos:

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

- Destination 172.16.30.0
- Iface eth0

```bash
arp -a
```

Associa endereço IP a um Endereço MAC

```bash
< ? (172.16.30.254) at 00:08:54:50:3f:2c [ether] on eth0
```

### Step 6

tux3:

```bash
> arp -d 172.16.30.254
> arp -a [retorna nada]
```

Restantes passos são feitos na aplicação Wireshark.

Não esquecer de tirar fotos de tudo e responder às questões da experiência e guardá-las para colocar no relatório.

### Perguntas

1. **What are the ARP packets and what are they used for?**

   ARP (Address Resolution Protocol) é um protocolo para descobrir dinamicamente a relação entre os endereços das camadas do protocolo e do hardware. Pacotes ARP possuem informações sobre endereços IP e MAC e têm com função o mapeamento de um endereço IP a um endereço MAC da máquina na rede local (endereço físico), para depois ser possível estabelecer ligações.

   

2. **What are the MAC and IP addresses of ARP packets and why?**

   Quando o tux32 tenta enviar um pacote ao tux34, como a entrada da tabela ARP referente ao tux34 foi apagada, o tux32 não sabe qual é o endereço MAC associado ao endereço IP do tux34 (172.16.30.254). Deste modo, irá enviar um pacote ARP em broadcast (para toda a rede local), sendo que este pacote contém o endereço IP (172.16.30.1) e o endereço MAC (00:21:5a:61:30:63) do tux32. O endereço MAC do destinatário, como não se conhece, tem o valor de 00:00:00:00:00:00.

   De seguida, o tux34 irá enviar um pacote ARP para o tux32, com o endereço MAC dele (00:21:5a:5a:7d:74), e o seu endereço IP (172.16.30.254). Portanto, pode concluir-se que cada pacote ARP contém campos para os endereços MAC e IP da máquina que envia, e para os endereços MAC e IP da máquina que recebe.

   

3. **What packets does the `ping` command generate?**

   O comando ping gera primeiro pacotes ARP para saber qual o endereço MAC do destinatário, depois gera pacotes ICMP (Internet Control Message Protocol), para a comunicação entre os tuxs.

    

4. **What are the MAC and IP addresses of the `ping` packets?**

   ping de tux 32 para tux 34:

   - IP address source: 172.16.30.1 (tux 32)
   - MAC address source: 00:21:5a:61:30:63 (tux32)
   - IP address destinatário: 172.16.30.254 (tux34)
   - MAC address destinatário: 00:21:5a:5a:7d:74  (tux34)

   Pacote de reply (tux 34 para tux 32):

   - IP address source: 172.16.30.254 (tux34)
   - MAC address source: 00:21:5a:5a:7d:74  (tux34)
   - IP address destinatário: 172.16.30.1 (tux32)
   - MAC address destinatário: 00:21:5a:61:30:63 (tux32)

   

5. **How to determine if a receiving Ethernet frame is ARP, IP, ICMP?**

   Conseguimos determinar o tipo da trama analisando o Ethernet header da trama:  se tiver o valor 0x0800, significa que a trama é do tipo IP. Caso o valor seja 0x0806, então a trama é do tipo ARP. Caso a trama seja do tipo IP, temos de analisar o seu IP header, se este tiver o valor igual a 1, então a trama é do tipo ICMP.

   

6. **How to determine the length of a receiving frame?**

   Podemos determinar o comprimento da trama através do Wireshark.

   

7. **What is the loopback interface and why is it important?**

   A interface loopback é uma interface virtual que está sempre disponível e é sempre possível de atingir enquanto pelo menos uma interface IP no *switch* seja operacional. Esta interface é importante porque permite ao computador receber respostas de si próprio, sendo útil para *debugging* já que podemos sempre dar *ping* ao seu endereço IP.