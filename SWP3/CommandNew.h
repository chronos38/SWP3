#pragma once
#include "ICommand.h"

class CommandNew : public ICommand
{
public:

	virtual ~CommandNew();

	virtual void Execute(Application&) override;
};
