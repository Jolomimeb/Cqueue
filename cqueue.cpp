#include "cqueue.h"
CQueue::CQueue(prifn_t priFn, HEAPTYPE heapType, STRUCTURE structure){
    //initializes member variables
    m_heap = nullptr;
    m_priorFunc = priFn;
    m_heapType = heapType;
    m_structure = structure;
    m_size = 0;
}


CQueue::~CQueue(){
    //calls the clear function
    clear();
}


void CQueue::clear() {
    clearRecursive(m_heap);
}
void CQueue::clearRecursive(Node* currHeap){
    //iterate through the heap and clears it
    if(currHeap != nullptr){
        clearRecursive(currHeap->m_left);
        clearRecursive(currHeap->m_right);
        delete currHeap;
    }
    m_size = 0;
    m_heap = nullptr;
}


CQueue::CQueue(const CQueue& rhs){
    //sets heap to null and size to 0 then calls recursive copy constructor
    m_heap = nullptr;
    m_size = 0;

    m_heap = CQueueCopyRecursive(rhs.m_heap);
    m_size = rhs.m_size;
}
Node* CQueue:: CQueueCopyRecursive(Node* aNode){
    //checks if heap is empty and performs copy

    if (aNode == nullptr){
        return nullptr;
    }

    Node* newNode = new Node(aNode->m_order);
    newNode->m_npl = aNode->m_npl;

    //goes through the heap and copy recursively
    newNode->m_left = CQueueCopyRecursive(aNode->m_left);
    newNode->m_right = CQueueCopyRecursive(aNode->m_right);

    return newNode;

}


CQueue& CQueue::operator=(const CQueue& rhs) {
    //checks for self assignment
    if (&rhs != this){
        if (m_heap != nullptr){
            clear();
        }
        //calls recursive assignment operator
        m_heap = CQueueAssignRecursive(rhs.m_heap);
    }
    return *this;
}
Node* CQueue::CQueueAssignRecursive(Node* aNode){
    //checks if heap is empty and performs assignment
    if (aNode == nullptr){
        return nullptr;
    }
    Node* newNode = new Node(aNode->m_order);
    newNode->m_npl = aNode->m_npl;

    //goes through the heap and copies recursively
    newNode->m_left = CQueueAssignRecursive(aNode->m_left);
    newNode->m_right = CQueueAssignRecursive(aNode->m_right);

    return newNode;
}


void CQueue::mergeWithQueue(CQueue& rhs) {
    //check self assignment
    if (&rhs == this){
        throw domain_error("cannot perform self assignment");
    }
    //checks if they have same priority function and throws error if they don't
    if (rhs.m_priorFunc != m_priorFunc){
        throw domain_error("cannot be merged different priority functions");
    }
    //checks if they have same data structure and throws error if they don't
    if (rhs.m_structure != m_structure){
        throw domain_error("cannot be merged different data structures");
    }
    //checks if it's empty and returns if it is
    if (rhs.m_size == 0){
        return;
    }

    //merge nonempty heap, checks if it is a skew or leftist heap
    if (getStructure() == SKEW){
        m_heap = mergeSkew(m_heap, rhs.m_heap, getPriorityFn());
    }
    else if (getStructure() == LEFTIST){
        m_heap = mergeLeftist(m_heap, rhs.m_heap, getPriorityFn());
    }
    m_size += rhs.m_size;
    rhs.m_size = 0;
    rhs.m_heap = nullptr;

}


void CQueue::insertOrder(const Order& order) {

    //creates new node
    Node* newNode = new Node(order);

    //checks if the structure is skew or leftist and then calls the merge function
    if (getStructure() == SKEW){
        m_heap = mergeSkew( m_heap,newNode,    getPriorityFn());
    }

    else if (getStructure() == LEFTIST){
        m_heap = mergeLeftist(m_heap, newNode, getPriorityFn());
    }

    m_size++;

}


int CQueue::numOrders() const{
    //returns m_size
    return m_size;
}


prifn_t CQueue::getPriorityFn() const {
    //returns m_priorFunc
    return m_priorFunc;
}


Order CQueue::getNextOrder() {
    //throws out of range if heap is empty
    if (m_heap == nullptr){
        throw out_of_range("Heap is empty");
    }
    Order nextOrder = m_heap->m_order;

    //m_heap->m_left == nullptr and m_heap->m_right == nullptr
    //checks if only one node in heap and deletes it and sets it to null
    if (m_size == 1){
        delete m_heap;
        m_heap = nullptr;
        m_size = m_size - 1;
    }

    else{
        //merges the left and right heap and deletes the top node in heap
        Node* tempHeap = m_heap;

        if (getStructure() == SKEW){
            m_heap = mergeSkew(m_heap->m_left, m_heap->m_right, getPriorityFn());
        }

        else if (getStructure() == LEFTIST){
            m_heap = mergeLeftist(m_heap->m_left, m_heap->m_right, getPriorityFn());
        }
        delete tempHeap;
        m_size--;
    };
    //returns the nextOrder
    return nextOrder;
}


void CQueue::setPriorityFn(prifn_t priFn, HEAPTYPE heapType) {

    //sets the heapType and priorFunc
    m_priorFunc = priFn;
    m_heapType = heapType;

    //builds new data structure
    m_heap = setHelper(m_heap);

}


HEAPTYPE CQueue::getHeapType() const{
    //returns heapType
    return m_heapType;
}


void CQueue::setStructure(STRUCTURE structure) {
    if (m_structure == structure) {
        return;
    }
    //sets the structure
    m_structure = structure;

    m_heap = setHelper(m_heap);

}


Node* CQueue::setHelper(Node* aNode) {
    Node *temp = nullptr;
    int tempSize = 0;
    int currSize = m_size;

    //loops until tempSize equals the size of the heap and then builds new data structure
    while (tempSize != currSize) {
        Order tempOrder = getNextOrder();
        Node *newNode = new Node(tempOrder);
        //checks if the structure is skew or leftist and then calls the merge function
        if (getStructure() == SKEW) {
            temp = mergeSkew(temp, newNode, getPriorityFn());
        } else if (getStructure() == LEFTIST) {
            temp = mergeLeftist(temp, newNode, getPriorityFn());
        }
        tempSize += 1;
    }
    m_size = tempSize;
    return temp;
}



STRUCTURE CQueue::getStructure() const {
    //returns the structure
    return m_structure;
}


void CQueue::printOrdersQueue() const {
    //calls the recursive printOrder function
    if (m_heap != nullptr){
        printOrdersQueueRecursive(m_heap);
    }
}
void CQueue::printOrdersQueueRecursive(Node* aNode) const{
    //display using preorder traversal
    cout << "[" << m_priorFunc(aNode->m_order) << "] " << "Order ID: " << aNode->m_order.getOrderID() << ", Customer ID: "
    << aNode->m_order.getCustomerID() << ", # of points: " << aNode->m_order.getPoints() << ", membership tier: "
    << aNode->m_order.getTierString() << ", item ordered: " << aNode->m_order.getItemString() << ", quantity: "
    << aNode->m_order.getCountString() << endl;

    //traverse left
    if(aNode->m_left != nullptr){
        printOrdersQueueRecursive(aNode->m_left);
    }

    //traverse right
    if(aNode->m_right != nullptr){
        printOrdersQueueRecursive(aNode->m_right);
    }
}


void CQueue::dump() const {
    if (m_size == 0) {
        cout << "Empty heap.\n" ;
    } else {
        dump(m_heap);
    }
    cout << endl;
}
void CQueue::dump(Node *pos) const {
    if ( pos != nullptr ) {
        cout << "(";
        dump(pos->m_left);
        if (m_structure == SKEW)
            cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID();
        else
            cout << m_priorFunc(pos->m_order) << ":" << pos->m_order.getOrderID() << ":" << pos->m_npl;
        dump(pos->m_right);
        cout << ")";
    }
}
ostream& operator<<(ostream& sout, const Order& order) {
    sout << "Order ID: " << order.getOrderID()
         << ", customer ID: " << order.getCustomerID()
         << ", # of points: " << order.getPoints()
         << ", membership tier: " << order.getTierString()
         << ", item ordered: " << order.getItemString()
         << ", quantity: " << order.getCountString();
    return sout;
}
ostream& operator<<(ostream& sout, const Node& node) {
    sout << node.getOrder();
    return sout;
}

void CQueue::swap(Node* & aNode, Node* & bNode){
    //perform swap on Node
    Node* tempNode = aNode;
    aNode = bNode;
    bNode = tempNode;
}


Node* CQueue::mergeLeftist(Node *aNode, Node *aHeap, prifn_t function) {

    //return the heap if node is null
    if (aNode == nullptr){
        return aHeap;
    }
    //return the node if heap is null
    if (aHeap == nullptr){
        return aNode;
    }

    //Check if it's a min heap
    if (m_heapType == MINHEAP) {
        //swap if aNode's priority is greater than the heaps priority
        if (function(aNode->m_order) > function(aHeap->m_order)){
            swap(aNode, aHeap);
        }
    }
        //check if it's a max heap
    else if (m_heapType == MAXHEAP) {
        //swap if aNode's priority is less than the heaps priority
        if (function(aNode->m_order) < function(aHeap->m_order)){
            swap(aNode, aHeap);
        }
    }

    //merge node's right child with heap to create new subtree
    aNode->m_right = mergeLeftist(aNode->m_right, aHeap, function);


    //swap anode's left and right child if left is null or has a lower npl than right child
    if (aNode->m_left != nullptr and  aNode->m_right != nullptr){
        if (aNode->m_left->m_npl < aNode->m_right->m_npl){
            swap(aNode->m_left, aNode->m_right);
        }
    }
    else if (aNode->m_left == nullptr and  aNode->m_right != nullptr){
        swap(aNode->m_left, aNode->m_right);
    }

    //update npl based on right child's npl
    if (aNode->m_right != nullptr){
        aNode->m_npl = aNode->m_right->m_npl + 1;
    }
    else{
        aNode->m_npl = 0;
    }

    return aNode;
}


Node* CQueue::mergeSkew(Node* aHeap, Node* aNode, prifn_t function) {
    //return the heap if node is null
    if (aHeap == nullptr){
        return aNode;
    }
    //return the node if heap is null
    if (aNode == nullptr){
        return aHeap;
    }


    //Check if it's a min heap
    if (m_heapType == MINHEAP) {
        //swap if aHeap's priority is greater than the heaps priority
        if (function(aHeap->m_order) > function(aNode->m_order)){
            swap(aHeap, aNode);
        }
    }

    //check if it's a max heap
    else if (m_heapType == MAXHEAP) {
        //swap if aHeap's priority is less than the heaps priority
        if (function(aHeap->m_order) < function(aNode->m_order)){
            swap(aHeap, aNode);
        }
    }

    swap( aHeap->m_left, aHeap->m_right);

    //merge node's left child with heap to create new subtree
    aHeap->m_left = mergeSkew(  aNode, aHeap->m_left, function);

    return aHeap;
}



