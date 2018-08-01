#include<iostream>
using namespace std;
typedef struct BiThrNode
{
    char data;
	struct BiThrNode *lchild,*rchild;      /*左右孩子指针*/
	int LTag,RTag;             			    /*左右标志*/
}BiThrNode,*BiThrTree;
BiThrTree pre;
void CreateBiTree(BiThrTree &T)
{
	char ch;
	/*按先序次序输入二叉树中结点的值(一个字符)，创建二叉链表表示的二叉树T*/
	cin>>ch;
	if(ch == '#') T=NULL;
	else
	{
		T=new BiThrNode;
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
/*以结点p为根的子树中序线索化*/
void InThreading(BiThrTree p)
{
	/*pre是全局变量，初始化时其右孩子指针为空，便于在树的最左点开始建线索*/
	if(p)
	{
		InThreading(p->lchild);            /*左子树递归线索化*/
		if(!(p->lchild) )                      /*p的左孩子为空*/
		{                  
			p->LTag=1;                     /*给p加上左线索*/
			p->lchild=pre;                 /*p的左孩子指针指向pre(前驱)*/
		}
		else
		{
			p->LTag=0;
		}
		if(!(pre->rchild) )                  /*pre的右孩子为空*/
		{
			pre->RTag=1;                  /*给pre加上右线索*/
			pre->rchild=p;                /*pre的右孩子指针指向p(后继)*/
		}
		else
		{
			pre->RTag=0;
		}
		pre=p;                            /*保持pre指向p的前驱*/
		InThreading(p->rchild);           /*右子树递归线索化*/
	}
}
/*带头结点的中序线索化*/
void InOrderThreading(BiThrTree &Thrt,BiThrTree T)
{
	/*中序遍历二叉树T，并将其中序线索化，Thrt指向头结点*/
	Thrt=new BiThrNode;  		/*建头结头*/
	Thrt->LTag=0;               /*头结点有左孩子，若树非空，则其左孩子为树根*/       
	Thrt->RTag=1;               /*头结点的右孩子指针为右线索*/
	Thrt->rchild=Thrt;          /*初始化时右指针指向自己*/
	if(!T) Thrt->lchild=Thrt;   /*若树为空，则左指针也指向自己*/
	else
	{
		Thrt->lchild=T; pre=Thrt; /*头结点的左孩子指向根，pre初值指向头结点*/
		InThreading(T);          /*调用上述算法，对以T为根的二叉树进行中序线索化*/
		pre->rchild=Thrt;        /*算法结束后，pre为最右结点，pre的右线索指向头结点*/
		pre->RTag=1;
		Thrt->rchild=pre;        /*头结点的右线索指向pre*/
	} 
}  
/*遍历中序线索二叉树*/
void InOrderTraverse_Thr(BiThrTree T)
{
	/*T指向头结点，头结点的左链lchild指向根结点*/
	/*中序遍历二叉线索树T的非递归算法，对每个数据元素直接输出*/
	BiThrTree p=T->lchild;    /*p指向根结点*/        
	while(p!=T)
	{
        while(p->LTag == 0)      /*沿左孩子向下*/
		{
		     p=p->lchild;
		}
		cout<<p->data<<" ";           /*访问其左子树为空的结点*/
		while(p->RTag == 1 && p->rchild!=T)  /*沿右线索访问后继结点*/
		{
		    p=p->rchild;
			cout<<p->data<<" ";
		}
		p=p->rchild;
	}
	cout<<p->data;
}
int main()
{
	BiThrTree T;
	BiThrTree Thrt;
	cout<<"Input the Threaded BinaryTree 's node:"<<endl;
	CreateBiTree(T);
	InOrderThreading(Thrt,T); /*带头结点的中序线索化*/
	cout<<"InOrderTraverse_Thr:"<<endl;
	InOrderTraverse_Thr(T);   /*遍历中序线索二叉树*/
	return 0;
}
