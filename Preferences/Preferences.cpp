/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include <wx/wx.h>
#include <wx/config.h>
#include "Preferences.h"

//Preferences frame constructor
PreferencesFrame::PreferencesFrame(const wxString& title) {
    wxFrame::Create(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300));
    wxPanel* panel = new wxPanel(this);
    wxStaticText* label = new wxStaticText(panel, wxID_ANY, "Settings will be here in future updates.", wxPoint(20, 20));
}