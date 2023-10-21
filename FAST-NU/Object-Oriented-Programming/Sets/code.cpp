#include <bits/stdc++.h>

using namespace std;

class Set
{
    int size;
    int* array;
public:
    Set(int siz = 0)
    {
        this->size = siz;
        this->array = new int[size];
        for(int i = 0; i < size; i++)
            array[i] = INT_MIN;
    }

    void operator - (const Set& obj)
    {
        int i, j; 
        for(i=0;i<this->size;i++)
        {
            for(j=0;j<obj.size;j++)
            {
                if(this->array[i]==obj.array[j])
                {
                    cout<<this->array[i]<<" ";
                }
            }
        }
        
        cout<< endl;
    }
    
    Set operator + (const Set& obj) {
        Set temp;
        temp.size = this->size + obj.size;
        temp.array = new int[temp.size];
        int i;
        for ( i = 0; i < this->size; i++)
        {
            temp.array[i] = this->array[i];
        }
        
        for ( int j = 0; j < temp.size; j++)
        {
            temp.array[i + j] = obj.array[j];
        }
        
        return temp;
    }

    friend bool operator==(const Set& lhs, const Set& rhs)
    {
        if (lhs.size != rhs.size)
        {
            return 1;    
        }
        
        for (int i = 0; i < lhs.size; i++)
        {
            if (lhs.array[i]!= rhs.array[i])
            {
                return 1;
            }
        }
        
        return 0;
    }

    bool Membership(int c)
    {
        for(int i = 0; i < this->size; i++)
            if( this->array[i] == c){
                return 0;   
            }
        return 1;
    }

    friend ostream &operator<<( ostream &output, const Set &s ) { 
        for(int i = 0; i < s.size; i++)
            output << s.array[i] << " ";
        output << endl;
        return output;            
    }
    
    friend istream &operator>>( istream  &input, Set &s ) { 
        int i;
        for(i = 0; i < s.size; i++)
            if (s.array[i] == INT_MIN){
                input >> s.array[i];
                break;
            }
        return input;            
    }

    ~Set()
    {
        delete [] array;
        array = nullptr;
    }
};

int main() 
{
    int s1 =0, s2 = 0, i;
    cout << "Enter Side of Set A: ";
    cin >> s1;
    cout << endl;
    
    Set A(s1);
    
    for(i = 0; i < s1; i++)
    {
        cout << "Enter Element " << i+1<<": ";
        cin >> A;
    }
    
    cout << A;
    
    cout << "Enter Side of Set B: ";
    cin >> s2;
    cout << endl;
    
    Set B(s2);
    
    for(i = 0; i < s2; i++)
    {
        cout << "Enter Element " << i+1<<": ";
        cin >> B;
    }
    
    cout << B;

    char c;
    cout << "Press A to find Union" << endl;
    cout << "Press B to find Intersection" << endl;
    cout << "Press C to Check Equality of Sets" << endl;
    cout << "Press D to Perform Membership test" << endl;
    cout << "Press E to Exit" << endl;
    cout << "Enter Choice: ";
    cin >> c;
    
    if (c == 'A')
    {
        cout << ( A + B );
    }
    else if (c == 'B')
    {
       ( A - B );
    }
    else if (c == 'C')
    {
       cout << (A == B);
    }
    else if (c == 'D')
    {
        int number;
        cout << "Enter number: ";
        cin >> number;
        
        cout<< "Membership for set A is: "<< A.Membership(number)<<endl;
        cout<< "Membership for set B is: "<< B.Membership(number)<<endl;
    }
    
    
    return 0;
}