#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


typedef struct{
    int TareaID;   //Numerado en ciclo iterativo
    char* Descripcion;
    int Duracion;  //entre 10-100
}Tarea;


void CargarTareas(Tarea **tareas,int c);
void OrdenarTareas(Tarea **todastareas,Tarea **tareaspendientes,Tarea **tareasrealizadas,int c);
void MostrarTareas(Tarea **tareas,int c);
Tarea* BusquedaPorPalabra(Tarea **tareas,int c,char *pal);
Tarea* BuscarTarea(Tarea **tareas,int c,int i);


int main(){
srand (time(NULL));

int cant,id;
char descripcion[100],palabra[50];
Tarea **todas_tareas,**tareas_pendientes, **tareas_realizadas;
Tarea *buscar_tarea,*buscar_palabra;

printf("Ingrese la cantidad de tareas a cargar: ");
scanf("%d",&cant);

todas_tareas = (Tarea**) malloc(sizeof(Tarea*) * cant);
tareas_pendientes = (Tarea**) malloc(sizeof(Tarea*) * cant);
tareas_realizadas = (Tarea**) malloc(sizeof(Tarea*) * cant);


CargarTareas(todas_tareas,cant);
OrdenarTareas(todas_tareas,tareas_pendientes,tareas_realizadas,cant);
MostrarTareas(tareas_realizadas,cant);


/////////////////////////BUSQUEDA POR PALABRA CLAVE/////////////////////
printf("\nIngrese palabra clave de la tarea que desea buscar: ");
scanf("%s",palabra);
buscar_palabra = BusquedaPorPalabra(todas_tareas,cant,palabra);
if(buscar_palabra == NULL){
    printf("No se encontro ninguna tarea asociada a la palabra clave '%s'",palabra);
}else{
    printf("La tarea con palabra clave '%s' es:\nID tarea: %d\nDescripcion: %s\nDuracion: %d",palabra,buscar_palabra->TareaID,buscar_palabra->Descripcion,buscar_palabra->Duracion);
///////////////////////////BUSQUEDA POR ID///////////////////////////////////
printf("\nIngrese ID de la tarea que desea buscar: ");
scanf("%d",&id);
buscar_tarea = BuscarTarea(todas_tareas,cant,id);
if(buscar_tarea == NULL){
    printf("No se encontro ninguna tarea asociada al ID: %d",id);
}else{
    printf("La tarea con ID %d es: %s\n",id,buscar_tarea->Descripcion);
}


    scanf(" %c");
    return 0;
}




void CargarTareas(Tarea **tareas,int c){
    char descripcion[100];
    for(int i=0;i<c;i++){
    
    tareas[i] = (Tarea*) malloc(sizeof(Tarea));
    tareas[i]->TareaID = i;
    tareas[i]->Duracion = rand() % 91+10;

    
    printf("Descripcion de la tarea ID %d: ",i);
    scanf("%s",descripcion);
    tareas[i]->Descripcion = (char*) malloc(strlen(descripcion)+1 * sizeof(char));
    strcpy(tareas[i]->Descripcion,descripcion);

    }
}


void OrdenarTareas(Tarea **todastareas,Tarea **tareaspendientes,Tarea **tareasrealizadas,int c){
    char respuesta[3];
    for(int i=0;i<c;i++){
        printf("\nSe completo la tarea ID: %d?\n Descripcion de tarea: %s\n SI/NO: ",i,todastareas[i]->Descripcion);
        scanf("%s",respuesta);
        if(strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0 || strcmp(respuesta,"Si") == 0){
            tareasrealizadas[i] = (Tarea*) malloc(sizeof(Tarea));
            tareaspendientes[i] = (Tarea*) malloc(sizeof(Tarea));

            tareasrealizadas[i] = todastareas[i];
            tareaspendientes[i] = NULL;
            
        }
        else{
            tareasrealizadas[i] = NULL;
            tareaspendientes[i] = todastareas[i];
        }
        
    }
}


void MostrarTareas(Tarea **tareas,int c){
    for(int i=0;i<c;i++){
        if(tareas[i] != NULL){
            printf("\nID de tarea: %d\n",tareas[i]->TareaID);
            printf("Descripcion: %s\n",tareas[i]->Descripcion);
            printf("Duracion: %d\n",tareas[i]->Duracion);
            printf("--------------------------------------\n");
        }
    }
}


Tarea* BusquedaPorPalabra(Tarea **tareas,int c,char *pal){
    for(int j=0;j<c;j++){
        if(strcmp(tareas[j]->Descripcion,pal) == 0){
            return tareas[j];
        }
    }
    return NULL;
}
Tarea* BuscarTarea(Tarea **tareas,int c,int i){
    
   

    for(int j=0;j<c;j++){
        if(tareas[j]->TareaID == i){
            return tareas[j];
        }
    }  
    return NULL;
}
