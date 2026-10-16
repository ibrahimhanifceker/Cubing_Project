#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

// using namespace std;

const int N = 9;

std::vector<char> front(N), bottom(N), top(N) , left(N), right(N), back(N);
std::vector<char> store;

void establishInitialPosition() {
    for (int i = 0; i < N; i++) {
        front[i] = 'o';
        bottom[i] = 'w';
        top[i] = 'y';
        left[i] = 'g';
        right[i] = 'b';
        back[i] = 'r';
    }
}

void executeD() {
    store = front;
    front[6] = left[6];
    front[7] = left[7];
    front[8] = left[8];
    left[6] = back[8];
    left[7] = back[7];
    left[8] = back[6];
    back[6] = right[6];
    back[7] = right[7];
    back[8] = right[8];
    right[6] = store[8];
    right[7] = store[7];
    right[8] = store[6];

    store = bottom;
    bottom[6] = store[0];
    bottom[3] = store[1];
    bottom[0] = store[2];
    bottom[1] = store[5];
    bottom[2] = store[8];
    bottom[5] = store[7];
    bottom[8] = store[6];
    bottom[7] = store[3];
}

void executeDprime() {
    store = left;
    left[6] = front[6];
    left[7] = front[7];
    left[8] = front[8];
    front[8] = right[6];
    front[7] = right[7];
    front[6] = right[8];
    right[6] = back[6];
    right[7] = back[7];
    right[8] = back[8];
    back[8] = store[6];
    back[7] = store[7];
    back[6] = store[8];


 

    store = bottom;
    bottom[0] = store[6];
    bottom[1] = store[3];
    bottom[2] = store[0];
    bottom[5] = store[1];
    bottom[8] = store[2];
    bottom[7] = store[5];
    bottom[6] = store[8];
    bottom[3] = store[7];
}


void executeB() {
    store = left;
    left[0] = top[2];
    left[3] = top[1];
    left[6] = top[0];
    top[0] = right[0];
    top[1] = right[3];
    top[2] = right[6];
    right[0] = bottom[2];
    right[3] = bottom[1];
    right[6] = bottom[0];
    bottom[0] = store[0];
    bottom[1] = store[3];
    bottom[2] = store[6];

    store = back;
    back[6] = store[0];
    back[3] = store[1];
    back[0] = store[2];
    back[7] = store[3];
    back[8] = store[6];
    back[5] = store[7];
    back[2] = store[8];
    back[1] = store[5];
}


void executeBprime() {
    store = top;
    top[2] = left[0];
    top[1] = left[3];
    top[0] = left[6];
    left[0] = bottom[0];
    left[3] = bottom[1];
    left[6] = bottom[2];
    bottom[2] = right[0];
    bottom[1] = right[3];
    bottom[0] = right[6];
    right[0] = store[0];
    right[3] = store[1];
    right[6] = store[2];




    store = back;
    back[0] = store[6];
    back[1] = store[3];
    back[2] = store[0];
    back[3] = store[7];
    back[6] = store[8];
    back[7] = store[5];
    back[8] = store[2];
    back[5] = store[1];
}


void executeF() {
    store = top;
    top[6] = left[8];
    top[7] = left[5];
    top[8] = left[2];
    left[2] = bottom[6];
    left[5] = bottom[7];
    left[8] = bottom[8];
    bottom[6] = right[8];
    bottom[7] = right[5];
    bottom[8] = right[2];
    right[2] = store[6];
    right[5] = store[7];
    right[8] = store[8];
    store = front;
    front[0] = store[6];
    front[1] = store[3];
    front[2] = store[0];
    front[3] = store[7];
    front[6] = store[8];
    front[7] = store[5];
    front[8] = store[2];
    front[5] = store[1];
}


void executeFprime() {
    store = left;
    left[8] = top[6];
    left[5] = top[7];
    left[2] = top[8];
    top[6] = right[2];
    top[7] = right[5];
    top[8] = right[8];
    right[8] = bottom[6];
    right[5] = bottom[7];
    right[2] = bottom[8];
    bottom[6] = store[2];
    bottom[7] = store[5];
    bottom[8] = store[8];


    store = front;
    front[6] = store[0];
    front[3] = store[1];
    front[0] = store[2];
    front[7] = store[3];
    front[8] = store[6];
    front[5] = store[7];
    front[2] = store[8];
    front[1] = store[5];
}

void executeL() {
    store = front;
    front[0] = top[0];
    front[3] = top[3];
    front[6] = top[6];
    top[0] = back[6];
    top[3] = back[3];
    top[6] = back[0];
    back[0] = bottom[0];
    back[3] = bottom[3];
    back[6] = bottom[6];
    bottom[0] = store[6];
    bottom[3] = store[3];
    bottom[6] = store[0];


    store = left;
    left[2] = store[0];
    left[5] = store[1];
    left[8] = store[2];
    left[0] = store[6];
    left[1] = store[3];
    left[3] = store[7];
    left[6] = store[8];
    left[7] = store[5];
}


void executeLprime() {
    store = top;
    top[0] = front[0];
    top[3] = front[3];
    top[6] = front[6];
    front[0] = bottom[6];
    front[3] = bottom[3];
    front[6] = bottom[0];
    bottom[0] = back[0];
    bottom[3] = back[3];
    bottom[6] = back[6];
    back[0] = store[6];
    back[3] = store[3];
    back[6] = store[0];
    store = left;
    left[0] = store[2];
    left[1] = store[5];
    left[2] = store[8];
    left[6] = store[0];
    left[3] = store[1];
    left[7] = store[3];
    left[8] = store[6];
    left[5] = store[7];
}



void executeR() {
    store = top;
    top[2] = front[2];
    top[5] = front[5];
    top[8] = front[8];
    front[2] = bottom[8];
    front[5] = bottom[5];
    front[8] = bottom[2];
    bottom[2] = back[2];
    bottom[5] = back[5];
    bottom[8] = back[8];
    back[2] = store[8];
    back[5] = store[5];
    back[8] = store[2];
    store = right;
    right[0] = store[2];
    right[1] = store[5];
    right[2] = store[8];
    right[6] = store[0];
    right[3] = store[1];
    right[7] = store[3];
    right[8] = store[6];
    right[5] = store[7];
}


void executeRprime() {
    store = front;
    front[2] = top[2];
    front[5] = top[5];
    front[8] = top[8];
    top[2] = back[8];
    top[5] = back[5];
    top[8] = back[2];
    back[2] = bottom[2];
    back[5] = bottom[5];
    back[8] = bottom[8];
    bottom[2] = store[8];
    bottom[5] = store[5];
    bottom[8] = store[2];


    store = right;
    right[2] = store[0];
    right[5] = store[1];
    right[8] = store[2];
    right[0] = store[6];
    right[1] = store[3];
    right[3] = store[7];
    right[6] = store[8];
    right[7] = store[5];
}

void executeU() {
    store = left;
    left[0] = front[0];
    left[1] = front[1];
    left[2] = front[2];
    front[0] = right[2];
    front[1] = right[1];
    front[2] = right[0];
    right[0] = back[0];
    right[1] = back[1];
    right[2] = back[2];
    back[2] = store[0];
    back[1] = store[1];
    back[0] = store[2];

    store = top;
    top[0] = store[6];
    top[1] = store[3];
    top[2] = store[0];
    top[5] = store[1];
    top[8] = store[2];
    top[7] = store[5];
    top[6] = store[8];
    top[3] = store[7];
}


void executeUprime() {
    store = front;
    front[0] = left[0];
    front[1] = left[1];
    front[2] = left[2];
    left[2] = back[0];
    left[1] = back[1];
    left[0] = back[2];
    back[0] = right[0];
    back[1] = right[1];
    back[2] = right[2];
    right[0] = store[2];
    right[1] = store[1];
    right[2] = store[0];

    store = top;
    top[6] = store[0];
    top[3] = store[1];
    top[0] = store[2];
    top[1] = store[5];
    top[2] = store[8];
    top[5] = store[7];
    top[8] = store[6];
    top[7] = store[3];
}

void printFace(std::string faceName, std::vector<char>& face) {
    std::cout << faceName << ": ";
    for (auto i : face) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void printPosition() {
    printFace("Front", front);
    printFace("Bottom", bottom);
    printFace("Top", top);
    printFace("Left", left);
    printFace("Right", right);
    printFace("Back", back);
}

bool checkInitial() {
    int faceCount = 0;
    faceCount += count(front.begin(), front.end(), 'o') == N;
    faceCount += count(bottom.begin(), bottom.end(), 'w') == N;
    faceCount += count(top.begin(), top.end(), 'y') == N;
    faceCount += count(left.begin(), left.end(), 'g') == N;
    faceCount += count(right.begin(), right.end(), 'b') == N;
    faceCount += count(back.begin(), back.end(), 'r') == N;
    return faceCount == 6;
}

std::string positionToWord() {
    std::string word = "";
    word.reserve(6 * N);
    for (auto clr : front) { word += clr; }
    for (auto clr : bottom) { word += clr; }
    for (auto clr : top) { word += clr; }
    for (auto clr : left) { word += clr; }
    for (auto clr : right) { word += clr; }
    for (auto clr : back) { word += clr; }
    return word;
}

void wordToPosition(std::string& word) {
    for(int i = 0; i < N; i++) { front[i] = word[i];};
    for(int i = 0; i < N; i++) { bottom[i] = word[i + N];};
    for(int i = 0; i < N; i++) { top[i] = word[i + 2 * N];};
    for(int i = 0; i < N; i++) { left[i] = word[i + 3 * N];};
    for(int i = 0; i < N; i++) { right[i] = word[i + 4 * N];};
    for(int i = 0; i < N; i++) { back[i] = word[i + 5 * N];};
}

int main() {
    establishInitialPosition();

    int noChange = 0;
    std::queue<std::string> q;
    q.push(positionToWord());

    std::set<std::string> wordSet;
    std::string word, new_word;

    constexpr int threshold = 2000;

    while (!q.empty()) {
        word = q.front();
        q.pop();
        wordToPosition(word);
        executeU();
        new_word = positionToWord();
        if (wordSet.contains(new_word)) {
            noChange++;
            if (noChange > threshold) {
                break;
            }
        }
        else {
            noChange = 0;
            q.push(new_word);
            wordSet.insert(new_word);
        }

        wordToPosition(word);
        executeR();
        new_word = positionToWord();
        if (wordSet.contains(new_word)) {
            noChange++;
            if (noChange > threshold) {
                break;
            }
        }
        else {
            noChange = 0;
            q.push(new_word);
            wordSet.insert(new_word);
        }
    }
    std::cout << wordSet.size() << std::endl;
}