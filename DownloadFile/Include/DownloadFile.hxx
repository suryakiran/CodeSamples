#ifndef DOWNLOAD_FILE_HXX
#define DOWNLOAD_FILE_HXX 1

#include <Poco/Foundation.h>

#include <string>
#include <set>
#include <vector>
#include <cstdio>
#include <iostream>

#include <boost/format.hpp>
#include <Signals.hxx>
#include <BoostSlots.hxx>

using namespace std ;
using boost::format ;

typedef pair <string, string> StringPair ;
typedef pair <long int, long int> LongIntPair ;

class DownloadFileException : public std::exception
{
    public:
        DownloadFileException () {}
        DownloadFileException (const string& s) { desc = s; }

        virtual ~DownloadFileException () throw() {}
        virtual const char* what() const throw() { return desc.c_str(); }
    protected:
        string desc ;
} ;

class DownloadFile : public SignalBase
{
	private:
		typedef boost::fusion::vector <
			BOOST_SIGNAL(void (bool))
			> SignalsVec ;
#include <SignalMacros.hxx>

	public:
		enum {
			Status = 0,
		} ;

	public:
		DownloadFile (const string& site) ;
		~DownloadFile () ;

		void download (void) ;

        void addPostField (const string& key, const string& value) ;
		void setGetMethod (bool http_get)
		{ m_httpGet = http_get ; }

		void setOutputFile (const string& file)
		{ m_outFile = file ; }

		string getOutputFile (void) 
		{ return m_outFile ; }

        static void init (const string& host, const unsigned int& port) ;

        void addUserData (const string& key, const string& value) ;
		StringPair getUserData (void)
		{ return m_userData ; }

		void start (void)  ;

        const string& getSite (void) const
        { return m_site ; }

        string& getSite (void)
        { return m_site ; }

        void setSite (const string& s)
        { m_site = s ; }

		const vector<StringPair>& getPostFieldData (void)
		{ return m_postFieldData ; }

		void setTimeout (const long int& secs, const long int& micro_secs = 0l) ;
		const LongIntPair& getTimeout (void) const ;

		void clearPostFieldData (void)
		{ m_postFieldData.clear() ; }

	private:
        vector <StringPair> m_postFieldData ;
		string m_site, m_outFile ;
		StringPair m_userData ;
		LongIntPair m_timeSpan ;

		bool m_httpGet, m_downloading ;

		static string m_proxyHost ;
		static unsigned int m_proxyPort ;

	protected:

} ;

#endif
