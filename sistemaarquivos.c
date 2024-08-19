#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um arquivo ou pasta
typedef struct Node {
    char nome[100];
    struct Node* pai;
    struct Node* filho;
    struct Node* irmao;
} Node;

// Função para criar um novo nó
Node* criarNo(const char* nome, Node* pai) {
    Node* novoNo = (Node*)malloc(sizeof(Node)); // Aloca memória para o novo nó
    strcpy(novoNo->nome, nome); // Copia o nome para o novo nó
    novoNo->pai = pai; // Define o nó pai
    novoNo->filho = NULL; // Inicializa o ponteiro para o primeiro filho
    novoNo->irmao = NULL; // Inicializa o ponteiro para o próximo irmão
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
    if (atual->irmao != NULL) { // Se houver irmão, imprime "-"
        printf("-");
    }
}
// Função para mostrar o conteúdo de uma pasta
void mostrarConteudo(Node* pasta) {
    printf("Conteúdo da pasta:\n");
    Node* arquivo = pasta->filho; // Pega o primeiro arquivo/pasta filho
    while (arquivo != NULL) {// Enquanto houver arquivos/pastas
        printf("%s", arquivo->nome);// Imprime o nome do arquivo/pasta
        if (arquivo->filho != NULL) {
            printf("-");
        }
        printf("\n");
        arquivo = arquivo->irmao;
    }
}

// Função para criar um novo arquivo
void criarArquivo(Node* atual) {
    char nomeArquivo[100];
    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeArquivo);
    Node* novoArquivo = criarNo(nomeArquivo, atual); // Cria um novo nó para o arquivo
    adicionarFilho(atual, novoArquivo);// Adiciona o arquivo como filho do nó atual
    printf("Arquivo criado com sucesso!\n");
}

int main() {
    Node* raiz = criarNo("raiz", NULL);
    Node* atual = raiz;
    
    while (1) {
        printf("\n");
        imprimirCaminho(atual);
        printf("\n");
        
        char opcao[10];
    
        fgets(opcao, sizeof(opcao), stdin);
        opcao[strcspn(opcao, "\n")] = 0; // Remove o caractere de nova linha

       if (strcmp(opcao, "ls") == 0) { // Listar conteúdo da pasta
            mostrarConteudo(atual);
        }

      //navegação de pastas
    // exclusao de pasta ou arquivo

        /*}*/ else if (strcmp(opcao, "mp") == 0) {
            char nomePasta[100];
            printf("Digite o nome da pasta: ");
            scanf("%s", nomePasta);
            Node* novaPasta = criarNo(nomePasta, atual);
            adicionarFilho(atual, novaPasta);
            printf("Pasta criada com sucesso!\n");

        } else if (strcmp(opcao, "ma") == 0) { // Criar arquivo
            criarArquivo(atual);

        } else if (strcmp(opcao, "ex") == 0) { // sair
            printf("Saindo...\n");
            return 0;
        }
    }

           