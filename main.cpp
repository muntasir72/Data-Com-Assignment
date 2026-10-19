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

vector<int> NRZ_L(vector<int> stream){
    vector<int> encoded_stream;
    for(int i : stream){
        if(i == 0) encoded_stream.push_back(1);
        else encoded_stream.push_back(-1);
    }
    return encoded_stream;
}

vector<int> NRZ_I(vector<int> stream){
    int level = 1;
    vector<int> encoded_stream;
    for(int i : stream){
        if(i == 1) level = (level+1)%2;
        else level = level;
        encoded_stream.push_back(level);
    }
    return NRZ_L(encoded_stream);
}

vector<int> Manchester(vector<int> stream){
    vector<int> zero = {1,-1};
    vector<int> one = {-1,1};

    vector<int> encoded_stream;

    for(int i = 0; i < stream.size(); i++){
        if(stream[i] == 0) encoded_stream.insert(encoded_stream.begin() + 2*i, zero.begin(), zero.end());
        else encoded_stream.insert(encoded_stream.begin() + 2*i, one.begin(), one.end());
    }

    return encoded_stream;
}

vector<int> Differential_Manchester(vector<int> stream){
    int level = 1;

    vector<int> encoded_stream;

    for(int i : stream){
        if(i == 1) level = (level+1)%2;
        else level = level;
        encoded_stream.push_back(level);
    }

    return Manchester(encoded_stream);
}


vector<int> B8ZS(vector<int> stream){

}

vector<int> HDB3(vector<int> stream){

}

vector<int> scrambling_schemes(vector<int> stream){
    int option;

    cout << "Which Scrambling Technique do you want?" << endl <<
            "1. B8ZS" << endl <<
            "2. HDB3" << endl;
    
    select_scrambling_scheme:

    cin >> option;

    switch(option){
        case(1): return B8ZS(stream);
        break;
        case(2): return HDB3(stream);
        break;
        default: cout << "Please select a valid option";
        goto select_scrambling_scheme;
    }
    
}

vector<int> scrambling(vector<int> stream){
    cout << "Do you want to implement scrambling?" << endl <<
            "1. Yes" << endl <<
            "2. No" << endl;
    int option;

    select_scrambling:

    cin >> option;

    switch(option){
        case(1): return scrambling_schemes(stream);
        break;
        case(2): return stream;
        break;
        default: cout << "Please select a valid option." << endl;
        goto select_scrambling;
    }
}

void lineEncodingSchemes(vector<int> &stream){
    cout << "1. NRZ-L" << endl << 
            "2. NRZ-I" << endl <<
            "3. Manchester" << endl <<
            "4. Differential Manchester" << endl << 
            "5. AMI" << endl << endl;

    int option;
    vector<int> encoded_stream;

    select_scheme:

    cin >> option;
    cout << endl;

    switch(option){
        case(1):encoded_stream = NRZ_L(stream);
        break;
        case(2):encoded_stream = NRZ_I(stream);
        break;
        case(3):encoded_stream = Manchester(stream);
        break;
        case(4):encoded_stream = Differential_Manchester(stream);
        break;
        case(5):encoded_stream = scrambling(stream);
        break;
        default:
        cout << "Please enter a valid encoding scheme";
        goto select_scheme;
    }
    
    cout << "Encoded Stream is: ";

    for(int i : encoded_stream){
        cout << i << " ";
    }
}

void digital_input(){
    cout << "1. Generate completely random data" << endl << 
            "2. Generate data with fixed zero sequences" << endl << 
            "3. Enter data manually" << endl << endl;

    int option;
    vector<int> stream;
    int size;

    select_dinput:

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
        default:
        cout << "Please enter a valid input";
        goto select_dinput;
    }

    vector<int> palindrome = longestPalindrome(stream);

    cout << "The stream is: ";

    for(int i : stream){
        cout << i << " ";
    }

    cout << endl << "Longest palindrome is: ";

    for(int i : palindrome){
        cout << i << " ";
    }

    cout << endl << endl;
    lineEncodingSchemes(stream);
}

int main(){
    cout << "==================================" << endl << 
            " DIGITAL SIGNAL ENCODER & DECODER " << endl << 
            "==================================" << endl << endl;

    int option;

    cout << "1. Digital Input" << endl <<
            "2. Analog Input" << endl <<
            "3. Exit" << endl << endl;

    select_input:

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
        goto select_input;
    }
    
    return 0;
}