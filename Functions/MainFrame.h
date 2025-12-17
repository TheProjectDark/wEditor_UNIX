/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#pragma once
#include <wx/wx.h>
#include "../SyntaxHighlighter/SyntaxHighlighter.h"
#include "DragNDrop.h"

//creating the frame class with its functions
class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);
        ~MainFrame();
        void OnDropFiles(const wxArrayString& filenames);

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