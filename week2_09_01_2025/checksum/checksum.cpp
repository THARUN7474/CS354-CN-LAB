#include <bits/stdc++.h>

using namespace std;

string binaryAddition(string a, string b)
{
    int n = a.length();
    string res = "";
    int carry = 0;
    for (int i = n - 1; i >= 0; --i)
    {                          // we are starting from end coz we do add from right to left
        int bit1 = a[i] - '0'; // 0001001001---here 1 is taken at 1st
        int bit2 = b[i] - '0'; // 0001101001---here 1 is taken at 1st then move to before on in R-L
        int sum = bit1 + bit2 + carry;
        res = to_string(sum % 2) + res;
        carry = sum / 2;
    }
    if (carry) // at last we might get carry ----if get it will be 1 so we add it to the result
    {
        for (int i = res.length() - 1; i >= 0 && carry; --i)
        {
            if (res[i] == '0')
            {
                res[i] = '1';
                carry = 0;
            }
            else
            {
                res[i] = '0';
            }
        }
    }
    return res;
}

string calculateChecksum(vector<string> dataSegments, int bitSize) // here as per example--4, 8
{
    string sum = string(bitSize, '0'); // 00000000
    for (const auto &segment : dataSegments)
    {
        sum = binaryAddition(sum, segment); // we go from left to right ---> like one seg to next segment
    }

    // here we are doing 1's complement of the sum----sum which is calculated above from all binary additions of all segments
    for (char &bit : sum) // inversion case
    {
        bit = (bit == '0') ? '1' : '0';
    }
    return sum;
}

bool verifyChecksum(vector<string> dataSegments, int bitSize) // i added that checksum direct to datasegments at the end
{
    string sum = string(bitSize, '0');
    for (const auto &segment : dataSegments)
    {
        sum = binaryAddition(sum, segment);
    }

    for (char bit : sum) // here we get 11111111 as sum of all segments and checksum if it is valid
    {
        if (bit == '0')
            return false; // even if any bit is not 0 then info or data got is not valid
    }
    return true;
}

int main()
{

    vector<string> dataSegments = {"10011001", "11100010", "00100100", "10000100"};
    int bitSize = 8;

    string checksum = calculateChecksum(dataSegments, bitSize);
    cout << "Checksum: " << checksum << endl;

    dataSegments.push_back(checksum);

    // if (verifyChecksum(dataSegments, bitSize))
    // {
    //     cout << "Data is valid (Checksum verified successfully)." << endl;
    // }
    // else
    // {
    //     cout << "Data is invalid (Checksum verification failed)." << endl;
    // }

    // for checking --invalid case

    vector<string> dataSegments2 = {"10011001", "11100010", "00100100", "10000101"};
    dataSegments2.push_back(checksum);

    if (verifyChecksum(dataSegments2,bitSize))
    {
        cout << "Data is valid (Checksum verified successfully)." << endl;
    }
    else
    {
        cout << "Data is invalid (Checksum verification failed)." << endl;
    }

    return 0;
}
