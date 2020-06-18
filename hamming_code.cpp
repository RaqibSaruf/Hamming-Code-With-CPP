#include<bits/stdc++.h>
using namespace std;

class Sender
{
    string message;
    int codewordsize;
    char parityType;

public:
    int getCodeWordSize()
    {
        return this->codewordsize;
    }
    void setMessage(string message)
    {
        this->message = message;
    }
    void setParityType(char parityType)
    {
        this->parityType = parityType;
    }
    string generateCodeword()
    {
        int parity_bit = 0;//number of parity bit

        while ( message.size() + parity_bit + 1 > pow(2, parity_bit))
        {
            parity_bit++;
        }

        this->codewordsize = message.size()+parity_bit;
        int n = this->codewordsize;

        char hamming_code[n];
        int parity = 0, data = message.size();

        //create codeword
        for (int i = 1; i <= n; i++)
        {
            if (i==pow(2, parity))
                {
                    hamming_code[i] = 'p';
                    parity++;
                }
            else
                {
                    hamming_code[i] = message[data-1];
                    data=data-1;
                }
        }


    int j=1;
    int k=1;
    while(j<=parity_bit)
    {
        int num_of_1=0;
        int parity_index=pow(2,j-1);
        int i= parity_index;

        //create parity set
        while(i<=n)
        {
            for(int m=1;m<=k;m++){
                if(hamming_code[i]=='1')
            {
                num_of_1++;
            }
            i++;
            if(i>n)break;
            }
            i=i+k;
        }

        k=k<<1;

        j++;

        //set parity value
        if(parityType=='o')
        {
            if(num_of_1%2==0)
                hamming_code[parity_index]='1';

            else
                hamming_code[parity_index]='0';
        }
        else if(parityType=='e')
        {
            if(num_of_1%2==0)
                hamming_code[parity_index]='0';

            else
                hamming_code[parity_index]='1';
        }
        else
        {
           cout<<"Please select valid parity type."<<endl;
           break;
        }
    }

    //converting char array to string
    string code;

    for(int i=1;i<=n;i++)
    {
        code.push_back(hamming_code[i]);
    }
    //print codeword
    cout<<"\nCodeWord: ";
    for(int i=n-1;i>=0;i--)
    {
        cout<< code[i];
    }
    cout<<endl;

    return code;

    }
};

class Receiver
{
    int codewordsize;
    char parityType;

public:
    void setCodeWordSize(int c_w_size)
    {
        this->codewordsize = c_w_size;
    }
    void setParityType(char parityType)
    {
        this->parityType = parityType;
    }
    void receiveCodeword(string codeword)
    {
        cout<<"Received CodeWord: ";
        for(int i=codewordsize-1;i>=0;i--)
        {
            cout<< codeword[i];
        }
        cout<<endl;

        int j=1;
        int parityBit=0;//number of parity bit
        for(int i=1;i<=codewordsize;i=pow(2,j-1))
        {
            parityBit++;
            j++;
        }
    string Error_bit;
     j=1;
    int k=1;
    while(j<=parityBit)
    {
        int num_of_1=0;
        int parity_index=pow(2,j-1);
        int i= parity_index;

        //create parity set
        while(i<=codewordsize)
        {
            for(int m=1;m<=k;m++){
                if(codeword[i-1]=='1')
            {
                num_of_1++;
            }

            i++;
            if(i>codewordsize)break;
            }
            i=i+k;
        }

        //calculate error bit
        if(parityType=='e')
        {
            if(num_of_1%2==0)
            {
                Error_bit.push_back('0');
            }
            else{
                Error_bit.push_back('1');
            }
        }
        else if(parityType=='o')
        {
            if(num_of_1%2==0)
            {
                Error_bit.push_back('1');
            }
            else{
                Error_bit.push_back('0');
            }
        }

        k=k<<1;

        j++;

    }

    reverse(Error_bit.begin(), Error_bit.end());
    cout<< "Binary Error bit: "<<Error_bit<<endl;

    int dec_value = 0;
    int base = 1;
//binary from string to decimal conversion
    for (int i = Error_bit.size() - 1; i >= 0; i--) {
        if (Error_bit[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    cout<< "Error Detect in Position: "<<dec_value<<endl;
    if(dec_value==0)
    {
        cout<<"No Error in Codeword."<<endl;
    }
    else{
        //correcting the codeword
        if(codeword[dec_value-1]== '1')
        {
            codeword[dec_value-1] = '0';
        }
        else if(codeword[dec_value-1]== '0')
        {
            codeword[dec_value-1] = '1';
        }
        cout<<"After Correcting, CODEWORD is: ";
        for(int i=codewordsize-1;i>=0;i--)
        {
            cout<< codeword[i];
        }
        cout<<endl;
    }


    }
};

string randomChange(string codeword, int num)
{
    srand(time(0));

    for(int i=1;i<=num;i++)
    {
        int random = rand() % (codeword.size()-1);
        if(codeword[random]=='1')
        {
            codeword[random] = '0';
        }
        else if(codeword[random]=='0')
        {
            codeword[random] = '1';
        }else
        {
            cout<<"Error in Codeword"<<endl;
            exit(1);
        }
    }

    return codeword;

}


int main()
{
    Sender sender;
    Receiver receiver;
    string message;
    char parityType; // 'o' for odd parity, 'e' for even parity
    // Take the message and parityType as input

    cout<< "Enter the Message: ";
    cin>>message;
    cout<< "Enter parity type('o' for odd parity, 'e' for even parity): ";
    cin>>parityType;

    sender.setMessage(message);
    sender.setParityType(parityType);

    string codeword = sender.generateCodeword();
    string correctCW = codeword;
    string singleErrorCW = randomChange(codeword, 1);
    string doubleErrorCW = randomChange(codeword, 2);
    int codewordsize = sender.getCodeWordSize();

    receiver.setCodeWordSize(codewordsize);
    receiver.setParityType(parityType);

    cout<<"\nFor No Change in codeword:"<<endl;
    receiver.receiveCodeword(correctCW);

    cout<<"\nFor Single bit Error:"<<endl;
    receiver.receiveCodeword(singleErrorCW);

    cout<<"\nFor Double bit Error:"<<endl;
    receiver.receiveCodeword(doubleErrorCW);

    return 0;
}
