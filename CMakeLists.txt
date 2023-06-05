cmake_minimum_required(VERSION 3.12)
project(PyPlus)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
	PythonPlus/main.cpp
	PythonPlus/Compiler/StringReplace.h
	PythonPlus/Compiler/Vector2.h
	PythonPlus/Compiler/GlobalData/BuiltIns.h
	PythonPlus/Compiler/Parsing/Node.cpp
	PythonPlus/Compiler/Parsing/Node.h
	PythonPlus/Compiler/Parsing/NodeType.h
	PythonPlus/Compiler/Parsing/Parser.cpp
	PythonPlus/Compiler/Parsing/Parser.h
	PythonPlus/Compiler/Tokenisation/Lexer.cpp
	PythonPlus/Compiler/Tokenisation/Lexer.h
	PythonPlus/Compiler/Tokenisation/Token.h
	PythonPlus/Compiler/Tokenisation/TokenType.h
	PythonPlus/Console/Colour.h
)

#This will enable tokens and nodes to be printed to the display
if (DEBUG)
	message(STATUS "Debug has been activated")
	add_definitions(-D _DEBUG)
endif()

add_executable(PythonPlus ${SOURCE_FILES})