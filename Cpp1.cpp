#include <iostream>
#include<time.h>
#include <vector>

using namespace std;

class Point
{
public:
	int x, y;  //��¼�ɽ����ĵ�����꣬˵���˾��Ƕ�ά������±�
	int direction;  //��������ֻ���º��ң���Ϊ�����Ͻǿ�ʼ��
	Point(int x0 = 0, int y0 = 0, int dir = 0){
		x = x0;
		y = y0;
		direction = dir;
	}
};

class XXL
{
public:
	XXL(int m0=8, int n0=4, int k0=4) 
	{  //���캯��
		M = m0;
		N = n0;
		K = k0;
		score = 0;
		matrix = new int *[M];
		for (int i = 0; i < M; i++)
		{
			matrix[i] = new int[N];
		}
	}
	void copy_matrix(int a[][4]) {     //��ֵ����
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = a[i][j];
			}
		}
	}
	// �����<<���أ���Ϊfriend�ſ��Է���XXL�����˽������
	friend ostream & operator<<(ostream &out, const XXL& xxl) 
	{
		for (int i = 0; i < xxl.M; i++)
		{
			for (int j = 0; j < xxl.N; j++)
			{
				out << xxl.matrix[i][j] << ' ';
			}
			out << endl;
		}
		return out;
	}
	
	bool find_commutative_point(int i, int j, int dir, int matrix[][4]) 
	{  //�жϸõ㽻�������޽��
		if (dir == 1) {  //���ҽ���
			if (j+1 <N && matrix[i][j+1] > 0) //����ɽ���
			{
				if (j + 3 < N) { //�ұ����ٵ���������ͬ��
					if (matrix[i][j] == matrix[i][j+2] && matrix[i][j] == matrix[i][j+3])
					{
						return true;  //�������������ϣ��ɽ���
					}
				}
				if (i + 2 < M)
				{
					if (matrix[i][j] == matrix[i + 1][j + 1] && matrix[i][j] == matrix[i + 2][j + 1])
					{
						return true; //�������������ϣ��ɽ���
					}
				}
			}
		}
		else  //���½���
		{
			if (i + 1 < M && matrix[i + 1][j] > 0) { //����ɽ���
				if (i + 3 < M) { //�±����ٵ���������ͬ��
					if (matrix[i][j] == matrix[i + 2][j] && matrix[i][j] == matrix[i + 3][j]) 
					{
						return true;  //����������������
					}
				}
				if (j + 2 < N) {
					if(matrix[i][j]==matrix[i+1][j+1] && matrix[i][j]==matrix[i+1][j+2])
					{
						return true;
					}
					
				}
			}
		}
		return false;
	}
	
	void xiao(int m[][4]) 
	{
		vector<Point> points;  //��¼��ǰ�ɽ����ĵ�
		int matrix[8][4];      //������һ��ʱ��¼��ǰ״̬
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++)
			{
				matrix[i][j] = m[i][j];
			}
		}
		
		for (i = 0; i < M; i++) //�����пɽ������ҳ�����Ȼ������������
		{
			for (int j = 0; j < N; j++)
			{
				if (matrix[i][j] > 0) { //�����ҽ������½������ж��Ƿ���Խ���������
					if (find_commutative_point(i, j, 1, matrix)) {
						points.push_back(Point(i,j,1));
					}
					if (find_commutative_point(i,j,2, matrix))
					{
						points.push_back(Point(i, j, 2));
					}
				}
				
			}
		}
		for ( i = 0; i < points.size(); i++) 
		{
			//TODO ���н��������,����setΪ-1
			//swap(points.x, points.y, points.dir)
			//tianchong()
			xiao(matrix);
			//score++;	
		}
	}
	/*	void display()
	{
	cout<<score;
	}*/
	
	~XXL() { //���ٶ�̬����
		for (int i = 0; i < M; i++)
		{
			delete []matrix[i];
		}
		delete []matrix;
		score++;
	}
	
private:
	int M;        //��
	int N;        //��
	int K;        //����
	int **matrix; //�����־���
	int score; //��ǰ�÷�
};

int main() {
	int m = 8;
	int n = 4;
	int k = 4;
//	int s; 
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
//	xxl.xiao(xxl.matrix)
//	cout<<s;
	getchar();
	return 0;

}