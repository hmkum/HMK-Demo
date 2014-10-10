#pragma once
#include <string>
#include <libgen.h>
#include <linux/limits.h>
#include <unistd.h>

enum VertexAttrib{Position = 0, Color, TexCoord, Normal};
#define PATH std::string("/home/kum/Dev/Projects/Opengl/kum/kum/") // FIX: working directory
#define ERROR std::string("Line: " + std::to_string(__LINE__) + " at" +__FILE__ + "\nError: ")