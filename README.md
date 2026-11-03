# Derzu - Sea Class

Sistema de controle de estoque de uma loja de roupas, desenvolvido em C++ para o projeto da disciplina Linguagem de Programação I, do professor Derzu Omaia.

O programa funciona pelo terminal e permite cadastrar camisas, calças e chapéus, organizar os produtos por categorias e consultar um resumo do estoque.

## Funcionalidades

- Cadastrar produtos com ID, nome, preço, quantidade e categorias.
- Registrar tamanho para camisas, numeração para calças e cor, modelo e material para os três tipos de roupa.
- Listar todos os produtos ou pesquisar pelo nome completo ou pelo início do nome, incluindo nomes com espaços.
- Escolher pelo índice quando a pesquisa encontrar mais de um resultado.
- Alterar os dados de um produto, incluindo categorias e atributos específicos do seu tipo.
- Remover produtos do estoque.
- Consultar produtos por categoria, selecionando uma categoria pelo índice.
- Exibir um relatório com produtos cadastrados, total de unidades, valor total do estoque e quantidade de produtos sem estoque.
- Carregar os dados automaticamente ao iniciar e salvá-los ao encerrar.

## Categorias

As categorias funcionam como tags. Durante o cadastro ou a alteração de um produto, informe todas em uma linha, separadas por espaços. Use `_` nos nomes compostos:

```text
inverno camisa roupa_de_frio
```

Categorias existentes são reutilizadas. Para cada categoria nova, o sistema solicita uma descrição. Categorias repetidas na mesma entrada são ignoradas.

Os nomes são convertidos para minúsculas com `tolower()`. Essa conversão funciona para letras de A a Z; para evitar diferenças com letras acentuadas em UTF-8, prefira nomes de categorias sem acentos.

## Compilação e execução

É necessário um compilador com suporte a C++11 ou superior, como o `g++`. Não são necessárias bibliotecas externas.

Na pasta do projeto:

```bash
g++ -std=c++11 main.cpp -o crud
./crud
```

No Windows, com o `g++` instalado:

```powershell
g++ -std=c++11 main.cpp -o crud.exe
.\crud.exe
```

Informe preços usando ponto como separador decimal, por exemplo, `49.90`.

## Menu

| Opção | Operação |
| --- | --- |
| 1 | Cadastrar produto |
| 2 | Listar todos os produtos |
| 3 | Pesquisar produto |
| 4 | Alterar produto |
| 5 | Remover produto |
| 6 | Mostrar produtos por categoria |
| 7 | Exibir relatório |
| 8 | Sair |

Na alteração, informe novamente os dados solicitados. As categorias escolhidas substituem as anteriores, e o tipo do produto é mantido.

## Estrutura do código

O [diagrama de classes UML](DIAGRAMA_CLASSES.md) apresenta os atributos, métodos e relacionamentos das seis classes do projeto.

| Arquivo | Responsabilidade |
| --- | --- |
| `main.cpp` | Apresenta o menu e chama as operações do estoque. |
| `Estoque.h` | Gerencia produtos e categorias, leituras de entrada, operações CRUD, consultas, relatório e persistência. |
| `Produto.h` | Define os dados comuns dos produtos e os métodos virtuais de exibição e gravação. |
| `Camisa.h` | Especializa produto com tamanho, cor, modelo e material. |
| `Calca.h` | Especializa produto com numeração, cor, modelo e material. |
| `Chapeu.h` | Especializa produto com cor, modelo e material. |
| `Categoria.h` | Representa uma categoria com nome e descrição. |

O projeto utiliza encapsulamento, composição com `Categoria`, herança e polimorfismo. Os produtos são armazenados em um `vector<Produto*>`, e as subclasses sobrescrevem métodos da classe `Produto`.

## Armazenamento dos dados

Produtos e categorias são gravados em um único arquivo de texto, `estoque.txt`, na pasta em que o programa é executado. O arquivo identifica o tipo de cada produto para reconstruir a subclasse correspondente na leitura.

A leitura e a escrita utilizam `fstream`, `getline`, `>>` e `<<`. As operações do sistema são realizadas nos vetores em memória; o arquivo é carregado ao iniciar e salvo ao encerrar. Para preservar as alterações, finalize pela opção **8 — Sair**.

O arquivo de dados, o executável e os PDFs de apoio são ignorados pelo Git.

## Uso de inteligência artificial

A IA foi utilizada para auxiliar tomadas de decisão sobre a modelagem e a organização do código e para escrever este README, além de fazer o DIAGRAMA_CLASSES.
