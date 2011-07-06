#include <std.hxx>

int main (void)
{
	double d (10.234334);

	cout << format("Number: -%1$3.2g-") % d << endl ;
	return 0;
}
