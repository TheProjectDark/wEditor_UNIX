/*
 * wEditor
 * Copyright (C) 2025 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */


#include <wx/wx.h>
#include <wx/filedlg.h>
#include <wx/file.h>

//creating the frame class with its functions
class MainFrame : public wxFrame
{
    public:
        MainFrame(const wxString& title);

    private:
        wxTextCtrl* textCtrl;

        void OnExit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnOpen(wxCommandEvent& event);
};

//app class to launch this fuckass editor
class App : public wxApp
{
    public:
        bool OnInit();
};

//the main part of the code
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 50), wxSize(780, 540), wxTE_MULTILINE);
    wxButton* save = new wxButton(panel, wxID_ANY, "Save", wxPoint(10, 10), wxSize(40, 30));
    wxButton* open = new wxButton(panel, wxID_ANY, "Open", wxPoint(60, 10), wxSize(50, 30));

    save->Bind(wxEVT_BUTTON, &MainFrame::OnSave, this);
    open->Bind(wxEVT_BUTTON, &MainFrame::OnOpen, this);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
}

wxIMPLEMENT_APP(App);

//showing the frame
bool App::OnInit() {
    SetExitOnFrameDelete(true);

    MainFrame* mainFrame = new MainFrame("wEditor");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Show();
    return true;
}

//save file function
void MainFrame::OnSave(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(
        this,
        "Save file",
        "",
        "",
        "Text & Code files (*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini)|*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini|All files (*.*)|*.*",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString path = saveFileDialog.GetPath();
    wxString content = textCtrl->GetValue();

    wxFile file;
    if (file.Open(path, wxFile::write))
    {
        file.Write(content);
        file.Close();
        wxMessageBox("File saved succesfully");
    }
    else
    {
        wxMessageBox("File saving error");
    }
}

//open file function
void MainFrame::OnOpen(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(
        this,
        "Open file",
        "",
        "",
        "Text & Code files (*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini)|*.txt;*.cpp;*.h;*.hpp;*.c;*.json;*.md;*.ini|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxFile file;
    if (!file.Open(openFileDialog.GetPath()))
    {
        wxMessageBox("Failed to open file");
        return;
    }

    wxString text;
    file.ReadAll(&text);
    file.Close();

    textCtrl->SetValue(text);
}

//ts shows the about window
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("wEditor Alpha v1.0",
                 "wEditor is simple cross-platform and open-souce text editor written on C++ using wxWidgets framework.", wxOK | wxICON_INFORMATION);
}

//ts closes the app
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}