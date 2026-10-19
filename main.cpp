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

vector<int> longestPalindrome(const vector<int>& stream) {
    int n = stream.size();
    vector<int> radius(2 * n);
    int left = 0, right = -1;

    // Odd-length palindromes
    for (int center = 0; center < n; center++) {
        int r = center > right ? 1
            : min(radius[left + right - center], right - center + 1);

        while (center - r >= 0 && center + r < n &&
               stream[center - r] == stream[center + r])
            r++;

        radius[center] = r;

        if (center + r - 1 > right) {
            left = center - r + 1;
            right = center + r - 1;
        }
    }

    // Even-length palindromes
    left = 0;
    right = -1;

    for (int center = 0; center < n; center++) {
        int r = center > right ? 0
            : min(radius[n + left + right - center + 1],
                  right - center + 1);

        while (center - r - 1 >= 0 && center + r < n &&
               stream[center - r - 1] == stream[center + r])
            r++;

        radius[n + center] = r;

        if (center + r - 1 > right) {
            left = center - r;
            right = center + r - 1;
        }
    }

    // Find the longest palindrome
    int bestStart = 0, bestLength = 0;

    for (int center = 0; center < n; center++) {
        // Odd-length palindrome
        int length = 2 * radius[center] - 1;
        if (length > bestLength) {
            bestLength = length;
            bestStart = center - radius[center] + 1;
        }

        // Even-length palindrome
        int evenRadius = radius[n + center];
        length = 2 * evenRadius;
        if (length > bestLength) {
            bestLength = length;
            bestStart = center - evenRadius;
        }
    }

    return vector<int>(
        stream.begin() + bestStart,
        stream.begin() + bestStart + bestLength
    );
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

    vector<int> palindrome = longestPalindrome(stream);

    cout << "The stream is: ";

    for(int i : stream){
        cout << i;
    }

    cout << endl << "Longest palindrome is: ";

    for(int i : palindrome){
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