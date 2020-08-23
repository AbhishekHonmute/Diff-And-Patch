#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<strings.h>
#include<errno.h>
#include<time.h>

int f1, f2, i = 0, status;
char file[20], ch, ch1, line[40];

int main(int argc, char *argv[]) {	
	
	f1 = open(argv[1], O_RDONLY );
	if(f1 == -1) {
		printf("file1 canot open\n");
		return 0;
	}
	read(f1, &ch, 1);
	if(read(f1, &ch, 1) == 0) {
		
		return 0;
	}
	lseek(f1, 4, SEEK_SET);
	read(f1, &ch, 1);
	while(ch != ' ') {
		file[i] = ch;
		i ++;
		read(f1, &ch, 1);
	}
	status = remove(file);
	f2 = open(file, O_CREAT | O_WRONLY, S_IWUSR | S_IRUSR);
	if(f2 == -1) {
		printf("file2 canot open\n");
		return 0;
	}
	if(read(f1, &ch, 1) == 0) {
		printf("hey you\n");
		return 0;
	}
	while(1) {
		if(ch == '-') {
			read(f1, &ch, 1);
			if(ch == '-') {
				read(f1, &ch, 1);
				if(ch == '-') {
					read(f1, &ch, 1);
					if(ch == '-') {
						break;
					}
				}
			}
		}
		read(f1, &ch, 1);
	}
	read(f1, &ch, 1);
	if(read(f1, &ch, 1) == 0) {
		printf("patching file %s\n", file);
		lseek(f1, 0, SEEK_SET);
		read(f1, &ch, 1);
		for(i = 0; i < 4; i ++){
			while(ch != '\n') {
				read(f1, &ch, 1);
			}
			read(f1, &ch, 1);
		}
		read(f1, &ch1, 1);
		while(ch1 != '-'){
			if(ch != '-') {
				read(f1, &ch, 1);
				while(ch != '\n') {
					write(f2, &ch, 1);
					read(f1, &ch, 1);
				}
				write(f2, &ch, 1);
				read(f1, &ch, 1);
				read(f1, &ch1, 1);
			}
			else {
				while(ch != '\n') {
					read(f1, &ch, 1);
				}
				read(f1, &ch, 1);
				read(f1, &ch1, 1);
			}
		}
	}
	else {
		printf("patching file %s\n", file);
		lseek(f1, 0, SEEK_SET);
		read(f1, &ch, 1);
		while(1) {
			if(ch == '-') {
				read(f1, &ch, 1);
				if(ch == '-') {
					read(f1, &ch, 1);
					if(ch == '-') {
						read(f1, &ch, 1);
						if(ch == '-') {
							break;
						}
					}
				}
			}
			read(f1, &ch, 1);
		}
		read(f1, &ch, 1);
		while(read(f1, &ch, 1) != 0) {	
			read(f1, &ch, 1);
			read(f1, &ch, 1);
			while(ch != '\n') {
				write(f2, &ch, 1);
				read(f1, &ch, 1);
			}
			write(f2, &ch, 1);
			
		}
	}
	
	close(f1);
	close(f2);

	return 0;
}
