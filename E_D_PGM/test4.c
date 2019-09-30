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
    
    FILE *arch,*sali, *sali2, *sali3, *sali4, *sali5;
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
	printf("matrizComienzo!!!: %d\n", otra[1][1]);
    

    //CLIENTE
    if(my_rank == 1){
        printf("%d primer elemento estructurante\n", my_rank);
        unsigned char local1[1000][1000];
        
        // Proceso	- Erosion - Primer elemento estructurante
        int rango1 = (fila);
        for(i=1; i<rango1-1; i++){
            for(j=1; j<colu-1; j++){
                int min =255;
                int k[3];
                k[0] = dibu[i-1][j-1];
                k[1] = dibu[i][j-1];
                k[2] = dibu[i-1][j];
                //k[1] = dibu[i][j+1];
                //k[2] = dibu[i+1][j];
                int l;
                for(l=0;l<3;l++){
                    //printf("k: %d", k[l]);
                    if(k[l]<min){
                        min = k[l];
                    }
                }
//                 printf("minimo: %d\n", min);
                local1[i-1][j-1]=min;
                
                    //printf("%d primin\n", min);
            }
        }
//         Mandar la matriz
            MPI_Send(local1, rango1*(colu-1), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
            
    }
        
    if(my_rank == 2){
        printf("%d Segundo elemento estructurante\n", my_rank);
        
        
        
        unsigned char local2[1000][1000];
        
        // Proceso	- Erosion - Segundo elemento estructurante
        int rango2 = (fila);
        for(i=1; i<fila-1; i++){
            for(j=1; j<colu-1; j++){
                int min =255;
                int k[3];

                //k[0] = dibu[i][j-1];
                k[0] = dibu[i-1][j-1];
                k[1] = dibu[i][j-1];
                k[2] = dibu[i][j];
                

                int l;
                for(l=0;l<3;l++){
                    //printf("k: %d", k[l]);
                    if(k[l]<min){
                        min = k[l];
                    }
                }
//                 printf("minimo: %d\n", min);
                local2[i][j-1]=min;
                
                    //printf("%d primin\n", min);
            }
        }
//         Mandar la matriz
            MPI_Send(local2, rango2*(colu-1), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    if(my_rank == 3){
        printf("%d Tercer elemento estructurante\n", my_rank);
        
        
        
        unsigned char local3[1000][1000];
        
        // Proceso	- Erosion - Tercer elemento estructurante
        int rango3 = (fila);
        for(i=1; i<fila-1; i++){
            for(j=1; j<colu-1; j++){
                int min =255;
                int k[3];

                //k[0] = dibu[i][j-1];
                k[0] = dibu[i-1][j-1];
                k[0] = dibu[i][j-1];
                k[2] = dibu[i+1][j+1];
                

                int l;
                for(l=0;l<3;l++){
                    //printf("k: %d", k[l]);
                    if(k[l]<min){
                        min = k[l];
                    }
                }
//                 printf("minimo: %d\n", min);
                local3[i][j-1]=min;
                
                    //printf("%d primin\n", min);
            }
        }
//         Mandar la matriz
            MPI_Send(local3, rango3*(colu-1), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    if(my_rank == 4){
        printf("%d Cuarto elemento estructurante\n", my_rank);
        
        
        
        unsigned char local4[1000][1000];
        
        // Proceso	- Erosion - Cuarto elemento estructurante
        int rango4 = (fila);
        for(i=1; i<fila-1; i++){
            for(j=1; j<colu-1; j++){
                int min =255;
                int k[2];

                //k[0] = dibu[i][j-1];
                k[0] = dibu[i-1][j-1];
                k[0] = dibu[i-1][j];
                //k[2] = dibu[i+1][j]+1;
                

                int l;
                for(l=0;l<2;l++){
                    //printf("k: %d", k[l]);
                    if(k[l]<min){
                        min = k[l];
                    }
                }
//                 printf("minimo: %d\n", min);
                local4[i-1][j-1]=min;
                
                    //printf("%d primin\n", min);
            }
        }
//         Mandar la matriz
            MPI_Send(local4, rango4*(colu-1), MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    
        
        

    //SERVIDOR
    if(my_rank == 0){
        printf("%d recibe resultado matriz\n", my_rank);
        
//         recibe lass dos matrices y las guarda
        unsigned char local1[1000][1000], local2[1000][1000], local3[1000][1000], local4[1000][1000], local5[1000][1000];
        
        

        //RECIBEN   
        MPI_Recv(local1, (fila)*(colu-1), MPI_UNSIGNED_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf("matrizservLocal11111111111: %d\n", local1[1][1]);      
        
        //LEEN
        
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++){
                otra[i][j] = local1[i][j];
            }
        }

        sali=fopen("erosionThread1.pgm","wb");
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


        unsigned char otra2[1000][1000],otra3[1000][1000],otra4[1000][1000],otra5[1000][1000];
        
        MPI_Recv(local2, (fila)*(colu-1), MPI_UNSIGNED_CHAR, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++){
                otra2[i][j] = local2[i][j];
            }
        }
        sali2=fopen("erosionThread2.pgm","wb");
        fprintf(sali2,"P5\n");
        fprintf(sali2,"# Creado por Juan Cordero y Alvaro Elgueda.\n");
        fprintf(sali2,"%d %d\n",colu,fila);
        fprintf(sali2,"%d\n",gris);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++)
            {
                fprintf(sali2,"%c",otra2[i][j]);
            }
        }

        MPI_Recv(local3, (fila)*(colu-1), MPI_UNSIGNED_CHAR, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++){
                otra3[i][j] = local3[i][j];
            }
        }
        sali3=fopen("erosionThread3.pgm","wb");
        fprintf(sali3,"P5\n");
        fprintf(sali3,"# Creado por Juan Cordero y Alvaro Elgueda.\n");
        fprintf(sali3,"%d %d\n",colu,fila);
        fprintf(sali3,"%d\n",gris);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++)
            {
                fprintf(sali3,"%c",otra3[i][j]);
            }
        }

        /*

        MPI_Recv(local4, (fila)*(colu-1), MPI_UNSIGNED_CHAR, 4, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++){
                otra4[i][j] = local4[i][j];
            }
        }
        sali=fopen("erosionThread4.pgm","wb");
        fprintf(sali,"P5\n");
        fprintf(sali,"# Creado por Juan Cordero y Alvaro Elgueda.\n");
        fprintf(sali,"%d %d\n",colu,fila);
        fprintf(sali,"%d\n",gris);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++)
            {
                fprintf(sali,"%c",otra4[i][j]);
            }
        }*/

        //MPI_Recv(local5, (fila)*(colu-1), MPI_UNSIGNED_CHAR, 5, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        /*for(i=0; i<fila; i++){
            for(j=0; j<colu; j++){
                otra5[i][j] = local5[i][j];
            }
        }*/
        
        //printf("servFinalLocal2: %d\n", local2[1][1]);
        //printf("servFinal!!: %d\n", otra[174][1]);
        
        // Fin del Proceso	
        //SALIDAS
        

        /*sali=fopen("erosionThread5.pgm","wb");
        fprintf(sali,"P5\n");
        fprintf(sali,"# Creado por Juan Cordero y Alvaro Elgueda.\n");
        fprintf(sali,"%d %d\n",colu,fila);
        fprintf(sali,"%d\n",gris);
        for(i=0; i<fila; i++){
            for(j=0; j<colu; j++)
            {
                fprintf(sali,"%c",otra5[i][j]);
            }
        }*/


    }

    /* Shut down MPI */
    MPI_Finalize();
} /* main */
