// tests.h

#ifndef TESTS_H
#define TESTS_H

#include "Graph.h"  
#include <iostream>
#include <cassert>

void ObhodAll(Tree<int>* tr) {

    tr->insert(2);
    tr->insert(1);
    tr->insert(3);
    tr->insert(4);

    std::vector<int> KLP_res = {2, 1, 3, 4}; 
    std::vector<int> LKP_res = {1, 2, 3, 4}; 
    std::vector<int> LPK_res = {1, 4, 3, 2};
    
    assert(tr->copyAsString() == KLP_res);

    tr->LKP();
    tr->KLP();
    tr->LPK();
}

void DeleRoot(Tree<int>* tr) {
    tr->deleteElement(2);

   
    std::vector<int> KLP_res = {3, 1, 4}; 
    std::vector<int> LKP_res = {1, 3, 4};
    std::vector<int> LPK_res = {1, 4, 3};

    assert(tr->copyAsString() == KLP_res);
    tr->LKP();
    tr->KLP();
    tr->LPK();
}

void DeleLeaf(Tree<int>* tr) {
    tr->deleteElement(1);

    std::vector<int> KLP_res = {3, 4};
    std::vector<int> LKP_res = {3, 4};
    std::vector<int> LPK_res = {4, 3};

    assert(tr->copyAsString() == KLP_res);
    tr->LKP();
    tr->KLP();
    tr->LPK();
}

void DelNodeWith1Child(Tree<int>* tr) {
    tr->deleteElement(3);

    
    std::vector<int> KLP_res = {4};
    std::vector<int> LKP_res = {4};
    std::vector<int> LPK_res = {4};

    assert(tr->copyAsString() == KLP_res);
    tr->LKP(); 
    tr->KLP();
    tr->LPK(); 
}

void Clear_test(Tree<int>* tr) {
    delete tr;

    std::vector<int> expectedEmpty = {};

    assert(tr->copyAsString() == expectedEmpty);
    tr->LKP(); 
    tr->KLP(); 
    tr->LPK(); 
}


void runTests() {
    Tree<int>* tr = new Tree<int>;

    ObhodAll(tr);
    DeleRoot(tr);
    DeleLeaf(tr);
    DelNodeWith1Child(tr);
    Clear_test(tr);
    delete tr;

}


#endif // TESTS_H
