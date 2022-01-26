//miniShell.c OS HW02:2015147543
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#define PROMPT "$"


int main(){
	char cmdline[BUFSIZ]; //User로부터 입력된 command line
	char* cmd_token[BUFSIZ]; // 스플릿시킨 command line을 저장하는 배열
	int i; // 루프를 위한 변수
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer); 
	pid_t pid;
	int file;
	int save_stdout = dup(1);
	int save_stdin = dup(0);
	int background = 0;
	while(1){
		dup2(save_stdout,1);
		dup2(save_stdin,0);
		printf("[%d:%d:%d]",t->tm_hour,t->tm_min,t->tm_sec); 
		printf("%s@%s%s",getenv("USER"),get_current_dir_name(), PROMPT); // 현재 디렉토리 $을 출력
		fgets(cmdline, sizeof(cmdline), stdin); // User로부터 command line 받아옴
		if(strchr(cmdline,'&')){ // background program
			background = 1;
			cmd_token[0] = strtok(cmdline,"&");
			strcpy(cmdline, cmd_token[0]);
		}
		if(strchr(cmdline,'<')){ // stdin redirection
			cmd_token[0] = strtok(cmdline, "<");	
			cmd_token[1] = strtok(NULL, "<");
			cmd_token[1] = strtok(cmd_token[1], " ");
			cmd_token[1] = strtok(cmd_token[1], "\n");
			strcpy(cmdline, cmd_token[0]);
			file = open(cmd_token[1], O_RDONLY);
			dup2(file,0);
			close(file);
		}
		else if(strchr(cmdline, '>')){ //stdout redirection
			cmd_token[0] = strtok(cmdline, ">");
			cmd_token[1] = strtok(NULL,">");
			cmd_token[1] = strtok(cmd_token[1], " ");
			cmd_token[1] = strtok(cmd_token[1], "\n");
			strcpy(cmdline, cmd_token[0]);
			file = open(cmd_token[1], O_WRONLY|O_CREAT|O_EXCL, 0644);
			dup2(file,1);
			close(file);	
		}
		cmd_token[0] = strtok(cmdline, " "); // 입력받은 command line을 스플릿 시키기		
		for(i=1; ; i++){
			cmd_token[i] = strtok(NULL, " ");
			if(cmd_token[i] == NULL) break;
		}
		if(strcmp(cmd_token[i-1], "\n") == 0) i--; // 명령어 끝에 공백 문자가 와도 무시
		else cmd_token[i-1] = strtok(cmd_token[i-1], "\n"); // 명렁어 끝에  공백 문자가 오지 않음
		if(strcmp(cmd_token[0], "exit") == 0) exit(1); // exit 입력 시...
		else if(strcmp(cmd_token[0], "cd") == 0){ // cd 입력 시...
			if(i == 1) chdir(getenv("HOME"));
			else if(i == 2){
				 if(chdir(cmd_token[1])) printf("No directory\n");
			}
			else printf("Wrong cd format\n");
			continue;
		}		
		pid = fork();		//자식 프로세스 생성
		if(pid == 0){
			execvp(cmd_token[0],cmd_token); // file 실행
			perror("execv");
		}
		else{
			if(!background)
				wait((int *)0);
			background = 0; // background로 실행 시 child process의 종료를 기다리지 않고 부모 프로세스 종료.
		}       
	}
	return 0;
}

