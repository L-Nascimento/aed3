#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um arquivo ou pasta
typedef struct Node {
    char nome[100];
    int verificaPasta; // 1 se for pasta, 0 se for arquivo
    struct Node* pai;
    struct Node* filho;
    struct Node* irmao;
} Node;

// Função para criar um novo nó
Node* criarNo(const char* nome, Node* pai, int verificaPasta) {
    Node* novoNo = (Node*)malloc(sizeof(Node)); // Aloca memória para o novo nó
    strcpy(novoNo->nome, nome); // Copia o nome para o novo nó
    novoNo->pai = pai; // Define o nó pai
    novoNo->filho = NULL; // Inicializa o ponteiro para o primeiro filho
    novoNo->irmao = NULL; // Inicializa o ponteiro para o próximo irmão
    novoNo->verificaPasta = verificaPasta; // Inicializa a variável para verificar se é pasta ou arquivo
    return novoNo; // Retorna o novo nó
}

// Função para adicionar um nó filho a um nó pai
void adicionarFilho(Node* pai, Node* filho) {
    if (pai->filho == NULL) { // Se o nó pai não tiver filhos, o novo nó será o primeiro filho
        pai->filho = filho;
    } else {
        Node* irmao = pai->filho; // Se o nó pai já tiver filhos, o novo nó será adicionado como irmão do último filho
        while (irmao->irmao != NULL) {
            irmao = irmao->irmao;
        }
        irmao->irmao = filho; // Adiciona o novo nó como irmão do último filho
    }
}

// Função para imprimir o caminho atual
void imprimirCaminho(Node* atual) {
    if (atual == NULL) {
        printf("->");
        return;
    }
    imprimirCaminho(atual->pai); // Chama a função recursivamente para o nó pai
    printf("-%s", atual->nome); // Imprime o nome do nó atual
}

// Função para mostrar o conteúdo de uma pasta
void mostrarConteudo(Node* pasta) {
    if (pasta == NULL || pasta->filho == NULL) {
        printf("Pasta vazia\n");
        return;
    }

    printf("Conteúdo da pasta:\n");
    Node* arquivo = pasta->filho; // Pega o primeiro arquivo/pasta filho
    while (arquivo != NULL) {// Enquanto houver arquivos/pastas
        printf("%s%s\n", arquivo->nome, (arquivo->verificaPasta ? "--" : "")); // Adiciona '/' para pastas
        arquivo = arquivo->irmao;
    }
}


// Função para criar um novo arquivo
void criarArquivo(Node* atual) {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);
    getchar(); 
    Node* novoArquivo = criarNo(nomeArquivo, atual, 0); // Cria um novo nó para o arquivo
    adicionarFilho(atual, novoArquivo);// Adiciona o arquivo como filho do nó atual
    printf("Arquivo criado com sucesso!\n");
}

// Função para acessar uma pasta
Node* acessarPasta(Node *pasta, char nome[]) {
    if (strcmp(nome, "..") == 0) {
        return (pasta->pai != NULL) ? pasta->pai : pasta;
    }
    Node *atual = pasta->filho;
    while (atual != NULL) {
        if (atual->verificaPasta && strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->irmao;
    }
    return NULL;
}

// Função para apagar um nó e seus descendentes
void apagarNode(Node *no) {
    if (no->filho != NULL) {
        apagarNode(no->filho);
    }
    if (no->irmao != NULL) {
        apagarNode(no->irmao);
    }
    free(no);
}

// Função para remover um arquivo ou pasta
void rm(Node *pasta, char nome[]) {
    Node *atual = pasta->filho;
    Node *anterior = NULL;
    
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (atual->verificaPasta && atual->filho != NULL) {
                printf("Apagando o conteúdo e a pasta '%s'\n", nome);
                apagarNode(atual->filho); 
                atual->filho = NULL;    
            }
            
            if (anterior == NULL) {
                pasta->filho = atual->irmao;  
            } else {
                anterior->irmao = atual->irmao; 
            }
            
            free(atual);  
            printf("'%s' removido com sucesso!\n", nome);
            return;
        }
        
        anterior = atual;  
        atual = atual->irmao;  
    }

    printf("Arquivo ou pasta '%s' não encontrado\n", nome);
}

int main() {
    Node* raiz = criarNo("raiz", NULL, 1);
    Node* atual = raiz;
    char nomePasta[100];
    
    while (1) {
        printf("\n");
        imprimirCaminho(atual);
        printf("\n");
        
        char opcao[10];
    
        fgets(opcao, sizeof(opcao), stdin);
        opcao[strcspn(opcao, "\n")] = 0; // Remove o caractere de nova linha

        if (strcmp(opcao, "ls") == 0) { // Listar conteúdo da pasta
            mostrarConteudo(atual);
        } else if (strcmp(opcao, "mp") == 0) {
            printf("Digite o nome da pasta: ");
            scanf("%s", nomePasta);
            getchar(); 
            Node* novaPasta = criarNo(nomePasta, atual, 1);
            adicionarFilho(atual, novaPasta);
            printf("Pasta criada com sucesso!\n");
           
        } else if (strcmp(opcao, "ma") == 0) { // Criar arquivo
            criarArquivo(atual);
           
        } else if (strcmp(opcao, "cd") == 0) { // Navegação
            printf("Digite o nome da pasta: ");
            scanf("%s", nomePasta);
            getchar(); 
            Node *novaPasta = acessarPasta(atual, nomePasta);
            if (novaPasta != NULL) {
                atual = novaPasta;
            } else {
                printf("Comando inválido\n");
            }
           
        } else if (strcmp(opcao, "rm") == 0) { // Remoção
             printf("Digite o nome da pasta ou arquivo: ");
            scanf("%s", nomePasta);
            getchar(); 
            rm(atual, nomePasta);
           
        } else if (strcmp(opcao, "ex") == 0) { // Sair
            printf("Saindo...\n");
            return 0;
        } else {
            printf("Comando inválido\n");
        }
    }
}
