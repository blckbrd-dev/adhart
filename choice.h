#pragma once

#include <map>
#include <string>

namespace adhart
{
	enum choice
	{
		NONE,
		LEFT,
		RIGHT,
		WAIT,
		PRAY,
		QUIT,
		YES,
		NO
	};

	static std::map<choice, std::string> choiceToText = {
		{ LEFT, 	"go left " }, 
		{ RIGHT, 	"go right" },
		{ WAIT, 	"wait    " },
		{ PRAY, 	"pray    " },
		{ QUIT, 	"quit    " },
		{ YES, 		"accept  " },
		{ NO, 		"decline " }
	};
}