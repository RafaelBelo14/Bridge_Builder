/*

Tipos de sentidos:

N - Null
S - Subir
D - Descer
A - Ambos

1º e última coluna são fixas pelo que são apenas calculadas as soluções em altura 0 nesses casos.
Ciclos for percorridos apenas pelas células que têm um bloco em comum com a em qustão.

*/

#include <iostream>
#include <vector>
#include <string> 
using namespace std;

struct celula {
      char sentido;
      long valor_subida;
      long valor_descida;
};

vector<int> test; 

int doCase(int n, int h, int H);
int mod_abs(int a, int mod);
int mod_add(int a, int b, int mod);

int main()
{
      int reps, n, h, H;
      cin >> reps;

      if (reps > 20) {
            return 0;
      }

      for (int i = 0; i < reps; i++) {
            cin >> n;
            cin >> h;
            cin >> H;

            // VERIFICA CONDIÇÕES INICIAIS
            if (n > 500 || n <= 0 || h > 500 || h <= 0 || H > 60000 || H <= 0) {
                  return 0;
            }

            // VERIFICA SOLUÇÕES IMPOSSÍVEIS
            if (h == H || h > H || n < 2) {
                  test.push_back(0);
            }
            else {
                test.push_back(doCase(n, h, H));  
            }
      }

      for (auto i = test.begin(); i != test.end(); ++i) 
            cout << *i << endl; 
      
      test.clear();
      return 0;
}

int doCase(int n, int h, int H) {

      int lines = n;
      int columns = H;
      int blockHeight = h;
      int k;

      // ALLOCA MEMÓRIA PARA O ARRAY DE ARRAY'S
      struct celula ** matriz = (struct celula ** )malloc(lines * sizeof(struct celula *));
      int solutions = 0;

      for (int i = 0; i < lines; i++) {

            //ALOCA MEMÓRIA PARA UM NOVO ARRAY QUE SERÁ UMA LINHA
            matriz[i] = (struct celula *)malloc(columns * sizeof(struct celula));

            for (int j = 0; j < columns; j++) {

                  if (i == 0) {
                        if (j == 0) {
                              matriz[i][j].sentido = 'S';
                              matriz[i][j].valor_subida = 1;
                              matriz[i][j].valor_descida = 0; 
                        }
                        else {
                              matriz[i][j].sentido = 'N';
                              matriz[i][j].valor_subida = 0;
                              matriz[i][j].valor_descida = 0;
                        }
                        break;
                  }
                  else {

                        // GUARDA NA CÉLULAS OS VALORES 'DEFAULT'
                        matriz[i][j].sentido = 'N';
                        matriz[i][j].valor_subida = 0;
                        matriz[i][j].valor_descida = 0;

                        if (j + (blockHeight - 1) < columns) {

                              // VALOR PARA PERCORRER NO CICLO FOR (IMPEDE DE SE PERCORRA A LINHA TODA)
                              if (j - (blockHeight - 1) < 0) {
                                    k = 0;
                              }
                              else {
                                    k = j - (blockHeight - 1);
                              }

                              //COLUNAS INTERMÉDIAS
                              if (i < lines - 1) {

                                    for (; k < j + blockHeight; k++) {
                                          
                                          // SÓ SOBE
                                          if ((matriz[i - 1][k].sentido == 'S' || matriz[i - 1][k].sentido == 'A') && k < j && k + blockHeight > j) {
                                                matriz[i][j].sentido = 'S';
                                                matriz[i][j].valor_subida = mod_add(matriz[i][j].valor_subida, matriz[i - 1][k].valor_subida, 1000000007);
                                          }
                                          // DESCE E SOBE
                                          if ((matriz[i - 1][k].sentido == 'S' || matriz[i - 1][k].sentido == 'A') && j < k && j + blockHeight > k) {
                                                if (matriz[i][j].sentido == 'S' || matriz[i][j].sentido == 'A') {
                                                      matriz[i][j].sentido = 'A';
                                                      matriz[i][j].valor_descida = mod_add(matriz[i][j].valor_descida, matriz[i - 1][k].valor_subida + matriz[i - 1][k].valor_descida, 1000000007);
                                                }
                                          } 
                                          // SÓ DESCE
                                          if ((matriz[i][j].sentido == 'N' || matriz[i][j].sentido == 'D') && j < k && j + blockHeight > k) {
                                                if (matriz[i - 1][k].sentido == 'S' || matriz[i - 1][k].sentido == 'D' || matriz[i - 1][k].sentido == 'A') {
                                                      matriz[i][j].sentido = 'D';
                                                      matriz[i][j].valor_descida = mod_add(matriz[i][j].valor_descida, matriz[i - 1][k].valor_subida + matriz[i - 1][k].valor_descida, 1000000007);
                                                }
                                          }
                                    }
                              }

                              // CASO SEJA A ÚLTIMA COLUNA SÓ CALCULA PARA A ALTURA 0
                              else if (i == lines - 1 && j == 0){

                                    for (; k < j + blockHeight; k++) {
                                          if ((matriz[i - 1][k].sentido == 'S' || matriz[i - 1][k].sentido == 'A' || matriz[i - 1][k].sentido == 'D') && j < k && j + blockHeight > k) {
                                                matriz[i][j].sentido = 'D';
                                                matriz[i][j].valor_descida = mod_add(matriz[i][j].valor_descida, matriz[i - 1][k].valor_subida + matriz[i - 1][k].valor_descida, 1000000007);
                                          }
                                    }
                              }

                              // ATUALIZA O TOTAL DE SOLUÇÕES
                              if (j == 0) {
                                    solutions = mod_add(solutions, matriz[i][j].valor_descida, 1000000007);
                              }
                        } 
                  }
            }
      }
      return mod_abs(solutions, 1000000007);
}

int mod_abs(int a, int mod) {
  return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}