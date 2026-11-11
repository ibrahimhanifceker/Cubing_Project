#include <iostream>
#include <unordered_set>
#include <string>
#include <vector>
#include <queue>
#include<fstream>
#include <set>
#include <algorithm>
#include <fstream>
#include <cstdint>

// using namespace std;

// cube map now: only checks the 34 small faces that are affected by U and R
/*  
    *POSITION MAPPING:
    FRONT
    0   1   2
    x   x   5
    x   x   8

    TOP: 
    0   1   2
    3   x   5       middle top piece doesn't move
    6   7   8

    BOTTOM:
    x   x   2
    x   x   5
    x   x   8

    RIGHT:
    0   1   2
    3   x   5       middle right piece doesn't move
    6   7   8

    LEFT:
    0   1   2
    x   x   x
    x   x   x

    BACK:
    0   1   2
    x   x   5
    x   x   8



*/
std::vector<char> front(9), bottom(9), top(9) , left(9), right(9), back(9);
std::vector<int> groupOrder(1, 0); //needs to have something first

void establishInitialPosition() {
    for (int i = 0; i < 9; i++) {
        front[i] = 'o';
        bottom[i] = 'w';
        top[i] = 'y';
        left[i] = 'g';
        right[i] = 'b';
        back[i] = 'r';
    }
}

void executeR() {
    //Only saving a few of the changed pieces
    char top2 = top[2], top5 = top[5], top8 = top[8];

    top[2] = front[2];
    top[5] = front[5];
    top[8] = front[8];

    front[2] = bottom[8];
    front[5] = bottom[5];
    front[8] = bottom[2];

    bottom[2] = back[2];
    bottom[5] = back[5];
    bottom[8] = back[8];

    back[2] = top8;
    back[5] = top5;
    back[8] = top2;

    char right0 = right[0];
    right[0] = right[2];
    right[2] = right[8];
    right[8] = right[6];
    right[6] = right0;

    char right1 = right[1];
    right[1] = right[5];
    right[5] = right[7];
    right[7] = right[3];
    right[3] = right1;
}

void executeRprime() {
    char front2 = front[2], front5 = front[5], front8 = front[8];

    front[2] = top[2];
    front[5] = top[5];
    front[8] = top[8];

    top[2] = back[8];
    top[5] = back[5];
    top[8] = back[2];

    back[2] = bottom[2];
    back[5] = bottom[5];
    back[8] = bottom[8];

    bottom[2] = front8;
    bottom[5] = front5;
    bottom[8] = front2;

    char right0 = right[0];
    right[0] = right[6];
    right[6] = right[8];
    right[8] = right[2];
    right[2] = right0;

    char right1 = right[1];
    right[1] = right[3];
    right[3] = right[7];
    right[7] = right[5];
    right[5] = right1;
}

void executeR2() {
    char top2 = top[2], top5 = top[5], top8 = top[8];
    top[2] = bottom[8];
    top[5] = bottom[5];
    top[8] = bottom[2];
    bottom[8] = top2;
    bottom[5] = top5;
    bottom[2] = top8;

    char front2 = front[2], front5 = front[5], front8 = front[8];
    front[2] = back[8];
    front[5] = back[5];
    front[8] = back[2];
    back[8] = front2;
    back[5] = front5;
    back[2] = front8;

    char right0 = right[0]; 
    right[0] = right[8]; 
    right[8] = right0;
    
    char right2 = right[2]; 
    right[2] = right[6]; 
    right[6] = right2;
    
    char right1 = right[1]; 
    right[1] = right[7]; 
    right[7] = right1;
    
    char right3 = right[3]; 
    right[3] = right[5]; 
    right[5] = right3;
}

void executeU() {
    char left0 = left[0], left1 = left[1], left2 = left[2];

    left[0] = front[0];
    left[1] = front[1];
    left[2] = front[2];

    front[0] = right[2];
    front[1] = right[1];
    front[2] = right[0];

    right[0] = back[0];
    right[1] = back[1];
    right[2] = back[2];

    back[0] = left2;
    back[1] = left1;
    back[2] = left0;

    char top0 = top[0];
    top[0] = top[6];
    top[6] = top[8];
    top[8] = top[2];
    top[2] = top0;

    char top1 = top[1];
    top[1] = top[3];
    top[3] = top[7];
    top[7] = top[5];
    top[5] = top1;
}

void executeUprime() {
    char front0 = front[0], front1 = front[1], front2 = front[2];

    front[0] = left[0];
    front[1] = left[1];
    front[2] = left[2];

    left[0] = back[2];
    left[1] = back[1];
    left[2] = back[0];

    back[0] = right[0];
    back[1] = right[1];
    back[2] = right[2];

    right[0] = front2;
    right[1] = front1;
    right[2] = front0;

    char top0 = top[0];
    top[0] = top[2];
    top[2] = top[8];
    top[8] = top[6];
    top[6] = top0;

    char top1 = top[1];
    top[1] = top[5];
    top[5] = top[7];
    top[7] = top[3];
    top[3] = top1;
}

void executeU2() {
    char front0 = front[0], front1 = front[1], front2 = front[2];
    front[0] = back[2];
    front[1] = back[1];
    front[2] = back[0];
    back[2] = front0;
    back[1] = front1;
    back[0] = front2;

    char left0 = left[0], left1 = left[1], left2 = left[2];
    left[0] = right[2];
    left[1] = right[1];
    left[2] = right[0];
    right[2] = left0;
    right[1] = left1;
    right[0] = left2;

    char top0 = top[0]; 
    top[0] = top[8]; 
    top[8] = top0;

    char top2 = top[2]; 
    top[2] = top[6]; 
    top[6] = top2;
    
    char top1 = top[1]; 
    top[1] = top[7]; 
    top[7] = top1;
    
    char top3 = top[3]; 
    top[3] = top[5]; 
    top[5] = top3;
}

bool checkIfSolved() { //Only checks the 32 affected small faces now
    for (int i = 0; i < 9; i++){
        if (top[i] != 'y') {
            return false;
        }
    }
    for (int i = 0; i < 9; i++){ 
        if (right[i] != 'b'){ 
            return false;
        }
    }
    if (left[0] != 'g' or left[1] != 'g' or left[2] != 'g') {
        return false;
    }
    if (front[0] != 'o' or front[1] != 'o' or front[2] != 'o' or front[5] != 'o' or front[8] != 'o'){
        return false;
    }
    if (back[0] != 'r' or back[1] != 'r' or back[2] != 'r' or back[5] != 'r' or back[8] != 'r'){
        return false;
    }
    if (bottom[2] != 'w' or bottom[5] != 'w' or bottom[8] != 'w') {
        return false;
    }

    return true;
}

int findOrderOfMoveSequence(const std::string& sequenceDescription) {
    int size = sequenceDescription.length();
    bool Done = false;
    int n = 0;
    establishInitialPosition();
    // std::cout << wordDescription << std::endl;
    while (Done == false){
        for (int i = 0; i< size; i++ ){
            if (sequenceDescription[i] == 'R'){
                executeR();
            }
            else if (sequenceDescription[i] == 'U'){
                executeU();
            }
            else if (sequenceDescription[i] == 'r'){
                executeRprime();
            }
            else if (sequenceDescription[i] == 'u'){
                executeUprime();
            }
            else if (sequenceDescription[i] == 'Z'){
                executeR2();
            }
            else if (sequenceDescription[i] == 'X'){
                executeU2();
            }
        }
        n++;
        if (checkIfSolved()){
            Done = true;
        }
    }
    //std::cout << sequenceDescription << std::endl;
    return n;
}

std::string compressSequence(const std::string& initial) {
    std::string compressedSequence; //turns UUU to u (u prime)
    size_t len = initial.length(); //size_t is specifically used to store object/ string sizes.
    size_t i = 0;

    while (i < len) {
        char move = initial[i];
        int count = 1;
        while (i + count < len and initial[i + count] == move) {
            count++;
        }

        int sameLetterCount = count % 4;
        if (move == 'U') {
            if (sameLetterCount == 1){
                compressedSequence.push_back('U');
            }
            else if(sameLetterCount == 2) {
                compressedSequence.push_back('X');
            }
            else if (sameLetterCount == 3) {
                compressedSequence.push_back('u');
            }
        } else if (move == 'R') {
            if (sameLetterCount == 1) {
                compressedSequence.push_back('R');
            }
            else if (sameLetterCount == 2) {
                compressedSequence.push_back('Z');
            }
            else if (sameLetterCount == 3) {
                compressedSequence.push_back('r');
            }
        }

        i += count;
    }
    return compressedSequence;
}

int main() {
    std::cout << "This program will explore the group of transformations\n";
    std::cout << "Generated by the U and R. This group will be denoted by G.\n";

    std::cout << "For this program to work, please make sure you have ran the PrintingElementsUR.exe program\n";

    std::ifstream file("elementsUR.txt", std::ios::in | std::ios::binary); 
    if (!file.is_open()) {
        std::cerr << "Check file name again: "<< std::endl;
        return 1;
    }
    //apparently ios::binary stops compiler from auto converting \n in text files

    std::string currentSequence;
    currentSequence.reserve(64); //sets the default storage for sequence as 64 bits instead of making resize for large strings
    char move;
    int order;
    int elementCount = 0;

    while (file.get(move)){
        if (move == ' ' or move == '\n' or move == '\r'){
            if(!currentSequence.empty()){
                order = findOrderOfMoveSequence(currentSequence); //if U and R isn't compressed, use compressSequence(currentSequence)
                if (order >= groupOrder.size()) {
                    groupOrder.resize(order + 1, 0); // If new higher order is returned, expands vector
                }
                groupOrder[order]++;
                currentSequence.clear();

                elementCount++;
                if (elementCount % 1000000 == 0) {
                    std::cout << "Program has found the order for " << elementCount << " elements\n";
                }
                establishInitialPosition();
            }
        }
        else{
            currentSequence.push_back(move);
        }
    }

    std::cout << "1 element of order 1\n";
    for (int o = 1; o < groupOrder.size(); o++) { 
        if (groupOrder[o] > 0) {
                std::cout << groupOrder[o] << " elements of order " << o << "\n";
        }
    }
}
