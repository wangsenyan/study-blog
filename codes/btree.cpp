#include<iostream>

using namespace std;
template<class KeyT>
struct BTreeNode{
	int n;
	KeyT *keys;
	bool isLeaf;
	struct BTreeNode **childs;
	struct BTreeNode *parent;
};

template <class KeyT>
class BTree{
	private:
		typedef struct BTreeNode<KeyT> *BTreeNodeLink;
		BTreeNodeLink T;
		int t;
    public:
		BTree(int tVal=2);
		~BTree();
		BTreeNodeLink searchBTree(BTreeNodeLink T,KeyT k,int &index);
		BTreeNodeLink getRoot();
		void insertBTreeNode(KeyT k);
		void deleteBTreeKey(BTreeNodeLink T,KeyT k);
		void createBTree(KeyT *keyValues);
		void printBTreeBFS(BTreeNodeLink t);
		
		void splitChild(BTreeNodeLink x,int i,BTreeNodeLink y);
		void insertBTreeNonFull(BTreeNodeLink x,KeyT k);
		BTreeNodeLink  __allocateNode();
		void deleteNode(BTreeNodeLink node);
		void deleteTree(BTreeNodeLink t);
};


template<class KeyT>
BTree<KeyT>::BTree(int tVal)
{
	t=tVal;
	typename BTree<KeyT>::BTreeNodeLink x=__allocateNode();
	x->isLeaf=true;
	x->n=0;
	T=x;
}

template<class KeyT>
BTree<KeyT>::~BTree()
{
	deleteTree(T);
	T=NULL;
}

template<class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::searchBTree(BTreeNodeLink T,KeyT k,int &index)
{
	if(NULL==T)
	{
		index=-1;
		return NULL;
	}
	int i=0;
	while(i<T->n&&k>T->keys[i])
	   ++i;
	if(i<T->n&&k==T->keys[i])
	{
		index=i;
		return T;
	}
	if(T->isLeaf)
	{
		index=-1;
		return NULL;
	}else{
		return searchBTree(T->childs[i],k,index);
	}
}
template<class KeyT>
void BTree<KeyT>::splitChild(typename BTree<KeyT>::BTreeNodeLink x,int index,typename BTree<KeyT>::BTreeNodeLink y)
{
	typename BTree<KeyT>::BTreeNodeLink z=__allocateNode();
	z->isLeaf=y->isLeaf;
	z->n=t-1;
	for(int i=0;i<t-1;++i)
	    z->keys[i]=y->keys[t+1];
	if(!y->isLeaf)
	{
		for(int i=0;i<t;++i)
		  z->childs[i]=y->childs[t+i];
	}
	z->parent=x;
	y->n=t-1;
	for(int i=x->n;i>=index+1;--i)
	    x->childs[i+1]=x->childs[i];
	x->childs[index+1]=z;
	for(int i=x->n-1;i>=index;--i)
	    x->keys[i+1]=x->keys[i];
    x->keys[index]=y->keys[t-1];
    x->n=x->n+1; 
}

template<class KeyT>
void BTree<KeyT>::insertBTreeNode(KeyT k)
{
	typename BTree<KeyT>::BTreeNodeLink r=T;
	if(r->n==2*t-1)
	{
		typename BTree<KeyT>::BTreeNodeLink s=__allocateNode();
		T=s;
		s->isLeaf=false;
		s->n=0;
		s->childs[0]=r;
		splitChild(s,0,r);
		insertBTreeNonFull(s,k);
		
	}else{
		insertBTreeNonFull(r,k);
	}
}
template<class KeyT>
void BTree<KeyT>::insertBTreeNonFull(typename BTree<KeyT>::BTreeNodeLink x,KeyT k)
{
	int i=x->n;
	if(x->isLeaf)
	{
		if(!i)
		{
			x->keys[0]=k;
			x->n=x->n+1;
			return;
		}
		while(i>=0 &&k<x->keys[i-1]){
			x->keys[i]=x->keys[i-1];
			--i;
		}
		x->keys[i]=k;
		x->n=x->n+1;
	}else{
		while(i>0&&k<x->keys[i-1])
           --i;
        if(2*t-1==x->childs[i]->n)
        {
        	splitChild(x,i,x->childs[i]);
        	if(k>x->keys[i])
        	   ++i;
		}
		insertBTreeNonFull(x->childs[i],k);
	}
}

//函数：删除特定关键字
//参数解释：
//K：要删除的关键字
//TSubTree：要删除的关键字所在节点指针
template<class KeyT>
void BTree<KeyT>::deleteBTreeKey(BTreeNodeLink TSubTree,KeyT k)
{
	if(NULL==TSubTree)
	  return;
	int searchIndex;
	BTreeNodeLink searchedNode=searchBTree(TSubTree,k,searchIndex);
	if(NULL==searchedNode)
	{
		cout<<"The keyword to be deleted not exist in this B-Tree!"<<endl;
	}
	int keyIndex=-1;
	for(int j=0;j<TSubTree->n;++j)
	{
		if(k==TSubTree->keys[j])
		{
			keyIndex=j;
			break;
		}
	}
	if(keyIndex!=-1&&TSubTree->isLeaf)
	{
		for(int j=keyIndex;j<TSubTree->n-1;++j)
		    TSubTree->keys[j]=TSubTree->keys[j+1];
		TSubTree->n=TSubTree->n-1;
		return; 
	}else if(keyIndex!=-1&&!TSubTree->isLeaf)
	{
		BTreeNodeLink predecessorNode=TSubTree->childs[keyIndex];
		BTreeNodeLink succeedNode=TSubTree->childs[keyIndex+1];
		if(predecessorNode->n>t-1)
		{
			KeyT predecessorKey=predecessorNode->keys[predecessorNode->n-1];
			TSubTree->keys[keyIndex]=predecessorKey;
			deleteBTreeKey(predecessorNode,predecessorKey);
		}else if(succeedNode->n>t-1)
		{
			KeyT succeedKey=succeedNode->keys[0];
			TSubTree->keys[keyIndex]=succeedKey;
			deleteBTreeKey(succeedNode,succeedKey);
		}else
		{
			predecessorNode->keys[predecessorNode->n]=k;
			for(int j=0;j<t-1;++j)
			   predecessorNode->keys[t+j]=succeedNode->keys[j];
		    //孩子呢？ 
			predecessorNode->n=2*t-1;
			for(int j=keyIndex;j<TSubTree->n-1;++j)
			   TSubTree->keys[j]=TSubTree->keys[j+1];
			for(int j=keyIndex+1;j<TSubTree->n;++j)
			   TSubTree->childs[j]=TSubTree->childs[j+1];
			TSubTree->n=TSubTree->n-1;
			if(0==TSubTree->n)
			    T=TSubTree->childs[keyIndex];
			deleteNode(succeedNode);
			deleteTreeKey(TSubTree->childs[keyIndex],k);
		}
	}else{
		int subTreeIndex;
		BTreeNodeLink searchedNode;
		BTreeNodeLink deletedKeySubT;
		for(int j=0;j<TSubTree->n+1;++j)
		{
			searchedNode=searchBTree(TSubTree->childs[j],k,subTreeIndex);
			if(searchedNode!=NULL)
			{
				deletedKeySubT=TSubTree->childs[j];
				break;
			}
		}
		if(deletedKeySubT->n<t)
		{
			int index;
			//与上面的重复 
			for(int i=0;i<TSubTree->n+1;++i)
			{
				if(TSubTree->childs[i]==deletedKeySubT)
				{
					index=i;
					break;
				}
			}
			BTreeNodeLink leftBrotherNode= TSubTree->childs[index-1];
			BTreeNodeLink rightBrotherNode= TSubTree->childs[index+1];
			if(index>=1&&leftBrotherNode->n>t-1)
			{
				for(int j=deletedKeySubT->n-1;j>=0;--j)
				   deletedKeySubT->keys[j+1]=deletedKeySubT->keys[j];
				deletedKeySubT->keys[0]=TSubTree->keys[index-1];
				deletedKeySubT->n=deletedKeySubT->n+1;
				TSubTree->keys[index-1]=leftBrotherNode->keys[leftBrotherNode->n-1];
				leftBrotherNode->n=leftBrotherNode->n-1;
			}else if(index<TSubTree->n+1&&rightBrotherNode->n>t-1){
				deletedKeySubT->keys[deletedKeySubT->n]=TSubTree->keys[index];
				deletedKeySubT->n=deletedKeySubT->n+1;
				TSubTree->keys[index]=rightBrotherNode->keys[0];
				for(int j=0;j<rightBrotherNode->n-1;++j)
				    rightBrotherNode->keys[j]=rightBrotherNode->keys[j+1];
				rightBrotherNode->n=rightBrotherNode->n-1;
			}else{
				if(index=-1)
				{
				   leftBrotherNode->keys[t-1]=TSubTree->keys[index-1];
				   for(int j=0;j<t-1;++j)
				       leftBrotherNode->keys[t+j]=deletedKeySubT->keys[j];
				    leftBrotherNode->n=2*t-1;
				    for(int j=0;j<t;++j)
				       leftBrotherNode->childs[t+j]=deletedKeySubT->childs[j];
				    for(int j = index - 1;j < TSubTree->n - 1;++j)
						TSubTree->keys[j] = TSubTree->keys[j + 1];
					TSubTree->n = TSubTree->n - 1;
					for(int j = index;j < TSubTree->n;++j)
						TSubTree->childs[j] = TSubTree->childs[j + 1];
					deleteNode(deletedKeySubT);
					deletedKeySubT = leftBrotherNode;
		    	}else
		    	{
		    		deletedKeySubT->keys[t - 1] = TSubTree->keys[index - 1];//父节点中的关键字
					for(int j = 0;j < t - 1;++j)
						deletedKeySubT->keys[t + j] = rightBrotherNode->keys[j];
					deletedKeySubT->n = 2 * t - 1;
					for(int j = 0;j < t;++j)
						deletedKeySubT->childs[t + j] = rightBrotherNode->childs[j];
					for(int j = index;j < TSubTree->n - 1;++j)
						TSubTree->keys[j] = TSubTree->keys[j + 1];
					TSubTree->n = TSubTree->n - 1;
					for(int j = index + 1;j < TSubTree->n;++j)
						TSubTree->childs[j] = TSubTree->childs[j + 1];
 
					deleteNode(rightBrotherNode);
				}
		   }
		}
		deleteBTreeKey(deletedKeySubT,k);
	} 
	
}

template<class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::__allocateNode()
{
	typename BTree<KeyT>::BTreeNodeLink newNode=new struct BTreeNode<KeyT>;
	newNode->n=0;
	newNode->keys=new KeyT[2*t-1];
	newNode->isLeaf=true;
	newNode->childs=new typename BTree<KeyT>::BTreeNodeLink[2*t];
	for(int i=0;i<2*t;++i)
	  newNode->childs[i]=NULL;
	return newNode;
}



template<class KeyT>
typename BTree<KeyT>::BTreeNodeLink BTree<KeyT>::getRoot()
{
	return T;
}

template <class KeyT>
void BTree<KeyT>::deleteNode(typename BTree<KeyT>::BTreeNodeLink node)
{
	delete[] node->keys;
}

template<class KeyT>
void BTree<KeyT>::deleteTree(typename BTree<KeyT>::BTreeNodeLink t)
{
	if(NULL==t)
	  return;
	if(t->isLeaf)
	  delete[]t->keys;
	else
	{
		for(int i=0;i<t->n;++i)
		  deleteTree(t->childs[i]);
		delete[]t->childs;
	}
}


int main()
{
	return 0;
}
