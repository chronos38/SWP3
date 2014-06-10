#pragma once
#include "PeerContext.h"
#include "ICommand.h"

ExceptionClass(ApplicationException)

// Mediator
class Application
{
public:
	
	Application(int argc, char** argv);
	~Application();

	int Execute();

	void AddPeer(PeerContextPtr pPeer);
	void RemovePeer(PeerContextPtr pPeer);
	void AddComposite(const String& sName, PeerContextCompositePtr pComposite);
	void RemoveComposite(const String& sName, PeerContextCompositePtr pComposite);

	String GetUser() const;
	String GetPort() const;

protected:

	Hash<String, String> ParseCommandLine(int argc, char** argv) const;
	void PrintHelp() const;
	void CreateRandomUser();
	void PrintCommands() const;

private:

	String m_sPort = "17539";
	String m_sUser = "";

	Hash<String, CommandPtr> m_Commands;
	Hash<String, PeerContextPtr> m_Peers;
	Hash<String, PeerContextCompositePtr> m_Composites;
	
	Thread m_Listener;
	Mutex m_PeersMutex;
	Mutex m_CompositesMutex;
};
