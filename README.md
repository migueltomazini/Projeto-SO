# Simulação: Tower Defense

Este projeto foi desenvolvido com o objetivo de implementar uma simulação utilizando threads e semáforos, como parte da disciplina **Sistemas Operacionais I (SSC0140)** ministrada por **Kalinka Regina Lucas Jaquie Castelo Branco** na Universidade de São Paulo (USP).  

## Visão Geral da Simulação

A simulação consiste em um cenário onde o jogador controla o posicionamento de **três torres** com o objetivo de eliminar um inimigo em movimento. As torres causam dano ao inimigo sempre que ele entra em seu raio de ataque.  

- A **saúde do inimigo** é definida como a **região crítica**, sendo acessada exclusivamente através de semáforos para garantir a integridade dos dados.  
- A biblioteca **OpenGL** foi utilizada para criar a interface gráfica da simulação.  

## Implementação Técnica  

### Threads  
- **Threads das Torres:** Cada torre possui uma thread dedicada para realizar seus ataques de forma independente.
- **Thread Principal:** A thread principal é responsável por controlar o timer, gerenciar o movimento dos elementos na simulação e garantir o funcionamento geral do sistema.

### Semáforos  
- **Sincronização:** Semáforos são utilizados para coordenar o acesso à saúde do inimigo, garantindo consistência ao manipular essa região crítica.  
- **Controle de Concorrência:** Eles evitam condições de corrida, garantindo que os ataques sejam tratados de forma sincronizada e consistente.  

## Funcionalidades  
- **Simulação Dinâmica:** A interface visual, implementada em OpenGL, exibe as torres atacando o inimigo em tempo real.
- **Interatividade:** O jogador pode selecionar estrategicamente o posicionamento das torres para maximizar o dano.  
- **Sincronização Segura:** O uso de semáforos protege a região crítica da saúde do inimigo, assegurando a integridade dos dados em um ambiente multithread.  
- **Escalabilidade:** A arquitetura permite expandir a simulação para incluir mais torres ou inimigos, destacando a flexibilidade do design concorrente.  

## Requisitos de Execução  

### Dependências  
Certifique-se de instalar as dependências necessárias para executar o programa:  

```bash
sudo apt-get install freeglut3-dev  
sudo apt-get install libglew-dev  
sudo apt-get install libglfw3-dev  
sudo apt-get install mesa-utils  
```
```bash
make
make run
```
