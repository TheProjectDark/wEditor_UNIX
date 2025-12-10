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