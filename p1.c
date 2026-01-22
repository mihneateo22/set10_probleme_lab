#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//a) && c)


int main()
{
    FILE *f_input;
    char s[256], sep[] = " ", *p, cs[256];
    int flag, c, i, first = 0;
    f_input = fopen("p1_f.txt", "wt");
    if(f_input == NULL)
    {
        perror("Nu s-a putut deschide fisierul!\n");
        exit(1);
    }
    printf("Un sir de caractere : ");
    fgets(s, 256, stdin);
    s[strcspn(s, "\n")] = '\0';

    printf("Introdu cifra 1, 2, 3, 4 sau 5. # (1 este pentru scriere directa, 2 pentru scriere caracter cu caracter, 3 pentru cuvant cu cuvant pe o singura linie, 4 pentru cuvant cu cuvant pe linii diferite, cate un cuvant pe fiecare linie, iar 5 pentru subpunctul c)) : ");
    scanf("%d", &flag);
    getchar();
    switch(flag)
    {
        case 1 :
            printf("\nAceasta este scrierea dintr-o bucata!\n\n");
            fputs(s, f_input);
            fclose(f_input);
            break;
        case 2 :
            printf("\nAceasta este scrierea caracter cu caracter!\n\n");
            i = 0;
            while(s[i] != '\0')
            {
                fputc(s[i], f_input);
                i++;
            }
            fclose(f_input);
            break;
        case 3 :
            printf("\nAceasta este scrierea cuvant cuvant, pe o singura linie!\n\n");
            strcpy(cs, s);
            p = strtok(cs, sep);
            fputs(p, f_input);
            p = strtok(NULL, sep);
            while(p != NULL)
            {
                fputs(" ", f_input);
                fputs(p, f_input);
                p = strtok(NULL, sep);
            }
            fclose(f_input);
            break;
        case 4 :
            printf("\nAceasta este scrierea cuvant cu cuvant, cate un cuvant pe linie\n\n");
            strcpy(cs, s);
            p = strtok(cs, sep);
            fputs(p, f_input);
            p = strtok(NULL, sep);
            while(p != NULL)
            {
                fputs("\n", f_input);
                fputs(p, f_input);
                p = strtok(NULL, sep);
            }
            fclose(f_input);
            break;
        case 5 : // subpunctul c)

            printf("Aceasta este rezolvarea subpunctului c)\n\n");
            char cuvant1[256], cuvant2[256], curr_word[256];
            unsigned int cnt = 0;
            printf("Cuvantul 1 : ");
            fgets(cuvant1, 256, stdin);
            cuvant1[strcspn(cuvant1, "\n")] = '\0';
            printf("Cuvantul 2 : ");
            fgets(cuvant2, 256, stdin);
            cuvant2[strcspn(cuvant2, "\n")] = '\0';

            fputs(s, f_input);
            fclose(f_input);

            FILE *fisier = fopen("temp.txt", "wt");
            f_input = fopen("p1_f.txt", "rt");
            if(fisier == NULL || f_input == NULL)
            {
                printf("Eroare la deschidere\n");
                exit(2);
            }

            while(fscanf(f_input, "%255s", curr_word) == 1)
            {
                if(strcmp(curr_word, cuvant1) == 0)
                {
                    cnt = 1;
                    fputs(cuvant2, fisier);
                    fputs(" ", fisier);
                }
                else
                {
                    fputs(curr_word, fisier);
                    fputs(" ", fisier);
                }
            }

            fclose(f_input);
            fclose(fisier);

            if(cnt == 0)
            {
                printf("Cuvantul 1 nu a putut fi gasit in fisier!\n");
                remove("temp.txt");
            }
            else
            {
                remove("p1_f.txt");
                rename("temp.txt", "p1_f.txt");
            }
            break;
        default :
            printf("Nu ati tastat o varianta valida!");
            fclose(f_input);
            break;
    }
    return 0;
}



//b)

/*
int main()
{
    FILE *f_output;
    f_output = fopen("p1_f.txt", "rt");
    char c, cuvant[256], sir[500];
    int flag;
    if(f_output == NULL)
    {
        printf("Fisierul nu a putut fi deschis.");
        exit(2);
    }

    printf("Introduceti cifra 1, 2 sau 3. # (1 este pentru afisare caracter cu caracter, 2 pentru afisare cuvant cu cuvant, iar 3 pentru afisarea intregii linii) : ");
    scanf("%d", &flag);

    switch(flag)
    {
        case 1 :
            printf("\nAceasta este varianta caracter cu caracter : \n");
            while((c = getc(f_output)) != EOF)
                putchar(c);
            printf("\n");
            break;
        case 2 :
            printf("\nAceasta este varianta cuvant cu cuvant : \n");
            while(fscanf(f_output, "%255s", cuvant) == 1)
            {
                printf("%s ", cuvant);
            }
            printf("\n");
            break;
        case 3 :
            printf("\nAceasta este varianta intreaga linie : \n");
            fgets(sir, 500, f_output);
            printf("%s\n", sir);
            break;
        default :
            printf("Nu ati tastat o varianta valida!\n");
            break;
    }
    fclose(f_output);
    return 0; 
}
*/