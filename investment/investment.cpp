#include <iostream>
#include <vector>
using namespace std;

int n, m, f_1, f_2, d = 10000;
vector<vector<double>> r;

void read_input() {
  cin >> n >> m >> f_1 >> f_2;
  for (int i = 0; i < n; i++) {
    vector<double> tmp;
    for (int j = 0; j < m; j++) {
      double t;
      cin >> t;
      tmp.push_back(t);
    }
    r.push_back(tmp);
  }
}

void DP() {
  vector<vector<double>> C(n, vector<double>(m, 0));
  vector<vector<int>> S(n, vector<int>(m, 0));
  for (int i = 0; i < n; i++)
    C[i][0] = d * r[i][0];
  for (int j = 1; j < m; j++)
    for (int i = 0; i < n; i++) {
      C[i][j] = C[i][j-1] - f_1;
      S[i][j] = i;
      for (int k = 0; k < n; k++)
	if (k != i && C[k][j-1] - f_2 > C[i][j]) {
	  C[i][j] = C[k][j-1] - f_2;
	  S[i][j] = k;
	}
      C[i][j] = C[i][j]*r[i][j];
    }

  int max_val = 0, max_idx = 0;
  for (int i = 0; i < n; i++)
    if (C[i][m-1] > max_val) {
      max_val = C[i][m-1];
      max_idx = i;
    }
  cout << "DP: max return: " << max_val << endl;
  for (int j = m-1; j >= 0; j--) {
    cout << "Choose Investment " << max_idx << " in Year " << j << ",  return: "<< C[max_idx][j] << endl;
    max_idx = S[max_idx][j];
  }
}

void greedy() {
  vector<double> R(m+1, 0);
  vector<int> I(m);
  for (int k = m-1; k >= 0; k--) {
    int q = 1;
    for (int i = 0; i < n; i++)
      if (r[i][k] > r[q][k])
	q = i;
    if (k == m-1 || R[k+1] + d * r[I[k+1]][k] - f_1 > R[k+1] + d * r[q][k] - f_2){
      R[k] = R[k+1] + d * r[I[k+1]][k] - f_1;
      I[k] = q;
    } else {
      R[k] = R[k+1] + d * r[q][k] - f_2;
      I[k] = q;
    }
  }
  cout << "greedy backwards: max return: " << R[0] << endl;
  for (int j = 0; j < m; j++)
    cout << "Choose Investment " << I[j] << " in Year " << j << endl;
}

void greedy2() {
  vector<double> R(m, 0);
  vector<int> I(m);
  for (int k = 0; k < m; k++) {
    int q = 1;
    for (int i = 0; i < n; i++)
      if (r[i][k] > r[q][k])
	q = i;
    if (k == 0) {
      R[k] = d * r[q][k];
      I[k] = q;
    }
    else if (R[k-1] + d * r[I[k-1]][k] - f_1 > R[k-1] + d * r[q][k] - f_2){
      R[k] = R[k-1] + d * r[I[k-1]][k] - f_1;
      I[k] = q;
    } else {
      R[k] = R[k-1] + d * r[q][k] - f_2;
      I[k] = q;
    }
  }
  cout << "greedy forwards: max return: " << R[m-1] << endl;
  for (int j = 0; j < m; j++)
    cout << "Choose Investment " << I[j] << " in Year " << j << endl;
}

int main() {
  read_input();
  DP();
  greedy();
  greedy2();
  return 0;
}
