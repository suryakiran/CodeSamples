#include "std.hxx"

namespace 
{
	void transform_test (void)
	{
		float values[5] ;

		values[0] = 0.0f ;
		values[1] = 1.0f ;
		values[2] = 2.0f ;
		values[3] = 3.0f ;
		values[4] = 4.0f ;

		cout << "Values Before Transform" << endl ;

		printContainer ("Values Before Transform", values) ;
		transform (values, values + 5, values, bind2nd(divides<float>(), 4.0)) ;
		printContainer("Values After Transform", values) ;
	}
}

int main (void)
{
	cout << "Std Test" << endl ;
	transform_test() ;
}
