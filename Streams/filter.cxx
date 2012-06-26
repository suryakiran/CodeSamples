#include "std.hxx"
#include <boost/iostreams/filter/regex.hpp>
#include <boost/iostreams/filtering_stream.hpp>
using namespace boost;
using namespace boost::iostreams;

struct MyFilter
{
    public:
        MyFilter (const string& p_s)
            :m_s(p_s)
        {
            m_filters += regex_filter(boost::regex ("/"), "%2f");
            m_filters += regex_filter(boost::regex (" "), "%20");
        }

        string filter ()
        {
            string s;
            filtering_ostream out;
            BOOST_FOREACH (const regex_filter& rf, m_filters)
            {
                out.push (rf);
            }
            out.push(back_inserter(s));

            out << m_s;
            return s;
        }

    private:
        string m_s;
        vector<regex_filter> m_filters;
};

int main (void)
{
    string s ("/Surya Kiran/Gullapalli");
    MyFilter f (s);
    cout << f.filter() << endl;
}
