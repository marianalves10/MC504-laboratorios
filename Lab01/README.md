# Soduku
O presente trabalho busca verificar a corretude de um jogo de Sudoku já preenchido.

# Compilação e teste
Para compilar é necessário executar o comando

*gcc -std=c99 lab01.c -lpthread*

e para testar é necessário ter um arquivo *.in* contendo uma matriz 9x9 preenchida com inteiros positivos, como, por exemplo,os arquivos presentes *falha.in* que dá resultado incorreto e *sucesso.in* que dá resultado correto.

Para testar, rode o comando

*./a.out <sucesso.in*.

# Saída
O programa exibirá o resultado esperado.

# Threads

Criamos 11 threads diferentes para fazer a divisão do trabalho. Um thread que percorre as linhas do tabuleiro verificando se existem dígitos válidos, e outra para as colunas. As demais 9 threads fazem o trabalho de verificar os dígitos de cada quadrado das submatrizes 3x3 que compõem o tabuleiro de sudoku.
