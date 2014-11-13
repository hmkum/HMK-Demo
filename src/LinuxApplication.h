#pragma once

#include "base.h"
#include "Application.h"

#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef linux || __linux__ || __linux
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

namespace hmk
{

class LinuxApplication : public Application
{
public:
	LinuxApplication();
	virtual ~LinuxApplication();
};

}