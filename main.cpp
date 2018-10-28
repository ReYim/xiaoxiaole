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

    int *check(int i, int j, int ijValue, int dir) {
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

    void xiao(int m[][4]) {
        vector<Point> points;
        int matrix[8][4];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j] = m[i][j];
            }
        }

        for (int i = 0; i < M-1; i++) {
            for (int j = 0; j < N-1; j++) {
                if (matrix[i][j] > 0) {
                    //right swap
                    int r = matrix[i][j];
                    int l = matrix[i][j+1];
                    int u = matrix[i+1][j];
                    int d = matrix[i][j];

                    int *rightSwapResult =  check(i, j+1, r, right);
                    int *leftSwapResult =   check(i, j, l, left);
                    int *downSwapResult =   check(i + 1, j, d, down);
                    int *upSwapResult =     check(i, j, u, up);
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
                        points.push_back(Point(i - 1, j, up, upSwapResult));
                    }
                }

            }
        }
        cout<<"points size:" << points.size()<< endl;
        for (int i = 0; i < points.size(); i++) {
            Point p = points.at(i);
            getScore(swap(p.x, p.y, p.direction, matrix), &p);
						cout<<"score:"<<p.score<<endl;
            //xiao(matrix);
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
        if (p.removeDirection[right] == right) {
            for (int j = p.y + Y; j< 4; j++) {
                if(m[p.x + X][j] == removeValue)
                    score ++;
								else break;
            }
            for (int j = p.y + Y - 1; j > - 1; j--) {
                if(m[p.x + X][j] == removeValue)
                    score ++;
								else break;
            }
        }
        if (p.removeDirection[left] == left) {
            for (int j = p.y + Y; j > -1; j--) {
                if(m[p.x + X][j] == removeValue)
                    score ++;
								else break;
            }
            for (int j = p.y + Y + 1; j < 4; j++) {
                if(m[p.x + X][j] == removeValue)
                    score ++;
								else break;
            }
        }
        if (p.removeDirection[down] == down) {
            for (int j = p.x; j < 8; j++) {
                if(m[j][p.y + Y] == removeValue)
                    score ++;
								else break;
            }
            for (int j = p.x -1; j > -1; j--) {
                if(m[j][p.y + Y] == removeValue)
                    score ++;
								else break;
            }
        }
        if (p.removeDirection[up] == up) {
            for (int j = p.x + X; j > -1; j--) {
                if(m[j][p.y + Y] == removeValue)
                    score ++;
								else break;
            }
            for (int j = p.x + X + 1; j < 8 + X; j++) {
                if(m[j][p.y + Y] == removeValue)
                    score ++;
								else break;
            }
        }
				point->score = score;
    }
    int **swap(int x, int y, int dir, int m[][4]) {
        matrix = new int *[M];
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
            matrix[x][y] = matrix[x][y-1];
            matrix[x][y-1] = tmp;
            return matrix;
				}
				
				
				{
            cout<<"direction is not exit : "<< dir << endl;
            return matrix;
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
    xxl.xiao(matrix);
    cout << xxl;
    return 0;
}
