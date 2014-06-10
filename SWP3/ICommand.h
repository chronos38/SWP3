#pragma once
#include "Definitions.h"

class Application;

class ICommand;
typedef Pointer<ICommand> CommandPtr;

// Command
class ICommand
{
public:

	virtual void Execute(Application&) = 0;
	virtual String GetID() const;
	virtual String GetHelp() const;
};
