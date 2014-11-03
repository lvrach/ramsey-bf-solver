#include <stdio.h>
#include <assert.h>
#include <string.h>

#if !defined(POINTS)
    #define POINTS 10
#endif

#define err -2
#define X 0
#define RED 2
#define BLUE 1


void print(int array[POINTS][POINTS]) {

	int i,j;

	printf("\t-\t-\t-\t-\n");
	for(i=0; i<POINTS; i++) {
		
		for(j=0; j<POINTS; j++) {
			
			switch(array[i][j]) {
				
				case err: 
					printf("...\t");
					break;
				case X:
					printf("   \t");
					break;
				case RED:
					printf("RED\t");
					break;
				case BLUE:
					printf("BLUE\t");
					break;
				default:
					printf("xxx\t");
					
			};

		}
		printf("\n");
	}
	return ;

}
void copy(int a[POINTS][POINTS],int b[POINTS][POINTS])
{
	int i,j;
	for(i=0;i<POINTS;i++)
		for(j=0;j<POINTS;j++)
			a[i][j] = b[i][j];
	return ;

}

int opposite(int type)
{

	if( type == RED)
		return BLUE;
	if( type == BLUE)
		return RED;

	assert(0);

}
int check_5(int array[POINTS][POINTS],
			char correlations[POINTS][POINTS][POINTS][POINTS])
{
	int l;
	int p1,p2,p3,p4;
	
	for(l=0; l<POINTS-1; l++) {
	
		for(p1=l+1; p1<POINTS-1; p1++) {
		
			if(array[l][p1] == X )
				continue;
			
			for(p2 = p1 + 1; p2 < POINTS; p2++) {
				
				if( array[l][p2] == X )
					continue;
				if( array[l][p1] !=  array[l][p2] )
					continue;
				
				for(p3 = p2 + 1; p3 < POINTS; p3++) {
					
					if( array[p2][p3] == X )
						continue;
					
					if( array[p2][p3] != array[l][p1] ) {
						


					}
					
					for(p4 = p3 + 1; p4 < POINTS; p4++) {
						
						if( array[p3][p4] == X ) 
							array[p3][p4] = opposite( array[l][p1] );				

						if( array[p3][p4] == array[l][p1] ) {
							printf("invalide quadrangle: (%i,%i,%i,%i) ",p1,p2,p3,p4);
							return 0;
						}			

					}

				}	

			}
		}
	}

return 1;	

}

int check_4(int array[POINTS][POINTS],
			char correlations[POINTS][POINTS][POINTS][POINTS])
{
	int p1,p2,p3,p4;
	// p1 > p2 > p3 > p4	
	int color;

	for(p1=0; p1<POINTS-1; p1++) {
	
		for(p2=p1+1; p2<POINTS-1; p2++) {
		
			if(array[p1][p2] == X )
				continue;			

			color = array[p1][p2];

			for(p3 = p2 + 1; p3 < POINTS; p3++) {
				
				if( array[p2][p3] == X )
					continue;

				if( array[p2][p3] !=  color )
					continue;
			
				if( correlations[p1][p2][p2][p3] == 1) {
					printf("corelation mismatch (%i:%i-%i:%i)\n",p1,p2,p2,p3);
					return 0;
				}
				
				for(p4 = p3 + 1; p4 < POINTS; p4++) {
				

					if( array[p3][p4] == X ) {
						correlations[p1][p4][p3][p4] = 1; 
						continue;
					}
					if( array[p3][p4] != color )
						continue;

					if( array[p1][p4] == color ) {
	//					printf("4-range mismatch (%i:%i:%i:%i)\n",p1,p2,p3,p4);
						return 0;

					}
					else if ( array[p1][p4] == X ) {

						array[p1][p4] = opposite( color );				

					}
					

				}	

			}
		}
	}

return 1;	

}

int check_3(int array[POINTS][POINTS] )
{

	int l,a,b;

	l = 0;//level;
	
	for(l=0; l<POINTS-1; l++) {
	
		for(a=l+1; a<POINTS-1; a++) {
		
			if(array[l][a] == X )
				continue;

			for(b=a+1; b<POINTS; b++) {
				
				if( array[l][b] == X )
					continue;
				
				if( array[l][a] == array[l][b]) {

					if ( array[l][a] == array[a][b] ) {
						return 0;

					}
					else if ( array[a][b] == X ) {
						array[b][a] = opposite(array[l][a]);		
						array[a][b] = opposite(array[l][a]);
//	#					printf("force to set %d:%d new array \n",a,b);

					}

				}
			}
		}
	}
	return 1;

}


void rcopy(char a[POINTS][POINTS][POINTS][POINTS],
		char b[POINTS][POINTS][POINTS][POINTS])	
{
	int i,j,k,l;
	for(i=0;i<POINTS;i++)
		for(j=0;j<POINTS;j++)
			for(k=0;k<POINTS;k++)
				for(l=0;l<POINTS;l++)
					a[i][j][k][l] = b[i][j][k][l];
	
	return;


}

int test( int level, int pconnects[POINTS][POINTS],
			char prelations[POINTS][POINTS][POINTS][POINTS]) 
{
	
	unsigned int t;
	int i,x,count;
	int connects[POINTS][POINTS];
	char relations[POINTS][POINTS][POINTS][POINTS];


	do {

		if(level >= POINTS  ) {
			printf("find");	
			print(connects);
			return 1;
		}
		
		count = 0;		
		for( i=level+1; i<POINTS; i++)
			if( pconnects[level][i] == X ) 
				count ++;
		
		if( count == 0) {
			printf("skip level%i\n",level);
			level ++;
		}

	} while(count == 0);
	
	if(level >= POINTS  ) {
		printf("find");	
		print(connects);
		return 1;
	}

	count = 2 << (count-1) ;
	
	for(t=0;t<count;t++) {
		
		copy(connects,pconnects);
		rcopy(relations,prelations);


		for(x=0, i=level+1; i<POINTS; i++) {
			
			if(connects[level][i] == X ) {
							
				if( (t >> x) % 2 == 0 ) {
					connects[level][i] = RED;
				}
				else {
					connects[level][i] = BLUE;
				}
				x ++;
			}
			
		}
		
		if (check_4(connects,relations) == 1 ){
	//		printf("dive to level: %i \n",level+1);
	//		print(connects);
			test(level+1,connects,relations); 
	//		printf("return to level: %i \n",level);
		}


	}
	return 0;
}


int main() {

	int i,j,count,x,t;
	int level=0;

	
	#pragma omp parallel
	{

		count = 2 << (POINTS-3) ;
		int connects[POINTS][POINTS] = {{ X }};
		
		for(i=0;i<POINTS;i++)
			for(j=0;j<POINTS;j++) {
				
				if(i==j)
					connects[i][j]= err;
				else if(i>j)
					connects[i][j]= err;
				else
					connects[i][j]= X;


			}
		
		char relations[POINTS][POINTS][POINTS][POINTS] = {{{{ 0 }}}};

		#pragma omp for schedule(dynamic , 16)
		for(t=0; t<count; t++) {

			printf("try:%i/%i \n", t, count);
		
			for( x=0, i=level+1; i<POINTS; i++) {
			
				
				if( (t >> x ) % 2 == 0 ) {
					connects[level][i] = RED;
				}
				else {
					connects[level][i] = BLUE;
				}

				x++;
						
			}
			
			test(level+1,connects,relations);

		}
	}

	return 0;

}

			      
