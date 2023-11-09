#define NC 10							/* Number of Cols        */
#define NR 10							/* Number of Rows        */
#define MAX(x,y) ( ((x) > (y)) ? x : y )

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

void initialize( float** t );
void set_bcs   ( float** t );

int main( int argc, char **argv ){
	
	int rank, n_procs;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &n_procs);

	//int stat;							/* Error Status  */
	int niter;							/* iter counter  */
	int n_linhas = (NR+2)/(n_procs-1);

	float **t, **told;
	float dt;							/* Delta t       */
	//float dtg;							/* Delta t global*/

	int i, j, iter;

	if(rank == 0){
		/* Instatiate t */
		t =  calloc(NR+2, sizeof(float*));
		t[0] = calloc((NR+2)*(NC+2), sizeof(float));
		for( i=0; i<=NR+1; i++)				/* Copy the pointers */
			t[i] = &t[0][i*(NC+2)];

		/* Instatiate told */
		told =  calloc(NR+2, sizeof(float*));
		told[0] =  calloc((NR+2)*(NC+2), sizeof(float));
		for( i=0; i<=NR+1; i++)				/* Copy the pointers */
			told[i] = &told[0][i*(NC+2)];


		initialize(t);						/* Give initial guesss of 0. */

		set_bcs(t);							/* Set the Boundary values   */

		for( i=0; i<=NR+1; i++ ) {       	/* Copy the values into told */
			for( j=0; j<=NC+1; j++ ) {
				told[i][j] = t[i][j];
				//printf("%08.4f ", told[i][j]);	/* Debug purposes only */
			}
			//printf("\n");						/* Debug purposes only */
		}
	}
	else {
		t =  calloc(n_linhas, sizeof(float*));
		t[0] = calloc((n_linhas)*(NC+2), sizeof(float));
		for( i=0; i<n_linhas; i++)				/* Copy the pointers */
			t[i] = &t[0][i*(NC+2)];
	}

	MPI_Scatter(t[0], (NR+2)*n_linhas, MPI_FLOAT, t[0], (NR+2)*n_linhas, MPI_FLOAT, 0, MPI_COMM_WORLD);
	if(rank > 0){
		for( i=0; i<n_linhas; i++ ) {
			for( j=0; j<=NR+1; j++ ) {
				printf("%08.4f ", t[i][j]);
			}
			printf("\n");
		}
	}
	
	MPI_Finalize();
	return 0;

   /*-------------------------------------------------*/
  /* Do Computation on Sub-grid for Niter iterations */
 /*-------------------------------------------------*/
	niter=10;

	for( iter=1; iter<=niter; iter++ ) {

		for( i=1; i<=NR; i++ )
			for( j=1; j<=NC; j++ )
				t[i][j] = 0.25 * ( told[i+1][j] + told[i-1][j] +
									told[i][j+1] + told[i][j-1] );
		dt = 0.;

		for( i=1; i<=NR; i++ )			/* Copy for next iteration  */
			for( j=1; j<=NC; j++ ){
				dt = MAX( abs(t[i][j]-told[i][j]), dt);
				told[i][j] = t[i][j];
			}

		  /*------------------------*/
		 /* Print some test values */
		/*------------------------*/
		if( (iter%niter) == 0 ) {
			printf("Iter = %4d: t[10][10] = %20.8f\n", 
					iter, t[10][10]); 
		}
		  /*---------------------*/
		 /* Debug purposes only */
		/*---------------------*/
		/*
		printf("\nIter = %4d\n", iter);
		for( i=0; i<=NR+1; i++ ) {       	
			for( j=0; j<=NC+1; j++ ) {
				printf("%08.4f ", told[i][j]);
			}
			printf("\n");
		}
		*/
	}  /* End of iteration */
	MPI_Finalize();
}    /* End of Program */

  /*-----------------------------------------------------*/
 /* Initialize all the values to 0. as a starting value */
/*-----------------------------------------------------*/
void initialize( float** t ){

  int i, j;
	  
	for( i=0; i<=NR+1; i++ )        /* Initialize */
		for ( j=0; j<=NC+1; j++ )
			t[i][j] = 0.0;
}

   /*----------------------------------------------------------------*/
  /* Set the values at the boundary.  Values at the boundary do not */
 /* Change through out the execution of the program                */
/*----------------------------------------------------------------*/
void set_bcs( float** t){

	int i, j;

	for( i=0; i<=NR+1; i++ ) {      /* Set Left and Right boundary */
		t[i][0]    = 100.0;
		t[i][NC+1] = 100.0;
	}

    /* Top and Bottom boundary */
	for( j=0; j<=NC+1; j++ ) {
		t[0][j]  = 100.0;
		t[NR+1][j] = 100.0;
	}

}