# Experiment 2

## Steps

1. Configure tuxy2 and register its IP and MAC addresses
2. Create vlany0 in the switch and add corresponding ports
3. Create vlany1 and add corresponding port
4. Start capture at tuxy3.eth0
5. In tuxy3, ping tuxy4 and then ping tuxy2
6. Stop capture and save log
7. Start new captures in tuxy3.eth0, tuxy4.eth0, and tuxy2.eth0
8. In tuxy3, do ping broadcast (ping –b 172.16.y0.255) for a few seconds
9. Observe results, stop captures and save logs
10. Repeat steps  7, 8 and 9, but now do ping broadcast in tuxy2 (`ping –b 172.16.y1.255`)



### Example for steps 1 (configuração da bancada 2)

Ligar Cabos

```bash
TUX23E0  -> Switch Porta 1 (Verificar que luz acende no Switch para saber porta)
TUX24E0  -> Switch Porta 2
TUX22E0  -> Switch Porta 3
```

Vista frontal das ligações no switch, lado esquerdo

|             |             |          |
| ----------- | ----------- | -------- |
| TUX23E0 (1) | TUX22E0 (3) | empty(5) |
| TUX24E0 (2) | empty(4)    | empty(6) |

tux23:

```bash
> ifconfig eth0 up
> ifconfig eth0 172.16.20.1/24
> ifconfig eth0 
```

tux24:

```bash
> ifconfig eth0 up
> ifconfig eth0 172.16.20.254/24
> ifconfig eth0 
```

tux22:

```bash
> ifconfig eth0 up
> ifconfig eth0 172.16.21.1/24
> ifconfig eth0 
```



| IP            | MAC               | tux/ether  |
| ------------- | ----------------- | ---------- |
| 172.16.20.1   | 00:21:5a:5a:7d:12 | tux23 eth0 |
| 172.16.21.1   | 00:21:5a:61:2b:72 | tux22 eth0 |
| 172.16.20.254 | 00:08:54:50:3f:2c | tux24 eth0 |

### Step 2

Ligar Cabo

```bash
TUX23S0  -> T3
T4 -> Switch Console
```

|             |             |          |
| ----------- | ----------- | -------- |
| TUX23E0 (1) | TUX22E0 (3) | empty(5) |
| TUX24E0 (2) | empty(4)    | empty(6) |

Para criar as vlans vais modificar o switch, para isso escolhes um  tux e ligas a porta série desse tux á porta série da consola do switch.  Abres o terminal GtKterm, primes Enter para verificar que há ligação,  depois podes seguir os passos abaixo.

Estes passos só precisam de ser feitos uma vez, não é para fazer em todos os tux's e não é preciso alterar cabos

Dar login no switch:

```bash
»enable
»password: ****** (deve ser 8nortel, olha para a prateleira e confirma)
```

Criar VLAN (vlan20):

```bash
»configure terminal
»vlan 20
»end
»show vlan id 20
```

Adicionar ports, Os valores das ports são os números que acendem ao ligar os cabos ao switch

Ligas as ports 1 e 2 à VLAN0

Add port 1 to vlan 20:

```bash
»configure terminal
»interface fastethernet 0/1             (x/y ;  x é o bloco, como só há um , o bloco é 0; y é o port mostrado no switch)
»switchport mode access
»switchport access vlan 20
»end
»show running-config interface fastethernet 0/1
»show interfaces fastethernet 0/1 switchport
```

Add port 2 to VLAN20:

```
»configure terminal
»interface fastethernet 0/2            
»switchport mode access
»switchport access vlan 20
»end
```

### Step 3

Criar outra VLAN (vlan21):

```
»configure terminal
»vlan 21
»end
»show vlan id 21
```

Adiciona a porta do tux22, porta 3.

Add port 3 to VLAN21:

```
»configure terminal
»interface fastethernet 0/3            
»switchport mode access
»switchport access vlan 21
»end
```

### Step 4

Antes de fazer a captura no wireshark, verifica que os pings que se vão  fazer abaixo funcionam. assim que tudo bem, prepara os comandos nas  consolas e podes começar a captura no WireShark.

### Step 5

No tux23 pingar o tux4:

```bash
ping 172.16.20.254 (deixa dar 10 pings e depois dá CTRL+C)
```

Pingar tux22:

```bash
ping 172.16.21.1 (deixa dar 10 pings e depois dá CTRL+C)
```

### Step 6

Parar a captura e guardar o ficheiro. Renomear para `exp2_step5.pcapng`

### Step 7

Antes de fazer estas capturas prepara o ping de baixo, depois segue estes passos:

- Em tux23 começar captura em eth0
- Passar para tux24
- Em tux24 começar captura em eth0
- Passar para tux22
- Em tux22 começar captura em eth0

### Step 8

No tux23, pingar em broadcast:

```
ping -b 172.16.20.255
(deixa dar 10 pings e depois dá CTRL+C)
```

- seria de esperar uma resposta do tux24, tal não acontece porque echo-ignore-broadcast está ativado por default
- para obter resposta no tux23, executar em tux24: echo 0 > /proc/sys/net/ipv4/icmp_echo_ignore_broadcasts

### Step 9

- Parar a captura em tux23
- Parar a captura em tux24
- Parar a captura em tux22
- Guardar o ficheiro de tux23 como `exp2_step7_tux23.pcapng`
- Guardar o ficheiro de tux24 como `exp2_step7_tux24.pcapng`
- Guardar o ficheiro de tux22 como `exp2_step7_tux22.pcapng`

### Step 10

Antes de fazer estas capturas prepara o ping de baixo, depois segue estes passos:

- Em tux23 começar captura em eth0
- Passar para tux24
- Em tux24 começar captura em eth0
- Passar para tux22
- Em tux22 começar captura em eth0

No tux22, pingar em broadcast:

```bash
ping -b 172.16.21.255
(deixa dar 10 pings e depois dá CTRL+C)
```

- Parar a captura em tux23
- Parar a captura em tux24
- Parar a captura em tux22
- Guardar o ficheiro de tux23 como `exp2_step10_tux23.pcapng`
- Guardar o ficheiro de tux24 como `exp2_step10_tux24.pcapng`
- Guardar o ficheiro de tux22 como `exp2_step10_tux22.pcapng`