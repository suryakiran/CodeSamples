#ifndef SIGNAL_BASE_HXX
#define SIGNAL_BASE_HXX 1

#include <string>
#include <map>
#include <set>

using namespace std ;

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence/intrinsic.hpp>
#include <boost/fusion/functional.hpp>
#include <boost/fusion/iterator.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#define BOOST_SIGNAL(...) boost::shared_ptr< boost::signals2::signal < __VA_ARGS__ > >

class SignalBase
{
	public:
		~SignalBase () ;

		void blockSignals (bool p_block) { m_blockAllSignals = p_block ; }
		bool blockSignals (void)         { return m_blockAllSignals ; }

		void blockSignal (int p_id, bool p_block) ;
		bool blockSignal (int p_id) ;

	protected:
		SignalBase () ;

	private:
		set<int> m_blockedSignals ;
		bool m_blockAllSignals ;
} ;

#endif
