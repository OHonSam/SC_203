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

vector<bool> genSieveSundaram(int limit);
void writeFile(ofstream& fout, const string& path, int limit);
void readFile(ifstream& fin, const string& path, vector<int>& v);
bool isPrimeSundaram(vector<bool>& sieve, int n);

int main() {
    const string path = "randomData.txt";
    writeFile(fout, path, 100000);  // generate 1000 random integers with a given
                                   // 'limit' value and write to file

    vector<bool> sieve = genSieveSundaram(100000);  // generate sieve of Sundaram with the size of 'limit' numbers (both prime
        // and not prime numbers)(the size is also the 'limit' value))

    vector<int> randomData;
    readFile(fin, path, randomData);

    for (int i = 0; i < randomData.size(); ++i) {
        if (isPrimeSundaram(sieve, randomData[i])) {
            cout << randomData[i] << " "
                 << ":prime" << endl;
        } else {
            cout << randomData[i] << " "
                 << ":not prime" << endl;
        }
    }
}

vector<bool> genSieveSundaram(int limit) {
    auto start = chrono::high_resolution_clock::now();

    vector<bool> sieve(limit + 1, false);

    int k=(limit-2)/2;

    for(int i=1;i<=k;++i){
        for(int j=i;(i+j+2*i*j)<=k;++j)
            sieve[i+j+2*i*j]=true;
    }

    vector<bool> primes(limit+1,false);

    primes[2]=true;

    for(int i=1;i<=k;++i){
        if(sieve[i]==false){
            primes[2*i+1]=true;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by the Sieve of Sundaram is : " << fixed << time_taken
         << setprecision(9) << " sec" << endl;

    return primes;
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
bool isPrimeSundaram(vector<bool>& sieve, int n) {
    if (sieve[n] == true) {
        return true;
    }
    return false;
}
