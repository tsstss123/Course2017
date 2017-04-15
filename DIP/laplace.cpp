#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char in[] = "input.bmp", out[] = "output.bmp";
#define BUFSIZE 10000000
#define MAXLINE 10000
unsigned char head_buf[100];
unsigned char *R[MAXLINE], *G[MAXLINE], *B[MAXLINE];
double pix_percent[256];

void lap(unsigned char *P[], int xlen, int ylen){
	unsigned char *T[MAXLINE];
	for(int i = 0; i < ylen; ++i){
		T[i] = (unsigned char*)malloc(sizeof(unsigned char) * xlen);
	}

	int cnt[3][3] = {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};

	for(int i =1; i + 1< ylen; ++i)
		for(int j = 1; j + 1 < xlen; ++j){
			int val = P[i][j], pcnt = 0;
			for(int ni = -1; ni <= 1; ++ni)
				for(int nj = -1; nj <= 1; ++nj){
					int nx = i + ni, ny = j + nj;
					if(!ni && !nj)
						val += int(P[i][j]) * 8;
					else
						val -= P[nx][ny];
				}
			if(val < 0) val = 0;
			if(val > 255) val = 255;
			T[i][j] = val;
		}

	for(int i = 0; i < ylen; ++i){
		memcpy(P[i], T[i], sizeof(unsigned char) * xlen);
	}
}
void conv_avg(unsigned char *P[], int xlen, int ylen, int cx, int cy){
	unsigned char *T[MAXLINE];
	for(int i = 0; i < ylen; ++i){
		T[i] = (unsigned char*)malloc(sizeof(unsigned char) * xlen);
	}

	int detx = cx / 2, dety = cy / 2;

	for(int i = 0; i < ylen; ++i)
		for(int j = 0; j < xlen; ++j){
			int val = 0, pcnt = 0;
			for(int ni = -detx; ni <= detx; ++ni)
				for(int nj = -dety; nj <= dety; ++nj){
					int nx = i + ni, ny = j + nj;
					unsigned char pix;
					if(nx < 0 || nx >= ylen || ny < 0 || ny >= xlen)
						pix = 0;
					else{
						++pcnt;
						pix = P[nx][ny];
					}
					val += pix;
				}
			T[i][j] = val / pcnt;
		}
	for(int i = 0; i < ylen; ++i){
		memcpy(P[i], T[i], sizeof(unsigned char) * xlen);
	}
}

int main(int argc, char** argv)
{
	if(argc == 2){
		strcpy(in, argv[1]);
		strcpy(out, argv[2]);
	}

	FILE *fin = fopen(in, "rb"), *fout = fopen(out, "wb");

	if(fin == NULL){
		printf("Open File ERROR!\n");
		exit(1);
	}

	fread(head_buf, 54, 1, fin);
	fwrite(head_buf, 54, 1, fout);

	int xlen = *(int *)&head_buf[18], ylen = *(int *)&head_buf[22];
	printf("%d, %d\n",xlen, ylen);

	for(int i = 0; i < ylen; ++i){
		R[i] = (unsigned char*)malloc(sizeof(unsigned char) * xlen);
		G[i] = (unsigned char*)malloc(sizeof(unsigned char) * xlen);
		B[i] = (unsigned char*)malloc(sizeof(unsigned char) * xlen);
	}

	for(int i = 0; i < ylen; ++i)
		for(int j = 0; j < xlen; ++j){
			unsigned char buf[3];
			fread(buf, 3, 1, fin);
			R[i][j] = buf[0];
			G[i][j] = buf[1];
			B[i][j] = buf[2];
		}

	printf("1)平均值滤波\n2)拉普拉斯锐化\n");
	int id = 0;
	scanf("%d", &id);
	
	if(id == 1){
		conv_avg(R, xlen, ylen, 7, 7);
		conv_avg(G, xlen, ylen, 7, 7);
		conv_avg(B, xlen, ylen, 7, 7);
	}else if(id == 2){
		lap(R, xlen, ylen);
		lap(G, xlen, ylen);
		lap(B, xlen, ylen);
	}

	for(int i = 0; i < ylen; ++i)
		for(int j = 0; j < xlen; ++j){
			fwrite(&R[i][j], 1, 1, fout);
			fwrite(&G[i][j], 1, 1, fout);
			fwrite(&B[i][j], 1, 1, fout);
		}

	fclose(fout);
	system("pause");
	return 0;
}