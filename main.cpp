#include <iostream>
#include <cmath>
using namespace std;
#define MAX 4294967296

// Define array with flags for composites with length MAX/64
// We will store all flags as integer bitmask so one integer can contain 32 flags
// The primes themselves can be more than sqrt of MAX so MAX/64 will be enough for all primes
int flagArr[MAX>>6] = {0};

// If I define these functions as a regular functions the program seg faults. Not sure why
// Check if the flag bit is 1
#define checkComp(x) (flagArr[x>>6]&(1<<((x>>1)&31)))
// Set the flag bit to 1
#define setComp(x) (flagArr[x>>6]|=(1<<((x>>1)&31)))

void sieve()
{
    long i,j,k;

    // We don't need to check all numbers. Numbers > sqrt(MAX) should be already marked if composite
    for(i=3;i<(int)sqrt((double)MAX);i+=2)
    {
        // If the number is not already set as composite
        if(!checkComp(i))
        {
            // Set all numbers that can be divided by i to composite
            // We don't need to numbers < i power 2 because they should be already set
            // by previous loop
            for(j=i*i,k=i<<1;j<MAX;j+=k)
                setComp(j);
        }
    }

    cout << "2" << endl;
    for(i=3,j=2;i<MAX;i+=2)
    {
        if(!checkComp(i))
        {
            cout << i << endl;
            j++;
        }
    }
}

int main() {
    // ~ 4,294,967,296
    cout << pow(2,32) << endl;

    // Took ~ 0.35 seconds on CPU0: Intel(R) Core(TM) i5-4310U CPU @ 2.00GHz. RAM 16G
    sieve();
    return 0;
}
