#include<bits/stdc++.h>
using namespace std;

void generateRandomBits(vector<int> &stream, int size){
    for(int i = 0; i < size; i++){
        int num = rand()%2;
        stream.push_back(num);
    }
}

void generateBitsWithZeroRuns(vector<int> &stream, int size){
    vector<int> zeroes = {0,0,0,0};
    for(int i = 0; i < size - 4; i++){
        int num = rand()%2;
        stream.push_back(num);
    }
    stream.insert(stream.begin() + rand()%(size - 3), zeroes.begin(), zeroes.end());
}

void insertBits(vector<int> &stream, int size){
    cout << "Enter the stream: ";
    for(int i = 0; i < size; i++){
        int num;
        cin >> num;
        stream.push_back(num);
    }
}

vector<int> longestPalindrome(vector<int> stream){
    
}

void digital_input(){
    cout << "1. Generate completely random data" << endl << 
            "2. Generate data with fixed zero sequences" << endl << 
            "3. Enter data manually" << endl << endl;

    int option;
    vector<int> stream;
    int size;

    cin >> option;
    cout << endl << "size of the stream: ";
    cin >> size;
    cout << endl << endl;

    switch(option){
        case(1): generateRandomBits(stream, size);
        break;
        case(2): generateBitsWithZeroRuns(stream, size);
        break;
        case(3): insertBits(stream, size);
        break;
        default: ;
    }

    cout << "the stream is: ";

    for(int i : stream){
        cout << i;
    }
}

int main(){
    cout << "==================================" << endl << 
            " DIGITAL SIGNAL ENCODER & DECODER " << endl << 
            "==================================" << endl << endl;

    int option;

    cout << "1. Digital Input" << endl <<
            "2. Analog Input" << endl <<
            "3. Exit" << endl << endl;

    cin >> option;
    cout << endl;
    srand(time(0));

    switch(option){
        case(1): digital_input();
        break;
        case(2): cout << "2";
        break;
        case(3): cout << "3";
        break;
        default: cout << "Enter a valid option";
    }
    
    return 0;
}