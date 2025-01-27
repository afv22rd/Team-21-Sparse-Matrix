/*
Sparse Matrices with Linked Lists
URI CSC 212 Spring 2023 Term Project
Group Members: C. Horton, P. Meralta, W. Kingvilay, A. Frias
*/

#include "sparseMatrix.h"

/*
Node Class Constructors
*/

Node::Node(int row, int col, int val) {
    this->row = row;
    this->col = col;
    this->value = val;
}

Node::~Node() {
    
}

/*
Matrix Class Helpers
*/

Node* SparseMatrix::findBeforeRow(int row, int col) {
    Node* beforeRow = this->topOfRow[row];
    while (beforeRow != nullptr) {
        if (beforeRow->nextInRow == nullptr) return nullptr;
        if (beforeRow->nextInRow->col >= col) return beforeRow;
        beforeRow = beforeRow->nextInRow;
    }
}

Node* SparseMatrix::findBeforeCol(int row, int col) {
    Node* beforeCol = this->topOfCol[col];
    while (beforeCol != nullptr) {
        if (beforeCol->nextInCol == nullptr) return nullptr;
        if (beforeCol->nextInCol->row >= row) return beforeCol;
        beforeCol = beforeCol->nextInCol;
    }
}

/*
Matrix Class Constructors
*/

SparseMatrix::SparseMatrix() {

}

SparseMatrix::SparseMatrix(int defaultValue) {
    this->defaultValue = defaultValue;
}

SparseMatrix::~SparseMatrix() {

}

/*
Matrix Class Basic Operations
*/

// Return node present at (row, col). If not present, return nullptr
Node* SparseMatrix::getNode(int row, int col) { 
    // Check bounds
    if (row < 0 || row >= rows || col < 0 || col >= cols) return nullptr;
    // Iterate through rows
    Node* i = this->topOfRow[row];
    while (i != nullptr) {
        if (i->col == col) return i;
        if (i->col > col) return nullptr;
        i = i->nextInRow;
    }
    return nullptr;
}

// Get value of matrix at (row, col), regardless if node exists
int SparseMatrix::getValue(int row, int col) {
    Node* target = getNode(row, col);
    if (target != nullptr) return target->value; // If node exists
    return defaultValue; // If node doesn't exist
}

// Set node with value at (row, col)
void SparseMatrix::setNode(int row, int col, int value) {
    // Check bounds and extend lists if too small
    if (row < 0 || col < 0) return;
    while (row >= rows) {
        topOfRow.push_back(nullptr);
        rows += 1;
    }
    while (col >= cols) {
        topOfCol.push_back(nullptr);
        cols += 1;
    }

    // Check if node already exists
    Node* target = getNode(row, col);
    if (target != nullptr) {
        if (value == defaultValue) return removeNode(row, col); // Node shouldn't exist
        target->value = value;
        return;
    }

    // Find pointers of before/after nodes in row and col
    Node* beforeRow = findBeforeRow(row, col);
    Node* beforeCol = findBeforeCol(row, col);

    // Create node and set its pointers
    Node* insert = new Node(row, col, value);
    if (beforeRow != nullptr) {
        insert->nextInRow = beforeRow->nextInRow;
        beforeRow->nextInRow = insert;
    }
    if (beforeCol != nullptr) {
        insert->nextInCol = beforeCol->nextInCol;
        beforeCol->nextInCol = insert;
    }
}

// Remove node at (row, col)
void SparseMatrix::removeNode(int row, int col) {
    Node* target = getNode(row, col);
    if (target == nullptr) return; // Make sure node exists
    // Find pointers of before/after nodes in row and col
    Node* beforeRow = findBeforeRow(row, col);
    Node* beforeCol = findBeforeCol(row, col);
    // Set before pointers to point to after node
    if (beforeRow != nullptr) beforeRow->nextInRow = target->nextInRow;
    if (beforeCol != nullptr) beforeCol->nextInCol = target->nextInCol;
    // Delete node
    delete target;
}

// Return a string that can be printed
std::string SparseMatrix::showMatrix() {

}

/*
Matrix Class Matrix Operations
*/

// Adds operand matrix to this matrix
void SparseMatrix::sumMatrix(SparseMatrix* operand) {

}

// Multiplies this matrix by operand matrix
void SparseMatrix::multiplyMatrix(SparseMatrix* operand) {

}
