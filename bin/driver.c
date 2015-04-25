#include "driver.h"

int BZ2DLLLoadLibrary(void)
{
	HINSTANCE hLib;

	if (BZ2DLLLoaded == 1){ _getch(); return 0; }
	hLib = LoadLibrary(_T(BZ2_LIBNAME));
	if (hLib == NULL){
		fprintf(stderr, "Can't load %s\n", BZ2_LIBNAME);
		_getch();
		return -1;
	}
	BZ2_bzlibVersion = GetProcAddress(hLib, "BZ2_bzlibVersion");
	BZ2_bzopen = GetProcAddress(hLib, "BZ2_bzopen");
	BZ2_bzdopen = GetProcAddress(hLib, "BZ2_bzdopen");
	BZ2_bzread = GetProcAddress(hLib, "BZ2_bzread");
	BZ2_bzwrite = GetProcAddress(hLib, "BZ2_bzwrite");
	BZ2_bzflush = GetProcAddress(hLib, "BZ2_bzflush");
	BZ2_bzclose = GetProcAddress(hLib, "BZ2_bzclose");
	BZ2_bzerror = GetProcAddress(hLib, "BZ2_bzerror");

	if (!BZ2_bzlibVersion || !BZ2_bzopen || !BZ2_bzdopen
		|| !BZ2_bzread || !BZ2_bzwrite || !BZ2_bzflush
		|| !BZ2_bzclose || !BZ2_bzerror) {
		fprintf(stderr, "GetProcAddress failed.\n");
		_getch();
		return -1;
	}
	BZ2DLLLoaded = 1;
	BZ2DLLhLib = hLib;
	return 0;

}

int BZ2DLLFreeLibrary(void)
{
	if (BZ2DLLLoaded == 0){ return 0; }
	FreeLibrary(BZ2DLLhLib);
	BZ2DLLLoaded = 0;
}


bool init()
{
#ifdef _WIN32
	if (BZ2DLLLoadLibrary()<0){
		fprintf(stderr, "Loading of %s failed.  Giving up.\n", BZ2_LIBNAME);
		return false;
	}
	printf("Loading of %s succeeded.  Library version is %s.\n",
		BZ2_LIBNAME, BZ2_bzlibVersion());
#endif
	return true;
}

bool destroy()
{
#ifdef _WIN32
   BZ2DLLFreeLibrary();
#endif
	return true;
}

bool decompress(char *fn_r, char *fn_w, int level)
{
	int len;
	char buff[0x1000];
	char mode[10];
	bool status = true;
	
	status = init();

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
	
	status = destroy();
	return status;
}

bool compress(char *fn_r, char *fn_w, int level)
{
	int len;
	char buff[0x1000];
	char mode[10];
	bool status = true;
	
	status = init();

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
	
	status = destroy();
	return status;
}
