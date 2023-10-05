#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbolbinarios.h"

void inserta(arbol **A, char x[])
{
    if (*A == NULL)
    {
        *A = (arbol *)malloc(sizeof(arbol));
        (*A)->dato = (char *)malloc((strlen(x) + 1) * sizeof(char));
        strcpy((*A)->dato, x);
        (*A)->h_izq = NULL;
        (*A)->h_der = NULL;
    }
    else
    {
        if (strlen(x) + 1 < strlen((*A)->dato) + 1)
            inserta(&(*A)->h_izq, x);
        else if (strlen(x) + 1 > strlen((*A)->dato) + 1)
            inserta(&(*A)->h_der, x);
    }
}

int es_miembro(arbol *A, char x[])
{
    int i, cont = 0;

    if (A == NULL)
    {
        return -1;
    }
    else
    {
        if (strlen(x) + 1 == strlen(A->dato) + 1)
        {
            for (i = 0; i < strlen(A->dato) + 1; i++)
            {
                if (x[i] == A->dato[i])
                {
                    cont++;
                }
            }
            if (cont == strlen(A->dato) + 1)
            {
                return 1;
            }
            else
            {
                return -1;
            }
        }
        else if (strlen(x) + 1 < strlen(A->dato) + 1)
        {
            return es_miembro(A->h_izq, x);
        }
        else
        {
            return es_miembro(A->h_der, x);
        }
    }
}

void cambio(char auxx[50])
{
    int i, temp = 0;
    for (i = 0; i < 100 && temp == 0; i++)
    {
        if (auxx[i] == '\n')
        {
            auxx[i] = '\0';
            temp = 1;
        }
    }
}

char suprime_min(arbol **A)
{
    char aux[strlen((*A)->dato)];
    if ((*A)->h_izq == NULL)
    {
        strcpy(aux, (*A)->dato);
        arbol *tmp = *A;
        *A = (*A)->h_der;
        free(tmp);
        return aux[strlen((*A)->dato)];
    }
    else
    {
        return suprime_min(&((*A)->h_izq));
    }
}

void suprime(arbol **A, char x[])
{
    char aux[50];
    if (*A != NULL)
    {
        if (strlen(x) + 1 < strlen((*A)->dato) + 1)
            suprime(&((*A)->h_izq), x);
        else if (strlen(x) + 1 > strlen((*A)->dato) + 1)
            suprime(&((*A)->h_der), x);
        // Lo  encontre
        else if ((*A)->h_izq == NULL && (*A)->h_der == NULL)
        {
            arbol *tmp = *A;
            *A = NULL;
            free(tmp);
        }
        else if ((*A)->h_izq == NULL)
        {
            arbol *tmp = *A;
            *A = (*A)->h_der;
            free(tmp);
        }
        else if ((*A)->h_der == NULL)
        {
            arbol *tmp = *A;
            *A = (*A)->h_izq;
            free(tmp);
        }
        else
        { // ambos  hijos  estan  presentes
            aux[50] = suprime_min(&(*A)->h_der);
            strcpy((*A)->dato, aux);
        }
    }
}

void listar(arbol *A)
{
    if (A != NULL)
    {
        printf(" %s \n", A->dato);
        listar(A->h_der);
        listar(A->h_izq);
    }
}
int main()
{
    arbol *raiz;
    raiz = NULL;
    char aux[50], aux2[50], aux3[50];
    int res, opcion;
    do
    {
        printf("Menu\n");
        printf("1- Agregar una cadena al arbol \n");
        printf("2- Buscar si existe \n");
        printf("3- Eliminar un elemento\n");
        printf("4- Mostrar cadenas ingresadas en el arbol\n");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1:
            printf("Ingrese una cadena\n ");
            fflush(stdin);
            fgets(aux, 50, stdin);
            cambio(aux);
            inserta(&raiz, aux);
            break;
        case 2:
            printf("Ingrese cadena a buscar\n ");
            fflush(stdin);
            fgets(aux2, 50, stdin);
            cambio(aux2);
            res = es_miembro(raiz, aux2);
            if (res == 1)
            {
                printf("El  elemento  buscado  existe  en el arbol\n");
            }
            else
            {
                printf("No  existe \n");
            }
            break;
        case 3:
            printf("Ingrese cadena a eliminar\n");
            fflush(stdin);
            fgets(aux3, 50, stdin);
            cambio(aux3);
            suprime(&raiz, aux3);
            break;
        case 4:
            printf("Lista de cadenas ingresadas:\n");
            listar(raiz);
            break;
        }
    } while (opcion != 0);
    return 0;
}
