#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct AUTOMOBIL
{
    char marca[50];
    char carburant;
    char model[15];
    struct data
    {
        char luna[15];
        int an;
    } data;
} AUTOMOBIL;

void afisare_info_fisier(int *n);
void citire_din_fisier(int *n);
void append_bmw(AUTOMOBIL *v, int *n); //subpunctul b)
int find_car(int *n); //subpunctul c)
void lista_5ani(AUTOMOBIL *lista, int *cnt, int *n); // subpunctul d)
void ordonare_crescator(int *n); //subpunct e)
void decapotabile(int *n); //subpunct f)

//nu am mai facut switch pt main
int main()
{
    int n, i;
    AUTOMOBIL *v = NULL;
    FILE *f = fopen("p7_f.bin", "wb");
    if(f == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }

    printf("Introduceti numarul automobilelor din parcul auto : ");
    scanf("%d", &n);
    getchar();

    v = malloc(sizeof(AUTOMOBIL) * n);

    for(i = 0; i < n; i++)
    {
        printf("Marca %d : ", i + 1);
        fgets(v[i].marca, 50, stdin);
        v[i].marca[strcspn(v[i].marca, "\n")] = '\0';

        printf("Carburant %d : ", i + 1);
        scanf("%c", &v[i].carburant);
        getchar();
        
        printf("Modelul %d : ", i + 1);
        fgets(v[i].model, 15, stdin);
        v[i].model[strcspn(v[i].model, "\n")] = '\0';

        printf("Luna fabricatie %d : ", i + 1);
        fgets(v[i].data.luna, 15, stdin);
        v[i].data.luna[strcspn(v[i].data.luna, "\n")] = '\0';

        printf("An fabricatie %d : ", i + 1);
        scanf("%d", &v[i].data.an);
        getchar();
        printf("\n");
    }
    fwrite(v, sizeof(AUTOMOBIL), n, f);
    fclose(f);
    append_bmw(v, &n);
    ordonare_crescator(&n);
    citire_din_fisier(&n);
    printf("\n%d\n", find_car(&n)); // se afiseaza 1 daca s-a gasit, respectiv 0 in caz contrariu
    // afisare_info_fisier(&n);
    decapotabile(&n);
    return 0;
}

void afisare_info_fisier(int *n)
{
    FILE *f = fopen("p7_f.bin", "rb");
    if(f == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }
    AUTOMOBIL *y = NULL;
    y = malloc(sizeof(AUTOMOBIL) * (*n));
    int i;
    fread(y, sizeof(AUTOMOBIL), (*n), f);
    for(i = 0; i < (*n); i ++)
    {
        printf("%s, %c, %s, %s, %d\n", y[i].marca, y[i].carburant, y[i].model, y[i].data.luna, y[i].data.an);
    }
    fclose(f);
    free(y);
}

void append_bmw(AUTOMOBIL *v, int *n)
{
    int nr_adaugat;
    FILE *f = fopen("p7_f.bin", "ab");
    if(f == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }

    int i;
    printf("Introduceti numarul de automobile de adaugat in fisier : ");
    scanf("%d", &nr_adaugat);
    getchar();
    (*n) = (*n) + nr_adaugat;

    AUTOMOBIL curr;

    for(i = 0; i < nr_adaugat; i++)
    {
        printf("Marca %d : ", i + 1);
        fgets(curr.marca, 50, stdin);
        curr.marca[strcspn(curr.marca, "\n")] = '\0';

        printf("Carburant %d : ", i + 1);
        scanf("%c", &curr.carburant);
        getchar();
        
        printf("Modelul %d : ", i + 1);
        fgets(curr.model, 15, stdin);
        curr.model[strcspn(curr.model, "\n")] = '\0';

        printf("Luna fabricatie %d : ", i + 1);
        fgets(curr.data.luna, 15, stdin);
        curr.data.luna[strcspn(curr.data.luna, "\n")] = '\0';

        printf("An fabricatie %d : ", i + 1);
        scanf("%d", &curr.data.an);
        getchar();
        printf("\n");

        fwrite(&curr, sizeof(AUTOMOBIL), 1, f);
    }
    fclose(f);
}

void citire_din_fisier(int *n)
{
    FILE *f = fopen("p7_f.bin", "rb");
    if(f == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }
    AUTOMOBIL *y = malloc(sizeof(AUTOMOBIL) * (*n));
    fread(y, sizeof(AUTOMOBIL), (*n), f); // pentru a actualiza vectorul in cazul in care se adauga elemente
    fclose(f);
    free(y);
}

int find_car(int *n)
{
    FILE *f = fopen("p7_f.bin", "rb");
    if(f == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }

    char marca_car[50], carburant_functie;
    printf("Marca masinii de cautat : ");
    fgets(marca_car, 50, stdin);
    marca_car[strcspn(marca_car, "\n")] = '\0';


    printf("Carburantul masinii de cautat : ");
    scanf("%c", &carburant_functie);
    getchar();

    AUTOMOBIL *y = malloc(sizeof(AUTOMOBIL) * (*n));
    fread(y, sizeof(AUTOMOBIL), (*n), f);
    int i;
    for(i = 0; i < (*n); i ++)
    {
        if(strcmp(y[i].marca, marca_car) == 0 && y[i].carburant == carburant_functie)
            return 1;
    }
    fclose(f);
    free(y);
    return 0;
}

void lista_5ani(AUTOMOBIL *lista, int *cnt, int *n)
{
    FILE *f = fopen("p7_f.bin", "rb");
    if(f == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }
    AUTOMOBIL *y = malloc(sizeof(AUTOMOBIL) * (*n));
    fread(y, sizeof(AUTOMOBIL), (*n), f);
    int i;

    lista = NULL;
    (*cnt) = 0;
    for(i = 0; i < (*n); i ++)
    {
        if(y[i].data.an < 2021)
        {
            (*cnt)++;
            lista = realloc(lista, sizeof(AUTOMOBIL) * (*cnt));
            fread(&y[i], sizeof(AUTOMOBIL), 1, f);
        }
        else if(y[i].data.an == 2021)
        {
            if(strcmp(y[i].data.luna, "1") == 0)
            {
                (*cnt)++;
                lista = realloc(lista, sizeof(AUTOMOBIL) * (*cnt));
                fread(&y[i], sizeof(AUTOMOBIL), 1, f);
            }
        }
    }
    fclose(f);
    free(y);
}

void ordonare_crescator(int *n)
{
    FILE *f = fopen("p7_f.bin", "rb");
    FILE *rezultat = fopen("p7_fe).bin", "wb");
    if(f == NULL || rezultat == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }
    AUTOMOBIL *y = malloc(sizeof(AUTOMOBIL) * (*n));
    fread(y, sizeof(AUTOMOBIL), (*n), f);
    int i, j;
    for(i = 0; i < (*n) - 1; i++)
        for(j = i + 1; j < (*n); j++)
        {
            if(y[i].data.an > y[j].data.an)
            {
                AUTOMOBIL temp = y[i];
                y[i] = y[j];
                y[j] = temp;
            }
            else if(y[i].data.an == y[j].data.an)
            {
                int li = atoi(y[i].data.luna);
                int lj = atoi(y[j].data.luna);
                if (li > lj) 
                {
                    AUTOMOBIL temp = y[i];
                    y[i] = y[j];
                    y[j] = temp;
                }
            }
        }
    fwrite(y, sizeof(AUTOMOBIL), (*n), rezultat);
    for(i = 0; i < (*n); i ++)
    {
        printf("%s, %c, %s, %s, %d\n", y[i].marca, y[i].carburant, y[i].model, y[i].data.luna, y[i].data.an);
    }
    fclose(f);
    fclose(rezultat);
    free(y);
}

void decapotabile(int *n)
{
    FILE *f = fopen("p7_f.bin", "rb");
    if(f == NULL)
    {
        perror("Eroare la deschidere");
        exit(1);
    }
    AUTOMOBIL *y = malloc(sizeof(AUTOMOBIL) * (*n));
    fread(y, sizeof(AUTOMOBIL), (*n), f);

    printf("cititi un an de la tastatura : ");
    int an;
    scanf("%d", &an);
    getchar();
    int i;
    for(i = 0; i < (*n); i ++)
    {
        if(y[i].data.an == an)
        {
            if(strcmp(y[i].model, "decapotabila") == 0)
                printf("%s, %c, %s, %s, %d\n", y[i].marca, y[i].carburant, y[i].model, 
            y[i].data.luna, y[i].data.an);
        }
    }
    fclose(f);
    free(y);
}