/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		 - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("[----- [Your Name] [Student ID] -----]\n");
	printf("\t신승용       2019038073\n");
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {	// 연결리스트를 초기화하는 함수, 이중 연결리스트는 쌍방으로 정보를 교환하므로 이중포인터를 이용한다.

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if (*h != NULL)	// 헤드가 비어있지 않으면 비운후 동적할당을 해야하기 때문에 헤드가 비어있는지 확인
		freeList(*h);	//비어있지 않으면 freeList()함수를 호출해 메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));	//연결리스트 동적할당
	(*h)->first = NULL;	//노드가 가리키는 주소를 NULL로 초기화
	return 1;
}

int freeList(headNode* h) {	// 연결리스트를 동적할당 해제하는 함수 노드를 하나씩 해제하고 헤더노드를 해제하므로 싱글 포인터를 받았다.
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;	// 연결리스트의 헤더노드의 주소를 p로 넘긴다.

	listNode* prev = NULL;	// temp의 역할을 할 listNode* 를 선언한다.
	while (p != NULL) {	// p가 NULL이 될 때 까지 뒤로 이동한다.
		prev = p;	// p의 주소를 prev로 넘긴후
		p = p->rlink;	// 다음노드의 주소를 p로 넘긴다 (p가 다음노드로 이동)
		free(prev);	// prev를 동적할당 해제한다.
	}
	free(h);	//헤더노드를 동적할당 해제하여 연결리스트를 해제한다
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {	//마지막 부분에 노드를 추가하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	//추가할 노드를 동적할당한다
	node->key = key;	//입력받은 키값을 노드에 입력한다.
	node->rlink = NULL;	//노드가 가리키는 주소를 초기화한다.
	node->llink = NULL; //노드가 가리키는 주소를 초기화한다.

	if (h->first == NULL)	//연결리스트가 비어있을경우
	{
		h->first = node;	//연결리스트의 처음 부분에 노드를 삽입한다.
		return 0;
	}

	listNode* n = h->first;	//연결리스트의 마지막부분으로 이동하기위해 n을 선언한다.
	while (n->rlink != NULL) {	//n이 연결리스트의 마지막부분으로 이동할때까지 반복
		n = n->rlink;
	}
	n->rlink = node;	//마지막 노드의 rlink에 연결하여 마지막 부분에 삽입한다.
	node->llink = n;	//삽입한 노드도 마지막 노드였던 노드에 주소를 연결한다.
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {	//마지막 노드를 삭제하는 함수

	if (h->first == NULL)	// 연결리스트가 비어있을 경우
	{
		printf("nothing to delete.\n");	// 에러메세지 출력
		return 0;
	}

	listNode* n = h->first;	//n은 마지막 노드까지 이동하기위해 선언
	listNode* trail = NULL;	

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if (n->rlink == NULL) {	//노드가 하나만 있어 rlink에 아무것도 연결이 되어있지 않은경우
		h->first = NULL;	//연결되어있는 주소 초기화
		free(n);	//연결리스트 동적할당해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while (n->rlink != NULL) {	//n이 연결리스트의 마지막 노드까지 이동
		trail = n;
		n = n->rlink;
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL;	//마지막 전노드의 rlink를 연결 해제
	free(n);	//마지막 노드 동적할당 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {	//첫번째에 노드를 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	//삽입할 노드를 동적할당
	node->key = key;	//동적할당 받은 노드에 키값을 입력
	node->rlink = node->llink = NULL;	//노드가 연결되어있는 주소 초기화

	if (h->first == NULL)	//연결리스트가 비어있을 경우
	{
		h->first = node;	// 첫번째에 입력받은 노드 삽입
		return 1;
	}

	node->rlink = h->first;	//입력받은 노드의 rlink에 현재 첫번째 노드의 주소 연결
	node->llink = NULL;	//첫번째 노드이므로 llink는 비워둔다

	listNode *p = h->first;	
	p->llink = node;	//첫번째 노드였던 노드의 llink에 입력받은 노드를 연결
	h->first = node;	//헤더 노드를 입력받은 노드로 연결

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {	//연결리스트의 첫번째 노드를 삭제하는 함수

	if (h->first == NULL)	//연결리스트가 비어있을 경우
	{
		printf("nothing to delete.\n");	//에러메세지 출력
		return 0;
	}
	listNode* n = h->first;	
	h->first = n->rlink;	//헤더 노드를 첫번째 노드의 오른쪽에 있는 노드로 연결

	free(n);	//첫번째 노드 동적할당 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {	//리스트 역순으로 정렬하는 함수


	if (h->first == NULL) {	//연결리스트가 비어있을경우
		printf("nothing to invert...\n");	//에러메세지 출력
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while (n != NULL) {	//n이 노드의 맨 끝까지 이동 할때 까지 반복
		trail = middle;	
		middle = n;	//middle 다음칸으로 이동
		n = n->rlink;	//n 다음칸으로 이동
		middle->rlink = trail;	//middle의 rlink와 llink를 맞바꾼다
		middle->llink = n;
	}

	h->first = middle;	//헤더노드를 마지막 노드로 설정

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {	//키값을 오름차순으로 삽입하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));	//입력받을 노드를 동적할당
	node->key = key;	//입력받은 키값을 동적할당한 노드에 입력
	node->llink = node->rlink = NULL;	//동적할당한 노드 연결된 주소값 초기화

	if (h->first == NULL)	//연결리스트가 비어있을 경우
	{
		h->first = node;	//첫번째에 노드 삽입
		return 0;
	}

	listNode* n = h->first;

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while (n != NULL) {	//n이 연결리스트의 마지막이 될때까지 반복
		if (n->key >= key) {	//n이 가리키는 키값이 입력받은 키값보다 클경우
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if (n == h->first) {	//n의 노드가 첫번째 노드일 경우
				insertFirst(h, key);	//insertFirst()함수를 이용하여 첫번째에 노드삽입
			}
			else { /* 중간이거나 마지막인 경우 */
				node->rlink = n;	//입력받은 노드의 rlink를 n에 연결
				node->llink = n->llink;	// 입력받은 노드의 llink를 n의 왼쪽에 있던 노드에 연결
				n->llink->rlink = node;	//n의 왼쪽에 있던 노드의 rlink를 node에 연결
			}
			return 0;
		}

		n = n->rlink; //n을 다음 노드로 이동
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key);	//insertLast()함수를 이용하여 입력받은 노드를 마지막 노드로 삽입
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {	//연결리스트에서 노드를 삭제하는 함수

	if (h->first == NULL)	//연결리스트가 비어있을 경우
	{
		printf("nothing to delete.\n");	//에러메세지 출력
		return 1;
	}

	listNode* n = h->first;

	while (n != NULL) {	//n이 마지막 노드로 이동할때 까지 반복
		if (n->key == key) {	//n이 가리키는 노드의 키값이 입력받은 키값과 같을경우
			if (n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h);	//deleteFirst()를 이용하여 첫번째 노드 삭제
			}
			else if (n->rlink == NULL) { /* 마지막 노드인 경우 */
				deleteLast(h);	//deleteLast()함수를 이용하여 마지막 노드 삭제
			}
			else { /* 중간인 경우 */
				n->llink->rlink = n->rlink;	//n의 왼쪽에 있는 노드의 rlink를 n의 오른쪽 노드와 연결
				n->rlink->llink = n->llink;	//n의 오른쪽에 있는 노드의 llink를 n의 왼쪽 노드와 연결
				free(n);	//n 동적할당 해제
			}
			return 1;
		}

		n = n->rlink;//n을 다음 노드로 이동
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);	//오류메세지 출력
	return 1;
}


