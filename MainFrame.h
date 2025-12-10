#pragma once
#include <wx/wx.h>
#include "SyntaxHighlighter/SyntaxHighlighter.h"

//creating the frame class with its functions
class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);
        ~MainFrame();

    private:
        wxTextCtrl* textCtrl;
        wxChoice* languageChoice;
        SyntaxHighlighter* currentHighlighter;
        wxString currentLanguage;

        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
        void OnText(wxCommandEvent& event);
        void OnLanguageChange(wxCommandEvent& event);
        void HighlightSyntax();
};