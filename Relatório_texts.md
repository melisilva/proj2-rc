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
