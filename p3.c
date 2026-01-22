#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *f = fopen("p3_f.txt", "wt");
    FILE *f_binary = fopen("p3_f.bin", "wb");
    if(f == NULL || f_binary == NULL)
    {
        perror("Eroare la deschidere!\n");
        exit(1);
    }

    int n, i, *v = NULL, *y = NULL;
    printf("introduceti numarul de elemente ale vectorului : ");
    scanf("%d", &n);
    v = malloc(sizeof(int) * n);

    printf("introduceti elementele vectorului : \n");
    scanf("%d", &v[0]);
    fprintf(f, "%d", v[0]);
    for(i = 1; i < n; i++)
    {
        scanf("%d", &v[i]);
        fprintf(f, " %d", v[i]); //scriere in .txt
    }
    fwrite(v, sizeof(int), n, f_binary); //scriere in .bin

    fclose(f);
    fclose(f_binary);

    f = fopen("p3_f.txt", "rt");
    f_binary = fopen("p3_f.bin", "rb");
    if(f == NULL || f_binary == NULL)
    {
        perror("Eroare la deschidere");
        exit(2);
    }

    //afisare din fisierul binary
    printf("elementele vectorului sunt (.bin) : \n");
    y = malloc(sizeof(int) * n);
    fread(y, sizeof(int), n, f_binary);
    for(i = 0; i < n; i++)
    {
        printf("%d ", y[i]);
    }
    printf("\n");


    //afisarea din fisierul text
    printf("elementele vectorului sunt (.txt) : \n");
    i = 0;
    while(fscanf(f, "%d", &y[i]) == 1 && i < n)
    {
        printf("%d ", y[i]);
        i++;
    }
    printf("\n");

    free(v);
    free(y);
    fclose(f);
    fclose(f_binary);
    return 0;
}