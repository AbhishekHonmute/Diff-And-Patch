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
#include<dirent.h>
#define SIZE 2500
#define LINE 200
int loop = 0;
char ops[8], opt;	
int opn;

void print(char fl1[SIZE][LINE], char b[SIZE][LINE], char ans[SIZE][LINE], int i,int j, int *q) {
	if(i==0 || j==0) {
		return;
	}
	if(b[i][j]=='c'){
         	print(fl1, b, ans, i-1, j-1, q);
        	strcpy(ans[*q], fl1[i-1]);
        	(*q) ++;
	}
	else if(b[i][j]=='u') {
		print(fl1, b, ans, i-1, j, q);
	}
	else {
		print(fl1, b, ans, i, j-1, q);
	}
	return;
}

void flcs(char ans[SIZE][LINE], char fl1[SIZE][LINE], char fl2[SIZE][LINE], char b[SIZE][LINE], int c[SIZE][LINE], int m, int n, int *q) {	
	int i, j;
	
	for(i=0;i<=m;i++) {
		c[i][0]=0;
	}
	for(i=0;i<=n;i++) {
		c[0][i]=0; 
	}                     
	//c, u and l denotes cross, upward and left directions respectively
	
	for(i=1;i<=(m +1);i++) {	
		for(j=1;j<=(n + 1);j++) {
 			if(strcmp(fl1[i-1], fl2[j-1]) == 0) {
                         	c[i][j]=c[i-1][j-1]+1;
                        	b[i][j]='c';
                	}
                 	else if(c[i-1][j]>=c[i][j-1]) {
                        	c[i][j]=c[i-1][j];
                        	b[i][j]='u';
                 	}
                 	else {
                   		c[i][j]=c[i][j-1];
                      		b[i][j]='l';
                    	}
          	}
  	}
  	print(fl1, b, ans, m +1, n +1, q);
}

void copystr(char fl1[SIZE][LINE], char l1[SIZE][LINE], char fl2[SIZE][LINE], char l2[SIZE][LINE], int m, int n) {
	int i;
	for(i = 0; i <= m; i ++) {
		strcpy((fl1)[i], (l1)[i]);
	}
	for(i = 0; i <= n; i ++) {
		strcpy((fl2)[i], (l2)[i]);
	}
}

void removespace(char fl1[SIZE][LINE], char fl2[SIZE][LINE], int m, int n) {
	int i, j, k;
	for(i = 0; i <= m; i ++) {
		j = 0;
		while(fl1[i][j] != '\0'){
			if(fl1[i][j] == ' ') {
				k = j;
				while(fl1[i][k - 1] != '\0') {
					fl1[i][k] = fl1[i][k +1];
					k ++;
				}
				fl1[i][k] = fl1[i][k +1];
			}
			else {
				j ++;
			}	
		}
	}
	for(i = 0; i <= n; i ++) {
		j = 0;
		while(fl2[i][j] != '\0'){
			if(fl2[i][j] == ' ') {
				k = j;
				while(fl2[i][k - 1] != '\0') {
					fl2[i][k] = fl2[i][k +1];
					k ++;
				}
				fl2[i][k] = fl2[i][k +1];
			}
			else {
				j ++;
			}
		}
	}
}

void spacenext1(char fl1[SIZE][LINE], int i, int j) {
	int sp = 0, k = 0;
	if(fl1[i][j] == '\0') {
		return;
	}
	else if (fl1[i][j] != ' ') {
		j ++;
		sp = 1;
		spacenext1(fl1, i, j);
	}
	else {
		if(sp == 1) {
			j ++;
		}
		if(fl1[i][j] == ' ') {
			k = j - 1;
			while(fl1[i][k + 1] != '\0') {
				fl1[i][k] = fl1[i][k +1];
				k ++;
			}
			fl1[i][k] = fl1[i][k +1];
			sp = 2; 
		}
		spacenext1(fl1, i, j);
	}
}

void spacenext2(char fl2[SIZE][LINE], int i, int j) {
	int sp = 0, k = 0;
	if(fl2[i][j] == '\0') {
		return;
	}
	else if (fl2[i][j] != ' ') {
		j ++;
		sp = 1;
		spacenext2(fl2, i, j);
	}
	else {
		if(sp == 1) {
			j ++;
		}
		if(fl2[i][j] == ' ') {
			k = j - 1;
			while(fl2[i][k + 1] != '\0') {
				fl2[i][k] = fl2[i][k +1];
				k ++;
			}
			fl2[i][k] = fl2[i][k +1];
			sp = 2;
		}
		spacenext2(fl2, i, j);
	}
}

void multspace(char fl1[SIZE][LINE], char fl2[SIZE][LINE], int m, int n) {
	int i = 0, j =0;
	for(i = 0; i <= m; i ++) {
		j = 0;
		spacenext1(fl1, i, j);
	}
	for(i = 0; i <= n; i ++) {
		j = 0;
		spacenext2(fl2, i, j);
	}
}

void tabspace(char l1[SIZE][LINE], char l2[SIZE][LINE], int m, int n) {
	int i = 0, j = 0, k = 0, sp = 0;
	for(i = 0; i <= m; i ++) {
		sp = strlen(l1[i]);
		j = 0;
		while(l1[i][j] != '\0') {
			if(l1[i][j] == '\t') {
				//printf("hey\n");
				for(k = sp; k >= j; k --) {
					l1[i][k + 7] = l1[i][k];
					//printf("%c\n", l1[i][k + 8]);
				}
				sp = sp + 7;
				l1[i][sp] = '\0';
				for(k = j;k < j + 8; k ++) {
					l1[i][k] = ' ';
					//printf("non\n");
				}
				j = j + 7;
			}
			j ++;
		}
	}
	for(i = 0; i <= n; i ++) {
		sp = strlen(l2[i]);
		j = 0;
		while(l2[i][j] != '\0') {
			if(l2[i][j] == '\t') {
				//printf("hey\n");
				for(k = sp; k >= j; k --) {
					l2[i][k + 7] = l2[i][k];
					//printf("%c\n", l1[i][k + 8]);
				}
				sp = sp + 7;
				l2[i][sp] = '\0';
				for(k = j;k < j + 8; k ++) {
					l2[i][k] = ' ';
					//printf("non\n");
				}
				j = j + 7;
			}
			j ++;
		}
	}
}

void casediff(char fl1[SIZE][LINE], char fl2[SIZE][LINE], int m, int n) {
	int i = 0, j = 0;
	for(i = 0; i<= m; i ++) {
		j = 0;
		while(fl1[i][j] != '\0') {
			if((fl1[i][j] > 64) && (fl1[i][j] < 91)) {
				fl1[i][j] = fl1[i][j] + 32;
			}
			j ++;
		}
	}
	for(i = 0; i<= n; i ++) {
		j = 0;
		while(fl2[i][j] != '\0') {
			if((fl2[i][j] > 64) && (fl2[i][j] < 91)) {
				fl2[i][j] = fl2[i][j] + 32;
			}
			j ++;
		}
	}
}

void diff(char filename1[40], char filename2[40]) {	
	char l1[SIZE][LINE], l2[SIZE][LINE], ans[SIZE][LINE], fn[2][40], blank[60] = " ";
	char line[LINE], fl1[SIZE][LINE], fl2[SIZE][LINE], ch, b[SIZE][LINE];
	int c[SIZE][LINE], f1, f2, i = 0, j = 0, k = 0, m = -1 , n = -1, jp, kp, t, p, q = 0;
	
	strcpy(fn[0], filename1);
	strcpy(fn[1], filename2);
	if(loop != 0) {
		printf("diff %s %s\n", fn[0], fn[1]);
	}
	
	f1 = open(fn[0], O_RDONLY );
	if(f1 == -1) {
		printf("diff: %s: No such file or directory\n", fn[0]);
		return;
	}
	f2 = open(fn[1], O_RDONLY );
	if(f2 == -1) {
		printf("diff: %s: No such file or directory\n", fn[1]);
		return;
	}
	
	/*if(f1 == 0) {
		printf("f1=%s  f2=%s\n", fn[0], fn[1]);
		return;
	}*/
	
	i = 0;
	while(read(f1, &ch, 1)) {	
		j = 0;
		while(ch != '\n' && ch != EOF) {
			line[j] = ch;
			j ++;
			read(f1, &ch, 1);
		}
		line[j] = '\0';
		strcpy(l1[i], line);
		m = i;
		i ++;
	}
	l1[i][j] = '\0';
	
	i = 0;
	while(read(f2, &ch, 1)) {	
		j = 0;
		while(ch != '\n' && ch != EOF) {	
			line[j] = ch;
			j ++;
			read(f2, &ch, 1);
		}
		line[j] = '\0';
		strcpy(l2[i], line);
		n = i;
		i ++;
	}
	l2[i][j] = '\0';
	i = 0;
	copystr(fl1, l1, fl2, l2, m, n);
	for(i = 0; i <= opn; i ++) {
		if(ops[i] == 'w'){
			removespace(fl1, fl2, m, n);
		}
		else if(ops[i] == 'b'){
			multspace(fl1, fl2, m, n);
		}
		else if(ops[i] == 't'){
			tabspace(l1, l2, m, n);
		}
		else if(ops[i] == 'i') {
			casediff(fl1, fl2, m, n);
		}
	}
	//printf("%d %d\n", m, n);
	flcs(ans, fl1, fl2, b, c, m, n, &q);
	/*printf("\n\n");
	for(i = 0; i <= m; i++) {	
		printf("%s\n", fl1[i]);
	}
	for(i = 0; i <= n; i++) {	
		printf("%s\n", fl2[i]);
	}
	printf("\n\n");*/
	
	close(f1);
	close(f2);
	if(q == 0) {
		return;
	}
	switch(opt) {	
		case'z': {	
			i = 0;
			j = 0;
			k = 0;
			jp = -1;
			kp = -1;
			if(m == -1) {	
				if(n == -1) {	
				}
				else if(n == 0){	
					printf("%da%d\n", m + 1, n + 1);
					printf("> %s\n", l2[0]);
				}
				else{	
					printf("%da%d,%d\n", m + 1, kp + 2, n +1);
					k = n;
					for(t = (kp + 1); t <= k; t ++) {	
						printf("> %s\n", l2[t]);
					}
				}
				return;
			}
			for(i = 0; i < q; i++) {	
				while(strcmp(fl1[j], ans[i]) != 0) {	
					j++;
				}
				while(strcmp(fl2[k], ans[i]) != 0) {	
					k++;
				}
				//printf("f1 %d f2 %d\n", j, k);
				if((k - kp) == 1) {	
					if((jp +2) == j) {	
						printf("%dd%d\n", (jp + 2), k);
						printf("< %s\n", l1[(jp + 1)]);
					}
					else if((jp + 2) < j) {	
						printf("%d,%dd%d\n", (jp + 2), j, k);
						for(t = (jp + 1); t < j; t ++) {	
							printf("< %s\n", l1[t]);
						}
					}
				}
				else if((j - jp) == 1) {	
					if((kp +2) == k) {	
						printf("%da%d\n", (jp + 1), k);
						printf("> %s\n", l2[(kp + 1)]);
					}
					else if((kp + 2) < k) {	
						printf("%da%d,%d\n", (jp + 1), (kp + 2), (k));
						for(t = (kp + 1); t < k; t ++) {	
							printf("> %s\n", l2[t]);
						}
					}
				}
				else {	
					if(((jp +2) == j) && ((kp +2) == k)) {
						printf("%dc%d\n", (jp + 2), (kp + 2));
						printf("< %s\n---\n> %s\n", l1[jp + 1], l2[kp + 1]);
					}
					else if(((jp +2) == j) && ((kp +2) != k)){
						printf("%dc%d,%d\n", (jp + 2), (kp + 2), k);
						printf("< %s\n---\n", l1[jp + 1]);
						for(t = (kp + 1); t < k; t ++) {
							printf("> %s\n", l2[t]);
						}
					}
					else if(((jp +2) != j) && ((kp +2) == k)) {
						printf("%d,%dc%d\n", (jp + 2), j, (kp + 2));
						for(t = (jp + 1); t < j; t ++) {
							printf("< %s\n", l1[t]);
						}
						printf("---\n> %s\n", l2[kp + 1]);
					}
					else {
						printf("%d,%dc%d,%d\n", (jp + 2), j, (kp + 2), k);
						for(t = (jp + 1); t < j; t ++) {
							printf("< %s\n", l1[t]);
						}
						printf("---\n");
						for(t = (kp + 1); t < k; t ++) {
							printf("> %s\n", l2[t]);
						}
					}
					
				}
				kp = k;
				jp = j;
				j++;
				k++;
			}
			j = m + 1;
			k = n + 1;
			if((k - kp) == 1) {
				if((jp +2) == j) {
					printf("%dd%d\n", (jp + 2), k);
					printf("< %s\n", l1[(jp + 1)]);
				}
				else if((jp + 2) < j) {
					printf("%d,%dd%d\n", (jp + 2), j, k);
					for(t = (jp + 1); t < j; t ++) {
						printf("< %s\n", l1[t]);
					}
				}
			}
			else if((j - jp) == 1) {
				if((kp +2) == k) {
					printf("%da%d\n", (jp + 1), k);
					printf("> %s\n", l2[(kp + 1)]);
				}
				else if((kp + 2) < k) {
					printf("%da%d,%d\n", (jp + 1), (kp + 2), (k));
					for(t = (kp + 1); t < k; t ++) {
						printf("> %s\n", l2[t]);
					}
				}
			}
			else {
				if(((jp +2) == j) && ((kp +2) == k)) {
					printf("%dc%d\n", (jp + 2), (kp + 2));
					printf("< %s\n---\n> %s\n", l1[jp + 1], l2[kp + 1]);
				}
				else if(((jp +2) == j) && ((kp +2) != k)) {
					printf("%dc%d,%d\n", (jp + 2), (kp + 2), k);
					printf("< %s\n---\n", l1[jp + 1]);
					for(t = (kp + 1); t < k; t ++) {
						printf("> %s\n", l2[t]);
					}
				}
				else if(((jp +2) != j) && ((kp +2) == k)) {
					printf("%d,%dc%d\n", (jp + 2), j, (kp + 2));
					for(t = (jp + 1); t < j; t ++) {
						printf("< %s\n", l1[t]);
					}
					printf("---\n> %s\n", l2[kp + 1]);
				}
				else {
					printf("%d,%dc%d,%d\n", (jp + 2), j, (kp + 2), k);
					for(t = (jp + 1); t < j; t ++) {
						printf("< %s\n", l1[t]);
					}
					printf("---\n");
					for(t = (kp + 1); t < k; t ++) {
						printf("> %s\n", l2[t]);
					}
				}
				
			}
			break;
		}
		case'y':{
			i = 0;
			j = 0;
			k = 0;
			jp = -1;
			kp = -1;
			if(m == -1) {	
				if(n == -1) {
					return;
				}
				for(t = 0; t <= n; t ++) {	
					printf("%-62s> %s\n", blank, l2[t]);
				}
				return;
			}
			else if(n == -1) {
				for(t = 0; t <= m; t ++) {
					printf("%-62s< %s\n", l1[t], blank);
				}
				return;
			}
			for(i = 0; i < q; i++) {	
				while(strcmp(l1[j], ans[i]) != 0) {	
					j++;
				}
				while(strcmp(l2[k], ans[i]) != 0) {	
					k++;
				}
				//printf("f1 %d f2 %d\n", j, k);
				
				if((k - kp) == 1) {	
					for(t = (jp + 1); t < j; t ++) {
						printf("%-62s< %s\n", l1[t], blank);
					}
				}
				else if((j - jp) == 1) {	
					for(t = (kp + 1); t < k; t ++) {
						printf("%-62s> %s\n", blank, l2[t]);
					}
				}
				else {	
					if((j - jp) > (k - kp)) {
						p = 1;
						for(t = (kp + 1); t < k; t ++) {
							printf("%-62s| %s\n", l1[jp + p], l2[t]);
							p ++;
						}
						for(t = (jp + p); t < j; t ++) {
							printf("%-62s< %s\n", l1[t], blank);
						}
					}
					else if((j - jp) < (k - kp)) {
						p = 1;
						for(t = (jp + 1); t < j; t ++) {
							printf("%-62s| %s\n", l1[t], l2[kp + p]);
							p ++;
						}
						for(t = (kp + p); t < k; t ++) {
							printf("%-62s< %s\n", blank, l2[t]);
						}
					}
					else {
						p = 1;
						for(t = (jp + 1); t < j; t ++) {
							printf("%-62s| %s\n", l1[t], l2[kp + p]);
							p ++;
						}
					}
				}
				kp = k;
				jp = j;
				j++;
				k++;
				printf("%-62s  %s\n", ans[i], ans[i]);
			}
			j = m + 1;
			k = n + 1;
			if((k - kp) == 1) {	
				for(t = (jp + 1); t < j; t ++) {
					printf("%-62s< %s\n", l1[t], blank);
				}
			}
			else if((j - jp) == 1) {	
				for(t = (kp + 1); t < k; t ++) {
					printf("%-62s> %s\n", blank, l2[t]);
				}
			}
			else {	
				if((j - jp) > (k - kp)) {
					p = 1;
					for(t = (kp + 1); t < k; t ++) {
						printf("%-62s| %s\n", l1[jp + p], l2[t]);
						p ++;
					}
					for(t = (jp + p); t < j; t ++) {
						printf("%-62s< %s\n", l1[t], blank);
					}
				}
				else if((j - jp) < (k - kp)) {
					p = 1;
					for(t = (jp + 1); t < j; t ++) {
						printf("%-62s| %s\n", l1[t], l2[kp + p]);
						p ++;
					}
					for(t = (kp + p); t < k; t ++) {
						printf("%-62s< %s\n", blank, l2[t]);
					}
				}
				else {
					p = 1;
					for(t = (jp + 1); t < j; t ++) {
						printf("%-62s| %s\n", l1[t], l2[kp + p]);
						p ++;
					}
				}
			}
			break;
		}
		case'c':{
			struct stat buff1, buff2;
			stat(fn[0], &buff1);
			stat(fn[1], &buff2);
			i = 0;
			j = 0;
			k = 0;
			jp = -1;
			kp = -1;
			if((m == n) && (m == (q - 1))) {
				return;
			}
			if(m == -1) {
				if(n == -1) {
					
				}
				else if(n == 0) { 
					printf("*** %s   %s", fn[0], ctime(&buff1.st_mtime));
					printf("--- %s   %s", fn[1], ctime(&buff2.st_mtime));
					printf("***************\n");
					printf("*** %d ****\n", m + 1);
					printf("--- %d ----\n", n + 1);
					printf("+ %s\n", l2[n]);
				}
				else{ 
					printf("*** %s   %s", fn[0], ctime(&buff1.st_mtime));
					printf("--- %s   %s", fn[1], ctime(&buff2.st_mtime));
					printf("***************\n");
					printf("*** %d ****\n", m + 1);
					printf("--- %d,%d ----\n", kp + 2, n + 1);
					for(t = (kp + 1); t <= n; t ++) {
						printf("+ %s\n", l2[t]);
					}
				}
				return;
			}
			if(m == 0) {
				printf("*** %s   %s", fn[0], ctime(&buff1.st_mtime));
				printf("--- %s   %s", fn[1], ctime(&buff2.st_mtime));
				printf("***************\n");
				if(n == -1) {
					printf("*** %d ****\n", m + 1);
					printf("- %s\n", l1[m]);
					printf("--- %d ----\n", n + 1);
					return;
				}
				else if(n == 0){
					printf("*** %d ****\n", m + 1);
					printf("! %s\n", l1[m]);
					printf("--- %d ----\n", n + 1);
					printf("! %s\n", l2[n]);
					return;
				}
				else {
					printf("*** 1 ****\n");
					for(i = 0; i < q; i++) {
						while(strcmp(l1[j], ans[i]) != 0) {
						 	j++;
						}
						while(strcmp(l2[k], ans[i]) != 0) {
							k++;
						}
						//printf("f1 %d f2 %d\n", j, k);
						if((k - kp) == 1) {
							for(p = (jp + 1); p < j; p ++) {
								printf("- %s\n", l1[p]);
							}
						}
						else {
						 	for(p = (jp + 1); p < j; p ++) {
						 		printf("! %s\n", l1[p]);
							}
							
						}
						printf("  %s\n", l1[j]);
						kp = k;
						jp = j;
						j++;
						k++;
					}
					j = m + 1;
					k = n + 1;
					if((k - kp) == 1) {
						for(p = (jp + 1); p <= m; p ++) {
							printf("- %s\n", l1[p]);
						}
					}
					else {
						for(p = (jp + 1); p <= m; p ++) {
							printf("! %s\n", l1[p]);
						}
						
					}
					
					printf("--- 1,%d ----\n", n + 1);
					if((n + 1) == q) {
						break;
					}
					
					
					j = 0;
					k = 0;
					jp = -1;
					kp = -1;
					for(i = 0; i < q; i++) {
						while(strcmp(l1[j], ans[i]) != 0) {
							j++;
						}
						while(strcmp(l2[k], ans[i]) != 0) {
							k++;
						}
						//printf("f1 %d f2 %d\n", j, k);
						if((j - jp) == 1) {
							for(p = (kp + 1); p < k; p ++) {
								printf("+ %s\n", l2[p]);
							}
						}
						else {
						  	for(p = (kp + 1); p < k; p ++) {
						  		printf("! %s\n", l2[p]);
							}
							
						}
						printf("  %s\n", l1[j]);
						kp = k;
						jp = j;
						j++;
						k++;
					}
					j = m + 1;
					k = n + 1;
					if((j - jp) == 1) {
					
						for(p = (kp + 1); p <= n; p ++){	
							printf("+ %s\n", l2[p]);
						}
					}
					else {	
						for(p = (kp + 1); p <= n; p ++){	
							printf("! %s\n", l2[p]);
						}
					}
					return;	
				}
				
			}
			printf("*** %s   %s", fn[0], ctime(&buff1.st_mtime));
			printf("--- %s   %s", fn[1], ctime(&buff2.st_mtime));
			printf("***************\n");
			printf("*** 1,%d ****\n", m + 1);
			for(i = 0; i < q; i++) {
				while(strcmp(fl1[j], ans[i]) != 0) {
				 	j++;
				}
				while(strcmp(fl2[k], ans[i]) != 0) {
					k++;
				}
				//printf("f1 %d f2 %d\n", j, k);
				if((k - kp) == 1) {
					for(p = (jp + 1); p < j; p ++) {
						printf("- %s\n", l1[p]);
					}
				}
				else {
				 	for(p = (jp + 1); p < j; p ++) {
				 		printf("! %s\n", l1[p]);
					}
					
				}
				printf("  %s\n", l1[j]);
				kp = k;
				jp = j;
				j++;
				k++;
			}
			j = m + 1;
			k = n + 1;
			if((k - kp) == 1) {
				for(p = (jp + 1); p <= m; p ++) {
					printf("- %s\n", l1[p]);
				}
			}
			else {
				for(p = (jp + 1); p <= m; p ++) {
					printf("! %s\n", l1[p]);
				}
				
			}
			
			printf("--- 1,%d ----\n", n + 1);
			if((n + 1) == q) {
				break;
			}
			
			
			j = 0;
			k = 0;
			jp = -1;
			kp = -1;
			for(i = 0; i < q; i++) {
				while(strcmp(fl1[j], ans[i]) != 0) {
					j++;
				}
				while(strcmp(fl2[k], ans[i]) != 0) {
					k++;
				}
				//printf("f1 %d f2 %d\n", j, k);
				if((j - jp) == 1) {
					for(p = (kp + 1); p < k; p ++) {
						printf("+ %s\n", l2[p]);
					}
				}
				else {
				  	for(p = (kp + 1); p < k; p ++) {
				  		printf("! %s\n", l2[p]);
					}
					
				}
				printf("  %s\n", l1[j]);
				kp = k;
				jp = j;
				j++;
				k++;
			}
			j = m + 1;
			k = n + 1;
			if((j - jp) == 1) {
			
				for(p = (kp + 1); p <= n; p ++){	
					printf("+ %s\n", l2[p]);
				}
			}
			else {	
				for(p = (kp + 1); p <= n; p ++){	
					printf("! %s\n", l2[p]);
				}
			}
			
			
			break;
		}
		default: {
			printf("invalid argument\n");
			return;
			break;
		}
	}
	return;
}

void dire(char fn1[40], char fn2[40], char *argv[5], int argc, char get, int ar[2]) {	
	char dl1[SIZE][LINE], dl2[SIZE][LINE], temp[40], name1[40], name2[40];
	char input1[40], input2[40];
	int i = 0, j = 0, k = 0, m , n;
	//printf("loop:%d\n", loop);
	//printf("files        %s   %s\n", fn1, fn2);
	DIR *df1, *df2, *df3, *df4;
	struct dirent *d1, *d2;
	df1 = opendir(fn1);
	if(df1 != NULL) {
		df2 = opendir(fn2);
		if(df2 == NULL) {
			printf("diff: %s/%s: No such file or directory\n", fn1, fn2);
			return;
		}
		else {
			
			if(loop != 0) {	
				printf("diff %s %s\n", fn1, fn2);
			}
			i = 0;
			j = 0;
			while((d1 = readdir(df1)) != NULL) {
				if((d1->d_name)[0] == '.'){
					
				}
				else {
					strcpy(dl1[i], (d1->d_name));
					//printf("i= %d (d1 -> d_name) %s\n", i, dl1[i]);
					i ++;
					m = i;
				}
			}
			i = 0;
			j = 0;
			while((d2 = readdir(df2)) != NULL) {
				if((d2->d_name)[0] == '.'){
					
				}
				else {
					strcpy(dl2[i], (d2->d_name));
					//printf("i= %d (d2 -> d_name) %s\n", i, dl2[i]);
					i ++;
					n = i;
				}
			}
			for(i = 0; i < m; i ++) {
				strcpy(name1, dl1[i]);
				k = i;
				for(j = (i + 1); j <m; j ++) {
					if(strcmp(name1, dl1[j]) > 0) {
						k = j;
						strcpy(name1, dl1[j]);
					}
				}
				strcpy(temp, dl1[i]);
				strcpy(dl1[i], dl1[k]);
				strcpy(dl1[k], temp);
				//printf("i= %d sort1 %s\n", i, dl1[i]);
			}
			
			for(i = 0; i < n; i ++) {
				strcpy(name2, dl2[i]);
				k = i;
				for(j = (i + 1); j <n; j ++) {
					if(strcmp(name2, dl2[j]) > 0) {
						k = j;
						strcpy(name2, dl2[j]);
					}
				}
				strcpy(temp, dl2[i]);
				strcpy(dl2[i], dl2[k]);
				strcpy(dl2[k], temp);
				//printf("i= %d sort2 %s\n", i, dl2[i]);
			}
			/*for(i = 0; i < m; i++) {	
				printf("%s\n", dl1[i]);
			}
			for(i = 0; i < n; i++) {	
				printf("%s\n", dl2[i]);
			}
			printf("\n\n");*/
			i = 0;
			j = 0;
			strcpy(name1, dl1[i]);
			strcpy(name2, dl2[j]);
			input1[0] = '\0';
			input2[0] = '\0';
			while(1) {
				if(strcmp(name1, name2) == 0) {
					loop ++;
					for(k = 0; k < argc; k ++) {
						if(k == ar[0]) {
							sprintf(input1, "%s/%s", fn1, name1);
						}
						else if(k == ar[1]) {
							sprintf(input2, "%s/%s", fn2, name2);
						}
						else {
							
						}
					}
					df3 = opendir(input1);
					df4 = opendir(input2);
					
					if((df3 == NULL) && (df4 == NULL)){
						//printf("recur  %s   %s\n", input1, input2);
						loop ++;
						diff(input1, input2);
					}
					else if(df3 == NULL) {
						printf("File %s is a directory while file %s is a regular file\n", name2, name1);
					}
					else if(df4 == NULL){
						printf("File %s is a directory while file %s is a regular file\n", name1, name2);
					}
					else if((df3 != NULL) && (df4 != NULL)){
						printf("common subdirectories : %s and %s \n", input1, input2);
						if(get == 'r') {
							//printf("recur\n");
							dire(input1, input2, argv, argc, get, ar);
						}
					}
					i ++;
					j ++;
					//printf("i=%d  j=%d\n", i, j);
					strcpy(name1, dl1[i]);
					strcpy(name2, dl2[j]);
				}
				else if(strcmp(name1, name2) > 0) {
					printf("only in %s: %s\n", fn2, name2);
					j ++;
					strcpy(name2, dl2[j]);
				}
				else if(strcmp(name1, name2) < 0) {
					printf("only in %s: %s\n", fn1, name1);
					i ++;
					strcpy(name1, dl1[i]);
				}
				if((i == (m)) && (j == (n))) {
					break;
				}
				if(i == (m)) {
					for(k = j; k < n; k ++) {
						printf("only in %s: %s\n", fn2, dl2[k]);
					}
					break;
				}
				if(j == (n)) {
					for(k = i; k < m; k ++) {
						printf("only in %s: %s\n", fn1, dl1[k]);
					}
					break;
				}
				
			}
		return;
		}
	}
	diff(fn1, fn2);
	return;
}

int main(int argc, char *argv[]) {	
	
	char fn[2][40], get;
	int i = 0, j = 0, k = 0, sdf, ar[2];
	
	if(argc < 3) {	
		printf("insufficient arguments\n");
		return 0;
	}
	opt = 'z';
	strcpy(fn[0], argv[1]);
	strcpy(fn[1], argv[2]);
	k = 0;
	j = 0;
	sdf = 0;
	opn = -1;
	for(i = 1; i < argc; i++) {	
		if(argv[i][0] == '-') {	
			if((argv[i][1] == 'w') || (argv[i][1] == 'b') || (argv[i][1] == 't') || (argv[i][1] == 'i')) {
				opn = k;
				ops[k] = argv[i][1];
				k ++;
			}
			else if(argv[i][1] == 'r') {
				get = 'r';
			}
			else {
				if(sdf > 0) {
					printf("diff: conflecting output style option\ndiff:try 'diff --help' for more information\n");
					return 0;
				}
				opt = argv[i][1];
				sdf ++;
			}
		}
		else {
			strcpy(fn[j], argv[i]);
			ar[j] = i;
			j ++;
		}
	}
	ops[k] = '\0';
	dire(fn[0], fn[1], argv, argc, get, ar);
	return 0;
}

