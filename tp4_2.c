#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>


struct Tarea
{
    int TareaID; //Numerico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; //entre 10-100
}typedef Tarea;

struct Nodo
{
    Tarea T;
   struct Nodo *Siguiente;
}typedef Nodo;


Nodo *startPendiente;
Nodo *startRealizada;

Nodo * ListaVacia();
// Nodo *CrearNodo(Tarea T);
Nodo *CrearNodo(Tarea t);
void InsertarNodo(Nodo **startPendiente, Tarea t);
Tarea CrearTarea(int *i);
void MostrarLista(Nodo ** startPendiente); 

Nodo * QuitarNodoID(Nodo **startPendiente, int id);// para mover a la otra lista
Nodo * QuitarNodoChar(Nodo **startPendiente,char palabra[]);

void AgregarNodo(Nodo ** startPendiente, Nodo * Tnodo);


void BuscarTareaPorPalabra(Nodo *startPendiente, Nodo *startRealizada, char palabra[] );

void BuscarNodo(Nodo **startPendiente, Nodo**startRealizada);


int main(){


srand(time(NULL));
startPendiente=ListaVacia();
startRealizada=ListaVacia();

Nodo *aux;

int aux1=1;
int i=0;
int num=1000;
Tarea  t;
char clave[40];
int opcion1=2;
int id;
int opcion2=1;


       do{  
                       
                  printf("0- Para salir del menu\n");
                  printf("1-Cargar una Tarea\n");
                  printf("2-Mostrar tareas pendientes\n");
                  printf("3-Mostar tareas realizadas\n");
                  printf("4-Mover tareas pendientes a realizadas\n");
                  printf("5-Buscar Tarea\n");
                  scanf("%d",&opcion1);
                  fflush(stdin);

                    switch (opcion1)
                    {
                      case 1:
                  while (aux1 !=0){
                  
                          printf("Quiere insertar una tarea:(si:1/no:0)?\n");
                          scanf("%d",&aux1);


                        if (aux1==1){
                    
                        i++;

                        
                        InsertarNodo(&startPendiente, CrearTarea(&num));

                          }
                    

                      }

                      break;
                      case 2:
                          printf("******************\n 2_Mostrando lista de pendientes  \n ");
                            MostrarLista(&startPendiente);
                      break;
                      case 3:

                            printf("******************\n 2_Mostrando lista de Realiazada  \n ");
                            MostrarLista(&startRealizada);

                      break;
                      case 4:
                          while (opcion2!=0)
                          {
                            printf("Indique el id que desea mover a la lista de realizada:\n");
                              scanf("%d",&id);
                            fflush(stdin);
                            printf("Muevo tareas:\n");
                            aux=QuitarNodoID(&startPendiente,id);
                          AgregarNodo(&startRealizada,aux);


                          printf("Desea modificar otra tarea?(si:1/no:0)\n");
                          scanf("%d", &opcion2);
                              fflush(stdin);

                          }
                          
                            
                      break;

                      case 5:
                      BuscarNodo(&startPendiente,&startRealizada);
                      break;
                    
                    default:
                      break;
                    }

                  
        }while (opcion1 !=0);




   while (startPendiente)
   {
      free(startPendiente);
      startPendiente=startPendiente->Siguiente;
   }
   

   while (startRealizada)
   {
    free(startRealizada);
    startRealizada=startRealizada->Siguiente;
   }
   




    return 0;
}




Nodo * ListaVacia(){

    return NULL;
}


Nodo *CrearNodo(Tarea t){
Nodo *NuevoNodo=(Nodo*)malloc(sizeof(Nodo));
NuevoNodo->T=t;
NuevoNodo->Siguiente=NULL;

 return NuevoNodo;
}

void InsertarNodo(Nodo **startPendiente, Tarea t){
Nodo *NodoNuevo=CrearNodo(t);
NodoNuevo->Siguiente= *startPendiente;
*startPendiente=NodoNuevo;


}



Tarea  CrearTarea (int *i){ // se saco el *CrearTarea,


srand(time(NULL));


char Buff[100];
printf("Ingrese la descripcion de la tarea:\n");
fflush(stdin);
gets(Buff);
 Tarea * NuevaTarea=(Tarea *)malloc(sizeof(Tarea));
 NuevaTarea->Descripcion=(char*)malloc(sizeof(char)*strlen(Buff));

 strcpy(NuevaTarea->Descripcion,Buff);
 NuevaTarea->TareaID=(*i)++; 
 
 fflush(stdin);

NuevaTarea->Duracion=rand()%(100-10)+10;


  return *NuevaTarea;



}



void MostrarLista(Nodo ** startPendiente){

    printf("- - - -Muestro - - - -\n");

    Nodo * aux = *startPendiente; 

    while (aux != NULL)
    {
        printf("ID:%d\n", aux->T.TareaID);
        printf("Descripcion:\n");
        puts( aux->T.Descripcion);
        printf("Duracion: %d\n",  aux->T.Duracion);
        printf("------------------------------\n");
        
        aux = aux->Siguiente;
    }
    

}





Nodo * QuitarNodoID(Nodo ** startPendiente, int id){

Nodo *aux= *startPendiente;
Nodo *antAux= *startPendiente;

  while ( aux && aux->T.TareaID !=id)
  {
    antAux=aux;
    aux=antAux->Siguiente;
  }
  
   if (aux)
   {
    if (aux == *startPendiente)
    {
        *startPendiente=aux->Siguiente;
    }else
    {
        antAux->Siguiente=aux->Siguiente;
    }
    
    aux->Siguiente=NULL;
   }
   

  return aux;



}

void AgregarNodo(Nodo ** startPendiente, Nodo * Tnodo){

 Tnodo->Siguiente = *startPendiente;
    *startPendiente = Tnodo;
}




void BuscarTareaPorPalabra(Nodo *startPendiente, Nodo *startRealizada, char palabra[] ){

 Nodo *aux=startPendiente;

 while (aux && strstr(aux->T.Descripcion,palabra)==NULL)
 {
       

           aux=aux->Siguiente;

 }
 
  if (aux ==NULL)
  {
    aux=startRealizada;
    while (aux && strstr(aux->T.Descripcion,palabra) ==NULL)
    {
      aux=aux->Siguiente;
    }
    
   if (aux==NULL)
   {
    printf("No se encontro la tarea:\n");
   }else
   {
        printf("Se encontro la tarea  de id %d en la lista de realizadas\n", aux->T.TareaID);
            printf("La descripcion de la tarea es ");
            puts(aux->T.Descripcion);
   }
   
  


  }else
  {
    
        printf("Se encontro la tarea  de id %d en la lista de pendientes\n", aux->T.TareaID);
            printf("La descripcion de la tarea es ");
            puts(aux->T.Descripcion);
  }
  


}



Nodo *QuitarNodoChar(Nodo **startPendiente,char palabra[]){

Nodo * aux= *startPendiente;
Nodo * antAux= *startPendiente;

 while (aux != NULL && strcmp(aux->T.Descripcion, palabra) !=0)
 {
    antAux=aux;
    aux=aux->Siguiente;
 }
 

  if (aux)
  {
    if (aux ==*startPendiente)
    {
       *startPendiente=aux->Siguiente;
    }else
    {
        antAux->Siguiente=aux->Siguiente;
    }
    
    aux->Siguiente=NULL;
  }
  

  return aux;

}




void BuscarNodo(Nodo **startPendiente, Nodo**startRealizada){
 
 Nodo *aux;
 Nodo *aux2;

  int opcion, id;
  char clave[40];
  int op=1;

  printf("Buscar Nodo:\n1_ID\n2_Palabra\n");
  scanf("%d",&opcion);
  fflush(stdin);

  switch (opcion)
  {
    
    
  case 1:
  printf("Ingrese el id de la tarea:\n");
  scanf("%d",&id);
  aux=QuitarNodoID(startPendiente,id);
  aux2=QuitarNodoID(startRealizada,id);

  if (aux)
  {
    printf("Tarea %d Pendiente", aux->T.TareaID);
            printf("Descripcion: %s\n", aux->T.Descripcion);
            printf("Duracion: %d\n", aux->T.Duracion);
            printf("------------------------------\n");
  }else
  {
    if (aux2)
    {
        printf("Tarea %d Realizada:\n", aux2->T.TareaID);
            printf("Descripcion: %s\n", aux2->T.Descripcion);
            printf("Duracion: %d\n", aux2->T.Duracion);
            printf("------------------------------\n");
    }else
    {
         printf("No se encuentra el nodo.\n");
    }
    
    
  }

    break;


  case 2:
  

    while (op !=0)
    {
       printf("Ingrese la palabra clave:\n");
       fflush(stdin);
       gets(clave);
    BuscarTareaPorPalabra(*startPendiente,*startRealizada,clave);
      printf("Desea buscar otro nodo:? 1-si| 0-no\n");
       scanf("%d",&op);



    }
    

  break;

  }



}