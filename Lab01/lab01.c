#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct 
{
    int linha;
    int coluna;
    int (** tabuleiro);
} auxiliar;

void * percorrer_linhas(void * params);

void * percorrer_colunas(void * params);

void * check_quadrado(void * params);


int main(void) 
{
    int ** tabuleiro = malloc(sizeof(int *)* 9);
    for (int i = 0; i < 9; i++){
        tabuleiro[i] = malloc(sizeof(int)*9);
    }
    for ( int i=0; i<9; i++ ){
        for ( int j=0; j<9; j++ ){
            scanf ("%d", &tabuleiro[i][j]);
        }
    }
    
    auxiliar **vetor = malloc(sizeof(auxiliar *)*10);

    vetor[0] = malloc(sizeof(auxiliar));
    vetor[0]->linha = 0;
    vetor[0]->coluna = 0;
    vetor[0]->tabuleiro = tabuleiro;

    vetor[1] = malloc(sizeof(auxiliar));
    vetor[1]->linha = 0;
    vetor[1]->coluna = 0;
    vetor[1]->tabuleiro = tabuleiro;
    
    vetor[2] = malloc(sizeof(auxiliar));
    vetor[2]->linha = 0;
    vetor[2]->coluna = 3;
    vetor[2]->tabuleiro = tabuleiro;
    
    vetor[3] = malloc(sizeof(auxiliar));
    vetor[3]->linha = 0;
    vetor[3]->coluna = 6;
    vetor[3]->tabuleiro = tabuleiro;
    
    vetor[4] = malloc(sizeof(auxiliar));
    vetor[4]->linha = 3;
    vetor[4]->coluna = 0;
    vetor[4]->tabuleiro = tabuleiro;
    
    vetor[5] = malloc(sizeof(auxiliar));
    vetor[5]->linha = 3;
    vetor[5]->coluna = 3;
    vetor[5]->tabuleiro = tabuleiro;
    
    vetor[6] = malloc(sizeof(auxiliar));
    vetor[6]->linha = 3;
    vetor[6]->coluna = 6;
    vetor[6]->tabuleiro = tabuleiro;
    
    vetor[7] = malloc(sizeof(auxiliar));
    vetor[7]->linha = 6;
    vetor[7]->coluna = 0;
    vetor[7]->tabuleiro = tabuleiro;
    
    vetor[8] = malloc(sizeof(auxiliar));
    vetor[8]->linha = 6;
    vetor[8]->coluna = 3;
    vetor[8]->tabuleiro = tabuleiro;
    
    vetor[9] = malloc(sizeof(auxiliar));
    vetor[9]->linha = 6;
    vetor[9]->coluna = 6;
    vetor[9]->tabuleiro = tabuleiro;
    
    void * linhas;
    void * colunas;
    void * quadrado1;
    void * quadrado2;
    void * quadrado3;
    void * quadrado4;
    void * quadrado5;
    void * quadrado6;
    void * quadrado7;
    void * quadrado8;
    void * quadrado9;

    pthread_t thread_linhas, thread_colunas, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;

    pthread_create(&thread_linhas, NULL, percorrer_linhas, vetor[0]);
    pthread_create(&thread_colunas, NULL, percorrer_colunas, vetor[0]);
    pthread_create(&thread1, NULL, check_quadrado, vetor[1]);
    pthread_create(&thread2, NULL, check_quadrado, vetor[2]);
    pthread_create(&thread3, NULL, check_quadrado, vetor[3]);
    pthread_create(&thread4, NULL, check_quadrado, vetor[4]);
    pthread_create(&thread5, NULL, check_quadrado, vetor[5]);
    pthread_create(&thread6, NULL, check_quadrado, vetor[6]);
    pthread_create(&thread7, NULL, check_quadrado, vetor[7]);
    pthread_create(&thread8, NULL, check_quadrado, vetor[8]);
    pthread_create(&thread9, NULL, check_quadrado, vetor[9]);

    pthread_join(thread_linhas, &linhas);
    pthread_join(thread_colunas, &colunas);
    pthread_join(thread1, &quadrado1);
    pthread_join(thread2, &quadrado2);
    pthread_join(thread3, &quadrado3);
    pthread_join(thread4, &quadrado4);
    pthread_join(thread5, &quadrado5);
    pthread_join(thread6, &quadrado6);
    pthread_join(thread7, &quadrado7);
    pthread_join(thread8, &quadrado8);
    pthread_join(thread9, &quadrado9);
    
    if (linhas == 1 && colunas == 1 && quadrado1 == 1 && quadrado2 == 1 && quadrado3 == 1 && quadrado4 == 1 && quadrado5 == 1 && quadrado6 == 1 && quadrado7 == 1 && quadrado8 == 1 && quadrado9 == 1 ) {
        printf("Sudoku est?? resolvido!\n");
    }
    else {
        printf("Sudoku n??o est?? resolvido!\n");
    }
    
    return 0;
}

// checa se um quadrado 3x3 cont??m todos os n??meros de 1 a 9, aparecendo exatamente 1 vez cada.
// recebe um apontador para os par??metros (dados da posi????o do quadrado e o tabuleiro)
// retorna 0 em caso de algum n??mero repetido ou faltate, 1 caso contr??rio 
void* check_quadrado(void* parametros) {
    auxiliar* quadrado = (auxiliar*) parametros;
    int contador[9] = {0};
    int i,j;

    // percorre todas as linhas do quadrado
    for (i = quadrado->linha; i < 3 + quadrado->linha; ++i) {
        // percorre todas as colunas de uma linha
        for (j = quadrado->coluna; j < 3 + quadrado->coluna; ++j) {
            // contador ?? atualizado com contagem de cada n??mero at?? o momento
            contador[quadrado->tabuleiro[i][j] - 1] += 1;
        }
    }
    // se, ao final, o contador tiver algum n??mero != 1, retornar 0
    for (i = 0; i < 9; i++) {
        if (contador[i] != 1) {
            return (void *) 0;
        }
    }

    // caso contr??rio (todos os n??meros de 1 a 9 aparecem exatamente 1 vez), retornar 1
    return (void *) 1;
}

void * percorrer_linhas(void * params){
    auxiliar * aux =(auxiliar *) params;
    int linha_inicial = aux->linha, coluna_inicial = aux->coluna;

    for (int i = linha_inicial; i < 9; ++i){
        int linhas[10] = {0};
        for (int j = coluna_inicial; j < 9; ++j){
            int verificar_posicao = aux->tabuleiro[i][j];
            if (linhas[verificar_posicao] != 0){
                return (void*) 0;
            }
            else {
                linhas[verificar_posicao] = 1;
            }
        }
    }

    return (void*) 1;
}
    
// fun??ao que checa se as colunas est??o preenchidas com digitos validos
void * percorrer_colunas(void * params) {
    auxiliar * dado = (auxiliar *) params;
    int comeco_linha = dado -> linha, comeco_coluna = dado -> coluna;
    for ( int i = comeco_coluna; i < 9; ++i) {
        int coluna[10] =  {0};
        for( int j = comeco_linha; j <9; ++j) {
            int num = dado->tabuleiro[j][i];
            if (coluna[num] != 0) {
                return (void*) 0; // a coluna nao esta preenchida
            }
            coluna[num] = 1;
        }
    }
    return (void*) 1; // todas as colunas tem numeros de 1 a 9
}
