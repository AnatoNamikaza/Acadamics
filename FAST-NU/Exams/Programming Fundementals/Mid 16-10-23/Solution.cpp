#include <iostream>

using namespace std;

int main()
{
    int x1 = 1, x2 = 2, x3 = 3, x4 = 4;
    //int x1 = 1, x2 = 1, x3 = 1, x4 = 2;
    
    long long int sum = 10;
    //long long int sum = 5;
    
    for (int i = 5; i <= 50; i++)
    {
        
        if( i % 2 == 0)
        {

            sum += (x1 + x3);
            x2 = x4;
            x4 = (x1 + x3);
            cout<< i <<"th term : "<< x4 <<" ::"<<sum<< endl;            
        }
        
        if( i % 2 == 1)
        {
            sum += (x2 + x4);
            x1 = x3; // + x1;
            x3 = (x2 + x4);
            cout<< i <<"th term : "<< x3 <<" ::"<<sum<< endl;            
        }
    }
    
    cout<<"--------- Done ---------"<<endl;

    return 0;
}