#include <string> 
#include <iostream> 
#include <boost/foreach.hpp> 
#include <boost/xpressive/xpressive.hpp> 
using namespace std; 
using namespace boost::xpressive; 

int main() 
{ 
	std::string buffer = 
		"FROGGIE\r\n" 
		"Volume = 1\r\n" 
		"Other1= 2\r\n" 
		"Channel=3\r\n" 
		"Other =4\r\n" 
		"\r\n" 
		"FROGGIE\r\n" 
		"Volume = 5\r\n" 
		"Other1= 6\r\n" 
		"Channel=7\r\n" 
		"Other =8\r\n" 
		"\r\n" 
		"FROGGIE\r\n" 
		"Volume = 9\r\n" 
		"Other1= 0\r\n" 
		"Channel=10\r\n" 
		"\r\n"; 
	mark_tag name(1), value(2); 
	sregex name_value_pair_ = 
		(name= +alnum) >> *_s >> "=" >> *_s >> 
		(value= +_d) >> *_s >> _ln; 
	sregex message_ = 
		*_s >> "FROGGIE" >> _ln >> +name_value_pair_ >> _ln; 
	sregex re_ = +message_; 
	smatch what; 
	if(regex_search(buffer, what, re_)) 
	{ 
		cout << "Msg count: " << what.nested_results().size() << endl; 
		BOOST_FOREACH(smatch const &msg, what.nested_results()) 
		{ 
			cout << "Message:\n" << msg[0] << endl; 
			cout << " name/value pair count: " 
				<< msg.nested_results().size() << endl; 
			BOOST_FOREACH(smatch const &nvp, msg.nested_results()) 
			{ 
				cout << " name:" << nvp[name] 
					<< ", value:" << nvp[value] << endl; 
			} 
		} 
	} 
	return 0; 
} 
