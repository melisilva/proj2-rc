## Introdução

O projeto tinha como objetivos estudar os protocolos FTP e TCP/IP, usando-os para criar uma aplicação de download de ficheiros e desenvolver uma rede de computadores, usada para testar a mencionada aplicação.

## Parte 1 - Aplicação de Download

#### Arquitetura da aplicação

A interação com a aplicação faz-se usando comandos com o seguinte formato no terminal: fttp://[<user>:<password>@<host>/<url-path>].

A aplicação está dividida em três ficheiros, download.c, que controla o fluxo de execução e faz a comunicação com o servidor; parse.c, que efetua o processamento do argumento url e socket.c, onde se encontra a manipulação de sockets e da ligação FTP.

Começamos por fazer o parse do url, de modo a obter a informação passada à aplicação através deste argumento, ou seja, o **utilizador**, **password** (estes parâmetros podem não ser especificados, o que fará com que o programa entre em modo anónimo), **host**, através do qual e da função gethostbyname() é possível obter o endereço IP do host e **path**, que nos informa onde se encontra o ficheiro que pretendemos descarregar e também graças à função basename(), podemos obter o nome deste, para que no final do programa, ao criar o ficheiro transferido, sabemos que nome lhe atribuir.

 De seguida, estabelecemos uma conexão, abrindo uma *socket* TCP com o endereço IP obtido e a porta 21 (porta FTP). Antes de continuarmos verificamos se o código de resposta do servidor é 220, que sinaliza que a *socket* está pronta. Enviamos os valores de **utilizador** e **password** através da *socket* ao servidor, respeitando o comando FTP descrito no RFC 959, *USER <SP> <username> <CRLF>* e verificando se o código de resposta obtido é o esperado segundo as informações encontradas neste RFC.

Entramos em modo passivo, enviando através da *socket* o comando "pasv", permitindo-se assim uma mútua comunicação entre o servidor e o cliente FTP, estabelecendo-se uma nova conexão TCP (abrindo uma nova *socket*), obtemos os valores do endereço IP e da porta através da resposta do servidor ao comando.

Mandamos o comando "retr" + **path** através primeira *socket* para pedir ao servidor o envio do ficheiro para download. Procedemos à criação do ficheiro com os dados que recebemos do servidor, lidos a partir da nova *socket*.

#### Caso de sucesso

A nossa aplicação foi testada em várias condições: modo anónimo, modo não anónimo, vários servidores FTP. Um exemplo de um deste testes pode ser visualizado nos Anexos.

## Parte 2 - Configuração da *Network* e Análise

#### Experiência 1 - Configuração IP

Esta experiência tem como objetivo interligar os computadores tux33 e tux34 (trabalhamos na bancada 3) na mesma subrede, através de um switch. Para assim, foi necessário perceber o que são pacotes ARP, para que servem, que tipo de pacotes é que o comando *ping* gera e o que são endereços MAC e IP.

Usamos o comando `ifconfig` para configurar os endereços IP's de cada um dos tuxes e o comando `route` para estabelecer rotas entre eles. Testamos a conectividade entre os dois através de `ping`, depois de eliminar a tabela ARP dos tuxes (`arp -d`), utilizamos este comando de novo e analisamos o resultado com o Wireshark.

Já que eliminamos a tabela ARP, o protocolo ARP (Address Resolution Protocol) foi executado. Este mapeia um endereço IP (identificador público que cada máquina precisa de usar numa rede para poder comunicar com outras) a um endereço MAC da máquina na rede local (endereço físico), para depois ser possível estabelecer ligações.

Quando o tux33 tenta enviar um pacote ao tux34, como não sabe o endereço MAC deste, envia um protocolo ARP em broadcast  (para toda a rede local) com os seus endereços IP (172.16.30.1) e MAC (00:21:5a:61:30:63). O endereço MAC do destinatário, como não o conhece, tem o valor de 00:00:00:00:00:00. O computador da rede local que se identificar pelo endereço IP de destino enviado pelo pedido, irá responder ao tux33 com outro protocolo ARP, dizendo-lhe o seu endereço MAC, é isto que observamos com o tux34. 

Depois de descoberto o endereço MAC do destinatário, `ping` começa a gerar pacotes ICMP (Internet Control Message Protocol), para a comunicação entre os tuxes.

Conseguimos determinar o tipo de trama Ethernet recebida, analisando o cabeçalho do pacote:  se tiver o valor 0x0800, significa que a trama é do tipo IP. Caso o valor seja 0x0806, então a trama é do tipo ARP. Caso a trama seja do tipo IP, temos de analisar o seu IP header, se este tiver o valor igual a 1, então a trama é do tipo ICMP. Podemos também determinar o comprimento da trama através do Wireshark.

Ocasionalmente foi observado o envio de tramas *loopback* pelo emissor, esta é uma interface virtual que está sempre disponível e é sempre possível de atingir enquanto pelo menos uma interface IP no *switch* seja operacional. Esta interface é importante porque permite ao computador receber respostas de si próprio, sendo útil para *debugging* já que podemos sempre dar *ping* ao seu endereço IP. 

#### Experiência 2 - Virtual LANs

Nesta experiência criamos duas LANs virtuais (VLAN30 e VLAN31) no switch, que não possuíam conexão entre si, e observar a conectividade entre os tuxes, depois de os configurar em cada uma das subredes.

 Para configurar a vlan30, tivemos de utilizar o programa GKTERM, que estava ligado ao switch:

```
configure terminal
vlan 30
end 
show vlan id 30
```

De seguida adicionamos as portas do switch (estes valores variam consoante os cabos ligados). Ligamos o tux33E0 à porta 1:

```
configure terminal
interface fastethernet 0/1             
switchport mode access
switchport access vlan 30
end
```

Temos de associar dois tuxes portas à vlan30 (tux33 e tux34), enquanto que para vlan31 só precisamos de tux32. Testamos a conectividade entre os tuxes com o recurso ao comando `ping`, este teve sucesso entre os tuxes 33 e 34 (o que seria de esperar já que se encontram na mesma subrede), no entanto não houve resposta no caso do tux33 e tux32, uma vez que não existe nenhuma routa entre VLAN's. 

Efetuamos um ping em broadcast em tux33, `ping -b 172.16.30.255`, que não obteve resposta, uma vez que em tux34 está ativado o comando`echo-ignore-broadcast` e o tux32 não faz parte da rede local de tux33. Concluímos que existem dois domínios de broadcast que correspondem às duas subredes, VLAN 30 (172.16.30.255) e VLAN 31 (172.16.31.255).

#### Experiência 3 - Configuração do Router - Remota

Esta experiência foi feita remotamente e teve como objetivos analisar o ficheiro de configuração de um Router Cisco, testar entradas DNS e configurar rotas na máquina local (utilizada uma máquina virtual Linux).

Começamos por analisar o ficheiro de configuração do Router Cisco, no qual está presente NAT (Network Address Translation), mecanismo implementado em routers que substitui os endereços IP locais nos pacotes por um endereço IP público de forma a se conseguir estabelecer uma ligação fora da rede. Sendo assim, o router que implementa o NAT torna-se responsável por encaminhar todos os pacotes para o endereço correto, dentro ou fora da rede local. Desta forma para configurar uma rede estática num router comercial precisamos do endereço IP da network que estamos a tentar aceder, da sua máscara e do endereço IP que estamos a usar como gateway. É possível configurar NAT num router comercial através dos comandos disponíveis nos Anexos ??:

```
conf t
interface gigabitethernet 0/0 
ip address 172.16.y1.254 255.255.255.0
no shutdown
ip nat inside
exit
interface gigabitethernet 0/1
ip address 172.16.1.y9 255.255.255.0
no shutdown
ip nat outside
exit
ip nat pool ovrld 172.16.1.y9 172.16.1.y9 prefix 24
ip nat inside source list 1 pool ovrld overload
access-list 1 permit 172.16.y0.0 0.0.0.7
access-list 1 permit 172.16.y1.0 0.0.0.7
ip route 0.0.0.0 0.0.0.0 172.16.1.254
ip route 172.16.y0.0 255.255.255.0 172.16.y1.253
end
```

Para configurar um serviço de DNS numa máquina só é necessário adicionar uma linha ao ficheiro "etc/resolv.conf" contendo o nome do servidor a usar e o endereço IP do mesmo, após este estar configurado, aparecerão pacotes relativos ao DNS.

Ao realizar um ping são enviados 2 pacotes DNS com dois pedidos: Adress
Mapping Record (A), para pedir o endereço IPv4 do host e IP Version 6
Address Record (AAAA) para pedir o endereço IPv6. Ambos estes pedidos
recebem respostas: Para "parlamento.pt"o endereço IPv4 é ... e o endereço IPv6 é ... **(refazer isto para obter fotos melhores e respostas)**.

#### Experiência 4 - Configuração do Router - FEUP

Esta experiência teve como base as experiências 2 e 3, utilizamos as configurações estudadas na experiência anterior e o conhecimento de como criar VLANs adquirido na experiência 2 para criar VLANs comunicáveis entre si, utilizando o tux34 como router. Através das configurações estudadas, também configuramos um router comercial, que conectava a rede criada à internet. 

