#include <std.hxx>

typedef boost::shared_ptr <int> int_ptr;

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

  void stack_test()
  {
    stack <int_ptr> si;
    si.push (int_ptr(new int(5)));
    si.push (int_ptr(new int(4)));
    si.push (int_ptr(new int(3)));
    si.push (int_ptr(new int(2)));
    si.push (int_ptr(new int(1)));
    si.push (int_ptr(new int(0)));

    cout << *(si.top()) << endl;
    cout << si.top().use_count() << endl;

    int_ptr ip = si.top();
    *ip = 587;

    cout << si.top().use_count() << endl;

    cout << *(si.top()) << endl;

  }
}

int main (void)
{
	cout << "Std Test" << endl ;
	//transform_test() ;
  stack_test();
}
