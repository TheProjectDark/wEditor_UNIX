#pragma once
#include <wx/wx.h>
#include "SyntaxHighlighter.h"

class SyntaxHighlightPython : public SyntaxHighlighter {
public:
    void ApplyHighlight(wxTextCtrl* textCtrl) override;
    wxString GetLanguageName() const override { return "Python"; }
};