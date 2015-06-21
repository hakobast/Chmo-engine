#ifndef DOUBLE_LINKED_LIST
#define DOUBLE_LINKED_LIST

template<class T>
class Node
{
	template<class T> friend class DoubleLinkedList;
private:
	Node* prevNode = 0;
	Node* nextNode = 0;
public:
	T* data = 0;

	Node(T* data) :data(data){};
};

template<class T>
class DoubleLinkedList
{
public:
	class iterator
	{
		template<class T> friend class DoubleLinkedList;
	public:
		void		reset();
		bool		hasNext();
		Node<T>*	next();
	private:
		Node<T>* firstNode_ = 0;
		Node<T>* currentNode_ = 0;

		iterator(Node<T>* firstNode) :firstNode_(firstNode){ reset(); };
	};

private:
	Node<T>* firstNode_ = 0;
	Node<T>* lastNode_ = 0;
public:
	Node<T>* first();
	Node<T>* last();
	void addToFront(Node<T>* node);
	void addToBack(Node<T>* node);
	void remove(Node<T>* node);
	bool isEmpty();
	iterator getIterator();
};

template<class T> inline Node<T>* DoubleLinkedList<T>::first()
{
	return firstNode_;
}

template<class T> inline Node<T>* DoubleLinkedList<T>::last()
{
	return lastNode_;
}

template<class T> inline void DoubleLinkedList<T>::addToFront(Node<T>* node)
{
	if (node == NULL)
		return;

	if (firstNode_ == NULL)
	{
		firstNode_ = lastNode_ = node;
	}
	else
	{
		firstNode_->prevNode = node;
		node->nextNode = firstNode_;
		firstNode_ = node;
	}
}

template<class T> inline void DoubleLinkedList<T>::addToBack(Node<T>* node)
{
	if (node == NULL)
		return;

	if (firstNode_ == NULL)
	{
		firstNode_ = lastNode_ = node;
	}
	else
	{
		lastNode_->nextNode = node;
		node->prevNode = lastNode_;
		lastNode_ = node;
	}
}

template<class T> inline void DoubleLinkedList<T>::remove(Node<T>* node)
{
	if (node == NULL)
		return;

	if (node->prevNode == NULL) // the first element
	{
		if (node->nextNode)
		{
			firstNode_ = node->nextNode;
			node->nextNode->prevNode = NULL;
			node->nextNode = NULL;
		}
		else if (node == firstNode_)
		{
			firstNode_ = lastNode_ = NULL;
		}
	}
	else if (node->nextNode == NULL) // the last element
	{
		lastNode_ = node->prevNode;
		node->prevNode->nextNode = NULL;
		node->prevNode = NULL;
	}
	else // the middle element
	{
		node->prevNode->nextNode = node->nextNode;
		node->nextNode->prevNode = node->prevNode;
		node->prevNode = NULL;
		node->nextNode = NULL;
	}
}

template<class T> inline bool DoubleLinkedList<T>::isEmpty()
{
	return firstNode_ == NULL;
}

template<class T> inline typename DoubleLinkedList<T>::iterator DoubleLinkedList<T>::getIterator()
{
	return iterator(firstNode_);
}

/////////////Iterator///////////////
template<class T> inline void DoubleLinkedList<T>::iterator::reset()
{
	currentNode_ = firstNode_;
}

template<class T> inline bool DoubleLinkedList<T>::iterator::hasNext()
{
	return currentNode_ != NULL;
}

template<class T> inline Node<T>* DoubleLinkedList<T>::iterator::next()
{
	Node<T>* temp = currentNode_;
	currentNode_ = currentNode_->nextNode;
	return temp;
}

////////////////////////////////////


#endif