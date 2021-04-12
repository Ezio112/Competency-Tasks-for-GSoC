#include "task3.hpp"

using namespace std;

int main()
{
	tuple<vector<int>,vector<float>,vector<char> > tup;
	tup = make_tuple(vector<int> (2,1),vector<float> (2,2.0f),vector<char> (2,'c'));

	get_vec<char>(tup)[0] = 'a';
	get_vec<char>(tup)[1] = 'b';

	get_vec<int>(tup)[0] = 3;
	get_vec<int>(tup)[1] = 5;
	
	for(auto x:get<0>(tup))
		cout<<x<<" ";
	cout<<endl;

	for(auto x:get<2>(tup))
		cout<<x<<" ";

	return 0;
}
