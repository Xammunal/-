#include <iostream>
using namespace std;
int main() {
    int A[10];

    for (int *Next = A, *End = Next + 9; Next <= End; ++ Next)

    {

        cin >> *Next;     

        *Next = *Next * *Next;    // *Next = (*Next) * (*Next);   

    }

    for (int *Next = A, *End = Next + 9; Next <= End; ++ Next)

        cout << *Next << " ";

    cout << endl;


    return 0;
}