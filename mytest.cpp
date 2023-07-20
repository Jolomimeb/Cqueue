/*****************************************
** File:    mytest.cpp
** Project: CMSC 341 Project 3, Spring 2023
** Author:  Oritsejolomisan Mebaghanje
** Date:    04/17/23
** E-mail:  xz94254@umbc.edu
**
** This file contains the program for mytest.cpp.
**
**
***********************************************/

#include "cqueue.h"
#include <random>
int priorityFn1(const Order &order);// works with a MAXHEAP
int priorityFn2(const Order &order);// works with a MINHEAP

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }
    void setSeed(int seedNum){
        // we have set a default value for seed in constructor
        // we can change the seed by calling this function after constructor call
        // this gives us more randomness
        m_generator = std::mt19937(seedNum);
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }

private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};

class myTester{
public:
    bool testInsertNormalMinHeap();
    bool testInsertNormalMinHeapHelper(Node* aNode, prifn_t function);

    bool testInsertNormalMaxHeap();
    bool testInsertNormalMaxHeapHelper(Node* aNode, prifn_t function);

    bool testRemoveNormalMinHeap();
    bool testRemoveNormalMinHeapHelper(Node* aNode, prifn_t function);
    bool testRemoveNormalMaxHeap();
    bool testRemoveNormalMaxHeapHelper(Node* aNode, prifn_t function);

    bool testLeftistHeapValues();
    bool testLeftistHeapValuesRecursive(Node* aNode);
    bool testLeftistHeapProperty();
    bool testLeftistHeapPropertyRecursive(Node* aNode);

    bool testChangePriFunction();

    bool testMergeEdge();
    bool testMergeNormal();

    bool testCopyConstructorNormal();
    bool testCopyConstructorEdge();

    bool testAssignmentOperatorNormal();
    bool testAssignmentOperatorEdge();

    bool testDequeEmpty();
    bool testMergePriorityException();

private:
};

int main(){
    myTester Tester1;

    //returns true
    if(Tester1.testInsertNormalMinHeap()){
        cout << "Test Insert Normal Min returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Insert normal Min returned false" << endl;
    }

    //returns true
    if(Tester1.testInsertNormalMaxHeap()){
        cout << "Test Insert Normal Max returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Insert normal Max returned false" << endl;
    }

    //returns true
    if(Tester1.testRemoveNormalMinHeap()){
        cout << "Test Remove Normal Min returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Remove Normal Min returned false" << endl;
    }

    //returns true
    if(Tester1.testRemoveNormalMaxHeap()){
        cout << "Test Remove Normal Max returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Remove normal Max returned false" << endl;
    }

    //returns true
    if(Tester1.testLeftistHeapValues()){
        cout << "Test leftist Heap values returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Leftist Heap values returned false" << endl;
    }

    //returns true
    if(Tester1.testLeftistHeapProperty()){
        cout << "Test leftist Heap Property returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Leftist Heap Property returned false" << endl;
    }

    //returns true
    if(Tester1.testChangePriFunction()){
        cout << "Test Change priority Function returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Change priority Function false" << endl;
    }

    //returns true
    if(Tester1.testMergeEdge()){
        cout << "Test Merge Edge returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Merge Edge returned false" << endl;
    }

    //returns true
    if(Tester1.testMergeNormal()){
        cout << "Test Merge Normal returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Merge Normal returned false" << endl;
    }

    //returns true
    if(Tester1.testCopyConstructorNormal()){
        cout << "Test copy constructor returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test copy constructor returned false" << endl;
    }

    //returns true
    if(Tester1.testCopyConstructorEdge()){
        cout << "Test copy constructor Edge returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test copy constructor Edge returned false" << endl;
    }

    //returns true
    if(Tester1.testAssignmentOperatorNormal()){
        cout << "Test assignment operator returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test assignment operator returned false" << endl;
    }

    //returns true
    if(Tester1.testAssignmentOperatorEdge()){
        cout << "Test assignment operator Edge returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test assignment operator Edge returned false" << endl;
    }

    //returns true
    if(Tester1.testDequeEmpty()){
        cout << "Test Dequeue empty returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Dequeue empty returned false" << endl;
    }

    //returns true
    if(Tester1.testMergePriorityException()){
        cout << "Test Merge Priority Exception returned true, works correctly for normal case" << endl;
    }
    else{
        cout << "Test Merge Priority Exception returned false" << endl;
    }

    return 0;
}

bool myTester::testInsertNormalMinHeap(){
    bool result = false;
    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);

    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    //calls helper function
    if (testInsertNormalMinHeapHelper(aQueue.m_heap, priorityFn2)){
        result = true;
    }

    return result;
}
bool myTester::testInsertNormalMinHeapHelper(Node *aNode, prifn_t function) {

    bool result = true;
    //checks if node is null
    if (aNode == nullptr){
        return result;
    }
    //checks if node has children
    if (aNode->m_left == nullptr and aNode->m_right == nullptr){
        result = true;
        return result;
    }
    //checks if left is null and if the priority function of left order is greater than that of node
    if (aNode->m_left != nullptr and function(aNode->m_left->m_order) < function(aNode->m_order)) {
        result = false;
    }
    //checks if right is null and if the priority function of right order is greater than that of node
    if (aNode->m_right != nullptr and function(aNode->m_right->m_order) < function(aNode->m_order)) {
        result = false;
    }
    //recursive call
    testInsertNormalMaxHeapHelper(aNode->m_left, function);
    testInsertNormalMaxHeapHelper(aNode->m_right, function);

    return result;
}


bool myTester::testInsertNormalMaxHeap(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);

    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    //calls recursive function
    if (testInsertNormalMaxHeapHelper(aQueue.m_heap, priorityFn1)){
        result = true;
    }

    return result;
}
bool myTester::testInsertNormalMaxHeapHelper(Node* aNode, prifn_t function){

    bool result = true;
    //checks if node is empty
    if (aNode == nullptr){
        return result;
    }
    //checks if node has children
    if (aNode->m_left == nullptr and aNode->m_right == nullptr){
        result = true;
        return result;
    }
    //checks if left is null and if the priority function of left order is greater than that of node
    if (aNode->m_left != nullptr and function(aNode->m_left->m_order) > function(aNode->m_order)) {
        result = false;
    }
    //checks if right is null and if the priority function of right order is greater than that of node
    if (aNode->m_right != nullptr and function(aNode->m_right->m_order) > function(aNode->m_order)) {
        result = false;
    }
    //recursive call
    testInsertNormalMaxHeapHelper(aNode->m_left, function);
    testInsertNormalMaxHeapHelper(aNode->m_right, function);

    return result;
}


bool myTester::testRemoveNormalMinHeap(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);

    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //gets the next order
    aQueue.getNextOrder();
    //calls recursive function
    if (testRemoveNormalMinHeapHelper(aQueue.m_heap, priorityFn2)){
        result = true;
    }

    return result;
}
bool myTester::testRemoveNormalMinHeapHelper(Node* aNode, prifn_t function){

    bool result = true;
    //checks if the node is null
    if (aNode == nullptr){
        return result;
    }
    //checks if node has children
    if (aNode->m_left == nullptr and aNode->m_right == nullptr){
        result = true;
        return result;
    }
    //checks if left is null and if the priority function of left order is greater than that of node
    if (aNode->m_left != nullptr and function(aNode->m_left->m_order) < function(aNode->m_order)) {
        result = false;
    }
    //checks if right is null and if the priority function of right order is greater than that of node
    if (aNode->m_right != nullptr and function(aNode->m_right->m_order) < function(aNode->m_order)) {
        result = false;
    }
    //recursive call
    testRemoveNormalMinHeapHelper(aNode->m_left, function);
    testRemoveNormalMinHeapHelper(aNode->m_right, function);

    return result;
}



bool myTester::testRemoveNormalMaxHeap(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);

    for (int i=0;i<300;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //returns the next order
    aQueue.getNextOrder();
    //recursive call
    if (testRemoveNormalMaxHeapHelper(aQueue.m_heap, priorityFn1)){
        result = true;
    }
    return result;
}
bool myTester::testRemoveNormalMaxHeapHelper(Node* aNode, prifn_t function){

    bool result = true;
    //checks if the node is null
    if (aNode == nullptr){
        return result;
    }
    //check if the node have children
    if (aNode->m_left == nullptr and aNode->m_right == nullptr){
        result = true;
        return result;
    }
    //checks if left is null and if the priority function of left order is greater than that of the node
    if (aNode->m_left != nullptr and function(aNode->m_left->m_order) > function(aNode->m_order)) {
        result = false;
    }
    //checks if right is null and if the priority function of right order is greater than that of the node
    if (aNode->m_right != nullptr and function(aNode->m_right->m_order) > function(aNode->m_order)) {
        result = false;
    }
    //recursive call
    testInsertNormalMaxHeapHelper(aNode->m_left, function);
    testInsertNormalMaxHeapHelper(aNode->m_right, function);

    return result;
}


bool myTester::testLeftistHeapValues(){
    bool result = false;
    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);

    for (int i=0;i<10;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //calls recursive function
    if (testLeftistHeapValuesRecursive(aQueue.m_heap)){
        result = true;
    }

    return result;
}
bool myTester::testLeftistHeapValuesRecursive(Node* aNode){
    bool result = false;
    //checks if tree is empty
    if (aNode == nullptr){
        return result;
    }
    //checks if left child or right child is null
    if (aNode->m_left == nullptr or aNode->m_right == nullptr){
        return result;
    }
    //checks if the npl of the left child is greater than or equal to that of the right
    if (aNode->m_left->m_npl >= aNode->m_right->m_npl) {
        result = true;
    }
    //recursive call
    testLeftistHeapValuesRecursive(aNode->m_left);
    testLeftistHeapValuesRecursive(aNode->m_right);

    return result;
}


bool myTester::testLeftistHeapProperty(){
    bool result = false;
    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);

    for (int i=0;i<10;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //calls recursive function
    if (testLeftistHeapPropertyRecursive(aQueue.m_heap)){
        result = true;
    }

    return result;
}
bool myTester::testLeftistHeapPropertyRecursive(Node* aNode){
    bool result = false;
    //checks if node is empty
    if (aNode == nullptr){
        return result;
    }
    //checks if left child or right child is null
    if (aNode->m_left == nullptr or aNode->m_right == nullptr){
        return result;
    }
    //checks if the npl of the left node is greater than or equal to that of the right node
    if (aNode->m_left->m_npl >= aNode->m_right->m_npl) {
        result = true;
    }
    //recursive call
    testLeftistHeapPropertyRecursive(aNode->m_left);
    testLeftistHeapPropertyRecursive(aNode->m_right);

    return result;
}


bool myTester::testChangePriFunction(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);

    for (int i=0;i<10;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    
    //changes the priority function
    aQueue.setPriorityFn(priorityFn2, MINHEAP);
    //checks if the priority function was successfully changed
    if (aQueue.getPriorityFn() == priorityFn2){
        result = true;
    }


    return result;
}

bool myTester::testMergeEdge(){
    bool result = false;
    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    CQueue emptyQueue(priorityFn2, MINHEAP, LEFTIST);

    for (int i=0;i<3;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //merging empty queue with normal queue
    int currSize = emptyQueue.m_size;
    emptyQueue.mergeWithQueue(aQueue);

    if (emptyQueue.m_size != currSize){
        result = true;
    }

    return result;
}
bool myTester::testMergeNormal(){
    bool result = false;
    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    CQueue newQueue(priorityFn2, MINHEAP, LEFTIST);

    //builds first cqueue
    for (int i=0;i<3;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    //builds second cqueue
    for (int i=0;i<5;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        newQueue.insertOrder(anOrder);
    }
    //saves the size of the new queue
    int currSize = newQueue.m_size;
    newQueue.mergeWithQueue(aQueue);

    if (newQueue.m_size != currSize){
        result = true;
    }

    return result;
}

bool myTester::testCopyConstructorNormal(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);


    for (int i=0;i<10;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //performs copy
    CQueue newQueue(aQueue);
    //checks if the two heaps have different address and if the order ID are the same
    if (newQueue.m_heap != aQueue.m_heap and newQueue.m_heap->m_order.getOrderID() == aQueue.m_heap->m_order.getOrderID()){
        result = true;
    }

    return result;
}
bool myTester::testCopyConstructorEdge(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);
    //performs copy
    CQueue newQueue(aQueue);
    //check if the two heap are empty
    if (newQueue.m_heap == nullptr and aQueue.m_heap == nullptr){
        result = true;
    }

    return result;
}

bool myTester::testAssignmentOperatorNormal(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn1, MAXHEAP, LEFTIST);

    for (int i=0;i<5;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }

    //performs assignment
    CQueue newQueue = aQueue;
    //checks if the two heaps have different address and if the order ID are the same
    if (newQueue.m_heap != aQueue.m_heap and newQueue.m_heap->m_order.getOrderID() == aQueue.m_heap->m_order.getOrderID()){
        result = true;
    }

    return result;
}
bool myTester::testAssignmentOperatorEdge(){
    bool result = false;

    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);


    //assigning empty queue
    CQueue newQueue = aQueue;
    //checks if the previous heap and new heap are both empty
    if (newQueue.m_heap == nullptr and aQueue.m_heap == nullptr){
        result = true;
    }

    return result;
}

bool myTester::testDequeEmpty(){
    bool result = false;
    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);

    //uses exception to perform test
    try{
        aQueue.getNextOrder();
        result = false;
    }
    catch (out_of_range & e){
        result = true;
    }

    return result;
}
bool myTester::testMergePriorityException(){
    bool result = false;
    //build cqueue
    Random orderIdGen(MINORDERID,MAXORDERID);
    Random customerIdGen(MINCUSTID,MAXCUSTID);
    customerIdGen.setSeed(0);
    Random membershipGen(0,5); // there are six tiers
    Random pointsGen(MINPOINTS,MAXPOINTS);
    Random itemGen(0,5); // there are six items
    Random countGen(0,3); // there are three possible quantity values
    CQueue aQueue(priorityFn2, MINHEAP, LEFTIST);
    CQueue newQueue(priorityFn1, MAXHEAP, LEFTIST);

    //creates first cqueue
    for (int i=0;i<3;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        aQueue.insertOrder(anOrder);
    }
    //creates second cqueue
    for (int i=0;i<5;i++){
        Order anOrder(static_cast<ITEM>(itemGen.getRandNum()),
                      static_cast<COUNT>(countGen.getRandNum()),
                      static_cast<MEMBERSHIP>(membershipGen.getRandNum()),
                      pointsGen.getRandNum(),
                      customerIdGen.getRandNum(),
                      orderIdGen.getRandNum());
        newQueue.insertOrder(anOrder);
    }
    //uses exception to test
    try{
        newQueue.mergeWithQueue(aQueue);
        result = false;
    }
    catch (domain_error & e){
        result = true;
    }

    return result;
}


int priorityFn1(const Order &order) {
    //this function works with a MAXHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-5003]
    //the highest priority would be 3+5000 = 5003
    //the lowest priority would be 0+0 = 0
    //the larger value means the higher priority
    int priority = static_cast<int>(order.getCount()) + order.getPoints();
    return priority;
}

int priorityFn2(const Order &order) {
    //this funcction works with a MINHEAP
    //priority value is determined based on some criteria
    //priority value falls in the range [0-10]
    //the highest priority would be 0+0 = 0
    //the lowest priority would be 5+5 =10
    //the smaller value means the higher priority
    int priority = static_cast<int>(order.getItem()) + static_cast<int>(order.getMemebership());
    return priority;
}
