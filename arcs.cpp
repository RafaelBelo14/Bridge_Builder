#include <iostream>
#include <vector>
#include <string> 
using namespace std;

struct celula {
      char sentido;
      int valor_subida;
      int valor_descida;
};

vector<int> test; 

int doCase(int n, int h, int H);

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

            if (n > 500 || h > 500 || H > 60000) {
                  return 0;
            }

            test.push_back(doCase(n, h, H));
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
      struct celula matriz[lines][columns];
      int solutions = 0;

      for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                  if (i == 0 && j == 0) {
                        matriz[i][j].sentido = 'S';
                        matriz[i][j].valor_subida = 1;
                        matriz[i][j].valor_descida = 0; 
                  }
                  else {
                        matriz[i][j].sentido = 'N';
                        matriz[i][j].valor_subida = 0;
                        matriz[i][j].valor_descida = 0; 
                  }
            }
      }

      for (int i = 1; i < lines; i++) {
            for (int j = 0; j < columns; j++) {

                  if (i < lines - 1) {
                        if (j + (blockHeight - 1) < columns) {
                              for (int k = 0; k < columns; k++) {
                                    if (matriz[i - 1][k].sentido == 'S' && k < j && k + blockHeight > j) {
                                          matriz[i][j].sentido = 'S';
                                          matriz[i][j].valor_subida += 1;
                                    }
                                    if (matriz[i - 1][k].sentido == 'S' && j < k && j + blockHeight > k) {
                                          matriz[i][j].sentido = 'D';
                                          matriz[i][j].valor_descida += 1;
                                    }
                              }
                        }
                  }
                  else {
                        for (int k = 0; k < columns; k++) {
                              if (matriz[i - 1][k].sentido == 'S' && j < k && j + blockHeight > k) {
                                    matriz[i][j].sentido = 'D';
                                    matriz[i][j].valor_descida += 1;
                              }
                              if (matriz[i - 1][k].sentido == 'D' && j < k && j + blockHeight > k) {
                                    matriz[i][j].sentido = 'D';
                                    matriz[i][j].valor_descida += 1;
                              }
                        }
                  }
     
            }
      }

      /*for (int i = 0; i < n; i++) {
            for (int j = 0; j < H; j++) {
                  cout << "(" << matriz[i][j].sentido << "," << matriz[i][j].valor_subida << "," << matriz[i][j].valor_descida << ")  ";
            }
            cout << endl;
      }*/

      for (int i = 1; i < n; i++) {
            solutions += matriz[i][0].valor_descida;
      }

      

      return solutions;

}