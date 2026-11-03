# Diagrama de classes

Diagrama UML baseado nas seis classes implementadas nos arquivos de cabeçalho do projeto.

```mermaid
classDiagram
    direction TB
    class Estoque {
        -vector~Produto*~ produtos
        -vector~Categoria~ categorias
        +Estoque()
        +~Estoque()
        +salvarArquivo(string caminho) bool
        +carregarArquivo(string caminho) bool
        +exibirTitulo(string titulo) void
        +lerTexto(string mensagem, string& valor) bool
        +lerInteiro(string mensagem, int& valor) bool
        +lerReal(string mensagem, float& valor) bool
        +listarCategorias() void
        +exibirPorCategoria() void
        +lerCategorias(vector~Categoria~& selecionadas) bool
        +cadastrarProduto() void
        +inserir(Produto* p) void
        +listarTodos() void
        +exibirRelatorio() void
        +exibirUm(string nome) void
        +alterar(string nome) void
        +remover(string nome) void
        +pesquisar(string nome) int
    }

    class Produto {
        -string id
        -string nome
        -vector~Categoria~ categorias
        -float preco
        -int quantidade
        +Produto()
        +Produto(string i, string n, vector~Categoria~ c, float p, int q)
        +~Produto()
        +exibir() void
        +getTipo() string
        +salvar(fstream& arquivo) void
        +getId() string
        +getNome() string
        +getCategorias() vector~Categoria~
        +getPreco() float
        +getQuantidade() int
        +setId(string i) void
        +setNome(string n) void
        +setCategoria(Categoria c) void
        +setPreco(float p) void
        +setQuantidade(int q) void
    }

    class Categoria {
        -string nome
        -string descricao
        +Categoria()
        +Categoria(string n, string d)
        +getNome() string
        +getDescricao() string
        +setNome(string n) void
        +setDescricao(string d) void
    }

    class Camisa {
        -string tamanho
        -string cor
        -string modelo
        -string material
        +Camisa()
        +Camisa(string i, string n, vector~Categoria~ c, float p, int q, string t, string co, string m, string mat)
        +exibir() void
        +getTipo() string
        +salvar(fstream& arquivo) void
        +getTamanho() string
        +getCor() string
        +getModelo() string
        +getMaterial() string
        +setTamanho(string t) void
        +setCor(string c) void
        +setModelo(string m) void
        +setMaterial(string mat) void
    }

    class Calca {
        -int numeracao
        -string cor
        -string modelo
        -string material
        +Calca()
        +Calca(string i, string n, vector~Categoria~ c, float p, int q, int num, string co, string m, string mat)
        +exibir() void
        +getTipo() string
        +salvar(fstream& arquivo) void
        +getNumeracao() int
        +getCor() string
        +getModelo() string
        +getMaterial() string
        +setNumeracao(int n) void
        +setCor(string c) void
        +setModelo(string m) void
        +setMaterial(string mat) void
    }

    class Chapeu {
        -string cor
        -string modelo
        -string material
        +Chapeu()
        +Chapeu(string i, string n, vector~Categoria~ c, float p, int q, string co, string m, string mat)
        +exibir() void
        +getTipo() string
        +salvar(fstream& arquivo) void
        +getCor() string
        +getModelo() string
        +getMaterial() string
        +setCor(string c) void
        +setModelo(string m) void
        +setMaterial(string mat) void
    }

    Produto <|-- Camisa
    Produto <|-- Calca
    Produto <|-- Chapeu
    Estoque "1" *-- "0..*" Produto : produtos
    Estoque "1" *-- "0..*" Categoria : categorias cadastradas
    Produto "1" *-- "0..*" Categoria : categorias copiadas
    Estoque ..> Camisa : cria
    Estoque ..> Calca : cria
    Estoque ..> Chapeu : cria
```

## Leitura do diagrama

- `+` indica membro público; `-` indica atributo privado.
- A seta com triângulo indica herança pública: `Camisa`, `Calca` e `Chapeu` herdam de `Produto`.
- O losango preenchido indica composição. `Estoque` mantém os produtos e os destrói ao removê-los ou ao ser destruído. As categorias são armazenadas por valor nos vetores de `Estoque` e de `Produto`.
- `1` e `0..*` indicam um proprietário e zero ou mais elementos, respectivamente. Embora o cadastro interativo exija pelo menos uma categoria, a classe `Produto` permite um vetor vazio.
- As setas tracejadas indicam que `Estoque` cria instâncias das três subclasses.
- `vector~T~` representa `vector<T>` na sintaxe Mermaid.

`Produto` é uma classe concreta. Seu destrutor e os métodos `exibir()`, `getTipo()` e `salvar(fstream&)` são virtuais; as três subclasses sobrescrevem esses métodos. Os atributos e métodos herdados não são repetidos nas subclasses.

Cada produto guarda cópias das categorias, sem compartilhar as mesmas instâncias do catálogo do estoque. Os qualificadores `const` de `Categoria::getNome()` e `Categoria::getDescricao()` foram omitidos na representação dos métodos para facilitar a leitura.

`main.cpp` contém a função de entrada e o menu, mas não define uma classe, por isso não aparece no diagrama.
