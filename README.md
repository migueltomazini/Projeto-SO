# Simulação: Tower Defense

Este projeto foi desenvolvido com o objetivo de implementar uma simulação utilizando threads e semáforos, como parte da disciplina **Sistemas Operacionais I (SSC0140)** ministrada por **Kalinka Regina Lucas Jaquie Castelo Branco** na Universidade de São Paulo (USP).  

## Visão Geral da Simulação

A simulação consiste em um cenário onde o jogador controla o posicionamento de **três torres** com o objetivo de eliminar um inimigo em movimento. As torres causam dano ao inimigo sempre que ele entra em seu raio de ataque.  

- A **saúde do inimigo** é definida como a **região crítica**, sendo acessada exclusivamente através de semáforos para garantir a integridade dos dados.  
- A biblioteca **OpenGL** foi utilizada para criar a interface gráfica da simulação.

## Como Jogar

- Posicionamento das Torres: Clique sobre as linhas destacadas no mapa para posicionar as torres. Esses são os locais permitidos para instalação.
- Trajeto do Inimigo: O inimigo seguirá pelo caminho marcado pela linha mais fina no mapa.
- Iniciar o Jogo: Após posicionar todas as torres, pressione S para começar a simulação.
- Reiniciar: Caso deseje reiniciar o jogo, pressione R.
- Finalizar: Para encerrar a simulação, feche a janela do programa.

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
### Linux
1. **Instalar Dependências**  
  ```bash
  sudo apt-get install freeglut3-dev  
  sudo apt-get install libglew-dev  
  sudo apt-get install libglfw3-dev  
  sudo apt-get install mesa-utils  
  ```
2. **Rodar o programa**
  ```bash
  make all
  make run
  ```
Comando ```bash make clean ``` também está disponível para excluir objetos e executável.

### Windows

Para rodar a simulação no Windows, siga os passos abaixo:  

1. **Instalar MinGW**  
   Baixe e instale o MinGW (Minimalist GNU for Windows) para compilar o programa. Certifique-se de adicionar o MinGW ao `PATH` do sistema.  

2. **Instalar Dependências**  
   Baixe as bibliotecas necessárias:  
   - [FreeGLUT](https://www.transmissionzero.co.uk/software/freeglut-devel/)  
   - [GLEW](http://glew.sourceforge.net/)  

   Extraia os arquivos das bibliotecas e configure-os no compilador MinGW:
   - Inclua os arquivos de cabeçalho (`*.h`) na pasta `include` do MinGW.
   - Coloque os arquivos `.lib` na pasta `lib` do MinGW.
   - Adicione os arquivos `.dll` ao diretório do projeto ou ao sistema.  

3. **Compilando o Projeto**  
   Abra o terminal no diretório do projeto e use o comando abaixo para compilar o programa:  
   ```bash
   gcc -o tower_defense main.c -lfreeglut -lglew32 -lopengl32 -lpthread
4. **Rodar o programa**
    ```bash
    make
    make run
    ```
