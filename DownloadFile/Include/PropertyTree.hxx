#ifndef PROPERTY_TREE_HXX
#define PROPERTY_TREE_HXX 1

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/format.hpp>

using boost::format ;

#include <iostream>
#include <string>

namespace pt = boost::property_tree ;

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

#define DECLARE_PROPERTY_TREE_TEMPLATE_FUNCTIONS(derivedClassName, typeName)                    \
template<> typeName                                                                             \
derivedClassName :: getValue (const std::string& p_key, const typeName& p_defaultValue) const ; \
template<> typeName                                                                             \
derivedClassName :: getValue (const std::string& p_key) const ;                                 \
template<> void                                                                                 \
derivedClassName :: setValue (const std::string& p_key, const typeName& p_value)

#define DEFINE_PROPERTY_TREE_DEFAULT_IMPLEMENTATION()                   \
public:                                                                 \
template <typename T> T                                                 \
	getValue (const std::string& p_key, const T& p_defaultValue) const  \
	{ return PropertyTree::getValue<T> (p_key, p_defaultValue) ; }      \
                                                                        \
template <typename T> T                                                 \
	getValue (const std::string& p_key) const                           \
	{ return PropertyTree::getValue<T> (p_key) ; }                      \
                                                                        \
template <typename T> void                                              \
	setValue (const std::string& p_key, const T& p_value)               \
	{ PropertyTree::setValue<T> (p_key, p_value) ; }

#define DERIVE_FROM_PROPERTY_TREE(className, prefixName)                \
	class className : public PropertyTree                               \
{                                                                       \
	public:                                                             \
		   className () : PropertyTree (prefixName) { }                 \
	DEFINE_PROPERTY_TREE_DEFAULT_IMPLEMENTATION()                       \
}

#endif
