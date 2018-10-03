#include <stdio.h>
#include <stdlib.h>

struct node{
	int data, height;
	struct node *lchild, *rchild;
};
typedef struct node Node;

Node* insertNode(Node* t, int data, int height){
	if(t==NULL){
		t=(Node *)malloc(sizeof(Node));
		t->data=data;
		t->lchild=NULL;
		t->rchild=NULL;
		t->height=height;
	}
	else if(t->data>data){
		t->lchild=insertNode(t->lchild, data, ++height);
	}
	else{
		t->rchild=insertNode(t->rchild, data, ++height);
	}
	return t;
}

void traverse(Node* t){
	if(t!=NULL){
		traverse(t->lchild);
		if(t->lchild==NULL && t->rchild==NULL){
			printf("%d %d\n", t->data, t->height);
		}
		traverse(t->rchild);
	}
}

int main(){
	Node *root=NULL;
	int num, data, i;
	scanf("%d", &num);
	for(i=0; i<num; i++){
		scanf("%d", &data);
		root=insertNode(root, data, 1);
	}
	traverse(root);
	return 0;
}

