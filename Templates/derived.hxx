#ifndef DERIVED_HXX
#define DERIVED_HXX 1

struct Base 
{
	Base() 
	{ cout << "Base Constructor" << endl ; }

	virtual ~Base()
	{ cout << "Base Destructor" << endl ; }

	virtual void func (void) = 0 ;

	template <typename ValueType> void
		funcTemplate (const ValueType& p_type) 
		{
			cout << "Value: " << p_type << endl ;
		}
} ;

struct Derived : public Base
{
	Derived() 
	{ cout << "Derived Constructor" << endl ; }

	virtual ~Derived()
	{ cout << "Derived Destructor" << endl ; }

	virtual void func () 
	{ funcTemplate(5) ; funcTemplate("Surya") ; }
} ;

#endif
