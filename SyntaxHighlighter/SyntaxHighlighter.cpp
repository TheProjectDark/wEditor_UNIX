/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlighter.h"
#include "SyntaxHighlightCPP.h"
#include "SyntaxHighlightPython.h"

SyntaxHighlighter* HighlighterFactory::CreateHighlighter(const wxString& language) {
    if (language == "C++") {
        return new SyntaxHighlightCPP();
    } 
    else if (language == "Python") {
        return new SyntaxHighlightPython();
    }
    return new SyntaxHighlightCPP();
}

std::vector<wxString> HighlighterFactory::GetAvailableLanguages() {
    return {
        "C++",
        "Python"
    };
}