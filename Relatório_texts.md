## Introdução

O projeto tinha como objetivos estudar os protocolos FTP e TCP/IP, usando-os para criar uma aplicação de download de ficheiros e desenvolver uma rede de computadores, usada para testar a mencionada aplicação.

## Part 1 - Download application

A interação com a aplicação faz-se usando comandos com o seguinte formato no terminal: fttp://[<user>:<password>@<host>/<url-path>].

A aplicação está dividida em três ficheiros, download.c, que controla o fluxo de execução e faz a comunicação com o servidor; parse.c, que efetua o processamento do argumento url e socket.c, onde se encontra a manipulação de sockets e da ligação FTP.



- Processamento começa com o parse do url e guardar as variáveis encontradas
- Socket



