#pragma once
#include <string>

enum VertexAttrib{Position = 0, Color, TexCoord, Normal};
#define PATH std::string("D:/Projects/C++ Projects/KumEngine/") // FIX: working directory
#define ERROR std::string("Line: " + std::to_string(__LINE__) + " at" +__FILE__ + "\nError: ")