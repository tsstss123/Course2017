#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char in[] = "input.bmp", out[] = "output.bmp";
#define BUFSIZE 10000000
unsigned char head_buf[100], reflect[256];
int gray_cnt[256], pix_cnt;
double pix_percent[256];
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

	unsigned char *pic_buf = (unsigned char*)malloc(sizeof(unsigned char[BUFSIZE]));
	int buf_len = 0;
	while(!feof(fin)){
		unsigned char buf[10];
		fread(buf, 3, 1, fin);
		int val = (1.0 + buf[0] + buf[1] + buf[2]) / 3;
		pic_buf[buf_len++] = val;
		gray_cnt[val] += 1;
		pix_cnt += 1;
	}

	for(int i = 0, sum = 0; i < 256; ++i){
		sum += gray_cnt[i];
		double pix_percent = 1.0 * sum / pix_cnt;
		reflect[i] = int(floor(pix_percent * 255 + 0.5)); 
	}

	//for(int i = 0; i < 256; ++i)if(reflect[i] == 0 && i)
		//reflect[i] = reflect[i - 1];

	for(int i = 0; i < buf_len; ++i){
		unsigned char newpix = reflect[pic_buf[i]];
		fwrite(&newpix, 1, 1, fout);
		fwrite(&newpix, 1, 1, fout);
		fwrite(&newpix, 1, 1, fout);
	}

	fclose(fout);
	return 0;
}