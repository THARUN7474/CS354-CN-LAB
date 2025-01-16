#include <bits/stdc++.h>
using namespace std;

void XOR(vector<int> &dividend, vector<int> &divisor, int start)
{
    for (int i = 0; i < divisor.size(); i++)
    {
        dividend[start + i] ^= divisor[i];
    }
}

vector<int> computeCRC(vector<int> data, vector<int> generator)
{
    int n = generator.size();
    vector<int> dividend = data;

    for (int i = 0; i < n - 1; i++)
    {
        dividend.push_back(0);
    }

    for (int i = 0; i <= dividend.size() - n; i++)
    {
        if (dividend[i] == 1)
        {
            XOR(dividend, generator, i);
        }
    }

    vector<int> remd(dividend.end() - (n - 1), dividend.end());
    return remd;
}

bool verifyCRC(vector<int> rData, vector<int> gen)
{
    int n = gen.size();

    for (int i = 0; i <= rData.size() - n; i++)
    {
        if (rData[i] == 1)
        {
            XOR(rData, gen, i);
        }
    }

    for (int i = rData.size() - (n - 1); i < rData.size(); i++)
    {
        if (rData[i] != 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{

    vector<int> data = {1, 0, 1, 1, 1};
    vector<int> generator = {1, 0, 1};

    vector<int> crc = computeCRC(data, generator);

    cout << "Original Data: ";
    for (int bit : data)
        cout << bit;
    cout << "\nCRC: ";
    for (int bit : crc)
        cout << bit;

    vector<int> transmittedData = data;
    transmittedData.insert(transmittedData.end(), crc.begin(), crc.end()); // to have error case we can modify that data which is transmitting to receiver

    cout << "\nTransmitted Data: ";
    for (int bit : transmittedData)
        cout << bit;

    bool isValid = verifyCRC(transmittedData, generator);

    cout << "\nData Verification Result: " << (isValid ? "No Error" : "Error Detected") << endl;

    return 0;
}
