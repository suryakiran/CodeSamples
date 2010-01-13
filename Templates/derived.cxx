#include "std.hxx"
#include "derived.hxx"

int main (void)
{
	Base* b = new Derived ;
	b->func() ;
}
