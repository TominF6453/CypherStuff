#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getUpperCase(char c) {
	if (c >= 'a') {
		return c - 32;
	} else {return c;}
}

int main(int argc, char* argv[]) {
	if ((argc != 3) || (argv[1][0] != 'd' && argv[1][0] != 'e')) {
		printf("Usage: cypher1 (d/e) (path)\n -> d - decrypt the file\n -> e - encrypt the file\n -> path - the file");
		return 1;
	}
	// File IO time
	FILE *fpr;
	FILE *fpw;

	fpr = fopen(argv[2], "r");
	if (!fpr) { 
		printf("File does not exist.");
		return 1;
	}
	char outpath[256];
	sprintf(&outpath, "%s%s", argv[2], ".out");
	fpw = fopen(outpath, "w");

	fseek(fpr, 0, SEEK_END);
	long len = ftell(fpr);
	fseek(fpr, 0, SEEK_SET);
	char *buf = (char *)malloc(len+1);
	buf[len] = 0;
	fread(buf, 1, len, fpr);
	fclose(fpr);

	// Files open, find whether to encrypt or decrypt.
	for (int i = 0; i < len; i++) {
		char a = buf[i];
		char b = buf[len - 1 - i];
	}
}
