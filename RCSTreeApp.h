#pragma once

#include "common.h"

class RCSTreeApp: public QtApplication
{
public:
	RCSTreeApp(int &argc, char **argv,
		SignalHandler sigtermHandler,
		const OptionList& optionList,
		EnvironmentScope environmentScope);

	~RCSTreeApp();

	bool UserCheck();
private:
};