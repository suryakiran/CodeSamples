//
// Not putting this piece of code between ifdef guards as this needs to be
// included as and when asked for.
//

SignalsVec m_signals ;                                                             
typedef boost::fusion::result_of::begin<SignalsVec>::type BeginIter ;              
typedef boost::fusion::result_of::end<SignalsVec>::type EndIter ;                  
template<int id> struct get_type                                                   
{                                                                                  
	typedef typename boost::fusion::result_of::value_of<                           
		typename boost::fusion::result_of::advance_c<BeginIter, id>::type >::type  
		::reference value_type ;                                               
} ;                                                                                

struct initialize                                                                  
{                                                                                  
	template <typename SmartPtr>                                                   
		void operator() (SmartPtr& p_item) const                                   
		{                                                                          
			typedef typename SmartPtr::value_type ItemType ;                       
			p_item = SmartPtr(new ItemType) ;                                      
		}                                                                          
}  ;                                                                               

public:                                                                                
	template <int id>                                                                  
		typename get_type<id>::value_type                                              
			signal (void) { return *(boost::fusion::at_c<id>(m_signals)) ; }           


#include <EmitSignalMacro.hxx>
