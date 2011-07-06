#include <Signals.hxx>

SignalBase :: SignalBase (): m_blockAllSignals(false) { }
SignalBase :: ~SignalBase () { }

void SignalBase :: blockSignal (int p_id, bool p_block)
{
	if (p_block)
		m_blockedSignals.insert(p_id) ;
	else
		m_blockedSignals.erase (p_id) ;
}

bool SignalBase :: blockSignal (int p_id)
{
	return static_cast<bool>(m_blockedSignals.count(p_id)) ;
}
