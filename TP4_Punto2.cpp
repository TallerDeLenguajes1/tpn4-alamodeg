#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int TareaID;//Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion;// entre 10 – 100
}T_tarea;
    
int aleatorio(int min,int max);
void cargarTareas(T_tarea **tareas,int cant_tareas);
void ordenartareas(T_tarea **tareas,T_tarea **tareasrealizadas,int cant_tareas);
void mostrarTareas(T_tarea **tareas,int cant_tareas);
T_tarea *buscaTareaPalabra(T_tarea **tareas,int cant_tareas, char clave[]);

int main()
{
    int cant_tareas; char clave[20];
    printf("Ingrese la cantidad de tareas que desea cargar: "); 
    scanf("%d",&cant_tareas);
    T_tarea **Tareas_Pendientes =(T_tarea**)malloc(cant_tareas * sizeof(T_tarea*));
    T_tarea **Tareas_Realizadas =(T_tarea**)malloc(cant_tareas * sizeof(T_tarea*));
    cargarTareas(Tareas_Pendientes,cant_tareas);
    puts("------ TAREAS PENDIENTES ------");
    mostrarTareas(Tareas_Pendientes,cant_tareas);
    ordenartareas(Tareas_Pendientes,Tareas_Realizadas,cant_tareas); 
    puts("------ TAREAS REALIZADAS ------");
    mostrarTareas(Tareas_Realizadas,cant_tareas);
    puts("------ BUSQUEDA PALABRA CLAVE ------");
    
    T_tarea *busquedapalabra = buscaTareaPalabra(Tareas_Realizadas,cant_tareas,clave);
    scanf(" %c");
    return 0;
}
int aleatorio(int min,int max){
    return min + rand() % (max-min+1);
}
void cargarTareas(T_tarea **tareas,int cant_tareas)
{
    
    //Reserva dinamica de N tareas
    for (int i = 0; i < cant_tareas; i++)
    {
        char aux[100];
        tareas[i] = (T_tarea*)malloc(sizeof(T_tarea));
        tareas[i]->TareaID = i+1;
        printf("Ingrese la actividad N%d:",i+1); scanf("%s",aux); 
        tareas[i]->Descripcion = (char*)malloc(strlen(aux)+1 * sizeof(char));
        strcpy(tareas[i]->Descripcion,aux);
        tareas[i]->Duracion = aleatorio(1,10);
    }
}
void mostrarTareas(T_tarea **tareas,int cant_tareas)
{
    for (int i = 0; i < cant_tareas; i++)
    {    
        if(tareas[i]!= NULL)
        {
            printf("ID Tarea: %d\n",tareas[i]->TareaID);
            printf("Descripcion: %s\n",tareas[i]->Descripcion);
            printf("Duracion: %d minutos\n",tareas[i]->Duracion);
            printf("----------------------------\n");
        }
    }
}
void ordenartareas(T_tarea **tareas, T_tarea **tareasrealizadas, int cant_tareas)
{
    for (int i = 0; i < cant_tareas; i++)
    {
        char aux[3];
        printf("¿Completo la tarea N%d? Tarea: %s (Si/No)\n",i+1,tareas[i]->Descripcion); scanf("%s",aux);
        if (strcmp(aux,"SI") == 0 || strcmp(aux,"si") == 0) //Comparo las cadenas, devuelve 0 si son iguales
        {
            tareasrealizadas[i] = (T_tarea*)malloc(sizeof(T_tarea));
            tareasrealizadas[i] = tareas[i];
            tareas[i] = NULL;
        }
        else
        {
            tareasrealizadas[i] = NULL; //Cargo NULL en las tareas no realizadas
        }
    }
}
T_tarea *buscaTareaPalabra(T_tarea **tareas,int cant_tareas ,char clave[])
{
    T_tarea *nula;
    //Cargo una nula en caso de no encontrar la tarea buscada
    nula->TareaID = 0;
    nula->Descripcion = NULL;
    nula->Duracion = 0;
    
    puts("Ingrese la tarea que desea buscar"); scanf("%s",clave);
    for (int i = 0; i < cant_tareas; i++)
    {
        if (strcmp(tareas[i]->Descripcion,clave) )
        {
            printf("Palabra clave: '%s' TareaID: %d Duracion: %d minutos\n",clave,tareas[i]->TareaID,tareas[i]->Duracion);
            return tareas[i];
        }
    }
    printf("No se encontro tarea asociada al ID\n");
    return nula; //Problemas al retornar nula, cuando no encuentra la palabra,otro problema es que no muestra la duracion y el id correcto
}