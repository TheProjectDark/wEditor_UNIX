/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "DragNDrop.h"
#include "MainFrame.h"

bool DragNDrop::OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& filenames)
{
    for (const auto& filename : filenames) {
        wxArrayString fileArray;
        fileArray.Add(filename);
        m_frame->OnDropFiles(fileArray);
    }
    return true;
}