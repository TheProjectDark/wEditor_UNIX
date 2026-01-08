/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#pragma once
#include <wx/wx.h>
#include <vector>

class SyntaxHighlighter {
public:
    virtual ~SyntaxHighlighter() = default;
    virtual void ApplyHighlight(wxTextCtrl* textCtrl) = 0;
    virtual wxString GetLanguageName() const = 0;
};

class HighlighterFactory {
public:
    static SyntaxHighlighter* CreateHighlighter(const wxString& language);
    static std::vector<wxString> GetAvailableLanguages();
};