CXX = clang++
CXXFLAGS = -std=c++20
SRC = main.cpp SyntaxHighlighter/SyntaxHighlightCPP.cpp SyntaxHighlighter/SyntaxHighlighter.cpp SyntaxHighlighter/Text.cpp SyntaxHighlighter/SyntaxHighlightC.cpp SyntaxHighlighter/SyntaxHighlightJava.cpp SyntaxHighlighter/SyntaxHighlightPython.cpp SyntaxHighlighter/SyntaxHighlightAssembly.cpp SyntaxHighlighter/SyntaxHighlightSQL.cpp Functions/DragNDrop.cpp Functions/ThemeSettings.cpp Preferences/Preferences.cpp
TARGET = wEditor
WX_CONFIG = /usr/local/bin/wx-config

# Get the base libraries and add stc explicitly
WX_LIBS = $(shell $(WX_CONFIG) --libs)
WX_STC_LIB = /usr/local/lib/libwx_osx_cocoau_stc-3.3.a
WX_SCINTILLA_LIB = -lwxscintilla-3.3
WX_LEXILLA_LIB = -lwxlexilla-3.3

.PHONY: all build clean

all: $(TARGET)
build: $(TARGET)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(shell $(WX_CONFIG) --cxxflags) $(SRC) -o $(TARGET) $(WX_STC_LIB) $(WX_LIBS) $(WX_SCINTILLA_LIB) $(WX_LEXILLA_LIB)

clean:
	rm -f $(TARGET)
