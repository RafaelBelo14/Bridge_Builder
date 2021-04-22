#include <iostream>
#include <algorithm>
#include<numeric>
#include <set>
#include <vector>
#include <string> 
#include <chrono>
#include <cstdint>
using namespace std;

//using namespace std::chrono;

vector<int> test; 
vector< vector< vector<char> > > matriz;

void doCase(int n, int h, int H);
void printMatriz();

int main()
{
      int reps, n, h, H;
      cin >> reps;

      for (int i = 0; i < reps; i++) {
            cin >> n;
            cin >> h;
            cin >> H;

            doCase(n, h, H);
      }

      for (auto i = test.begin(); i != test.end(); ++i) 
            cout << *i << endl; 
      
      test.clear();
      return 0;
}

void doCase(int n, int h, int H) {

      for (int i = 0; i < n; i++) {
            vector< vector<char> > row;
            for (int j = 0; j < H; j++) {
                  if (i == 0 && j == 0) {
                        vector<char> vect;
                        vect.push_back('S');
                        vect.push_back('0');
                        vect.push_back('0');
                        row.push_back(vect);
                        
                  }
                  else {
                        vector<char> vect;
                        vect.push_back('N');
                        vect.push_back('0');
                        vect.push_back('0');
                        row.push_back(vect);
                  }
            }
            matriz.push_back(row);
      }

      for (int i = 1; i < n; i++) {
            for (int j = 1; j < H; j++) {
                  if (matriz[i - 1][j - 1][0] == 'S') {
                        matriz[i][j][0] = 'S';
                        matriz[i][j][1] = '1';
                  }
            }
      }

      printMatriz();
}

void printMatriz() {
      for (int i = 0; i < matriz.size(); i++) {
            for (int j = 0; j < matriz[i].size(); j++) {
                  cout << "(" << matriz[i][j][0] << "," << matriz[i][j][1] << "," << matriz[i][j][2] << ") ";
            }
            cout << endl;
      }
}