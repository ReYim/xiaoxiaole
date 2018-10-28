#include <iostream>
#include<time.h>
#include <vector>
using namespace std;

#define right 4
#define left  1
#define up    2
#define down  3

class Point {
public:
  int x, y;
  int direction;
  int *removeDirection; //right,left,down,up
  int score;
  Point(int x0 = -1, int y0 = -1, int dir = -1, int *removeDir = NULL, int s = -1) {
    x = x0;
    y = y0;
    direction = dir;
    removeDirection = removeDir;
    score = s;
  }
};

class XXL {
private:
  int M;
  int N;
  int K;
  int score;
public:
  XXL(int m0=8, int n0=4, int k0=4) {
    M = m0;
    N = n0;
    K = k0;
    score = 0;
  }

  int *check(int i, int j, int ijValue, int dir, int *matrix[4]) {
    //right
    int *result = new int[4];
    for(int k = 0; k < 5; k++) {
      result[k] = 0;
    }
    if (j + 2 < N && dir != left) {
      if (ijValue == matrix[i][j+1] && ijValue == matrix[i][j+2]) {
        result[0] = 1;
        result[right] = right;
      }
    }
    //left
    if ( j - 2 > 0 && dir != right) {
      if (ijValue == matrix[i][j-1] && ijValue == matrix[i][j-2]) {
        result[0] = 1;
        result[left] = left;
      }
    }
    //up
    if (i - 2 > 0 && dir != down) {
      if (ijValue == matrix[i - 1][j] && ijValue == matrix[i - 2][j]) {
        result[0] = 1;
        result[up] = up;
      }
    }
    //down
    if (i + 2 < M && dir != up) {
      if (ijValue == matrix[i + 1][j] && ijValue == matrix[i + 2][j]) {
        result[0] = 1;
        result[down] = down;
      }
    }
    return result;
  }

  void xiao(int *matrix[4]) {
    vector<Point> points;

    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        if (matrix[i][j] > 0) {
          int u, l;
          int *result = new int[4];
          for(int k = 0; k < 5; k++) {
            result[k] = 0;
          }
          int *downSwapResult;
          int r = matrix[i][j];
          int d = matrix[i][j];
          if (i == M - 1) {
            u = -1;
            downSwapResult = result;
          } else {
            u = matrix[i+1][j];
            downSwapResult =   check(i + 1 , j, d, down, matrix);
          }
          if (j == N - 1) {
            l = -1;
          } else {
            l = matrix[i][j+1];
          }

          int *rightSwapResult =  check(i			, j+1, r, right, matrix);
          int *leftSwapResult =   check(i			, j, l, left, matrix);
          int *upSwapResult =     check(i		  , j, u, up, matrix);
          if (rightSwapResult[0]) {
            points.push_back(Point(i , j, right, rightSwapResult));
          }
          if (leftSwapResult[0]) {
            points.push_back(Point(i, j + 1, left, leftSwapResult));
          }
          if (downSwapResult[0]) {
            points.push_back(Point(i, j, down, downSwapResult));
          }
          if (upSwapResult[0]) {
            points.push_back(Point(i + 1, j, up, upSwapResult));
          }
        }

      }
    }
    cout<<"points size:" << points.size()<< endl;
    for (int i = 0; i < points.size(); i++) {
      Point p = points.at(i);
      int **swapedMatrix = swap(p.x, p.y, p.direction, matrix);
      getScore(swapedMatrix, &p);
      displayMatrix(swapedMatrix);
      cout<<"score:"<<p.score<<endl;
    }
  }
  void remove(int *m[4],int x, int y, int count, int dir) {
    if (count > 0) {
      for (int i = x; i > -1 ; i--) {
        if (i - count > -1) {
          m[i][y] = m[i - count][y];
        } else {
          m[i][y] = -1;
        }
      }
    }
  }
  void getScore(int *m[4], Point *point) {
    Point p = *point;
    int score = 0;
    cout<<"x:" << p.x<<endl;
    cout<<"y:" << p.y<<endl;
    cout<<"direction:" << p.direction<<endl;
    cout<<"removeDirection left:" << p.removeDirection[left]<<endl;
    cout<<"removeDirection right:" << p.removeDirection[right]<<endl;
    cout<<"removeDirection: up" << p.removeDirection[up]<<endl;
    cout<<"removeDirection:down" << p.removeDirection[down]<<endl;
    int X = 0, Y = 0;
    if (p.direction == right) {
      Y = 1;
    }
    if (p.direction == left) {
      Y = -1;
    }
    if (p.direction == down) {
      X = 1;
    }
    if (p.direction == up) {
      X = -1;
    }
    int removeValue = m[p.x + X][p.y + Y];
    cout<<"removeValue:" << removeValue<<endl;
    if (p.removeDirection[right] == right) {
      for (int j = p.y + Y; j< 4; j++) {
        if(m[p.x + X][j] == removeValue) {
          score ++;
          remove(m, p.x + X, j, 1, right);
        }
        else break;
      }
      for (int j = p.y + Y - 1; j > - 1; j--) {
        if(m[p.x + X][j] == removeValue) {
          score ++;
          remove(m, p.x + X, j, 1, right);
        }
        else break;
      }
    }
    if (p.removeDirection[left] == left) {
      for (int j = p.y + Y; j > -1; j--) {
        if(m[p.x + X][j] == removeValue) {
          score ++;
          remove(m, p.x + X, j, 1, left);
        }
        else break;
      }
      for (int j = p.y + Y + 1; j < 4; j++) {
        if(m[p.x + X][j] == removeValue) {
          score ++;
          remove(m, p.x + X, j, 1, left);
        }
        else break;
      }
    }
    if (p.removeDirection[down] == down) {
      int count1 = 0;
      for (int j = p.x + X; j < 8; j++) {
        if(m[j][p.y + Y] == removeValue) {
          score ++;
          count1 ++;
        }
        else break;
      }
      int count = 0;
      for (int j = p.x + X - 1; j > -1; j--) {
        if(m[j][p.y + Y] == removeValue) {
          score ++;
          count ++;
        }
        else break;
      }
      remove(m, p.x + count1, p.y + Y, count1, down);
      remove(m, p.x, p.y + Y , count, up);
    }
    if (p.removeDirection[up] == up) {
      int count1 = 0;
      for (int j = p.x + X; j > -1; j--) {
        if(m[j][p.y + Y] == removeValue) {
          score ++;
          count1 ++;
        }
        else break;
      }
      int count = 0;
      for (int j = p.x + X + 1; j < 8 + X; j++) {
        if(m[j][p.y + Y] == removeValue) {
          score ++;
          count ++;
        }
        else break;
      }
      remove(m, p.x, p.y + Y, count1, up);
      remove(m, p.x - count, p.y + Y , count, down);
    }
    point->score = score;
  }
  int **swap(int x, int y, int dir, int *m[4]) {
    int **matrix = new int *[M];
    for (int i = 0; i < M; i++) {
      matrix[i] = new int[N];
    }
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        matrix[i][j] = m[i][j];
      }
    }
    if (right == dir) {
      int tmp = matrix[x][y];
      matrix[x][y] = matrix[x][y+1];
      matrix[x][y+1] = tmp;
      return matrix;
    } else if (dir == down) {
      int tmp = matrix[x][y];
      matrix[x][y] = matrix[x+1][y];
      matrix[x+1][y] = tmp;
      return matrix;
    } else if (dir == left) {
      int tmp = matrix[x][y];
      matrix[x][y] = matrix[x][y-1];
      matrix[x][y-1] = tmp;
      return matrix;
    } else if (dir == up) {
      int tmp = matrix[x][y];
      matrix[x][y] = matrix[x - 1][y];
      matrix[x - 1][y] = tmp;
      return matrix;
    }
  }

  void displayMatrix(int *matrix[4]) {
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        cout << matrix[i][j] << ' ';
      }
      cout << endl;
    }
  }
  ~XXL() {
  }

};

int main() {
  int m = 8;
  int n = 4;
  int k = 4;
  int matrix[m][n] = {
    {3, 3, 4, 3},
    {3, 2, 3, 3},
    {2, 4, 3, 4},
    {1, 3, 4, 3},
    {3, 3, 1, 1},
    {3, 4, 3, 3},
    {1, 4, 4, 3},
    {2, 2, 3, 2},
  };
  cout<<"right:"<<right<<endl;
  cout<<"left:"<<left<<endl;
  cout<<"down:"<<down<<endl;
  cout<<"up:"<<up<<endl;
  int **matrixPointer = new int*[m];
  for (int i = 0; i < m; i++) {
    matrixPointer[i] = new int[n];
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      matrixPointer[i][j] = matrix[i][j];
    }
  }
  XXL xxl(m, n, k);
  xxl.displayMatrix(matrixPointer);
  xxl.xiao(matrixPointer);
  return 0;
}
