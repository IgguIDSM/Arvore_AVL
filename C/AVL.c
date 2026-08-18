#include <stdio.h>
#include <stdlib.h>

/*
# Criamos a classe nó com todos os parametros que iremos precisar.
#
# Em C não temos classes como no Python, então utilizamos uma struct
# para representar o nó da árvore.
*/
typedef struct No {
    int value;
    struct No* parent;
    struct No* left;
    struct No* right;
    int height;
} No;


/*
# Implementamos a àrvore AVL em si.
#
# Em C, a árvore também será representada por uma struct contendo
# a raiz e o tamanho da árvore.
*/
typedef struct {
    No* root;
    int size;
} AVLTree;


/* ============================================================
   FUNÇÕES DO NÓ
   ============================================================ */


/*
# Criamos um novo nó.
*/
No* create_node(int value, No* parent) {

    No* node = (No*) malloc(sizeof(No));

    if (node == NULL) {
        printf("Erro ao alocar memoria para o no.\n");
        exit(1);
    }

    node->value = value;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}


/*
# Retorna a sua altura relativa à sua ramificação esquerda
*/
int left_height(No* node) {

    return node->left == NULL ? 0 : node->left->height;
}


/*
# Retorna a sua altura relativo à sua ramificação direita
*/
int right_height(No* node) {

    return node->right == NULL ? 0 : node->right->height;
}


/*
# Retorna o fator de balanceamento do nó
# (fb = altura(esquerda) - altura(direita))
*/
int balance_factor(No* node) {

    return left_height(node) - right_height(node);
}


/*
# Retorna o maior valor entre dois números.
*/
int max(int a, int b) {

    return a > b ? a : b;
}


/*
# Atualiza a altura do nó relativo as suas ramificações.
*/
void update_height(No* node) {

    node->height = 1 + max(
        left_height(node),
        right_height(node)
    );
}


/*
# Define um novo nó como ramificação esquerda.
*/
void set_left(No* node, No* new_node) {

    node->left = new_node;

    if (new_node != NULL) {
        new_node->parent = node;
    }

    update_height(node);
}


/*
# Define um novo nó como ramificação direita.
*/
void set_right(No* node, No* new_node) {

    node->right = new_node;

    if (new_node != NULL) {
        new_node->parent = node;
    }

    update_height(node);
}


/*
# Booleano indicando se este nó é uma ramificação esquerda
# de um nó acima.
*/
int is_left_child(No* node) {

    return node->parent != NULL &&
           node->parent->left == node;
}


/*
# Booleano indicando se este nó é uma ramificação direita
# de um nó acima.
*/
int is_right_child(No* node) {

    return node->parent != NULL &&
           node->parent->right == node;
}


/* ============================================================
   FUNÇÕES DA ÁRVORE AVL
   ============================================================ */


/*
# Inicializa uma nova árvore AVL.
*/
void initialize_tree(AVLTree* tree) {

    tree->root = NULL;
    tree->size = 0;
}


/*
# Função que realiza uma rotação a esquerda.
*/
No* rotate_left(No* a) {

    No* b = a->right;

    /*
    # 1 - o novo filho direito de A se torna o filho esquerdo de B.
    */
    set_right(a, b->left);

    /*
    # 2 - O novo filho esquerdo de B se torna A.
    */
    set_left(b, a);

    /*
    # 3 - retornamos B para substituir o A por ele.
    */
    return b;
}


/*
# Função que realiza uma rotação a direita
# como é uma operação simétrica, será o mesmo conceito da função acima.
*/
No* rotate_right(No* a) {

    No* b = a->left;

    set_left(a, b->right);

    set_right(b, a);

    return b;
}


/*
# Função de Rebalanceamento da àrvore;
*/
No* rebalance(No* node) {

    if (node == NULL) {

        /*
        # àrvore vazia, não precisa de rebalanceamento
        */
        return NULL;
    }

    int balance = balance_factor(node);

    if (abs(balance) <= 1) {

        /*
        # o nó já está balanceado, então retornamos;
        */
        return node;
    }


    /*
    # Caso de desbalanceamento para a esquerda.
    */
    if (balance == 2) {

        if (balance_factor(node->left) == -1) {

            set_left(
                node,
                rotate_left(node->left)
            );
        }

        return rotate_right(node);
    }


    /*
    # Caso de desbalanceamento para a direita.
    */
    if (balance == -2) {

        if (balance_factor(node->right) == 1) {

            set_right(
                node,
                rotate_right(node->right)
            );
        }

        return rotate_left(node);
    }

    return node;
}


/*
# Função responsável por restaurar o balanceamento da árvore.
*/
void restore_balance(AVLTree* tree, No* node) {

    No* current = node;

    /*
    # Subimos a árvore e reestabelecemos o balanceamento
    # dos nós encontrados pelo caminho.
    */
    while (current != NULL) {

        update_height(current);

        int balance = balance_factor(current);

        /*
        # Guardamos o pai antes de realizar qualquer rotação.
        */
        No* parent = current->parent;

        /*
        # Caso de desbalanceamento para a esquerda.
        */
        if (balance > 1) {

            /*
            # Caso de rotação dupla esquerda-direita.
            */
            if (balance_factor(current->left) < 0) {

                No* new_left = rotate_left(current->left);
                set_left(current, new_left);
            }

            /*
            # Realizamos a rotação para a direita.
            */
            No* new_root = rotate_right(current);

            /*
            # Conectamos a nova raiz da subárvore ao seu antigo pai.
            */
            if (parent == NULL) {

                tree->root = new_root;
                new_root->parent = NULL;

            } else if (parent->left == current) {

                parent->left = new_root;
                new_root->parent = parent;

            } else {

                parent->right = new_root;
                new_root->parent = parent;
            }

            /*
            # Depois da rotação, continuamos subindo a partir do pai.
            */
            current = parent;
            continue;
        }


        /*
        # Caso de desbalanceamento para a direita.
        */
        if (balance < -1) {

            /*
            # Caso de rotação dupla direita-esquerda.
            */
            if (balance_factor(current->right) > 0) {

                No* new_right = rotate_right(current->right);
                set_right(current, new_right);
            }

            /*
            # Realizamos a rotação para a esquerda.
            */
            No* new_root = rotate_left(current);

            /*
            # Conectamos a nova raiz da subárvore ao seu antigo pai.
            */
            if (parent == NULL) {

                tree->root = new_root;
                new_root->parent = NULL;

            } else if (parent->left == current) {

                parent->left = new_root;
                new_root->parent = parent;

            } else {

                parent->right = new_root;
                new_root->parent = parent;
            }

            /*
            # Depois da rotação, continuamos subindo a partir do pai.
            */
            current = parent;
            continue;
        }


        /*
        # Se o nó está balanceado, simplesmente continuamos
        # subindo para verificar o próximo ancestral.
        */
        current = parent;
    }


    /*
    # Garantimos que a raiz não possua pai.
    */
    if (tree->root != NULL) {
        tree->root->parent = NULL;
    }
}


/* ============================================================
   INSERÇÃO
   ============================================================ */


/*
# Função responsável por adicionar um novo valor à árvore.
*/
void add(AVLTree* tree, int value) {

    tree->size++;

    No* parent = NULL;
    No* current = tree->root;

    /*
    #
    # Enquanto percorremos a árvore procuramos o local
    # correto para inserir o novo valor.
    */
    while (current != NULL) {

        parent = current;

        if (value < current->value) {

            /*
            # se o valor inserido é menor que o valor do Nó,
            # vai pra esquerda.
            */
            current = current->left;

        } else {

            /*
            # se não vai para a direita;
            */
            current = current->right;
        }
    }


    /*
    # achamos o parent, então criamos um novo nó
    */
    No* new_node = create_node(value, parent);


    if (parent == NULL) {

        /*
        # colocamos o novo nó como raiz.
        */
        tree->root = new_node;

    } else {

        if (value < parent->value) {

            /*
            # seguimos a mesma lógica da parte superior,
            # se for menor, esquerda, se for maior, direita
            */
            parent->left = new_node;

        } else {

            parent->right = new_node;
        }
    }


    /*
    # por fim, quando um novo Nó for adicionado,
    # reestabelecemos o balanceamento.
    */
    restore_balance(tree, new_node);
}


/* ============================================================
   OPERAÇÕES ADICIONAIS DA ÁRVORE AVL
   ============================================================ */


/*
# Esta função retorna o Nó mais a esquerda da árvore inteira.
*/
No* leftmost(No* starting_node) {

    No* previous = NULL;
    No* current = starting_node;

    while (current != NULL) {

        previous = current;
        current = current->left;
    }

    return previous;
}


/*
# Esta Função retorna o Menor valor da árvore.
*/
int minimum(AVLTree* tree) {

    if (tree->root == NULL) {

        /*
        # se não existir uma raiz,
        # a operação não pode ser realizada.
        */
        printf("Empty Tree\n");
        return -1;
    }

    return leftmost(tree->root)->value;
}


/*
# Esta função retorna o nó mais a direita da árvore inteira.
*/
No* rightmost(No* starting_node) {

    No* previous = NULL;
    No* current = starting_node;

    while (current != NULL) {

        previous = current;
        current = current->right;
    }

    return previous;
}


/*
# Esta função retorna o Maior Valor da árvore;
*/
int maximum(AVLTree* tree) {

    if (tree->root == NULL) {

        /*
        # se não existir uma raiz entra no mesmo caso
        # da função Minimum.
        */
        printf("Empty Tree\n");
        return -1;
    }

    return rightmost(tree->root)->value;
}


/* ============================================================
   BUSCA
   ============================================================ */


/*
# Função para localizar um nó especifico dentro da árvore,
# se ele existir, caso não, retorna NULL.
*/
No* locate_node(AVLTree* tree, int value) {

    No* current = tree->root;

    while (current != NULL) {

        if (value == current->value) {

            return current;
        }

        if (value < current->value) {

            current = current->left;

        } else {

            current = current->right;
        }
    }

    return NULL;
}


/*
# Verifica se determinado valor existe na árvore.
#
# No Python isso era feito através do __contains__.
*/
int contains(AVLTree* tree, int value) {

    No* node = locate_node(tree, value);

    return node != NULL;
}


/* ============================================================
   REMOÇÃO
   ============================================================ */


/*
# função para deletar uma folha da árvore;
*/
void delete_leaf(AVLTree* tree, No* node) {

    if (node->parent == NULL) {

        tree->root = NULL;

    } else if (is_left_child(node)) {

        node->parent->left = NULL;
        node->parent = NULL;

    } else {

        node->parent->right = NULL;
        node->parent = NULL;
    }

    free(node);
}


/*
# Esta função remove um nó da árvore;
*/
void delete_node(AVLTree* tree, int value) {

    No* node = locate_node(tree, value);

    if (node == NULL) {

        printf("Value not stored in tree\n");
        return;
    }


    No* replacement = NULL;
    No* rebalance_node = node->parent;


    if (node->left != NULL) {

        /*
        # se temos um filho a esquerda,
        # então substituimos com o nó mais a direita.
        */
        replacement = rightmost(node->left);


        /*
        # verificamos se um reparenteamento é necessário.
        */
        if (is_left_child(replacement)) {

            set_left(
                replacement->parent,
                replacement->left
            );

        } else {

            set_right(
                replacement->parent,
                replacement->left
            );
        }


    } else if (node->right != NULL) {

        /*
        # agora, se temos um filho a direita,
        # então substituimos com o nó mais a esquerda.
        */
        replacement = leftmost(node->right);


        /*
        # e verificamos novamente se um reparenteamento é necessário.
        */
        if (is_left_child(replacement)) {

            set_left(
                replacement->parent,
                replacement->right
            );

        } else {

            set_right(
                replacement->parent,
                replacement->right
            );
        }
    }


    if (replacement != NULL) {

        /*
        # se encontramos um substituto,
        # então substituimos o valor.
        */
        node->value = replacement->value;

        rebalance_node = replacement->parent;

        free(replacement);

    } else {

        /*
        # agora se não encontramos significa que
        # o nó a ser deletado é uma folha.
        */
        delete_leaf(tree, node);
    }


    tree->size--;


    if (rebalance_node != NULL) {

        restore_balance(tree, rebalance_node);
    }

    if (tree->root != NULL) {

        tree->root->parent = NULL;
    }
}


/* ============================================================
   RANGE QUERY
   ============================================================ */


/*
# Estrutura utilizada para armazenar os resultados da busca.
*/
typedef struct {

    No** nodes;
    int size;
    int capacity;

} Results;


/*
# Inicializa a estrutura de resultados.
*/
void initialize_results(Results* results) {

    results->size = 0;
    results->capacity = 10;

    results->nodes = (No**) malloc(
        sizeof(No*) * results->capacity
    );

    if (results->nodes == NULL) {

        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
}


/*
# Adiciona um nó aos resultados.
*/
void add_result(Results* results, No* node) {

    if (results->size >= results->capacity) {

        results->capacity *= 2;

        results->nodes = (No**) realloc(
            results->nodes,
            sizeof(No*) * results->capacity
        );

        if (results->nodes == NULL) {

            printf("Erro ao realocar memoria.\n");
            exit(1);
        }
    }

    results->nodes[results->size] = node;
    results->size++;
}


/*
# Função para retornar um valor dentre dois limites passados,
# um Minimo e um máximo
#
# retorna uma estrutura contendo todos os nós
# que estão dentro desse limite.
*/
void search(
    No* node,
    int min_value,
    int max_value,
    Results* results
) {

    /*
    # procuramos por valores dentro dos limites de min e max:
    */

    if (node == NULL) {

        /*
        # se o nó é inválido, nem perdemos tempo.
        */
        return;
    }


    if (
        min_value <= node->value &&
        node->value <= max_value
    ) {

        add_result(results, node);
    }


    if (node->value >= min_value) {

        search(
            node->left,
            min_value,
            max_value,
            results
        );
    }


    if (node->value <= max_value) {

        search(
            node->right,
            min_value,
            max_value,
            results
        );
    }
}


/*
# procura por valores entre um minimo e máximo
*/
Results range_query(
    AVLTree* tree,
    int min_value,
    int max_value
) {

    Results results;

    initialize_results(&results);

    search(
        tree->root,
        min_value,
        max_value,
        &results
    );

    return results;
}


/* ============================================================
   PERCURSOS — PARA VISUALIZAÇÃO DA ÁRVORE
   ============================================================ */


/*
# Percorre a árvore em ordem.
*/
void in_order(No* node) {

    if (node == NULL) {
        return;
    }

    in_order(node->left);

    printf(
        "Valor: %d | Altura: %d | FB: %d\n",
        node->value,
        node->height,
        balance_factor(node)
    );

    in_order(node->right);
}


/* ============================================================
   LIBERAÇÃO DA MEMÓRIA
   ============================================================ */


/*
# Libera todos os nós da árvore.
*/
void free_tree(No* node) {

    if (node == NULL) {
        return;
    }

    free_tree(node->left);
    free_tree(node->right);

    free(node);
}


/* ============================================================
   MAIN
   ============================================================ */

int main() {

    AVLTree tree;

    initialize_tree(&tree);


    /*
    # Inserindo alguns valores para testar a árvore.
    */

    add(&tree, 30);
    add(&tree, 20);
    add(&tree, 10);
    add(&tree, 40);
    add(&tree, 50);
    add(&tree, 25);
    add(&tree, 35);


    printf("=====================================\n");
    printf("ARVORE AVL\n");
    printf("=====================================\n");

    printf("Quantidade de nos: %d\n", tree.size);

    printf("Menor valor: %d\n", minimum(&tree));
    printf("Maior valor: %d\n", maximum(&tree));

    printf("\nPercurso em ordem:\n");

    in_order(tree.root);


    /*
    # Testando busca.
    */

    printf("\n=====================================\n");
    printf("BUSCA\n");
    printf("=====================================\n");

    if (contains(&tree, 25)) {

        printf("O valor 25 existe na arvore.\n");

    } else {

        printf("O valor 25 nao existe na arvore.\n");
    }


    /*
    # Testando range query.
    */

    printf("\n=====================================\n");
    printf("RANGE QUERY\n");
    printf("=====================================\n");

    Results results = range_query(
        &tree,
        20,
        40
    );

    printf("Valores entre 20 e 40:\n");

    for (int i = 0; i < results.size; i++) {

        printf(
            "%d ",
            results.nodes[i]->value
        );
    }

    printf("\n");

    free(results.nodes);


    /*
    # Testando remoção.
    */

    printf("\n=====================================\n");
    printf("REMOCAO\n");
    printf("=====================================\n");

    delete_node(&tree, 20);

    printf("\nArvore apos remover 20:\n");

    in_order(tree.root);


    /*
    # Liberamos a memória utilizada pela árvore.
    */

    free_tree(tree.root);

    return 0;
}