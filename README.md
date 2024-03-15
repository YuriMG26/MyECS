# MyEcs

Simple raylib-based sandbox for testing purposes focused on performance comparison between ECS and the traditional GameObjects approach.

## Descrição

O MyEcs é um projeto que serve como um espaço gráfico baseado em raylib para fins de teste de desempenho de sistemas de Entidade-Componentes-Sistemas (ECS) em comparação com o desempenho de GameObjects tradicionais.

Este projeto foi criado como um ambiente de teste para comparar o desempenho de sistemas de ECS com a abordagem tradicional de GameObjects em jogos e aplicativos. Ele usa a biblioteca raylib para lidar com a renderização gráfica e oferece um ambiente simples para experimentar e avaliar o desempenho dessas abordagens.

## Como Usar

1. Clone este repositório:
```bash
$ git clone https://github.com/YuriMG26/MyEcs.git
```

2. Compilação:
para compilar o projeto, é necessário instalar o [premake](https://premake.github.io/). Após isto, basta criar seu arquivo de build com o seguinte comando:
```bash
# Para gerar um Makefile
$ premake5 gmake2

# Para gerar um projeto do Visual Studio 2022
$ premake5 vs2022

# Para gerar um projeto do XCode4
$ premake5 xcode4
```
Após isto, basta abrir o projeto da IDE escolhida, ou compilar usando o `make`:

``` bash
# formato do comando make:
make [config=name]

# para simplesmente compilar com as configurações padrões (debug)
make

# para explicitamente compilar um executável de debug (com os símbolos de depuração)
make [config=debug]

# para compilar um executável de release (sem símbolos, e com otimizações ativadas)
make [config=release]
```

O arquivo executável será salvo em um diretório de acordo com a configuração passada ao sistema de compilação e o sistema operacional utilizado, por exemplo: em uma compilação de debug no Windows, o executável estará presente em `bin/Debug-windows-x86_64/MyEcs/`

3. Execute o projeto e explore o ambiente gráfico para fins de teste de desempenho.
Para executar com número variável de entidades (atualmente apenas OOP-based), execute o projeto com:
```bash
$ MyEcs.exe -entity [ENTITY_NUM]
```
Basta substituir [ENTITY_NUM] pelo número de entidades desejadas.
