#define  long_max  25;

typedef  struct  nodo{
    char *dato;
    struct  nodo *h_izq , *h_der;
}arbol;
void  inserta(arbol ** , char[]);
int  es_miembro (arbol*, char[]);
int  suprime_minimo (arbol **);
void  suprime (arbol**, char[]);
void  listar (arbol *);
void cambio(char auxx[50]);
