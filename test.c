#include<stdio.h>
#include<unistd.h>
int main(int argc, char* argv[]){
	int n;
	extern char* optarg;
	extern int optind;

	printf("current optind : %d\n", optind);

	while((n = getopt(argc, argv, "ab:c")) != -1){
		switch(n){
			case 'a':
				printf("option : a\n");
				break;
			case 'b':
				printf("option : b, arguments = %s\n", optarg);
				break;
			case 'c':
				printf("option : c\n");
				break;
		}
		printf("next optind : %d\n", optind);
	}
}