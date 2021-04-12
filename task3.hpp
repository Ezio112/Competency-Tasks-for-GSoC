#include<iostream>
#include<vector>
#include<tuple>
#include<typeinfo>

/*
I am declaring a function that will recursively iterate through elements of tuple,
and when it will encounter an element having type same as that of vector<T> (T will given by user), it will return reference to that vector.
*/

using namespace std;

template<typename T, size_t I=0,typename ...Ts>
vector<T>& get_vec(tuple<Ts...> &tup)
{
	if constexpr(I==sizeof...(Ts)) // we have iterated through whole tuple and element not found
	{
		cerr<<"Element not found in tuple"<<endl;
		exit(1);
	}
	else
	{
		if constexpr(is_same< vector<T>&, decltype(get<I>(tup)) >::value) // element found
		{
			return get<I>(tup);
		}
		else
		{
			return get_vec<T,I+1>(tup); //go to next element
		}
	}
}
