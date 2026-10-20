#include<bits/stdc++.h>
#include "raylib.h"
using namespace std;

bool validCheck(vector<int> stream){
    for(int i : stream){
        if(i != 0 && i != 1) return false;
    }
    return true;
}

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
    insert_bits:
    
    cout << "Enter the stream: ";

    for(int i = 0; i < size; i++){
        int num;
        cin >> num;
        stream.push_back(num);
    }
    if(!validCheck(stream)){
        stream.clear();
        cout << "Please enter a valid stream";
        goto insert_bits;
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

vector<int> AMI(vector<int> stream){
    int level = -1;
    vector<int> encoded_stream;

    for(int i : stream){
        if(i == 1){
            level = level*(-1);
            encoded_stream.push_back(level);
        }
        else{
            encoded_stream.push_back(0);
        }
    }

    return encoded_stream;
}

vector<int> B8ZS(vector<int> stream){
    vector<int> encoded_stream;
    int level = -1;

    for(int i = 0; i < stream.size(); i++){

        if(i + 7 < stream.size() &&
           vector<int>(stream.begin() + i, stream.begin() + i + 8) == vector<int>(8, 0)){

            encoded_stream.insert(encoded_stream.end(),
                {0,0,0,level,-level,0,level,-level});

            i += 7;
            continue;
        }

        if(stream[i] == 1)
            level = -level;

        encoded_stream.push_back(stream[i] == 1 ? level : 0);
    }

    return encoded_stream;
}

vector<int> HDB3(vector<int> stream){
    vector<int> encoded_stream;
    int level = -1;
    int pulse_count = 0;

    for(int i = 0; i < stream.size(); i++){

        if(i + 3 < stream.size() &&
           vector<int>(stream.begin() + i, stream.begin() + i + 4) == vector<int>(4, 0)){

            if(pulse_count % 2 == 1){
                encoded_stream.insert(encoded_stream.end(),
                    {0,0,0,level});
            }
            else{
                level = -level;
                encoded_stream.insert(encoded_stream.end(),
                    {level,0,0,level});
            }

            pulse_count = 0;
            i += 3;
            continue;
        }

        if(stream[i] == 1){
            level = -level;
            pulse_count++;
        }

        encoded_stream.push_back(stream[i] == 1 ? level : 0);
    }

    return encoded_stream;
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
        case(2): return AMI(stream);
        break;
        default: cout << "Please select a valid option." << endl;
        goto select_scrambling;
    }
}

void showWaveform(const vector<int>& signal) {
    if (signal.empty()) return;

    const int W = 1000, H = 420;
    const int left = 70, right = 30;
    const int top = 70, bottom = 290;
    const int axisY = 320;

    InitWindow(W, H, "Digital Signal Waveform");
    SetTargetFPS(60);

    float dx = float(W - left - right) / signal.size();

    // Convert voltage levels to screen coordinates.
    auto y = [&](int v) {
        return top + (1 - v) * (bottom - top) / 2;
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Encoded Digital Signal", 20, 20, 25, DARKGRAY);

        // Horizontal voltage reference lines.
        for (int v : {1, 0, -1}) {
            DrawLine(left, y(v), W - right, y(v), LIGHTGRAY);
        }

        // Voltage labels.
        DrawText("+1", 25, y(1) - 8, 16, DARKGRAY);
        DrawText("0",   35, y(0) - 8, 16, DARKGRAY);
        DrawText("-1", 25, y(-1) - 8, 16, DARKGRAY);

        // Draw the waveform.
        for (int i = 0; i < (int)signal.size(); i++) {
            int x1 = left + int(i * dx);
            int x2 = left + int((i + 1) * dx);

            // Horizontal segment.
            DrawLine(x1, y(signal[i]), x2, y(signal[i]), BLUE);

            // Vertical transition.
            if (i + 1 < (int)signal.size()) {
                DrawLine(
                    x2, y(signal[i]),
                    x2, y(signal[i + 1]),
                    BLUE
                );
            }
        }

        // Draw the time axis.
        DrawLine(left, axisY, W - right, axisY, BLACK);

        // Tick marks and time labels.
        for (int i = 0; i <= (int)signal.size(); i++) {
            int x = left + int(i * dx);

            // Tick mark.
            DrawLine(x, axisY - 5, x, axisY + 5, BLACK);

            // Time label.
            string label;

            if (i == 0)
                label = "0";
            else if (i == 1)
                label = "T";
            else
                label = to_string(i) + "T";

            DrawText(label.c_str(), x - 8, axisY + 10, 14, BLACK);
        }

        // X-axis title.
        DrawText("Time (T)", W / 2 - 40, 375, 18, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
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
    };
    showWaveform(encoded_stream);
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

vector<float> generateAnalogSignal(){
    vector<float> signal;
    int size = 100;

    for(int i = 0; i < size; i++){
        float t = (float)i / size;
        float value = sin(2 * PI * t);
        signal.push_back(value);
    }

    return signal;
}

vector<float> sampling(vector<float> signal){
    vector<float> sampled_signal;
    int sample_count = 20;
    int interval = signal.size() / sample_count;

    for(int i = 0; i < signal.size(); i += interval){
        sampled_signal.push_back(signal[i]);
    }

    return sampled_signal;
}

vector<float> quantization(vector<float> sampled_signal){
    vector<float> quantized_signal;
    int levels = 8;

    for(int i = 0; i < sampled_signal.size(); i++){
        int level = (sampled_signal[i] + 1) * levels / 2;

        if(level >= levels){
            level = levels - 1;
        }

        float value = -1 + (level + 0.5) * 2.0 / levels;
        quantized_signal.push_back(value);
    }

    return quantized_signal;
}

vector<int> pcmEncoding(vector<float> quantized_signal){
    vector<int> encoded_signal;
    int levels = 8;

    for(int i = 0; i < quantized_signal.size(); i++){
        int level = (quantized_signal[i] + 1) * levels / 2;

        if(level >= levels){
            level = levels - 1;
        }

        for(int bit = 2; bit >= 0; bit--){
            encoded_signal.push_back((level >> bit) & 1);
        }
    }

    return encoded_signal;
}

vector<float> pcmDecoding(vector<int> encoded_signal){
    vector<float> decoded_signal;
    int levels = 8;

    for(int i = 0; i + 2 < encoded_signal.size(); i += 3){
        int level = encoded_signal[i] * 4
                  + encoded_signal[i + 1] * 2
                  + encoded_signal[i + 2];

        float value = -1 + (level + 0.5) * 2.0 / levels;
        decoded_signal.push_back(value);
    }

    return decoded_signal;
}

void showAnalogWaveform(const vector<float>& signal){
    if(signal.empty()) return;

    const int W = 1000, H = 420;
    const int left = 70, right = 30;
    const int top = 70, bottom = 290;
    const int axisY = 320;

    InitWindow(W, H, "PCM Decoded Signal");
    SetTargetFPS(60);

    float dx = float(W - left - right) / signal.size();

    auto y = [&](float v){
        return top + (1 - v) * (bottom - top) / 2;
    };

    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("PCM Decoded Signal", 20, 20, 25, DARKGRAY);

        for(int v : {1, 0, -1}){
            DrawLine(left, y(v), W - right, y(v), LIGHTGRAY);
        }

        DrawText("+1", 25, y(1) - 8, 16, DARKGRAY);
        DrawText("0", 35, y(0) - 8, 16, DARKGRAY);
        DrawText("-1", 25, y(-1) - 8, 16, DARKGRAY);

        for(int i = 0; i < signal.size(); i++){
            int x1 = left + int(i * dx);
            int x2 = left + int((i + 1) * dx);

            DrawLine(x1, y(signal[i]), x2, y(signal[i]), BLUE);

            if(i + 1 < signal.size()){
                DrawLine(
                    x2, y(signal[i]),
                    x2, y(signal[i + 1]),
                    BLUE
                );
            }
        }

        DrawLine(left, axisY, W - right, axisY, BLACK);
        DrawText("Time", W / 2 - 25, 375, 18, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}

void analog_input(){
    vector<float> signal = generateAnalogSignal();

    vector<float> sampled_signal = sampling(signal);

    vector<float> quantized_signal = quantization(sampled_signal);

    vector<int> encoded_signal = pcmEncoding(quantized_signal);

    vector<float> decoded_signal = pcmDecoding(encoded_signal);

    cout << "Original sampled signal: ";
    for(float value : sampled_signal){
        cout << value << " ";
    }

    cout << endl << endl;

    cout << "Quantized signal: ";
    for(float value : quantized_signal){
        cout << value << " ";
    }

    cout << endl << endl;

    cout << "PCM Encoded bitstream: ";
    for(int bit : encoded_signal){
        cout << bit;
    }

    cout << endl << endl;

    cout << "Decoded signal: ";
    for(float value : decoded_signal){
        cout << value << " ";
    }

    cout << endl << endl;

    showAnalogWaveform(decoded_signal);
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
        case(2): analog_input();
        break;
        case(3): cout << "3";
        break;
        default: cout << "Enter a valid option";
        goto select_input;
    }
    
    return 0;
}