# Criamos a classe nó com todos os parametros que iremos precisar.
class No:
    def __init__(self,value,parent = None):
        self.value = value;
        self.parent = parent;
        self.left = None;
        self.right = None;
        self.height = 1;

    # Funcoes
    
    # Retorna a sua altura relativa à sua ramificação esquerda
    def left_height(self):
        return 0 if self.left is None else self.left.height;
    
    # Retorna a sua altura relativo à sua ramificação direita
    def right_height(self):
        return 0 if self.right is None else self.right.height;
    
    # Retorna o fator de balanceamento do nó (fb = altura(esquerda) - altura(direita))
    def balance_factor(self):
        return self.left_height() - self.right_height();

    # Atualiza a altura do nó relativo as suas ramificações.
    def update_heigth(self):
        self.height = 1 + max(self.left_height(),self.right_height());

    # Define um novo nó como ramificação esquerda.
    def set_left(self, node : No):
        self.left = node;
        if node is not None:
            node.parent = self;
        self.update_heigth();
        
    #Define um novo nó como ramificação direita.
    def set_right(self, node : No):
        self.right = node;
        if node is not None:
            node.parent = self;
        self.update_heigth()
        
    # Booleano indicando se este nó é uma ramificação esquerda de um nó acima.
    def is_left_child(self):
        return self.parent is not None and self.parent.left == self;
    
    # Booleano indicando se este nó é uma ramificação direita de um nó acima.
    def is_right_child(self):
        return self.parent is not None and self.parent.right == self;
#



# Implementamos a àrvore AVL em si.
class AVLTree:
    def __init__(self):
        self.root : No = None;
    # Funções da àrvore.
    
    # Função que realiza uma rotação a esquerda.
    def rotate_left(self,a : No):
        b = a.right;
        # 1 - o novo filho direito de A se torna o filho esquerdo de B.
        a.set_right(b.left);
        #2 - O novo filho esquerdo de B se torna A.
        b.set_left(a);
        return b; # 3 - retornamos B para substituir o A por ele.

    # Função que realiza uma rotação a direita
    # como é uma operação simétrica, será o mesmo conceito da função acima.
    
    def rotate_right(self, a : No):
        b = a.left;
        a.set_left(b.right);
        b.set_right(a);
        return b;
    
    #Função de Rebalanceamento da àrvore;
    
    def rebalance(self, node: No):
        if node is None:
            # àrvore vazia, não precisa de rebalanceamento
            return None;
        balance = node.balance_factor();
        
        if abs(balance) <= 1:
            # o nó já está balanceado, então retornamos;
            return None;
        
        
        #
        if balance == 2:
            if node.left.balance_factor() == -1:
                node.set_left(self.rotate_left(node.left))
            return self.rotate_right(node);
        
        
        #
        if node.right.balance_factor() == 1:
            node.set_right(self.rotate_right(node.right))
        return self.rotate_left(node);
    
        #
        
    def add(self,value : No):
        self.size += 1;
        parent = None;
        current = self.root;
        # 
        while current is not None:
            parent = current
            if value < current.value: # se o valor inserido é menor que o valor do Nó, vai pra esquerda.
                current = current.left;
            else: # se não vai para a direita;
                current = current.right;
        
        # achamos o parent, então criamos um novo nó
        new_node = No(value,parent);
        #
        if parent is None: 
            self.root = new_node; # colocamos o novo nó como filho do parent.
        else:
            if value < parent.value: # seguimos a mesma lógica da parte superior, se for menor, esquerda, se for maior, direita
                parent.left = new_node;
            else:
                parent.right = new_node;
        # por fim, quando um novo Nó for adicionado, reestabelecemos o balanceamento.
        self.restore_balance(new_node);
                

    def restore_balance(self,node: No):
        current = node;
        # Subimos a árvore e reebalanceamos os filhos direitos e esquerdos.
        while current is not None:
            current.set_left(self.rebalance(current.left));
            current.set_right(self.rebalance(current.right));
            current.update_heigth();
            current = current.parent;
        self.root = self.rebalance(self.root);
        self.root.parent = None;
        
    # Operações adicionais da árvore AVL:
    
    # Esta função retorna o Nó mais a esquerda da árvore inteira.
    def leftmost(self, starting_node : No):
        previous = None;
        current = starting_node;
        
        while current is not None:
            previous = current
            current = current.left;
        return previous;
    
    # Esta Função retorna o Menor valor da árvore.
    def minimum(self):
        if self.root is None: # se não existir uma raiz, levantamos uma exceção dizendo que a operação não pode ser realizada.
            raise Exception("Empty Tree");
        return self.leftmost(self.root).value;

    # Esta função retorna o nó mais a direita da árvore inteira.
    def rightmost(self,starting_node: No):
        previus = None;
        current = starting_node;
        while current is not None:
            previus = current;
            current = current.right;
        return previus;
    
    # Esta função retorna o Maior Valor da árvore;
    def maximum(self):
        if self.root is None: # se não existir uma raiz entra no mesmo caso da função Minimum.
            raise Exception("Empty Tree");
        return self.rightmost(self.root).value;
    
    
    # Função para localizar um nó especifico dentro da árvore, se ele existir, caso não, retorna None.
    def locate_node(self,value : No):
        current = self.root;
        while current is not None:
            if value == current.value:
                return current;
            if value < current.value:
                current = current.left;
            else:
                current = current.right;
        return None;
        
    #
    def __contains__(self, item : No):
        node = self.locate_node(item);
        return node is not None;
    
    # função para deletar uma folha da árvore;
    def delete_leaf(self,node: No):
        if node.parent is None:
            self.root = None;
        elif node.is_left_child():
            node.parent.left = None;
            node.parent = None;
        else:
            node.parent.right = None;
            node.parent = None;
    
    
    # Esta função remove um nó da árvore;
    def delete(self, value: No):
        
        node = self.locate_node(value);
        
        if node is None:
            raise Exception("Value not stored in tree");
        
        replacement = None;
        rebalance_node = node.parent;
        
        if node.left is not None: # se temos um filho a esquerda, então subistituimos com o nó mais a direita.
            replacement = self.rightmost(node.left);
            
            if replacement.is_left_child(): # verificamos se um reparenteamento é necessário.
                replacement.parent.set_left(replacement.left);
            else:
                replacement.parent.set_right(replacement.left);
                
                
        elif node.right is not None: # agora, se temos um filho a direita, então subistituimos com o nó mais a esquerda.
            replacement = self.leftmost(node.right);
            
            if replacement.is_left_child(): # e verificamos novamente se um reparenteamento é necessário.
                replacement.parent.set_left(replacement.right);
            else:
                replacement.parent.set_right(replacement.right);
                
                
        if replacement: # se encontramos um subistituto, então subistituimos o valor.
            node.value = replacement.value;
            rebalance_node = replacement.parent;
            
        else: # agora se não encontramos significa que o nó a ser deletado é uma folha.
            
            self.delete_leaf(node);
            
            
        if rebalance_node is not None:
            self.restore_balance(rebalance_node);
            
    # Função para retornar um valor dentre dois limites passados, um Minimo e um máximo
    # retorna um array contendo todos os nós que estão dentro desse limite.
    
    def search(self,node : No, min,max,results = []):
        # procuramos por valores dentro dos limites de min e max:
        
        if node is None: # se o nó é inválido, nem perdemos tempo.
            return;
        
        if min <= node.value and node.value <= max:
            results.append(node);
        #
        if node.value >= min:
            self.search(node.left,min,max,results);
        if node.value <= max:
            self.search(node.right,min,max,results);
        #
    
    def range_query(self,min,max):
        # procura por valores entre um minimo e máximo
        results = [];
        self.search(self.root,min,max,results);
        return results;