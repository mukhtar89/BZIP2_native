#include "driver.h"

bool decompress(char *fn_r, char *fn_w, int level)
{
	int len;
	char buff[0x1000];
	char mode[10];

	BZFILE *BZ2fp_r = NULL;
	FILE *fp_w = NULL;

	if (fn_w){
		if ((fp_w = fopen(fn_w, "wb")) == NULL){
			printf("can't open [%s]\n", fn_w);
			perror("reason:");
			return false;
		}
	}
	else{
		fp_w = stdout;
	}
	if ((fn_r == NULL && (BZ2fp_r = BZ2_bzdopen(_fileno(stdin), "rb")) == NULL)
		|| (fn_r != NULL && (BZ2fp_r = BZ2_bzopen(fn_r, "rb")) == NULL)){
		printf("can't bz2openstream\n");
		return false;
	}
	while ((len = BZ2_bzread(BZ2fp_r, buff, 0x1000))>0){
		fwrite(buff, 1, len, fp_w);
	}
	BZ2_bzclose(BZ2fp_r);
	if (fp_w != stdout) fclose(fp_w);

	return true;
}

bool compress(char *fn_r, char *fn_w, int level)
{
	int len;
	char buff[0x1000];
	char mode[10];

	BZFILE *BZ2fp_w = NULL;
	FILE *fp_r = NULL;

	if (fn_r){
		if ((fp_r = fopen(fn_r, "rb")) == NULL){
			printf("can't open [%s]\n", fn_r);
			perror("reason:");
			return false;
		}
	}
	else{
		fp_r = stdin;
	}
	mode[0] = 'w';
	mode[1] = '0' + level;
	mode[2] = '\0';

	if ((fn_w == NULL && (BZ2fp_w = BZ2_bzdopen(_fileno(stdout), mode)) == NULL)
		|| (fn_w != NULL && (BZ2fp_w = BZ2_bzopen(fn_w, mode)) == NULL)){
		printf("can't bz2openstream\n");
		return false;
	}
	while ((len = fread(buff, 1, 0x1000, fp_r))>0){
		BZ2_bzwrite(BZ2fp_w, buff, len);
	}
	BZ2_bzclose(BZ2fp_w);
	if (fp_r != stdin)fclose(fp_r);
	
	return true;
}
