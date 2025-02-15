//Big Int (1024 bit Integer) calculator -by Hrushikesh Musaloj (BT23CSE024)

//create these files before executing the program: 'num1.txt', 'num2.txt' and 'result.txt'
//store the two numbers in num1.txt and num2.txt files respectively
//the result will be stored in result.txt

//Enter the numbers upto 309 digits only


#include<iostream>
#include <string>
#include <fstream>
using namespace std;

#define MAXLENGTH 309
#define FILE1 "num1.txt"
#define FILE2 "num2.txt"
#define RESULTFILE "result.txt"
#define OVERFLOWED "OVERFLOWED"


string readStringFromFile(string fileName){
    string inputLine="NULL";
    string line;
    ifstream inFile(fileName); 
    if (!inFile) {
        cout << "Error: File could not be opened!\n Please create 3 files: 'num1.txt', 'num2.txt' and 'result.txt'" << endl;
        inputLine='0';
    }
    else{
        inputLine="";
        while (getline(inFile, line)) { 
        inputLine+=line;     
        } 
    }
    inFile.close();
    return inputLine;
}

void writeStringToFile(string outputString){
    ofstream outFile(RESULTFILE); 
    if (!outFile) {
        cout << "Error: Could not open the file for writing." << endl;
    }
    else{
        outFile<<outputString;
    }
    outFile.close(); 
}


class BigInt{
    private:
    string value;

    string createBigIntOne(){
        BigInt ONE;
        ONE.value[MAXLENGTH-1]='1';
        return ONE.value;
    }
    bool checkOverFlowForMultiplication(string s){
        bool overflowed=false;
        for(int i=0;i<MAXLENGTH && !overflowed;i++){
            if(s[i]!='0'){
                overflowed=true;
            }
        }
        return overflowed;
    }

    public:
    BigInt(){
        //set the value to zero for 309 digits
        for(int i=0;i<MAXLENGTH;i++){
            this->value+='0';
        }
    }

    BigInt(BigInt& x){//copy constructor
        this->value=x.value;
    }

    bool input(string fileName){
        bool fileRead=true;
        string input=readStringFromFile(fileName);
        if(input!="NULL"){
            int inputLength=input.length();
            bool negative=false;
            if(input[0]=='-'){
                negative=true;
                //make input to positive and then put negative at end of the function
                input=input.substr(1,inputLength-1);
                inputLength=inputLength-1;//removed the -ve symbol
            }
            if (inputLength > MAXLENGTH) {
                cout << "Input is too long. Reducing it to 309 digits" << endl;
                input = input.substr(inputLength-MAXLENGTH, MAXLENGTH);
                inputLength=MAXLENGTH;//to not put leading zeros 
            }
            if(negative){
                this->value ='-'+ string(MAXLENGTH - inputLength, '0') + input;//adding the negative symbol
            }
            else{
                this->value =string(MAXLENGTH - inputLength, '0') + input;
            }
        }
        else{
            fileRead=false;//failed to read the file
        }
        return fileRead;
    }
    void output(){
        string output=this->value;
        if(output!=OVERFLOWED){
            int i=-1;//removing leading zeros from output if any;
            bool flag=true;
            bool negative=false;

            if(output[0]=='-'){
                negative=true;
                //make input to positive and then put negative at end of the function
                output=output.substr(1,MAXLENGTH);
            }
            for(int k=0;k<MAXLENGTH-1 && flag;k++){//if answer is zero out put zero , so till maxlength-1
                if(output[k]!='0'){
                    flag=false;
                }
                else{
                    i++;
                }
            }
            //last leading zero is at i => take substring from i+1 till end
            if(i!=-1){
                output=output.substr(i+1,MAXLENGTH-(i+1));
            }
            if(negative){
                output='-'+output;
            }
        }
        writeStringToFile(output);
    }

    BigInt operator +(BigInt val2){
        BigInt val1;
        val1.value=this->value;
        BigInt result;
        bool val1Sign=(val1.value[0]!='-');//false means negative
        bool val2Sign=(val2.value[0]!='-');

        if(!val1Sign){
            val1.value=val1.value.substr(1,MAXLENGTH);//removing the negative signs
        }

        if(!val2Sign){
            val2.value=val2.value.substr(1,MAXLENGTH);
        }
        if(!(val1Sign^val2Sign)){//(val1Sign && val2Sign) || (!val1Sign && !val2Sign)
            //perform addition
            int index=MAXLENGTH-1;//last index of string
            int carry=0;
            while(index>=0){
                int sum = (val1.value[index]-'0')+(val2.value[index]-'0') + carry;
                carry=sum/10;//next carry
                sum=sum%10;
                result.value[index]=sum+'0';
                index--;
            }
            if(carry !=0){
                cout<<OVERFLOWED<<endl;
                result.value=OVERFLOWED;
            }
            if(!val1Sign && carry==0){//if it is not overflowed
                result.value = '-' + result.value;
            }
        }
        else{
            if(!val1Sign){
                result=val2-val1;
            }
            else{
                result=val1-val2;
            }
        }
        return result;
    }

    BigInt operator -(BigInt val2){
        BigInt val1;
        val1.value=this->value;
        BigInt result;
        bool val1Sign=(val1.value[0]!='-');//false means negative
        bool val2Sign=(val2.value[0]!='-');

        if(!val1Sign){
            val1.value=val1.value.substr(1,MAXLENGTH);//removing the negative signs
        }
        if(!val2Sign){
            val2.value=val2.value.substr(1,MAXLENGTH);
        }

        if((!val1Sign && !val2Sign)){
            // -val1 -(-val2)= val2-val1
            result=val2-val1;
        }
        else if((val1Sign && val2Sign)){
            // val1-val2 // main subtraction logic // in this block val1 and val2 are >0. if val1>val2=+ve else -ve
            if (val1.value<val2.value) {
                result=val2-val1;
                result.value='-'+ result.value;
            } else if (val1.value==val2.value) {
                // result.value;
            } else {
                // main subtraction val1>val2 => val1-val2
                int borrow=0;
                int num1,num2,numRes;
                for (int i = MAXLENGTH - 1; i >= 0; i--) {
                    num1 = (val1.value[i] - '0') + borrow;
                    num2 = (val2.value[i] - '0');
                    
                    if (num1 < num2) {
                        num1 += 10; 
                        borrow = -1;
                    } else {
                        borrow = 0;
                    }
                    numRes = num1 - num2;
                    result.value[i] = numRes + '0'; 
                }
            }

        }
        else{
            //add
            if(!val2Sign){ // val2 is -ve => val1-(-val2) => val1+val2
                result=val1+val2;
            }
            else{
                // val1 is negative => -val1 -val2 => -(val1+val2)
                result=val1+val2;
                if(result.value!=OVERFLOWED){
                    result.value='-'+ result.value;
                }
            }
        }
        
        return result;
    }

    BigInt operator *(BigInt val2){
        BigInt result;
        result.value=string(2*MAXLENGTH,'0');
        BigInt val1;
        bool overflowed=false;
        val1.value=this->value;
        bool val1Sign=(val1.value[0]!='-');//false means negative
        bool val2Sign=(val2.value[0]!='-');

        if(!val1Sign){
            val1.value=val1.value.substr(1,MAXLENGTH);//removing the negative signs
        }
        if(!val2Sign){
            val2.value=val2.value.substr(1,MAXLENGTH);
        }
        
        BigInt ONE;
        BigInt ZERO;//already initialized as zero in constructor
        ONE.value=createBigIntOne();

        if(val1.value==ONE.value){
            result=val2;
        }
        else if(val2.value==ONE.value){
            result=val1;
        }
        else if(val1.value!=ZERO.value && val2.value!=ZERO.value){
            for (int i = MAXLENGTH - 1; i >= 0; --i) {
                int carry = 0;
                for (int j = MAXLENGTH - 1; j >= 0; --j) {
                    int product = (val1.value[i] - '0') * (val2.value[j] - '0') + (result.value[i + j + 1] - '0') + carry;
                    carry = product / 10;
                    result.value[i + j + 1] = (product % 10) + '0';
                }
                result.value[i] += carry;
            }
            overflowed=checkOverFlowForMultiplication(result.value);
            if(!overflowed){
                result.value=result.value.substr(MAXLENGTH,MAXLENGTH);
            }
            else{
                result.value=OVERFLOWED;
                cout<<OVERFLOWED<<endl;
            }
        }
        if(result.value!=ZERO.value && (val1Sign^val2Sign) && !overflowed){
            result.value='-'+result.value;
        }
        return result;
    }
};

void addition(){
    cout<<"Addition"<<endl;
    BigInt b1,b2,b3;
    bool b1ReadFromFile= b1.input(FILE1);
    bool b2ReadFromFile= b2.input(FILE2);
    if(b1ReadFromFile && b2ReadFromFile){
        b3=b1+b2;
        b3.output(); 
    }
}

void subtraction(){
    cout<<"Subtraction"<<endl;
    BigInt b1,b2,b3;
    bool b1ReadFromFile= b1.input(FILE1);
    bool b2ReadFromFile= b2.input(FILE2);
    if(b1ReadFromFile && b2ReadFromFile){
        b3=b1-b2;
        b3.output(); 
    }
}
void multiplication(){
    cout<<"Multiplication"<<endl;
    BigInt b1,b2,b3;
    bool b1ReadFromFile= b1.input(FILE1);
    bool b2ReadFromFile= b2.input(FILE2);
    if(b1ReadFromFile && b2ReadFromFile){
        b3=b1*b2;
        b3.output(); 
    }
}

void calculatorMenu(){
    bool calculatorRunning=true;
    cout<<"\n\tBig Int (1024 bit Integer) calculator"<<endl;
    while(calculatorRunning){
        int option=4;
        cout<<"Choose the operation"<<endl;
        cout<<"1) Addition"<<endl<<"2) Subtraction"<<endl<<"3) Multiplication"<<endl<<"4) Exit"<<endl;
        cout<<"Enter value: ";
        cin>>option;
        switch(option){
            case 1: addition();
                break;
            case 2: subtraction();
                break;
            case 3: multiplication();
                break;
            default:{
                calculatorRunning=false;
            }
        }
    }
}

int main(){
    calculatorMenu();
}
