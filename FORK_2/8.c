#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
#include<string.h>



void fill_array(int n,int a[][n],int ch)
{
    
    for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
                {
                    a[i][j]=(ch==0)?(0):((n*i)+j+1);
                }
        }
   
}

void corner_change(int n,int s1,int s2,int c1,int c2,int a[][n])
{
     
    for(int i=s1;i<c1;i++)
        for(int j=s2;j<c2;j++)
            a[i][j]=(n*n+1)-a[i][j];
    
   
}

void doubly_even_order(int n,int a[][n])
{
    fill_array(n,a,1);

    int status;

    pid_t pid[4];
    pid[0]=vfork();

    if(pid[0]!=0)
{
    corner_change(n,0,0,n/4,n/4,a);
}
    else 
{
    pid[1]=vfork();
    if(pid[1]==0)
    {
        corner_change(n,0,3*(n/4),n/4,n,a);
        _exit(0);
    }
    else
    {
        pid[2]=vfork();
        if(pid[2]==0)
        {
            corner_change(n,3*(n/4),0,n,n/4,a);
            _exit(0);
        }
        else
        {
            pid[3]=vfork();
            if(pid[3]==0)
            {
                corner_change(n,3*(n/4),3*(n/4),n,n,a);
                _exit(0);
            }
            else
            {
                corner_change(n,(n/4),(n/4),3*(n/4),3*(n/4),a);
                _exit(0);
            }
            
        }
        
    }
    

    
    _exit(0);
}
    waitpid(-1,&status,0);
}

void display(int n,int a[][n])
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ",a[i][j]);
        }

    printf("\n");
    }
    
}

void odd_order(int n,int a[][n])
{
    fill_array(n,a,0);
    
    int i=n/2;
    int j=n-1;
    int status;

    pid_t pid[(n*n)];
    for(int num=1;num<=n*n;)
    {
        pid[num]=vfork();

        if(pid[num]==0)
        {
            if(i==-1 && j==n)
        {
            j=n-2;
            i=0;
        }
        else
        {
            if(j==n)
                j=0;

            if(i<0)
                i=n-1;
        }
        _exit(0);
        }
        else
        {
            if(a[i][j])
        {
            j-=2;
            i++;
            continue;
        }
        else
        {
                a[i][j]=num++;
        }
        
        }

        j++;
        i--;
    }

   waitpid(-1,&status,0);
}

void even_order(int n,int a[][n]) 
{

        int size = n * n;
        int halfN = n / 2;
        int subGridSize = size / 4, i;

        int subGrid[halfN][halfN];
 
        odd_order(halfN,subGrid);
        int gridFactors[] = {0, 2, 3, 1};
       
        pid_t pid;
        int status=0;
        pid=vfork();
        if(pid==0)
        {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                int grid = (r / halfN) * 2 + (c / halfN);
                a[r][c] = subGrid[r % halfN][c % halfN];
                a[r][c] += gridFactors[grid] * subGridSize;
            }
        }
        _exit(0);
        }
        else
        {
            int nColsLeft = halfN / 2;
            int nColsRight = nColsLeft - 1;
 
        for (int r = 0; r < halfN; r++)
            for (int c = 0; c < n; c++) {
                if (c < nColsLeft || c >= n - nColsRight
                        || (c == nColsLeft && r == nColsLeft)) {
 
                    if (c == 0 && r == nColsLeft)
                        continue;
 
                    int tmp = a[r][c];
                    a[r][c] = a[r + halfN][c];
                    a[r + halfN][c] = tmp;
                }
            }
        }
        
        
    
        waitpid(-1,&status,0);
    }

void order(int n)
{
    int a[n][n];
    if(n%2==1)
        {odd_order(n,a);
        }
    else if(n%4==0)
       { doubly_even_order(n,a);}
    else if(n%4==2)
       { even_order(n,a);
       }
    printf("\nMagic Square Generated:\n");
    display(n,a);
}

int input()
{
    int n;
    printf("Enter n value of the square matrix to be genearated:\n");
    scanf("%d",&n);
    return n;
}


int main()
{   int n= input();
    order(n);
}