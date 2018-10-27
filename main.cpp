#include <iostream>
#include<time.h>
#include <vector>
using namespace std;

#define right 0
#define left  1
#define up    2
#define down  3

class Point {
public:
  int x, y;
  int direction;
  Point(int x0 = 0, int y0 = 0, int dir = 0) {
    x = x0;
    y = y0;
    direction = dir;
  }
};

class XXL {
private:
  int M;
  int N;
  int K;
  int **matrix;
  int score;
public:
  XXL(int m0=8, int n0=4, int k0=4) {
    M = m0;
    N = n0;
    K = k0;
    score = 0;
    matrix = new int *[M];
    for (int i = 0; i < M; i++) {
      matrix[i] = new int[N];
    }
  }
  void copy_matrix(int a[][4]) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        matrix[i][j] = a[i][j];
      }
    }
  }
  friend ostream & operator<<(ostream &out, const XXL& xxl) {
    for (int i = 0; i < xxl.M; i++) {
      for (int j = 0; j < xxl.N; j++) {
        out << xxl.matrix[i][j] << ' ';
      }
      out << endl;
    }
    return out;
  }

  bool check(int i, int j, int ijValue, int dir) {
    //right
    if (j + 2 < N && dir != left) {
      if (ijValue == matrix[i][j+1] && ijValue == matrix[i][j+2]) {
        return true;
      }
    }
    //left
    if ( j - 2 > 0 && dir != right) {
      if (ijValue == matrix[i][j-1] && ijValue == matrix[i][j-2]) {
        return true;
      }
    }
    //down
    if (i + 2 < M && dir != up) {
      if (ijValue == matrix[i + 1][j] && ijValue == matrix[i + 2][j]) {
        return true;
      }
    }
    //up
    if (i - 2 > 0 && dir != down) {
      if (ijValue == matrix[i - 1][j] && ijValue == matrix[i - 2][j]) {
        return true;
      }
    }
    return false;
  }

  void xiao() {
    vector<Point> points;
    //int matrix[8][4];
    //for (int i = 0; i < M; i++) {
    //  for (int j = 0; j < N; j++) {
    //    matrix[i][j] = m[i][j];
    //  }
    //}

    for (int i = 0; i < M-1; i++) {
      for (int j = 0; j < N-1; j++) {
        if (matrix[i][j] > 0) {
          //right swap
					int r = matrix[i][j];
					int l = matrix[i][j+1];
					int u = matrix[i+1][j];
					int d = matrix[i][j];

          bool rightSwapResult =  check(i, j+1, r, right);
          bool leftSwapResult =   check(i, j, l, left);
          bool downSwapResult =   check(i + 1, j, d, down);
          bool upSwapResult =     check(i, j, u, up);
          if (rightSwapResult || leftSwapResult) {
            points.push_back(Point(i,j,right));
          }
          if (downSwapResult || upSwapResult) {
            points.push_back(Point(i,j,down));
          }
        }

      }
    }
		cout<<"points size:" << points.size()<< endl;
    for (int i = 0; i < 1; i++) {
			Point p = points.at(i);
			cout<<"x:" << p.x<<endl;
			cout<<"y:" << p.y<<endl;
			cout<<"direction:" << p.direction<<endl;
      swap(p.x, p.y, p.direction);
      //tianchong()
      //xiao(matrix);
      //score++;
    }
  }
  //int [][4] swap(int x, int y, int dir) {
  void swap(int x, int y, int dir) {
    if (right == dir) {
      int tmp = matrix[x][y];
      matrix[x][y] = matrix[x][y+1];
      matrix[x][y+1] = tmp;
    } else if (dir == down) {
      int tmp = matrix[x][y];
      matrix[x][y] = matrix[x+1][y];
      matrix[x+1][y] = tmp;
    } else {
      cout<<"direction is not exit : "<< dir << endl;
    }
  }

  ~XXL() {
    for (int i = 0; i < M; i++) {
      delete []matrix[i];
    }
    delete []matrix;
  }

};

int main() {
  int m = 8;
  int n = 4;
  int k = 4;
  int matrix[8][4] = {
    {3, 3, 4, 3},
    {3, 2, 3, 3},
    {2, 4, 3, 4},
    {1, 3, 4, 3},
    {3, 3, 1, 1},
    {3, 4, 3, 3},
    {1, 4, 4, 3},
    {1, 2, 3, 2},
  };
  XXL xxl(m, n, k);
  xxl.copy_matrix(matrix);
	cout << xxl;
  xxl.xiao();
  cout << xxl;
  return 0;
}
