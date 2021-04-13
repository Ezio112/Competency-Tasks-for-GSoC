#include<iostream>
#include<string>
#include<vector>
#include<math.h>
#include<cstring>
using namespace std;

//Here I have represented the number in vector<int> and exponent to avoid rouding errors

// overloading operator == for number represented in vector<int>
bool operator == (vector<int> &lhs, vector<int> &rhs)
{
	size_t n1 = lhs.size(); 
	size_t n2 = rhs.size();

	//Removind leading zeros in both the numbers.
	while(!lhs.empty() && lhs[0]==0)
		lhs.erase(lhs.begin());
	while(!rhs.empty() && rhs[0]==0)
		rhs.erase(rhs.begin());

	//If size of vectors are not equal numbers are not equal.
	if(n1!=n2) return false;
	for(size_t i=0;i<n1;i++)
	{
		if(lhs[i]!=rhs[i]) return false;
	}
	return true;
}




// multiplying our number by 0.5
void multiply(vector<int> &num,int &num_exp)
{
	int carry = 0;
	auto n = num.size();
	auto i = n;
	for(i=0;i<n;i++)
	{
		num[i]*=5;
		num[i]+=carry;
		carry = num[i]/10;
		num[i] = num[i]%10;
	}
	if(carry!=0) {
		num.push_back(carry);
	}
	num_exp-=1;
}




// checks validity of our number
bool check_validity(vector<int> &vec, int exponent)
{
	int size_num = vec.size();
	if( (-exponent) < size_num) return false;  // if number is greater than 1
	vector<int> num; // our number to iterate with
	int num_exp; // exponent of above number
	num.push_back(5); 
	num_exp = -1;

	// loop to iterate through powers of 0.5
	while(true) // checking whether our number is power of 0.5 or not
	{
		if(exponent>num_exp) return false; 
		if(vec==num && exponent==num_exp) return true; //if both exponent and vector are same, then return true
		multiply(num,num_exp);
	}
	return true; //this line will never work.
}



//function to get our number in 'long double' from vector and exponent
long double get_float(vector<int> &vec,int exponent)
{
	long double number = 0.0;
	size_t n = vec.size();
	for(size_t i=n-1;i>=0;i--)
	{
		number*=10;
		number+=vec[i];
		if(i==0) break; 	// beacuse size_t type of number can not be negative, so the loop will run infinitely
	}
	number*=pow(10,exponent);
	return number;
}





long double operator ""_num (const char* number)
{
	size_t end_point;
	size_t size;
	int exponent=0;
	bool pos_exponent = true;
	try{
		size = strlen(number);
		end_point = size-1;

		// to get value of exponent, if explicitly given
		for(size_t i=0;i<size;i++)
		{
			if(number[i]=='e' || number[i]=='E')
			{
				end_point = i-1;
				if((i+1)==size)
				{
					cout<<"INVALID SYNTAX"<<endl;
					exit(0);
				} // if e is the last value in string, then syntex is wrong

				if(number[i+1]=='+')
				{
					pos_exponent = true;
					i++;
				}

				if(number[i+1]=='-')
				{
					pos_exponent = false;
					i++;
				}

				if((i+1)==size)
				{
					cout<<"INVALID SYNTAX"<<endl;
					exit(0);
				}// if no value after + or - sign, then syntex is wrong

				for(size_t j=i+1;j<size;j++)
				{
					exponent*=10;
					exponent+=(number[j]-'0'); //getting number in int from char and adding to exponent
				}

				if(pos_exponent==false) exponent*=-1; // multiplying exponent with -1, for negative exponents

				break;
			}
		}

		// getting position of "."
		for(size_t i=0;i<size;i++)
		{
			if(number[i]=='.')
			{
				exponent -= (end_point-i);
			}
		}// from now on we will ignore "." in string, because we have deacreased exponent to counter its effect


		vector<int> vec;

		while(true) // to transfer ending zeroes to exponent
		{
			if(number[end_point]=='0')
			{
				exponent++;
				end_point--;
			}
			else break;
		}

		for(size_t i=0;i<=end_point;i++)
		{
			while(number[i]=='0') i++; // to avoid starting zeroes to get into vector

			if(number[i]!='.')
			{
				vec.push_back(number[i] - '0'); // converting our number into vector
			}
		}


		// now I am reversing the vector for ease of operations 
		size_t n = vec.size();
		vector<int> new_vec( n );
		for(size_t i=0;i<n;i++)
		{
			new_vec[i] = vec[n-i-1];
		}


		if(!check_validity(new_vec,exponent)) // checking validity
		{
			throw(number);
		}
		return get_float(new_vec,exponent); //getting value in float
	}

	catch(const char* number)
	{
		cout<<"Your number "<<number<<" is not valid"<<endl;
		exit(0);
	}

	return 0.0; // this line will never work
}



int main()
{
	long double n;
	n = 5e-1_num;
	cout<<"5e-1_num = "<<n<<endl;
	n = 05e-1_num;
	cout<<"05e-1_num = "<<n<<endl;
	n = 0.125_num;
	cout<<"0.125_num = "<<n<<endl;
	n = 0.125000_num;
	cout<<"0.125000_num = "<<n<<endl;
	n = 125000e-6_num;
	cout<<"125000e-6_num = "<<n<<endl;
	n = 0.0125e+1_num;
	cout<<"0.0125e+1_num = "<<n<<endl;
	n = 0.987663459932229e+3_num;
	cout<<n<<endl;
	return 0;	
}
