
/*
ID: song chen
LANG: C
TASK: transform
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum type {
	NONE,
	CR90,
	CR180,
	CR270
};

static inline int coordinate(int x, int y, int n)
{
	return ( y * n + x );
}

static inline int coordinate_r90(int x, int y, int n)
{
	return ( (n - 1 - x) * n + y );
}

static inline int coordinate_r180(int x, int y, int n)
{
	return ( (n - 1 - y) * n + (n - 1 - x) );
}

static inline int coordinate_r270(int x, int y, int n)
{
	return ( x * n + (n - 1 - y) );
}

static inline void reflection(char *d1, int n)
{
	int x,y;
	char temp;
	for(y = 0; y < n; y++) {
		for(x = 0; x < n/2; x ++) {
			int idx1 = coordinate(x,y,n);
			int idx2 = coordinate((n-1-x),y,n);
			temp = d1[idx1];
			d1[idx1] = d1[idx2];
			d1[idx2] = temp;
		}
	}
}

static inline int cmp(const char *d1, const char *d2, int n, enum type t)
{
	int i, j;
	
	switch(t)
	{
		case NONE:
			for(i = 0; i < n; i++) {
				for(j = 0; j < n; j++) {
					if( d1[coordinate(i,j,n)] != d2[coordinate(i,j,n)] )
						return 0;
				}
			}
			break;
		case CR90:
			for(i = 0; i < n; i++) {
				for(j = 0; j < n; j++) {
					if( d1[coordinate_r90(i,j,n)] != d2[coordinate(i,j,n)] )
						return 0;
				}
			}
			break;
		case CR180:
			for(i = 0; i < n; i++) {
				for(j = 0; j < n; j++) {
					if( d1[coordinate_r180(i,j,n)] != d2[coordinate(i,j,n)] )
						return 0;
				}
			}
			break;
		case CR270:
			for(i = 0; i < n; i++) {
				for(j = 0; j < n; j++) {
					if( d1[coordinate_r270(i,j,n)] != d2[coordinate(i,j,n)] )
						return 0;
				}
			}
			break;
		default:
			printf("error!!\n");
			return 0;
	}

	return 1;
}

static inline void print(const char *data, int n, enum type t) 
{
	int x,y;
	for(y = 0; y < n; y++ ) {
		for(x = 0; x < n; x++) {
			switch(t) {
				case CR90:
					printf("%c ", data[coordinate_r90(x,y,n)]);
					break;
				case CR180:
					printf("%c ", data[coordinate_r180(x,y,n)]);
					break;
				case CR270:
					printf("%c ", data[coordinate_r270(x,y,n)]);
					break;
				case NONE:
				default:
					printf("%c ", data[coordinate(x,y,n)]);
					break;
			}
		}
		printf("\n");
	}
}

int main()
{
	FILE *fin, *fout;
	fin = fopen("transform.in", "r");
	fout = fopen("transform.out", "w");
	assert(fin != NULL && fout != NULL);

	int n;
	fscanf(fin, "%d", &n);

	assert(n > 0 && n <= 10);

	char d1[128];
	char d2[128];
	
	int i;
	for(i = 0; i < n; i ++) {
		fscanf(fin, "%s", &(d1[i*n]));
	}

	for(i = 0; i < n; i ++) {
		fscanf(fin, "%s", &(d2[i*n]));
	}

	int ret;

	if( cmp(d1, d2, n, CR90) ) {
		ret = 1;
	} else if( cmp(d1, d2, n, CR180) ) {
		ret = 2;
	} else if( cmp(d1, d2, n, CR270) ) {
		ret = 3;
	} else if( cmp(d1, d2, n, NONE) ) {
		ret = 6;
	} else {
		reflection(d1, n);
		if( cmp(d1, d2, n, NONE) ) {
			ret = 4;
		} else if( cmp(d1, d2, n, CR90) ) {
			ret = 5;
		} else if( cmp(d1, d2, n, CR180) ) {
			ret = 5;
		} else if( cmp(d1, d2, n, CR270) ) {
			ret = 5;
		} else {
			ret = 7;
		}
	}

	fprintf(fout, "%d\n", ret);
	exit(0);
}

