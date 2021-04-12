#include<iostream>
#include<tuple>
#include<vector>
#include "task4.hpp"

using namespace std;

int main()
{
	auto test = make_tuple(1,2,'c',2.0f);
	auto result = vec_tuple(test,10);
	for(int i=0;i<10;i++)
	{
		cout<< get<0>(result)[i]<<" "<< get<1>(result)[i] << " "<< get<2>(result)[i] <<" "<< get<3>(result)[i] <<endl;
	}
	return 0;
}
