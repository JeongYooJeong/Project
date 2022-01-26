#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 32
typedef struct{			// 하나의 프로세스가 가지고 있는 페이지 테이블
	int id[SIZE*2];
	int valid[SIZE*2];
	int frameIndex[SIZE*2];
}PageTable;

typedef struct _LRU{		// LRU 연결리스트
	int id;
	int start;
	int end;
	struct _LRU *next;
}LRU;

void allocation(PageTable *p, int AID, int num);	// 페이지테이블에 allocation 
int getValue(PageTable p, int AID);			// 페이지테이블에 AID의 valid 값 리턴
void update_LRU(LRU *head, LRU *new);			// LRU 업데이트
bool isEmpty(int memory[], int start, int end);		// physical memory에 start부터 end 자리까지 메모리가 전부 비어있는지 확인

int main(void){
	int pNum, N;
	int PID, AccessType, AID, FrameNum;
	int memory[SIZE];
	int pageFault = 0;
	int pageSize;
	int i,j,k;
	char Function[15];

	LRU *head = (LRU*)malloc(sizeof(LRU));
	LRU *new;
	LRU *current;
	head->next = NULL;

	scanf("%d",&pNum);
	scanf("%d", &N);
	PageTable p[pNum];
	for(i=0; i<pNum; i++)		// pageTable 초기화
		for(j=0; j<SIZE*2; j++)
			p[i].id[j] = -1;
	for(i=0; i<SIZE; i++)		// physical memory 초기화
		memory[i] = -1;
	for(i=0; i<N; i++){
		scanf("%d %d %d", &PID, &AccessType, &AID);
		if(AccessType){					// AID allocation 이면,
			scanf("%d", &FrameNum);
			strcpy(Function, "ALLOCATION");
			allocation(&p[PID], AID, FrameNum);	// PageTable에 할당
		}
		else{						// Memory access 이면,
			FrameNum = 0;
			for(j=0; j<SIZE*2; j++)
				if(p[PID].id[j] == AID)		// access할 frameNum 확인
					FrameNum++;
			strcpy(Function, "ACCESS");
			if(getValue(p[PID], AID) == 1){		// memory에 접근할 페이지가 이미 할당되어 있다면,
				new = (LRU*)malloc(sizeof(LRU));	
				new->id = AID;
				update_LRU(head, new);		// LRU 업데이트만 하면 된다
				
			}
			else{					// memory에 접근할 페이지가 할당되어있지 않다면,
				pageFault++;			// page fault가 발생한 것이고,
				pageSize = SIZE;
				while(getValue(p[PID], AID) != 1){	// memory에 접근할 페이지가 할당될 때까지 반복 수행
					if(FrameNum > pageSize/2 && FrameNum <= pageSize){	// buddy system에서 사용할 frameNum의 페이지 할당을 위한 사이즈
						for(j=0; j<SIZE; j+=pageSize){
							if(isEmpty(memory, j, j+pageSize)){	// memory에 페이지할당 사이즈만큼의 공간이 있다면,
								new = (LRU*)malloc(sizeof(LRU));
								new->id = AID;
								new->start = j;
								new->end = j+pageSize-1;
								new->next = NULL;
								update_LRU(head, new);
								for(k=j; k<j+pageSize; k++)
									memory[k] = AID;
								for(k=0; k<SIZE*2; k++)
									if(p[PID].id[k] == AID){
										p[PID].valid[k] = 1;
										p[PID].frameIndex[k] = j++;
									}
								break;
							}
						}
						if(getValue(p[PID], AID) != 1){			// 아직도 메모리에 페이지 할당이 안 되었다면, memory에 할당을 위한 공간이 없는 것이므로
							current = head->next;
							head->next = current->next;		// LRU 제거
							for(j=0; j<pNum; j++)
								for(k=0; k<SIZE*2; k++)
									if(p[j].id[k] == current->id)
										p[j].valid[k] = 0;	// 제거한 페이지의 pageTable 갱신
							for(j=current->start; j<= current->end; j++)
								memory[j] = -1;				// 메모리 해제
							free(current);		
						}
						
					}
					else
						pageSize /= 2;
				}
			}
		}
		// 여기서부터 Print //
		printf("* Input : Pid [%d] Function [%s] Alloc ID [%d] Page Num [%d]\n", PID, Function, AID, FrameNum);
		printf("%-30s",">> Physical Memory :");
		for(j=0; j<SIZE; j++){
			if(j%4 == 0)
				printf("|");
			if(memory[j] == -1)
				printf("-");
			else
				printf("%d", memory[j]);
		}
		printf("|\n");
		for(j=0; j<pNum; j++){
			printf(">> pid(%d) %-20s",j,"Page Table(AID) :");
			for(k=0; k<SIZE*2; k++){
				if(k%4 == 0)
					printf("|");
				if(p[j].id[k] == -1)
					printf("-");
				else
					printf("%d", p[j].id[k]);
			}
			printf("|\n");
			printf(">> pid(%d) %-20s",j,"Page Table(Valid) :");
			for(k=0; k<SIZE*2; k++){
				if(k%4 == 0)
					printf("|");
				if(p[j].id[k] == -1)
					printf("-");
				else
					printf("%d", p[j].valid[k]);
			}
			printf("|\n");	
		}
		// LRU는 연결리스트의 헤드부터 하나씩 접근하며 Print //
		printf("%-30s",">> LRU :");
		current = head->next;
		while(current != NULL){
			printf("%d:%d-%d ", current->id, current->start, current->end);
			current = current->next;
		}
		printf("\n\n");
	}
	printf("page fault = %d\n", pageFault);
	free(head);
	head = NULL;
	return 0;
}
void allocation(PageTable *p, int AID, int num){	// PageTable에 AID를 num 만큼 할당시키는 함수
	int i;
	for(i=0; i<SIZE*2; i++){
		if(p->id[i] == -1){
			p->id[i] = AID;
			p->valid[i] = 0;
			num--;
		}
		if(num == 0)
			break;
	}
	return;
}
int getValue(PageTable p, int AID){		//PageTable p에 AID의 valid 값을 리턴하는 함
	int i;
	for(i=0; i<SIZE*2; i++)
		if(p.id[i] == AID)
			return p.valid[i];
}
void update_LRU(LRU *head, LRU *new){		// new를 LRU 연결리스트에 새로 추가하거나, 기존에 존재하는 new를 연결리스트의 맨 뒤로 업데이트 하는 함수
	LRU *current = head;
	LRU *previous;
	while(current->next != NULL){
		previous = current;
		current = current->next;
		if(current->id == new->id){	// new의 id를 가진 LRU 구조체가 이미 연결리스트에 존재하는 경우 (메모리에 이미 해당 id가 할당되어 있는 경우)
			previous->next = current->next;
			new-> start = current->start;
			new->end = current->end;
			new->next = NULL;
			free(current);		// 중복되는 기존 구조체를 제거
			current = previous;
		}
	}
	current->next = new;			// 연결리스트 맨 끝에 new 추
	return;
}
bool isEmpty(int memory[], int start, int end){	// memory의 start부터 end까지 비어있는지 (-1) 인지 체크
	int i;
	for(i=start; i<end; i++)
		if(memory[i] != -1)
			return false;
	return true;
}

