#include <stdlib.h>
#include <stdio.h>

int main(void){
	FILE *in;
	extern FILE *popen();
	char buff[512];

	/*
	 * popen creates a pipe so we can read the output of the program we are
	 * invoking
	 */
	if((in = popen("netstat -n", "r")) == 0){
		perror("popen");
		exit(1);
	}

	/*
	 * read the output of netstat, one line at a time
	 */
	while(fgets(buff, sizeof(buff), in) != NULL ){
		printf("Output: %s", buff);
	}

	/*
	 * close the pipe
	 */
	pclose(in);
	return 0;
}
