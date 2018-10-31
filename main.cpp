#include <iostream>
#include<time.h>
#include <vector>
using namespace std;

#define right 1
#define left  2
#define up    3
#define down  4

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
public:
  int K;
  XXL(int m0=8, int n0=4, int k0=4) {
    M = m0;
    N = n0;
    K = k0;
  }

  int *check(int i, int j, int ijValue, int dir, int *matrix[4]) {
    int *result = new int[4];
    for(int k = 0; k < 5; k++) {
      result[k] = 0;
    }
    //right
		int rightCount = 0;
    if (j + 1 < N && dir != left) {
			for (int k = j + 1; k < N; k ++) {
				if (ijValue == matrix[i][k]) {
					rightCount ++;
				} else {
					break;		
				}
			}
    }
    //left
		int leftCount = 0;
    if ( j - 1 > -1 && dir != right) {
			for (int k = j - 1; k > -1; k --) {
				if (ijValue == matrix[i][k]) {
					leftCount ++;
				} else {
					break;		
				}
			}
    }
		//leftCount + rightCount >= 3
		if (rightCount + leftCount >= 2) {
			result[0] = 1;
			if (rightCount) {
				result[right] = rightCount;
			} 
			if (leftCount) {
        result[left] = leftCount;
			}
		}
    //up
		int upCount = 0;
    if (i - 1 > -1 && dir != down) {
			for (int k = i - 1; k > -1; k --) {
				if (ijValue == matrix[k][j]) {
					upCount ++;
				} else {
					break;
				}
			}
    }
    //down
		int downCount = 0;
    if (i + 1 < M && dir != up) {
			for (int k = i + 1; k < M; k ++) {
				if (ijValue == matrix[k][j]) {
					downCount ++;
				} else {
					break;
				}
			}
    }
		//downCount + upCount >= 3
		if (downCount + upCount >= 2) {
			result[0] = 1;
			if (downCount) {
				result[down] = downCount;
			} 
			if (upCount) {
        result[up] = upCount;
			}
		}
    return result;
  }

  int xiao(int *matrix[4]) {
		int S = 0;
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
				vector<Point> points;
        if (matrix[i][j] > 0) {
          int u, l;
          int *result = new int[4];
          for(int k = 0; k < 5; k++) {
            result[k] = 0;
          }
          int *downSwapResult;
          int r = matrix[i][j] == -1 ? -2 : matrix[i][j];
          int d = matrix[i][j] == -1 ? -2 : matrix[i][j];
          if (i == M - 1) {
            u = -2;
            downSwapResult = result;
          } else {
						u = matrix[i + 1][j] == -1 ? -2 : matrix[i + 1][j];
            downSwapResult =   check(i + 1 , j, d, down, matrix);
          }
          if (j == N - 1) {
            l = -2;
          } else {
						l = matrix[i][j + 1] == -1 ? -2 : matrix[i][j + 1];
          }

          int *rightSwapResult =  check(i			, j+1, r, right, matrix);
          int *leftSwapResult =   check(i			, j, l, left, matrix);
          int *upSwapResult =     check(i		  , j, u, up, matrix);

	int **swapedMatrix = matrix;

	if (leftSwapResult[0] && !rightSwapResult[0] && !downSwapResult[0]&& !upSwapResult[0]) {
		points.push_back(Point(i, j + 1, left, leftSwapResult));
		swapedMatrix = swap(points.back().x, points.back().y, points.back().direction, swapedMatrix);
	}
	if (rightSwapResult[0] && !leftSwapResult[0] && !downSwapResult[0]&& !upSwapResult[0]) {
		points.push_back(Point(i , j, right, rightSwapResult));
		swapedMatrix = swap(points.back().x, points.back().y, points.back().direction, swapedMatrix);
	}
	if (rightSwapResult[0] && leftSwapResult[0]&& !downSwapResult[0]&& !upSwapResult[0]) {
		points.push_back(Point(i, j + 1, left, leftSwapResult));
		points.push_back(Point(i , j, right, rightSwapResult));
		swapedMatrix = swap(points.back().x, points.back().y, points.back().direction, swapedMatrix);
	}
	  if (downSwapResult[0] && upSwapResult[0] && !leftSwapResult[0]&& !rightSwapResult[0]) {
	    points.push_back(Point(i, j, down, downSwapResult));
	    points.push_back(Point(i + 1, j, up, upSwapResult));
						swapedMatrix = swap(points.back().x, points.back().y, points.back().direction, swapedMatrix);
					}
	  if (downSwapResult[0] && !upSwapResult[0] && !leftSwapResult[0]&& !rightSwapResult[0]) {
	    points.push_back(Point(i, j, down, downSwapResult));
						swapedMatrix = swap(points.back().x, points.back().y, points.back().direction, swapedMatrix);
	  }
	  if (upSwapResult[0] && !downSwapResult[0]&& !leftSwapResult[0]&& !rightSwapResult[0]) {
	    points.push_back(Point(i + 1, j, up, upSwapResult));
						swapedMatrix = swap(points.back().x, points.back().y, points.back().direction, swapedMatrix);
	  }
	if ((rightSwapResult[0] || leftSwapResult[0])&& (downSwapResult[0] || upSwapResult[0])) {
		if (rightSwapResult[0]){
			points.push_back(Point(i , j, right, rightSwapResult));
		} else if (leftSwapResult[0]) {
			points.push_back(Point(i, j + 1, left, leftSwapResult));
		} else if (downSwapResult[0]) {
	    		points.push_back(Point(i, j, down, downSwapResult));
		} else if (upSwapResult[0]) {
	    		points.push_back(Point(i + 1, j, up, upSwapResult));
		}
		swapedMatrix = swap(points.back().x, points.back().y, points.back().direction, swapedMatrix);
	}
	if(points.size() > 0) {
		int score = 0;
		for(int i= 0; i < points.size(); i ++) {
			K++;
			Point p = points.at(i);
			destroy(swapedMatrix, &p);
			score += p.score;
		}
		score = xiao(swapedMatrix) + score; 
		if( score > S) {
			S = score;
		}
	}
        }
      }
    }
		return S;
  }

  void remove(int *m[4],int x, int y, int count) {
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
  void destroy(int *m[4], Point *point) {
    Point p = *point;
    //cout<<"x:" << p.x<<endl;
    //cout<<"y:" << p.y<<endl;
    //cout<<"direction:" << p.direction<<endl;
    //cout<<"removeDirection left:" << p.removeDirection[left]<<endl;
    //cout<<"removeDirection right:" << p.removeDirection[right]<<endl;
    //cout<<"removeDirection: up" << p.removeDirection[up]<<endl;
    //cout<<"removeDirection:down" << p.removeDirection[down]<<endl;
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
    //cout<<"removeValue:" << removeValue<<endl;
		if (p.removeDirection[right] && p.removeDirection[left] && !p.removeDirection[up]&& !p.removeDirection[down]) {
			if (p.removeDirection[right]) {
				for (int j = p.y + Y; j < p.y + Y + p.removeDirection[right] + 1; j++) {
					remove(m, p.x + X, j, 1);
				}
			}
			if (p.removeDirection[left]) {
				for (int j = p.y + Y - 1; j > p.y + Y - p.removeDirection[left] - 1; j--) {
					remove(m, p.x + X, j, 1);
				}
			}
		} else if ((!p.removeDirection[right] && p.removeDirection[left]) ||(p.removeDirection[right] && !p.removeDirection[left]) && !p.removeDirection[up]&& !p.removeDirection[down]) {
			if (p.removeDirection[right]) {
				for (int j = p.y + Y; j < p.y + Y + p.removeDirection[right] + 1; j++) {
					remove(m, p.x + X, j, 1);
				}
			}
			if (p.removeDirection[left]) {
				for (int j = p.y + Y; j > p.y + Y - p.removeDirection[left] - 1; j--) {
					remove(m, p.x + X, j, 1);
				}
			}
		}
		if (p.removeDirection[down] && p.removeDirection[up]&& !p.removeDirection[right]&& !p.removeDirection[left]) {
			if (p.removeDirection[down]) {
				remove(m, p.x + X + p.removeDirection[down], p.y + Y, p.removeDirection[down] + 1 + p.removeDirection[up]);
			}
		} else if ((p.removeDirection[down] && !p.removeDirection[up]) || (!p.removeDirection[down] && p.removeDirection[up])&& !p.removeDirection[right]&& !p.removeDirection[left]) {
			if (p.removeDirection[down]) {
				remove(m, p.x + X + p.removeDirection[down], p.y + Y, p.removeDirection[down] + 1);
			}
			if (p.removeDirection[up]) {
				remove(m, p.x + X, p.y + Y, p.removeDirection[up] + 1);
			}
		}
		if((p.removeDirection[up] || p.removeDirection[down]) && (p.removeDirection[right] || p.removeDirection[left])) {
			if (p.removeDirection[right]) {
				for (int j = p.y + Y; j < p.y + Y + p.removeDirection[right]; j++) {
					remove(m, p.x + X, j, 1);
				}
			}
			if (p.removeDirection[left]) {
				for (int j = p.y + Y - 1 ; j > p.y + Y - p.removeDirection[left] - 1; j--) {
					remove(m, p.x + X, j, 1);
				}
			}
		}
		int scoreArr[3] = {1,4,10};
    int score = 0;
		for(int i = 3; i < 6; i++) {
			if (p.removeDirection[left] + p.removeDirection[right] + 1 == i) {
				score = scoreArr[i-3];
			}
			if (p.removeDirection[down] + p.removeDirection[up] + 1 == i) {
				score = scoreArr[i-3];
			}
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
	clock_t start,finish;
	start = clock();
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
    {1, 2, 3, 2},
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
  cout<<xxl.xiao(matrixPointer)<<endl;
  cout<<xxl.K<<endl;
	finish = clock();
	cout<<double(finish - start)<<"ms"<<endl;
  return 0;
}
