#include <DownloadFile.hxx>

#include <Poco/URIStreamOpener.h>

#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Timespan.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/File.h>
using Poco::Net::HTTPClientSession ;
using Poco::Net::HTTPResponse ;
using Poco::Net::HTTPMessage ;
using Poco::Net::HTTPStreamFactory ;
using Poco::StreamCopier;
using Poco::Path ;
using Poco::File ;
using Poco::URI;
using Poco::Exception;
using Poco::URIStreamOpener ;
using Poco::Net::HTTPRequest ;
using Poco::Net::HTMLForm ;
using Poco::Net::HTTPClientSession ;

#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include <boost/foreach.hpp>

string       DownloadFile :: m_proxyHost ("") ;
unsigned int DownloadFile :: m_proxyPort (0) ;

void DownloadFile :: init (const string& host, const unsigned int& port)
{
	m_proxyHost = host ;
	m_proxyPort = port ;
	URIStreamOpener::defaultOpener().registerStreamFactory 
		(
		 "http", 
		 new HTTPStreamFactory (host, port)
		) ;
}

DownloadFile :: DownloadFile (const string& site)
	: m_site(site), m_httpGet (true)
{
	boost::fusion::for_each(m_signals, initialize()) ;
	m_postFieldData.clear() ;
	m_timeSpan = make_pair (30l, 0l) ;
}

const LongIntPair& DownloadFile :: getTimeout (void) const
{ return m_timeSpan ; }

void DownloadFile :: setTimeout (const long int& secs, const long int& micro_secs)
{ m_timeSpan = make_pair (secs, micro_secs) ; }

DownloadFile :: ~DownloadFile ()
{
}

void DownloadFile :: addUserData (const string& key, const string& value)
{
	m_userData = make_pair (key, value) ;
}

void DownloadFile :: addPostField (const string& key, const string& value)
{
	m_postFieldData.push_back (make_pair (key, value)) ;
}

void DownloadFile :: download (void)
{
	fstream fout ;
	try
	{
		URI uri (m_site) ;

		HTTPClientSession session (uri.getHost(), uri.getPort()) ;
		if (!m_proxyHost.empty())
		{
			session.setProxyPort (m_proxyPort) ;
			session.setProxyHost (m_proxyHost) ;
		}

		HTTPRequest req ("HTTP/1.1") ;
		req.setURI (uri.getPathAndQuery()) ;

		HTMLForm form ;

		Poco::Timespan timeOut (m_timeSpan.first, m_timeSpan.second) ; 

		if (m_httpGet) req.setMethod("GET") ;
		else           req.setMethod("POST") ;

		BOOST_FOREACH (StringPair kv, m_postFieldData)
			form.set (kv.first, kv.second) ;

		form.prepareSubmit (req) ;
		req.setContentType(form.getEncoding()) ;

		session.setTimeout (timeOut) ;
		ostream& os = session.sendRequest (req) ;
		if (!m_httpGet) form.write (os) ;

		HTTPResponse res ;
		istream& rs = session.receiveResponse (res) ;
		fout.open (m_outFile.c_str(), ios::out) ;
		StreamCopier::copyStream(rs, fout);
		fout.close() ;

		while (
				res.getStatus() == HTTPResponse :: HTTP_FOUND
				//		|| res.getStatus() == HTTPResponse :: HTTP_MOVED_PERMANENTLY
			  )
		{
			uri.resolve (res["Location"]) ;
			req.setURI (uri.getPathAndQuery()) ;

			ostream& os = session.sendRequest (req) ;
			if (!m_httpGet) form.write (os) ;

			istream& rs = session.receiveResponse (res) ;
			fout.open (m_outFile.c_str(), ios::out) ;
			StreamCopier::copyStream(rs, fout);
			fout.close() ;
		}
		emitSignal <Status>(true) ;
	}
	catch (Exception& exc)
	{
		fout.close() ;
		Poco::File file(m_outFile) ;
		if (file.exists())
			file.remove() ;
		emitSignal<Status>(false) ;
		cout << exc.displayText() << endl ;
	}
	return ;
}
