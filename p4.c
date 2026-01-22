#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *ft = fopen("p4_f.txt", "wt");
    FILE *fb = fopen("p4_f.bin", "wb");
    if(ft == NULL || fb == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }

    int *a, *b, n, m, i, j;
    printf("introduceti numarul de linii al matricei : ");
    scanf("%d", &n);
    fprintf(ft, "%d ", n);
    fwrite(&n, sizeof(int), 1, fb);

    printf("introduceti numarul de coloane al matricei : ");
    scanf("%d", &m);
    fprintf(ft, "%d\n", m);
    fwrite(&m, sizeof(int), 1, fb);

    a = malloc(sizeof(int) * n * m);
    for(i = 0; i < n; i ++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &a[i*m + j]);
            fprintf(ft, "%d ", a[i*m + j]);
        }
        fprintf(ft, "\n");
    }
    fwrite(a, sizeof(int), n * m, fb);

    fclose(ft);
    fclose(fb);


    ft = fopen("p4_f.txt", "rt");
    fb = fopen("p4_f.bin", "rb");

    int n2, m2;
    fscanf(ft, "%d", &n2);
    fscanf(ft, "%d", &m2);
    for(i = 0; i < n2; i++)
    {
        for(j = 0; j < m2; j++)
        {
            fscanf(ft, "%d", &a[i*m2 + j]);
            printf("%d ", a[i*m2 + j]);
        }
        printf("\n");
    }
    printf("\n");

    fread(&n, sizeof(int), 1, fb);
    fread(&m, sizeof(int), 1, fb);
    b = malloc(sizeof(int) * n * m);
    fread(b, sizeof(int), n * m, fb);
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d ", b[i*m + j]);
        }
        printf("\n");
    }

    fclose(ft);
    fclose(fb);
    free(a);
    return 0;
}