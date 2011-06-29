#ifndef PropertyTree_h_INCLUDED
#define PropertyTree_h_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>

class PropertyTree : public pt::ptree
{
	public:
		PropertyTree() : pt::ptree() { }

		PropertyTree(const std::string& p_prefix)
			: pt::ptree(), m_prefix(p_prefix) { }

		virtual ~PropertyTree () { }

		void setPrefix (const std::string& p_prefix)
		{ m_prefix = p_prefix ; }

		template <typename ValueType> void
			setValue(const std::string& p_key, const ValueType& p_value) 
			{ put(getKey(p_key), p_value) ;}

		template <typename ValueType> ValueType
			getValue (const std::string& p_key, const ValueType& p_defaultValue) const
			{
				boost::optional<ValueType> val =
					get_optional<ValueType>(getKey(p_key)) ;
				if (!val) return p_defaultValue ;
				else      return val.get() ;
			}

		template <typename ValueType> ValueType
			getValue (const std::string& p_key) const
			{ return get<ValueType>(getKey(p_key)) ; }

		void printTree (std::ostream& p_stream = std::cout) const
		{ 
			pt::write_xml (p_stream, static_cast<pt::ptree>(*this), 
					pt::xml_writer_settings<char>(' ', 4)) ; 
		}

		void printTree (const std::string& p_fileName) const
		{
			pt::write_xml (p_fileName, static_cast<pt::ptree>(*this), 
				std::locale(), pt::xml_writer_settings<char>(' ', 4)) ; 
		}

		void loadTree (const std::string& p_fileName)
		{ pt::read_xml (p_fileName, static_cast<pt::ptree&>(*this)) ; }

		void loadTree (std::istream& p_stream)
		{ pt::read_xml (p_stream, static_cast<pt::ptree&>(*this)) ; }

	private:
		std::string m_prefix ;

	protected:
		std::string getKey (const std::string& p_key) const
		{
			if (m_prefix.empty()) return p_key ;
			return (format ("%1%.%2%") % m_prefix % p_key).str() ;
		}
} ;
#endif
