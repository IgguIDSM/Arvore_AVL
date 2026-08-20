# Árvores AVL — Estrutura, Funcionamento e Aplicações

> Implementação e estudo prático de Árvores Binárias de Busca (ABB) autobalanceadas para a disciplina de Estrutura de Dados Avançados.

![GitHub](https://img.shields.io/badge/GitHub-Arvore__AVL-181717?logo=github)
![C](https://img.shields.io/badge/C-Implementação-A8B9CC?logo=c&logoColor=black)
![Python](https://img.shields.io/badge/Python-3.x-3776AB?logo=python&logoColor=white)

---

## Sobre o Projeto

Este repositório reúne as implementações teóricas e práticas de Árvores AVL desenvolvidas primariamente em C, contendo também suporte e estudos em Python. O objetivo principal é compreender como a estrutura controla sua própria altura (`-1 ≤ FB ≤ +1`) através de rotações automáticas após operações de inserção e remoção.

### O que é uma Árvore AVL?
Mantém as propriedades de uma árvore binária de busca, mas calcula o Fator de Balanceamento (FB) a cada alteração:
```text
FB = altura(esquerda) - altura(direita)
```

---

## Complexidade e Rotações

Em uma árvore AVL balanceada, o tempo de execução permanece logarítmico mesmo nos piores cenários:

| Operação | Complexidade |
| :--- | :--- |
| Busca / Inserção / Remoção | O(log n) |
| Mínimo / Máximo / Consulta por intervalo | O(log n) |
| Rotações de Balanceamento | O(1) |

### Casos de Balanceamento Suportados:
* LL (Rotação simples à direita)
* RR (Rotação simples à esquerda)
* LR (Rotação dupla esquerda-direita)
* RL (Rotação dupla direita-esquerda)

---

## Organização do Repositório

```text
Arvore_AVL/
├── C/          # Código principal da implementação em C 
├── PY/         # Implementação em Python
├── .gitignore
└── leiame.txt # Passo a Passo de como executar ambos os arquivos
```

---

## Como Executar (Versão principal em C)

### Pré-requisitos
* Compilador GCC instalado
* Git

### Passo a Passo
```bash
# Clone o repositório
git clone https://github.com/IgguIDSM/Arvore_AVL.git

# Acesse a pasta do projeto em C
cd Arvore_AVL/C

# Compile o código
gcc AVL.c -o AVL

# Execute o programa
./AVL
```

---

## Autores e Contexto Acadêmico

Trabalho prático desenvolvido na Universidade de Vassouras (Campus Saquarema) para o curso de Bacharelado em Engenharia de Software na disciplina de Estrutura de Dados Avançados.

* Felippe Pereira Miguel
* Felipe Casagrande Oliveira
* Igor dos Santos Moura
* Joanne Garcia Azevedo
* Kadu Luis Santos Novaes
* Larissa Barbosa Simas
* Leonardo Paulucci
* Luis Andrei Abreu Senna
* Maria Regina Garcia Duarte
* Rayan Roque dos Santos
