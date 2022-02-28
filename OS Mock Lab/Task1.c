#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int **arr1;
int **arr2;
int **arr3;
int x = 0;
int m=0 , n=0;
void *Sum(void *l);

int main(int argc, char *argv[])
{
     m = atoi(argv[1]);
     n = atoi(argv[2]);
     
    arr1 = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        arr1[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr1[i][j] = rand() % 50;
        }
    }

    arr3 = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        arr3[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr3[i][j] = 0;
        }
    }

    arr2 = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
    {
        arr2[i] = (int *)malloc(n * sizeof(int));
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr2[i][j] = rand() % 50;
        }
    }

    pthread_t *t = (pthread_t *)malloc(m * sizeof(pthread_t));
    for (int i = 0; i < m; i++)
    {
        pthread_create(&t[i], NULL, Sum, NULL);
    }
    for (int i = 0; i < m; i++)
    {
        pthread_join(t[i], NULL);
    }

    printf("\nArr1\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\nArr2\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr2[i][j]);
        }
           printf("\n");
    }

    printf("\n");
    printf("\nArr3\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", arr3[i][j]);
        }
        printf("\n");
    }
    pthread_exit(NULL);
}

void *Sum(void *l)
{
    int a = x++;
   // printf("%d\n", a);
   // printf("n: %d\n",n);
    for (int i = 0; i < n; i++)
    {
     //   printf("%d\n", a);
        arr3[a][i] = arr1[a][i] + arr2[a][i];/* code */
    }
    pthread_exit(NULL);
}