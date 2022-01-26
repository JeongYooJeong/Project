#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


#define MAX_LEN 40000000 // 최대로 읽을 수 있는 입력 데이터 수

int main(int argc, char* argv[]){
	pid_t child_pid;
	int i,j; // 루프를 위한 변수
	double *x = (double*)malloc(sizeof(double)*MAX_LEN); // x값 저장을 위한 동적할당
	double *y = (double*)malloc(sizeof(double)*MAX_LEN); // y값 저장을 위한 동적할당
	double x_avr = 0.0; // x average
	double y_avr = 0.0; // y average
	double beta1_head=0.0; // beta1의 분자 값을  저장
	double beta1_body=0.0; // beta1의 분모 값을 저장
	double beta0 = 0.0; 
	double ptr[2]; // 파이프라인을 통한 데이터 전달을 위한 변수
	int count=0;	// 읽은 입력 데이터 수
	int pipes_child[2]; 
	int pipes_child2[2];
	int MAX_PROCESS_NUM = atoi(argv[2]); // 생성할 프로세스 개수는 입력으로부터 전달 받음

	while(scanf("%lf %lf\n",x,y) != EOF){
		x_avr += *x;
		y_avr += *y;
		x++,y++;		
		count++;
	}	
	if(pipe(pipes_child) == -1 || pipe(pipes_child2) == -1){
		perror("pipe");
		exit(1);
	}	
		
	x_avr /= count; // get x_average
	y_avr /= count; // get y_average

	x -= count; // 포인터 위치 원래대로 되돌려 놓기
	y -= count;
		
	for(i=0; i<MAX_PROCESS_NUM; i++){
		switch(fork()){
			case 0:	
				x = x + count/MAX_PROCESS_NUM * i; // initialize location of x
				y = y + count/MAX_PROCESS_NUM * i; // initialize location of y	
				for(j=count/MAX_PROCESS_NUM *i; j<count/MAX_PROCESS_NUM *(i+1); j++){ 
					beta1_head += (*x-x_avr)*(*y-y_avr);
					beta1_body += (*x-x_avr)*(*x-x_avr);
					x++,y++;
				}	
				ptr[0] = beta1_head;
				ptr[1] = beta1_body;					
				write(pipes_child[1],ptr,sizeof(ptr));  //pipe를 통해 전송할 데이터 쓰기
				exit(0);
			case -1:
				perror("fork");
				exit(1);
			default: ;		
		}
	}
	
	for(i=0; i<MAX_PROCESS_NUM; i++){
		wait(NULL);
		read(pipes_child[0],ptr,sizeof(ptr)); // 자식 프로세스로부터 전달된 데이터 읽기
		beta1_head += ptr[0];
		beta1_body += ptr[1];
	}
	beta1_head /= beta1_body; // 분자 값에서 분모 값을 나누기
	beta0 = y_avr - beta1_head*x_avr; 
	printf("y = %f + %fx\n",beta0,beta1_head);

	free(x); // x 동적 메모리 해제
	free(y); // y 동적 메모리 해제
	x = NULL;
	y = NULL;
	return 0;
}

