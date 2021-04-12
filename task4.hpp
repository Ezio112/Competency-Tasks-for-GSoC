#include<tuple>
#include<vector>

using namespace std;

/*First I am making a tuple containing vector of those values in tuple, then modifying values in tuple to given values by 
recursively iterating through values of tuple*/

template<size_t I=0,typename ...Ts>
constexpr void assign_vector(tuple<Ts...> tup, int rep, tuple<vector<Ts>... > &res)
{
	if constexpr( I==sizeof...(Ts) ) // if we have iterated through all values, then stop the function
	{
		return ;
	}
	else{
		for(int i=0;i<rep;i++)
		{
			get<I>(res)[i] = get<I>(tup);
		}
		assign_vector<I+1>(tup,rep,res);// go to next element
	}
}

template<typename ...Ts>
tuple<vector<Ts>... > vec_tuple(tuple<Ts...> tup,int rep)
{
	auto result = make_tuple(vector<Ts>(rep)... ); //getting tuple of vector of given size.
	assign_vector(tup,rep,result); //function to modify values of  'result' tuple according to value in 'tup'
	return result;
}
