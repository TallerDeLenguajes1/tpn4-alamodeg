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
T_tarea *buscarTareaID(T_tarea **tareas,int cant_tareas);

int main()
{
    int cant_tareas;
    printf("Ingrese la cantidad de tareas que desea cargar: "); 
    scanf("%d",&cant_tareas);
    
    T_tarea **Tareas_Pendientes = (T_tarea**)malloc(cant_tareas * sizeof(T_tarea*));
    T_tarea **Tareas_Realizadas = (T_tarea**)malloc(cant_tareas * sizeof(T_tarea*));
    
    cargarTareas(Tareas_Pendientes,cant_tareas);
    puts("------ TAREAS PENDIENTES ------");
    mostrarTareas(Tareas_Pendientes,cant_tareas);
    ordenartareas(Tareas_Pendientes,Tareas_Realizadas,cant_tareas); 
    puts("------ TAREAS REALIZADAS ------");
    mostrarTareas(Tareas_Realizadas,cant_tareas);
    mostrarTareas(Tareas_Pendientes,cant_tareas);
    puts("------ BUSQUEDA ID DE TAREAS YA REALIZADAS------");
    T_tarea *resultadoid = buscarTareaID(Tareas_Realizadas,cant_tareas);
    if (resultadoid == NULL)
    {
        printf("No se encontro ninguna tarea relacionada a ese ID\n");
    }
    else
    {
        printf("Se encontro la tarea, su id es %d",resultadoid->TareaID);
    }
    
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
T_tarea *buscarTareaID(T_tarea **tareas,int cant_tareas)
{
    int aux;
    printf("Ingrese el id de la tarea a buscar\n");
    scanf("%d",&aux);
    for (int i = 0; i < cant_tareas; i++)
    {
        while (tareas[i] != NULL) //Para poder comparar el numero cuando la tarea[i] no es nula.
        {
            if (tareas[i]->TareaID == aux)
            {
                return tareas[i];
            }
        }
    }
    return NULL;
}