#include <iostream>
#include <pthread.h>
using namespace std;
int N;

struct node
{
	int **A;
	int **temp;
	int **adj;
	float **inv;
	int i;
	int j;
	int n;
};

void *getCofactor(void *arg)
{
	struct node *th = (struct node *)arg;
	int i = 0, j = 0;

	
	for (int row = 0; row < th->n; row++)
	{
		for (int col = 0; col < th->n; col++)
		{
			
			if (row != th->i && col != th->j)
			{
				th->temp[i][j++] = th->A[row][col];

				
				if (j == th->n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
	pthread_exit(NULL);
}

int determinant(int **A, int n)
{
	int D = 0;

	if (n == 1)
		return A[0][0];

	int **temp = new int *[N];
	for (int i = 0; i < N; i++)
		temp[i] = new int[N]; 

	int sign = 1; 

	struct node *th = (struct node *)malloc(n * sizeof(struct node));
	pthread_t *pth = (pthread_t *)malloc(n * sizeof(pthread_t));

	for (int f = 0; f < n; f++)
	{
		
		th[f].A = A;
		th[f].temp = temp;
		th[f].i = 0;
		th[f].j = f;
		th[f].n = n;
		pthread_create(&pth[f], NULL, getCofactor, &th[f]);
		pthread_join(pth[f], NULL);

		D += sign * A[0][f] * determinant(th[f].temp, n - 1);
		sign = -sign;
	}

	return D;
}

void adjoint(int **A, int **adj)
{
	if (N == 1)
	{
		adj[0][0] = 1;
		return;
	}

	
	int sign = 1;
	int **temp = new int *[N];
	for (int i = 0; i < N; i++)
		temp[i] = new int[N];

	struct node *th = (struct node *)malloc(N * N * sizeof(struct node));
	pthread_t *pth = (pthread_t *)malloc(N * N * sizeof(pthread_t));
	int st_index = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// Get cofactor of A[i][j]
			th[st_index].A = A;
			th[st_index].temp = temp;
			th[st_index].i = i;
			th[st_index].j = j;
			th[st_index++].n = N;
			pthread_create(&pth[st_index - 1], NULL, getCofactor, &th[st_index - 1]);
			if (N == 2)
				pthread_join(pth[st_index - 1], NULL);
			// sign of adj[j][i] positive if sum of row
			// and column indexes is even.
			sign = ((i + j) % 2 == 0) ? 1 : -1;

			// Transpose
			adj[j][i] = (sign) * (determinant(th[st_index - 1].temp, N - 1));
		}
	}
	if (N > 2)
	{
		for (int i = 0; i < st_index; i++)
			pthread_join(pth[i], NULL);
	}
}

template <class T>
void display(T **A)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
}

bool inverse(int **A, float **inverse)
{
	int det = determinant(A, N);
	if (det == 0)
	{
		cout << "Singular matrix, can't find its inverse\n";
		return false;
	}

	int **adj = new int *[N];
	for (int i = 0; i < N; i++)
		adj[i] = new int[N];
	
	adjoint(A, adj);
	cout << "\nThe Adjoint is :\n\n";
	display(adj);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			inverse[i][j] = adj[i][j] / float(det);

	return true;
}



int main()
{

	cout<<"Enter the Order of the matrix:"<<endl;
	cin>>N;
	int **A = new int *[N];
	for (int i = 0; i < N; i++)
		A[i] = new int[N];

	int **adj = new int *[N];
	for (int i = 0; i < N; i++)
		adj[i] = new int[N];

	float **inv = new float *[N];
	for (int i = 0; i < N; i++)
		inv[i] = new float[N];

	cout << "Enter the matrix of order " << N << ": " << endl;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> A[i][j];
	

	cout << "\nInput matrix is :\n";
	display(A);
		
	if (inverse(A, inv))
		{
			cout << "\nThe Inverse is :\n\n";
			display(inv);
		}
	printf("\n");
	return 0;
}