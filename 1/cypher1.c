#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getUpperCase(char c) {
	if (c >= 'c') {
		return c - 32;
	} else {return c;}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: cypher1 (path)\n -> path - the file");
		return 1;
	}
	// File IO time
	FILE *fpr;
	FILE *fpw;

	fpr = fopen(argv[1], "r");
	if (!fpr) { 
		printf("File does not exist.");
		return 1;
	}
	char outpath[256];
	sprintf(&outpath, "%s%s", argv[1], ".out");
	fpw = fopen(outpath, "w");

	fseek(fpr, 0, SEEK_END);
	long len = ftell(fpr);
	fseek(fpr, 0, SEEK_SET);
	char *buf = (char *)malloc(len+1);
	buf[len] = '\0';
	fread(buf, 1, len, fpr);
	fclose(fpr);

	//printf("%s\n", buf);

	// Files open, find whether to encrypt or decrypt.
	char *a, *b;
	for (int i = 0; i < len/2; i++) {
		a = &(buf[i]);
		b = &(buf[len - 2 - i]);
		*a = getUpperCase(*a);
		*b = getUpperCase(*b);
		//printf("a = %c-%d | b = %c-%d\n", *a,*a,*b,*b);
		if (a == b) break;
		// Get tens and ones slot from a and b and swap them. ex. 65 ----- 92 -> 29 ----- 56
		int a1 = *a % 10;
		int a10 = *a / 10;
		int b1 = *b % 10;
		int b10 = *b / 10;

		*a = b1 * 10 + b10;
		*b = a1 * 10 + a10;
		//printf("a = %c-%d | b = %c-%d\n", *a,*a,*b,*b);
	}

	fwrite(buf, 1, len, fpw);
	fclose(fpw);
	return 0;
}
