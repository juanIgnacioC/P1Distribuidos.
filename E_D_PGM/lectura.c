// lectura.c   (Creado por Rodrigo Pavez M)
#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* Programa que permite la lectura y generacion de archivos en formato PGM
Este formato tiene la siguiente estructura:
P5									// Es la cadena magica que identifica al PGM
# Comentarios pueden ser varios		
ancho alto							// Pixel de ancho y pixel de alto en formato decimal
grises								// Escala de grises entre 0 y 255 en formato decimal
los ascii correspondientes a la cantidad ancho x alto pixeles.
*/

main()
{
    int         my_rank;       /* rank of process (Se guardara el id de este proceso)     */
    int         n;             /* number of processes (Se almacena la cantidad de procesos) */
//     int size = 10;
//     int buffer[size];
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
	printf("\ngris : %d",gris);

	for(i=0; i<fila; i++){
		for(j=0; j<colu; j++)
		{
			c=fgetc(arch);
			dibu[i][j] = c;
			otra[i][j] = c;
		}
	}

	
// Proceso	- Erosion
	for(i=1; i<fila-1; i++){
		for(j=1; j<colu-1; j++){
			int min =255;
			int k[5];
			k[0] = dibu[i][j-1];
			k[1] = dibu[i-1][j];
			k[2] = dibu[i][j];
			k[3] = dibu[i][j+1];
			k[4] = dibu[i+1][j];
			int l;
			for(l=0;l<5;l++){
				if(k[l]<min){
					min = k[l];
				}
			}
			otra[i][j]=min;
		}
	}
	// Fin del Proceso	
    sali=fopen("erosionN.pgm","wb");
	fprintf(sali,"P5\n");
	fprintf(sali,"# Creado por Rodrigo Pavez. (2019)\n");
	fprintf(sali,"%d %d\n",colu,fila);
    fprintf(sali,"%d\n",gris);
	for(i=0; i<fila; i++){
		for(j=0; j<colu; j++)
		{
			fprintf(sali,"%c",otra[i][j]);
		}
	}
	
	
	// Dilatacion
	for(i=1; i<fila-1; i++){
		for(j=1; j<colu-1; j++){
			int max =0;
			int k[5];
			k[0] = dibu[i][j-1];
			k[1] = dibu[i-1][j];
			k[2] = dibu[i][j];
			k[3] = dibu[i][j+1];
			k[4] = dibu[i+1][j];
			int l;
			for(l=0;l<5;l++){
				if(k[l]>max){
					max = k[l];
				}
			}
			otra[i][j]=max;
		}
	}

	// Fin del Proceso	
    sali=fopen("dilatacionN.pgm","wb");
	fprintf(sali,"P5\n");
	fprintf(sali,"# Creado por Rodrigo Pavez. (2019)\n");
	fprintf(sali,"%d %d\n",colu,fila);
    fprintf(sali,"%d\n",gris);
	for(i=0; i<fila; i++){
		for(j=0; j<colu; j++)
		{
			fprintf(sali,"%c",otra[i][j]);
		}
	}
	fclose(arch);
	fclose(sali);
}
