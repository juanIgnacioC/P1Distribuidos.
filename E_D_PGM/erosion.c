#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "mpi.h"

/**
COMPILAR: mpicc labMpi.c -o lab
EJECUTAR: mpirun -np 2 ./lab

int MPI_Init(int *argc, char ***argv);
int MPI_Comm_size (MPI_Comm comm, int *size);
int MPI_Comm_rank (MPI_Comm comm, int *rank);
int MPI_Finalize(void);

int MPI_Send(void* buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm);
int MPI_Recv(void* buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status);
fgets(buffer, MAX_BUFFER, stdin);

srand(time(NULL));
sleep(rand()%3);
sprintf(void* buf, char[] mensaje, ...);

*/
main(int argc, char* argv[]) {
    int         my_rank;       /* rank of process (Se guardara el id de este proceso)     */
    int         n;             /* number of processes (Se almacena la cantidad de procesos) */
    int size = 10;
    int buffer[size];
    srand(time(NULL));   // Initialization, should only be called once.

    /* Start up MPI */
    MPI_Init(&argc, &argv);

    /* Find out process rank (Id del proceso) */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    /* Find out number of processes (cantidad de procesos) */
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    
    FILE *arch,*sali;
	unsigned char c,c1,c2;
	int fila, colu, i, j, gris;
	unsigned char dibu[1000][1000],otra[1000][1000];

	arch=fopen("imgNueva.pgm","rb");
	c1=fgetc(arch);
	c2=fgetc(arch);
    if (c1!='P' || c2!='5')
    {
		printf("\nFormato no corresponde a una Imagen\n");
		exit (0);
    }
	c=fgetc(arch);
    c=fgetc(arch);
	while (c!='\n')
		c=fgetc(arch);
	fscanf(arch,"%d",&colu);
	fscanf(arch,"%d",&fila);
	fscanf(arch,"%d",&gris);
	
	printf("\n%c%c",c1,c2);
	printf("\nfila : %d",fila);
	printf("\ncolu : %d",colu);
	printf("\ngris : %d\n",gris);

	for(i=0; i<fila; i++){
		for(j=0; j<colu; j++)
		{
			c=fgetc(arch);
			dibu[i][j] = c;
			otra[i][j] = c;
		}
	}
    

    //CLIENTE
    if(my_rank == 1){
        printf("%d primera parte matriz\n", my_rank);
        unsigned char local1[1000][1000];
        
        // Proceso	- Erosion
        int rango1 = (fila)/2;
        for(i=0; i<rango1; i++){
            local1[i][0]=otra[i][0];
        }
        for(j=0; i<colu; j++){///////
            local1[rango1][j]=otra[rango1][j];
        }
        
        for(i=1; i<rango1; i++){
            for(j=1; j<colu; j++){
                int min =255;
                int k[5];
                k[0] = dibu[i][j-1];
                k[1] = dibu[i-1][j];
                k[2] = dibu[i][j];
                k[3] = dibu[i][j+1];
                k[4] = dibu[i+1][j];
                int l;
                for(l=0;l<5;l++){
                    //printf("k: %d", k[l]);
                    if(k[l]<min){
                        min = k[l];
                    }
                }
//                 printf("minimo: %d\n", min);
                local1[i][j]=min;
                //otra[i][j] = min;
                
                    //printf("%d primin\n", min);
            }
        }
//         Mandar la matriz
            MPI_Send(local1, fila/2*(colu), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
            
    }
        
    if(my_rank == 2){
        printf("%d segundaparte matriz\n", my_rank);
        
        
        
        unsigned char local2[1000][1000];
        
        // Proceso	- Erosion
        int rango2 = (fila)/2;
        for(i=0; i<rango2; i++){
            local2[i][0]=otra[i][0];
        }
        for(j=0; i<colu; j++){
            local2[0][j]=otra[0][j];
        }
        //local2[0][0] = dibu[rango2][0];
        
        for(i=rango2; i<fila; i++){
            for(j=1; j<colu; j++){
                int min =255;
                int k[5];
                k[0] = dibu[i][j-1];
                k[1] = dibu[i-1][j];
                k[2] = dibu[i][j];
                k[3] = dibu[i][j+1];
                k[4] = dibu[i+1][j];
                int l;
                
                for(l=0;l<5;l++){
                    //printf("k: %d", k[l]);
                    if(k[l]<min){
                        min = k[l];
                    }
                }
//                 printf("minimo: %d\n", min);
                local2[(i-rango2)][j]=min;
                //otra[i][j] = min;
                
                    //printf("%d primin\n", min);
            }
        }
//         Mandar la matriz
            MPI_Send(local2, fila/2*(colu), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }
        
        

    //SERVIDOR
    if(my_rank == 0){
        printf("%d recibe resultado matriz\n", my_rank);
        
//         recibe lass dos matrices y las guarda
        unsigned char local1[1000][1000], local2[1000][1000];
        
        MPI_Recv(local1, fila/2*(colu), MPI_UNSIGNED_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
                
        
        MPI_Recv(local2, fila/2*(colu), MPI_UNSIGNED_CHAR, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        
        int rango1 = (fila)/2;
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++){
                if(i < (rango1))
                    otra[i][j] = local1[i][j];
                else{
                    otra[i][j] = local2[(i-rango1)][j];
                }
            }
        }
        //printf("servFinalLocal2: %d\n", local2[1][1]);
        //printf("servFinal!!: %d\n", otra[174][1]);
        
        // Fin del Proceso	
        sali=fopen("erosionNuevo.pgm","wb");
        fprintf(sali,"P5\n");
        fprintf(sali,"# Creado por Juan Cordero y Alvaro Elgueda.\n");
        fprintf(sali,"%d %d\n",colu,fila);
        fprintf(sali,"%d\n",gris);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++)
            {
                fprintf(sali,"%c",otra[i][j]);
            }
        }
        printf("\n");
        printf("Archivo erosionNuevo.pgm satisfactoriamente creado\n");
    }

    /* Shut down MPI */
    MPI_Finalize();
} /* main */
