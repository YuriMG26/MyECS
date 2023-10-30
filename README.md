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
para compilar o projeto, basta realizar o comando make:
```bash
$ make all
```

3. Execute o projeto e explore o ambiente gráfico para fins de teste de desempenho.
Para executar com número variável de entidades (atualmente apenas OOP-based), execute o projeto com:
```bash
$ ecs.exe -entity [ENTITY_NUM]
```
Basta substituir [ENTITY_NUM] pelo número de entidades desejadas.