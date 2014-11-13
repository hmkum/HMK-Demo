#pragma once

#include "base.h"
#include "Application.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#include <direct.h>
#define GetCurrentDir _getcwd

namespace hmk
{

class WindowsApplication : public Application
{
public:
	WindowsApplication();
	virtual ~WindowsApplication();
};

}