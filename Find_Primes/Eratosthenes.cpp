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

vector<bool> genSieveEratosthenes();
void writeFile(ofstream& fout, const string& path);
void readFile(ifstream& fin, const string& path, vector<int>& v);
bool isPrimeEratosthenes(vector<bool>& sieve, int n);

// calcTotalTime(findPrimes_Eratosthenes(10000));
// template <typename Fun, typename... Args>
// void calcTotalTime(Fun fun, Args args...) {
//     auto start = chrono::high_resolution_clock::now();

//     fun(args...);

//     auto end = chrono::high_resolution_clock::now();

//     // Calculating total time taken by the program.
//     double time_taken =
//         chrono::duration_cast<chrono::nanoseconds>(end - start).count();

//     time_taken *= 1e-9;

//     cout << "Time taken by program is : " << fixed << time_taken
//          << setprecision(9);
//     cout << " sec" << endl;
// }
int main() { 
    const string path = "randomData.txt";
    writeFile(fout, path);//generate 1000 random integers and write to file 

    vector<bool> sieve = genSieveEratosthenes();//generate sieve of eratosthenes with the size of 10000 numbers (both prime and not prime numbers)

    vector<int> randomData;
    readFile(fin, path, randomData);

    
    for(int i=0;i<randomData.size();++i){
        if(isPrimeEratosthenes(sieve, randomData[i])){
            cout<<randomData[i]<<" "<<":prime"<<endl;
        }
        else{
            cout<<randomData[i]<<" "<<":not prime"<<endl;
        }
    }

 }
vector<bool> genSieveEratosthenes() {
    auto start = chrono::high_resolution_clock::now();

    int n = 10000;

    vector<bool> primes(n, true);

    primes[0] = false;
    primes[1] = false;

    for (int i = 2; i <= sqrt(n); i++) {
        if (primes[i] == true) {
            for (int j = i * i; j <= n; j+=i) {
                primes[j] = false;
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double time_taken =
        chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by the Sieve of Eratosthenes is : " << fixed
         << time_taken << setprecision(9) << " sec" << endl;

    return primes;
}
void writeFile(ofstream& fout, const string& path) {
    fout.open(path);

    for (int i = 0; i < 1000; ++i) {
        fout << rand() % 10000 << " ";
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
bool isPrimeEratosthenes(vector<bool>& sieve, int n) {
    if (sieve[n] == true) {
        return true;
    }
    return false;
}
