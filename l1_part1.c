#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <ctype.h>

void writing(int size,FILE*f1,FILE*f2,int block,char symbols[block]){
	for(int i=0;i<size;i+=10){
		if(size-i<block)block =size-i;
		fread(symbols,sizeof(char),block,f1);
		for(int i=0;i<block;i++){
			if(isalpha(symbols[i])&&((int)symbols[i]>96)&&((int)symbols[i]<123))
				symbols[i]=(char)((int)symbols[i]-32);
			printf("%c",symbols[i]);
		}
		printf("\nnumber of bytes what were wrote: %d\n",block);
		fwrite(symbols,sizeof(char),block,f2);
	}
}

int main(){
	FILE *f1,*f2;
	int sf2,block = 10;
	if((f1 = fopen("txt1","rt"))== NULL)	printf ("Error opening file txt1: %s\n",strerror(errno));
	if((sf2 =creat("txt2",0644)) == -1 )	printf ("Error opening or creating file txt2: %s\n",strerror(errno));
	if((f2 = fopen("txt2","wt"))== NULL)	printf ("Error opening file txt2: %s\n",strerror(errno));
	char symbols[block];
        fseek(f1, 0, 2);
        int size = ftell(f1) - 1;
        printf("The size of given file is : %d\n", size);
	fseek(f1, 0, 0);
	writing(size,f1,f2,block,symbols);
        int size2 = ftell(f2);
        printf("total number of bytes what were wrote: %d\n", size2);
	return 0;
}
