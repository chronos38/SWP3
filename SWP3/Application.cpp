#include "Application.h"
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

Application::Application(int argc, char** argv)
{
	Hash<String, String> options = ParseCommandLine(argc, argv);

	for (auto option : options) {
		if (option.first == "-h" || option.first == "--help") {
			PrintHelp();
		} else if (option.first == "-p" || option.first == "--port") {
			m_sPort = option.second;
		} else if (option.first == "-u" || option.first == "--user") {
			m_sUser = option.second;
		}
	}

	if (m_sUser == "") {
		CreateRandomUser();
	}

	m_Listener = Thread([this]() {
		try {
			PeerContextPtr pPeer(new PeerContext());
			pPeer->Listen("127.0.0.1", this->GetPort());

			while (true) {

			}
		} catch (...) {
			exit(EXIT_FAILURE);
		}
	});

	m_Listener.detach();
}

Application::~Application()
{
}

int Application::Execute()
{
	String sInput = "";

	cout << "Welcome to this extremely easy to use Peer-To-Peer program\n";
	cout << "Commands are:\n";
	PrintCommands();

	do {
		cin >> sInput;
		std::transform(sInput.begin(), sInput.end(), sInput.begin(), ::toupper);
		auto found = m_Commands.find(sInput);

		if (found != m_Commands.end()) {
			found->second->Execute(*this);
		}

	} while (sInput != "EXIT");

	return (EXIT_SUCCESS);
}

String Application::GetUser() const
{
	return m_sUser;
}

String Application::GetPort() const
{
	return m_sPort;
}

Hash<String, String> Application::ParseCommandLine(int argc, char** argv) const
{
	Hash<String, String> option;

	for (int i = 0; i < argc; i++) {
		String sArg = argv[i];

		if (sArg.find("--") != String::npos) {
			if (i + 1 < argc) {
				option[sArg] = argv[i + 1];
			} else {
				option[sArg] = "";
			}
		} else if (sArg.find("-") != String::npos) {
			if (i + 1 < argc) {
				option[sArg] = argv[i + 1];
			} else {
				option[sArg] = "";
			}
		} else {
			option[sArg] = sArg;
		}
	}

	return option;
}

void Application::PrintHelp() const
{
	cout << "Options are:\n";
	cout << "\t-h, --help:\t\t\tPrint this message\n";
	cout << "\t-p [arg], --port [arg]:\t\tSpecify port or service (defaults to 17539)\n";
	cout << "\t-u [arg], --user [arg]:\t\tSet peer username\n" << endl;
	exit(EXIT_SUCCESS);
}

void Application::CreateRandomUser()
{
	static const String sValidChars = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int i = 0; i < 16; i++) {
		m_sUser.push_back(sValidChars[rand() % sValidChars.size()]);
	}
}

void Application::PrintCommands() const
{
	for (auto command : m_Commands) {
		cout << "\t" << command.first << ": " << command.second->GetHelp() << "\n";
	}

	cout << "\n";
	cout << "Enter an empty command to print this list again.\n";
}
