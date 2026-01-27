/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlightSQL.h"

void SyntaxHighlightSQL::ApplyHighlight(wxTextCtrl* textCtrl)
{
    wxString text = textCtrl->GetValue();
    highlightRange.occupiedRanges.clear();

    wxTextAttr normal (*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    // First pass: mark strings and comments (highest priority - don't highlight inside them)
    // Strings
    size_t start = text.find("'");
    while (start != wxString::npos) {
        size_t end = text.find("'", start + 1);
        if (end != wxString::npos) {
            wxTextAttr stringAttr(wxColour(204, 0, 204));
            textCtrl->SetStyle(start, end + 1, stringAttr);
            highlightRange.Mark(start, end + 1);
            start = text.find("'", end + 1);
        } else {
            break;
        }
    }

    // Comments
    size_t commentPos = text.find("--");
    while (commentPos != wxString::npos) {
        size_t endOfLine = text.find("\n", commentPos);
        if (endOfLine == wxString::npos) endOfLine = text.length();
        wxTextAttr commentAttr(wxColour(128, 128, 128));
        textCtrl->SetStyle(commentPos, endOfLine, commentAttr);
        highlightRange.Mark(commentPos, endOfLine);
        commentPos = text.find("--", endOfLine);
    }

    // Second pass: highlight keywords, types, etc (but skip already highlighted areas)
    //SQL keywords
    std::vector<wxString> keywords = {
        "SELECT", "FROM", "WHERE", "INSERT", "UPDATE", "DELETE", "JOIN", "INNER", "LEFT", "RIGHT", "ON", "CREATE", "TABLE", "ALTER", "DROP", "INDEX", "VIEW", "TRIGGER", "PROCEDURE", "FUNCTION", "UNION", "GROUP BY", "ORDER BY", "HAVING", "DISTINCT", "AS", "AND", "OR", "NOT", "IN", "IS", "NULL", "LIKE", "BETWEEN", "EXISTS", "CONSTRAINT",
        "select", "from", "where", "insert", "update", "delete", "join", "inner", "left", "right", "on", "create", "table", "alter", "drop", "index", "view", "trigger", "procedure", "function", "union", "group by", "order by", "having", "distinct", "as", "and", "or", "not", "in", "is", "null", "like", "between", "exists", "constraint"
    };

    for (const auto& keyword : keywords)
    {
        size_t pos = text.find(keyword);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + keyword.length())) {
                // Check word boundaries for single-word keywords
                bool validMatch = true;
                if (keyword[0] != ' ') {
                    if (pos > 0 && wxIsalnum(text[pos - 1])) validMatch = false;
                    if (pos + keyword.length() < text.length() && wxIsalnum(text[pos + keyword.length()])) validMatch = false;
                }
                if (validMatch) {
                    wxTextAttr keywordAttr(wxColour(0, 153, 51));
                    textCtrl->SetStyle(pos, pos + keyword.length(), keywordAttr);
                    highlightRange.Mark(pos, pos + keyword.length());
                }
            }
            pos = text.find(keyword, pos + 1);
        }
    }

    //data types
    std::vector<wxString> dataTypes = {
        "INT", "INTEGER", "VARCHAR", "CHAR", "TEXT", "DATE", "FLOAT", "DOUBLE", "BOOLEAN", "DECIMAL", "BLOB",
        "int", "integer", "varchar", "char", "text", "date", "float", "double", "boolean", "decimal", "blob"
    };
    for (const auto& dtype : dataTypes)
    {
        size_t pos = text.find(dtype);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + dtype.length())) {
                // Check word boundaries
                bool validMatch = true;
                if (pos > 0 && wxIsalnum(text[pos - 1])) validMatch = false;
                if (pos + dtype.length() < text.length() && wxIsalnum(text[pos + dtype.length()])) validMatch = false;
                if (validMatch) {
                    wxTextAttr typeAttr(wxColour(0, 102, 204));
                    textCtrl->SetStyle(pos, pos + dtype.length(), typeAttr);
                    highlightRange.Mark(pos, pos + dtype.length());
                }
            }
            pos = text.find(dtype, pos + 1);
        }
    }

    //protected words
    std::vector<wxString> protectedWords = {
        "PRIMARY", "KEY", "FOREIGN", "REFERENCES", "UNIQUE", "CHECK", "DEFAULT", "AUTO_INCREMENT",
        "primary", "key", "foreign", "references", "unique", "check", "default", "auto_increment"
    };
    for (const auto& pword : protectedWords)
    {
        size_t pos = text.find(pword);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + pword.length())) {
                // Check word boundaries
                bool validMatch = true;
                if (pos > 0 && wxIsalnum(text[pos - 1])) validMatch = false;
                if (pos + pword.length() < text.length() && wxIsalnum(text[pos + pword.length()])) validMatch = false;
                if (validMatch) {
                    wxTextAttr pwordAttr(wxColour(255, 102, 0));
                    textCtrl->SetStyle(pos, pos + pword.length(), pwordAttr);
                    highlightRange.Mark(pos, pos + pword.length());
                }
            }
            pos = text.find(pword, pos + 1);
        }
    }

    //symbols
    std::vector<wxString> symbols = { ",", ";", "(", ")", "=", "<", ">", "+", "-", "*", "/" };
    for (const auto& symbol : symbols)
    {
        size_t pos = text.find(symbol);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + symbol.length())) {
                wxTextAttr symbolAttr(wxColour(255, 102, 204));
                textCtrl->SetStyle(pos, pos + symbol.length(), symbolAttr);
                highlightRange.Mark(pos, pos + symbol.length());
            }
            pos = text.find(symbol, pos + 1);
        }
    }
}