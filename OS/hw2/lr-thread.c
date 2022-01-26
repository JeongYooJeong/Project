#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LEN 40000000 // 최대로 읽을 수 있는 입력 데이터 수

// 스레드간의 공유할 변수들... 
double *x,*y;  //x,y좌표
double x_avr, y_avr; //x,y 평균
int MAX_THREAD_NUM; //생성할 스레드 개수
double beta1_head; // beta1의 분자,분모값
double beta1_body; // 배열크기는 임의로 잡음...
int count; // 입력받은 데이터 수
//
void *thread_function(void *arg); //thread funtion

int main(int argc, char* argv[]){
	int res;
	int i;
	void *thread_result;
	double beta1=0.0;
	double beta0=0.0;
	double *x_ptr, *y_ptr;
	x = (double*)malloc(sizeof(double)*MAX_LEN);
	y = (double*)malloc(sizeof(double)*MAX_LEN);
        MAX_THREAD_NUM = atoi(argv[2]); // 스레드 개수는 입력으로부터 전달됨
        pthread_t thread_handle[MAX_THREAD_NUM];// 스레드의 ID를 저장할 변수
	x_ptr = x;
	y_ptr = y;
	x_avr = 0.0;
	y_avr = 0.0;
	count = 0;
	beta1_head = 0.0;
	beta1_body = 0.0;
	while(scanf("%lf %lf\n",x,y) != EOF){
		x_avr += *x;
		y_avr += *y;
		x++,y++;
		count++;
	}
	x_avr /= count;
	y_avr /= count;
	x = x_ptr; // 포인터 위치 원래대로 되돌려놓기
	y = y_ptr;

	for(i=0; i<MAX_THREAD_NUM; i++){ //스레드 생성
		res = pthread_create(&(thread_handle[i]),NULL,thread_function,(void*)i);
	}
	if(res != 0){ // 스레드 생성 에러 확인
		printf("[Main] Thread Creation Fail.\n");
		exit(1);
	}
	for(i=0; i<MAX_THREAD_NUM; i++){
		res = pthread_join(thread_handle[i], &thread_result);
		if(res != 0){
			printf("[Main]join thread(%d) failed\n",i);
		}
	}

//	for(i=0; i<MAX_THREAD_NUM; i++){ //beta1, beta0 값 계산
//		beta1 += beta1_head[i];
//		beta0 += beta1_body[i];
//	}
	beta1 = beta1_head/beta1_body;	
	//beta1 /= beta0;
	beta0 = y_avr - beta1*x_avr;
	printf("y = %f + %fx\n",beta0,beta1);
	free(x);
	free(y);
	x = NULL;
	y = NULL;
	return 0;
}
void *thread_function(void *arg){
	int my_number = (int)arg;	
	int i;
	double head = 0.0;
	double body = 0.0;
	double *x_ptr = x + count/MAX_THREAD_NUM*my_number;
	double *y_ptr = y + count/MAX_THREAD_NUM *my_number;
	for(i=count/MAX_THREAD_NUM *my_number; i< count/MAX_THREAD_NUM *(my_number+1);i++){
		head += (*x_ptr-x_avr)*(*y_ptr-y_avr);
		body += (*x_ptr-x_avr)*(*x_ptr-x_avr);
		x_ptr++, y_ptr++;			
	}
	beta1_head += head;
	beta1_body += body;
}

