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
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		 - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
	printf("\t�Ž¿�       2019038073\n");
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


int initialize(headNode** h) {	// ���Ḯ��Ʈ�� �ʱ�ȭ�ϴ� �Լ�, ���� ���Ḯ��Ʈ�� �ֹ����� ������ ��ȯ�ϹǷ� ���������͸� �̿��Ѵ�.

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if (*h != NULL)	// ��尡 ������� ������ ����� �����Ҵ��� �ؾ��ϱ� ������ ��尡 ����ִ��� Ȯ��
		freeList(*h);	//������� ������ freeList()�Լ��� ȣ���� �޸� ����

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));	//���Ḯ��Ʈ �����Ҵ�
	(*h)->first = NULL;	//��尡 ����Ű�� �ּҸ� NULL�� �ʱ�ȭ
	return 1;
}

int freeList(headNode* h) {	// ���Ḯ��Ʈ�� �����Ҵ� �����ϴ� �Լ� ��带 �ϳ��� �����ϰ� �����带 �����ϹǷ� �̱� �����͸� �޾Ҵ�.
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first;	// ���Ḯ��Ʈ�� �������� �ּҸ� p�� �ѱ��.

	listNode* prev = NULL;	// temp�� ������ �� listNode* �� �����Ѵ�.
	while (p != NULL) {	// p�� NULL�� �� �� ���� �ڷ� �̵��Ѵ�.
		prev = p;	// p�� �ּҸ� prev�� �ѱ���
		p = p->rlink;	// ��������� �ּҸ� p�� �ѱ�� (p�� �������� �̵�)
		free(prev);	// prev�� �����Ҵ� �����Ѵ�.
	}
	free(h);	//�����带 �����Ҵ� �����Ͽ� ���Ḯ��Ʈ�� �����Ѵ�
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
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {	//������ �κп� ��带 �߰��ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode));	//�߰��� ��带 �����Ҵ��Ѵ�
	node->key = key;	//�Է¹��� Ű���� ��忡 �Է��Ѵ�.
	node->rlink = NULL;	//��尡 ����Ű�� �ּҸ� �ʱ�ȭ�Ѵ�.
	node->llink = NULL; //��尡 ����Ű�� �ּҸ� �ʱ�ȭ�Ѵ�.

	if (h->first == NULL)	//���Ḯ��Ʈ�� ����������
	{
		h->first = node;	//���Ḯ��Ʈ�� ó�� �κп� ��带 �����Ѵ�.
		return 0;
	}

	listNode* n = h->first;	//���Ḯ��Ʈ�� �������κ����� �̵��ϱ����� n�� �����Ѵ�.
	while (n->rlink != NULL) {	//n�� ���Ḯ��Ʈ�� �������κ����� �̵��Ҷ����� �ݺ�
		n = n->rlink;
	}
	n->rlink = node;	//������ ����� rlink�� �����Ͽ� ������ �κп� �����Ѵ�.
	node->llink = n;	//������ ��嵵 ������ ��忴�� ��忡 �ּҸ� �����Ѵ�.
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {	//������ ��带 �����ϴ� �Լ�

	if (h->first == NULL)	// ���Ḯ��Ʈ�� ������� ���
	{
		printf("nothing to delete.\n");	// �����޼��� ���
		return 0;
	}

	listNode* n = h->first;	//n�� ������ ������ �̵��ϱ����� ����
	listNode* trail = NULL;	

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if (n->rlink == NULL) {	//��尡 �ϳ��� �־� rlink�� �ƹ��͵� ������ �Ǿ����� �������
		h->first = NULL;	//����Ǿ��ִ� �ּ� �ʱ�ȭ
		free(n);	//���Ḯ��Ʈ �����Ҵ�����
		return 0;
	}

	/* ������ ������ �̵� */
	while (n->rlink != NULL) {	//n�� ���Ḯ��Ʈ�� ������ ������ �̵�
		trail = n;
		n = n->rlink;
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL;	//������ ������� rlink�� ���� ����
	free(n);	//������ ��� �����Ҵ� ����

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {	//ù��°�� ��带 �����ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode));	//������ ��带 �����Ҵ�
	node->key = key;	//�����Ҵ� ���� ��忡 Ű���� �Է�
	node->rlink = node->llink = NULL;	//��尡 ����Ǿ��ִ� �ּ� �ʱ�ȭ

	if (h->first == NULL)	//���Ḯ��Ʈ�� ������� ���
	{
		h->first = node;	// ù��°�� �Է¹��� ��� ����
		return 1;
	}

	node->rlink = h->first;	//�Է¹��� ����� rlink�� ���� ù��° ����� �ּ� ����
	node->llink = NULL;	//ù��° ����̹Ƿ� llink�� ����д�

	listNode *p = h->first;	
	p->llink = node;	//ù��° ��忴�� ����� llink�� �Է¹��� ��带 ����
	h->first = node;	//��� ��带 �Է¹��� ���� ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {	//���Ḯ��Ʈ�� ù��° ��带 �����ϴ� �Լ�

	if (h->first == NULL)	//���Ḯ��Ʈ�� ������� ���
	{
		printf("nothing to delete.\n");	//�����޼��� ���
		return 0;
	}
	listNode* n = h->first;	
	h->first = n->rlink;	//��� ��带 ù��° ����� �����ʿ� �ִ� ���� ����

	free(n);	//ù��° ��� �����Ҵ� ����

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {	//����Ʈ �������� �����ϴ� �Լ�


	if (h->first == NULL) {	//���Ḯ��Ʈ�� ����������
		printf("nothing to invert...\n");	//�����޼��� ���
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while (n != NULL) {	//n�� ����� �� ������ �̵� �Ҷ� ���� �ݺ�
		trail = middle;	
		middle = n;	//middle ����ĭ���� �̵�
		n = n->rlink;	//n ����ĭ���� �̵�
		middle->rlink = trail;	//middle�� rlink�� llink�� �¹ٲ۴�
		middle->llink = n;
	}

	h->first = middle;	//�����带 ������ ���� ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {	//Ű���� ������������ �����ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode));	//�Է¹��� ��带 �����Ҵ�
	node->key = key;	//�Է¹��� Ű���� �����Ҵ��� ��忡 �Է�
	node->llink = node->rlink = NULL;	//�����Ҵ��� ��� ����� �ּҰ� �ʱ�ȭ

	if (h->first == NULL)	//���Ḯ��Ʈ�� ������� ���
	{
		h->first = node;	//ù��°�� ��� ����
		return 0;
	}

	listNode* n = h->first;

	/* key�� �������� ������ ��ġ�� ã�´� */
	while (n != NULL) {	//n�� ���Ḯ��Ʈ�� �������� �ɶ����� �ݺ�
		if (n->key >= key) {	//n�� ����Ű�� Ű���� �Է¹��� Ű������ Ŭ���
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if (n == h->first) {	//n�� ��尡 ù��° ����� ���
				insertFirst(h, key);	//insertFirst()�Լ��� �̿��Ͽ� ù��°�� ������
			}
			else { /* �߰��̰ų� �������� ��� */
				node->rlink = n;	//�Է¹��� ����� rlink�� n�� ����
				node->llink = n->llink;	// �Է¹��� ����� llink�� n�� ���ʿ� �ִ� ��忡 ����
				n->llink->rlink = node;	//n�� ���ʿ� �ִ� ����� rlink�� node�� ����
			}
			return 0;
		}

		n = n->rlink; //n�� ���� ���� �̵�
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key);	//insertLast()�Լ��� �̿��Ͽ� �Է¹��� ��带 ������ ���� ����
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {	//���Ḯ��Ʈ���� ��带 �����ϴ� �Լ�

	if (h->first == NULL)	//���Ḯ��Ʈ�� ������� ���
	{
		printf("nothing to delete.\n");	//�����޼��� ���
		return 1;
	}

	listNode* n = h->first;

	while (n != NULL) {	//n�� ������ ���� �̵��Ҷ� ���� �ݺ�
		if (n->key == key) {	//n�� ����Ű�� ����� Ű���� �Է¹��� Ű���� �������
			if (n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h);	//deleteFirst()�� �̿��Ͽ� ù��° ��� ����
			}
			else if (n->rlink == NULL) { /* ������ ����� ��� */
				deleteLast(h);	//deleteLast()�Լ��� �̿��Ͽ� ������ ��� ����
			}
			else { /* �߰��� ��� */
				n->llink->rlink = n->rlink;	//n�� ���ʿ� �ִ� ����� rlink�� n�� ������ ���� ����
				n->rlink->llink = n->llink;	//n�� �����ʿ� �ִ� ����� llink�� n�� ���� ���� ����
				free(n);	//n �����Ҵ� ����
			}
			return 1;
		}

		n = n->rlink;//n�� ���� ���� �̵�
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);	//�����޼��� ���
	return 1;
}


