#pragma once
#include <wx/wx.h>
#include "SyntaxHighlighter.h"

class SyntaxHighlightCPP : public SyntaxHighlighter {
public:
    void ApplyHighlight(wxTextCtrl* textCtrl) override;
    wxString GetLanguageName() const override { return "C++"; }
};