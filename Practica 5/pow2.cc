//Manuel Alberola Torres 74017527P
#include <iostream>
using namespace std;

long pow2_1(long n);
long pow2_2(long n);
long pow2_3(long n);
long pow2_4(long n);

int steeps = 0;


int main () {
    cout<<"n" <<"\tpow2_1" <<"\tpow2_2" <<"\tpow2_3" <<"\tpow2_4" <<endl;
    for (unsigned long n = 0; n<500; n+=2){
        cout<<n;

        pow2_1(n);
        cout<<"\t" <<steeps;
        steeps = 0;

        pow2_2(n);
        cout<<"\t" <<steeps;
        steeps = 0;

        pow2_3(n);
        cout<<"\t" <<steeps;
        steeps = 0;

        if(n<20){
            pow2_4(n);
            cout<<"\t" <<steeps;
            steeps = 0;
        }
        cout<<endl;
    }
    return 0;
}

long pow2_1(long n){
    steeps ++;
    if(n==0){
        return 1;
    } else {
        return 2 * pow2_1(n-1);
    }
}

long pow2_2 (long n){
    steeps++;
    if (n == 0){
        return 1;
    }else if (n % 2 == 0){
        return pow2_2(n/2) * pow2_2(n/2);
    }
    return 2 * pow2_2(n/2) * pow2_2(n/2);
}

long pow2_3(long n){
    steeps++;
    if(n==0){
        return 1;
    } else if (n % 2 == 0){
        long r = pow2_3(n/2);
        return r * r;
    }
    long r = pow2_3(n/2);
    return r * r;
    return 2 * r * r;
}

long pow2_4(long n){
    steeps++;
    if(n==0){
        return 1;
    }
    return pow2_4(n-1) + pow2_4(n-1);
}
