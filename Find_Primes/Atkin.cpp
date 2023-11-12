#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

ofstream fout;
ifstream fin;

vector<bool> genSieveAtkin(int limit);
void writeFile(ofstream& fout, const string& path, int limit);
void readFile(ifstream& fin, const string& path, vector<int>& v);
bool isPrimeAtkin(vector<bool>& sieve, int n);

int main() {
    const string path = "randomData.txt";
    writeFile(fout, path, 10000);  // generate 1000 random integers with a given
                                   // 'limit' value and write to file

    vector<bool> sieve = genSieveAtkin(10000);  // generate sieve of atkin with the size of 'limit' numbers (both prime
        // and not prime numbers)(the size is also the 'limit' value))

    vector<int> randomData;
    readFile(fin, path, randomData);

    for (int i = 0; i < randomData.size(); ++i) {
        if (isPrimeAtkin(sieve, randomData[i])) {
            cout << randomData[i] << " "
                 << ":prime" << endl;
        } else {
            cout << randomData[i] << " "
                 << ":not prime" << endl;
        }
    }
}

vector<bool> genSieveAtkin(int limit) {
    auto start = chrono::high_resolution_clock::now();

    vector<bool> sieve(limit + 1, false);

    if (limit > 2) sieve[2] = true;
    if (limit > 3) sieve[3] = true;

    for (int x = 1; x * x <= limit; ++x) {
        for (int y = 1; y * y <= limit; ++y) {
            int n = (4 * x * x) + (y * y);
            if (n <= limit && (n % 12 == 1 || n % 12 == 5))
                sieve[n] = sieve[n] ^ true;

            n = (3 * x * x) + (y * y);
            if (n <= limit && n % 12 == 7) sieve[n] = sieve[n] ^ true;

            n = (3 * x * x) - (y * y);
            if (x > y && n <= limit && n % 12 == 11) sieve[n] = sieve[n] ^ true;
        }
    }
    for (int r = 5; r * r <= limit; r++) {
        if (sieve[r]) {
            for (int i = r * r; i <= limit; i += r * r) sieve[i] = false;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by the Sieve of Atkin is : " << fixed << time_taken
         << setprecision(9) << " sec" << endl;

    return sieve;
}
void writeFile(ofstream& fout, const string& path, int limit) {
    fout.open(path);

    for (int i = 0; i < 1000; ++i) {
        fout << rand() % limit << " ";
    }

    fout.close();
}
void readFile(ifstream& fin, const string& path, vector<int>& v) {
    fin.open(path);

    for (int i = 0; i < 1000; ++i) {
        int x;
        fin >> x;
        v.push_back(x);
    }

    fin.close();
}
bool isPrimeAtkin(vector<bool>& sieve, int n) {
    if (sieve[n] == true) {
        return true;
    }
    return false;
}
