#include <bits/stdc++.h>
using namespace std;


vector<int> to_int(string s) {
    vector<int> v;
    for (char c : s) {
        if (c == '0' || c == '1') { 
            v.push_back(c - '0');  
        } else {
            cerr << "Invalid input: Only binary digits (0 or 1) are allowed." << endl;
            exit(1); // Exit the program
        }
    }
    return v;
}

vector<int> bitstuff(vector<int> data) {
    int b1 = 0;
    vector<int> v;
    for (auto i : data) {
        if (i == 1) {
            b1++;
            v.push_back(i);
            if (b1 == 5) { // x11111x case
                v.push_back(0);
                b1 = 0;
            }
        } else {
            v.push_back(i);
            b1 = 0; // Reset consecutive 1s count
        }
    }
    return v;
}

vector<int> unbitstuff(vector<int> data) {
    int b1 = 0;
    vector<int> v;
    for (auto i : data) {
        if (i == 1) {
            b1++;
            v.push_back(i);
        } else {
            if (b1 == 5) {
                // Skip the stuffed 0
                b1 = 0;
                continue;
            }
            v.push_back(i);
            b1 = 0;
        }
    }
    return v;
}

int main() {
    string s;
    cout << "Enter a binary string: ";
    getline(cin, s); 
    vector<int> v = to_int(s);

    vector<int> stuffed = bitstuff(v);
    vector<int> unstuffed = unbitstuff(stuffed);

    
    cout << "Original Data:   ";
    for (int i : v) cout << i;
    cout << endl;

    cout << "Stuffed Data:    ";
    for (int i : stuffed) cout << i;
    cout << endl;

    cout << "Unstuffed Data:  ";
    for (int i : unstuffed) cout << i;
    cout << endl;

    return 0;
}
