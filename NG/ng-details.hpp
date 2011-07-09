#ifndef NG_IMAGE_DETAILS
#define NG_IMAGE_DETAILS 1

#include <Common/PropertyTree.hxx>

using namespace std ;

struct NgImageDetails : public PropertyTree
{
	NgImageDetails ()
		: PropertyTree ("NgPod") { }
} ;

#endif
