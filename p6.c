#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct persoana
{
    char nume[50];
    char prenume[50];
    float varsta;
} persoana;

void afisare_fisiere(int *cnt_pers);
void scriere_fisiere(int *cnt_pers, persoana *y);

int main()
{
    int cnt_pers; //numarul de persoane din fisiere
    cnt_pers = 5;

    FILE *ft = fopen("p6_f.txt", "wt");
    FILE *fb = fopen("p6_f.bin", "wb");
    if(ft == NULL || fb == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }

    persoana *v = malloc(sizeof(persoana) * (cnt_pers));
    int i;

    for(i = 0; i < 5; i ++)
    {
        printf("Nume : ");
        fgets(v[i].nume, 50, stdin);
        v[i].nume[strcspn(v[i].nume, "\n")] = '\0';
        fputs(v[i].nume, ft);
        fputs(" ", ft);

        printf("Prenume : ");
        fgets(v[i].prenume, 50, stdin);
        v[i].prenume[strcspn(v[i].prenume, "\n")] = '\0';
        fputs(v[i].prenume, ft);
        fputs(" ", ft);

        printf("Varsta : ");
        scanf("%f", &v[i].varsta);
        getchar();
        fprintf(ft, "%.0f\n", v[i].varsta);

        printf("\n");
    }

    fwrite(v, sizeof(persoana), (cnt_pers), fb);

    fclose(ft);
    fclose(fb);


    ft = fopen("p6_f.txt", "rt");
    fb = fopen("p6_f.bin", "rb");
    if(ft == NULL || fb == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }

    persoana *y = malloc(sizeof(persoana) * (cnt_pers));
    char linie[150];

    fread(y, sizeof(persoana), cnt_pers, fb);
    //afisare_fisiere(&cnt_pers);

    //subpunctul c)

    persoana N;
    unsigned int flag = 0;

    printf("Citeste o persoana pentru a o verifica (c)\n");
    printf("Nume : ");
    fgets(N.nume, 50, stdin);
    N.nume[strcspn(N.nume, "\n")] = '\0';
    printf("Prenume : ");
    fgets(N.prenume, 50, stdin);
    N.prenume[strcspn(N.prenume, "\n")] = '\0';
    printf("Varsta : ");
    scanf("%f", &N.varsta);

    for(i = 0; i < cnt_pers && flag == 0; i ++)
    {
        if(strcmp(N.nume, y[i].nume) == 0)
        {
            if(strcmp(N.prenume, y[i].prenume) == 0)
                if(N.varsta == y[i].varsta)
                {
                    printf("\nPersoana verificata se afla deja in fisier\n");
                    flag = 1;
                }
        }
    }

    if(flag == 1)
    {
        fclose(ft);
        fclose(fb);
        afisare_fisiere(&cnt_pers);
    }

    if(flag == 0)
    {
        fclose(fb);
        fclose(ft);

        cnt_pers++;

        fb = fopen("p6_f.bin", "ab");
        ft = fopen("p6_f.txt", "at");
        if(ft == NULL || fb == NULL)
        {
            perror("Eroare la deschidere");
            exit(1);
        }
        fwrite(&N, sizeof(N), 1, fb);
        fprintf(ft, "%s %s %.0f\n", N.nume, N.prenume, N.varsta);
        fclose(fb);
        fclose(ft);
        afisare_fisiere(&cnt_pers);
    }


    // subpunctul d)

    fb = fopen("p6_f.bin", "rb");
    if(fb == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }
    fread(y, sizeof(persoana), cnt_pers, fb);
    float medie = 0.0;

    for(i = 0; i < cnt_pers; i++)
    {
        medie += y[i].varsta;
    }

    medie = medie / cnt_pers;
    fclose(fb);
    printf("Media de varsta este : %.2f\n", medie);

    // subpunctul e)

    int j;
    for(i = 0; i < cnt_pers - 1; i ++)
    {
        for(j = i + 1; j < cnt_pers; j ++)
        {
            if(y[i].varsta > y[j].varsta)
            {
                persoana temp = y[i];
                y[i] = y[j];
                y[j] = temp;
            }
        }
    }
    scriere_fisiere(&cnt_pers, y);
    afisare_fisiere(&cnt_pers);

    // subpunctul f)

    char nume_tastatura[50];

    getchar();

    printf("Introduceti un NUME pentru a cauta (f) : ");
    fgets(nume_tastatura, 50, stdin);
    nume_tastatura[strcspn(nume_tastatura, "\n")] = '\0';

    for(i = cnt_pers - 1; i >= 0; i--)
    {
        if(strcmp(y[i].nume, nume_tastatura) == 0)
        {
            for(j = i; j < cnt_pers - 1; j ++)
                y[j] = y[j+1];
            cnt_pers--;
        }
    }

    scriere_fisiere(&cnt_pers, y);
    afisare_fisiere(&cnt_pers);



    free(v);
    free(y);
    return 0;
}

void afisare_fisiere(int *cnt_pers)
{
    FILE *ft = fopen("p6_f.txt", "rt");
    FILE *fb = fopen("p6_f.bin", "rb");
    if(ft == NULL || fb == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }
    persoana *y = malloc(sizeof(persoana) * (*cnt_pers));
    char linie[150];

    fread(y, sizeof(persoana), (*cnt_pers), fb);

    //afisare fisier text
    while(fgets(linie, 150, ft) != NULL)
    {
        fputs(linie, stdout);
    }

    //afisare fisier binar
    for(unsigned int i = 0; i < (*cnt_pers); i++)
    {
        printf("%s %s %.0f\n", y[i].nume, y[i].prenume, y[i].varsta);
    }
    free(y);
    fclose(ft);
    fclose(fb);
}

void scriere_fisiere(int *cnt_pers, persoana *y)
{
    FILE *ft = fopen("p6_f.txt", "wt");
    FILE *fb = fopen("p6_f.bin", "wb");
    if(!ft || !fb) 
    {
        perror("Eroare la deschidere"); 
        exit(1); 
    }

    for (int i = 0; i < *cnt_pers; i++) 
        fprintf(ft, "%s %s %.0f\n", y[i].nume, y[i].prenume, y[i].varsta);

    fwrite(y, sizeof(persoana), *cnt_pers, fb);

    fclose(ft);
    fclose(fb);
}
