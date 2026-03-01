/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

 #include "Text.h"

 void Text::ApplyHighlight(wxTextCtrl* textCtrl) {
    wxString text = textCtrl->GetValue();
    highlightRange.occupiedRanges.clear();

    wxTextAttr normal(*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);
    // For plain text, we won't do any actual syntax highlighting, but we can still mark the entire range as occupied to prevent any other highlighters from trying to style it.
    highlightRange.Mark(0, text.length());
 }