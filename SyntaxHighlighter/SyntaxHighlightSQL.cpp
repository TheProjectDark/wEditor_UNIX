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

    wxTextAttr normal (*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    //SQL keywords
    std::vector<wxString> keywords = {
        "SELECT", "FROM", "WHERE", "INSERT", "UPDATE", "DELETE", "JOIN", "INNER", "LEFT", "RIGHT", "ON", "CREATE", "TABLE", "ALTER", "DROP", "INDEX", "VIEW", "TRIGGER", "PROCEDURE", "FUNCTION", "UNION", "GROUP BY", "ORDER BY", "HAVING", "DISTINCT", "AS", "AND", "OR", "NOT", "IN", "IS", "NULL", "LIKE", "BETWEEN", "EXISTS",
        "select", "from", "where", "insert", "update", "delete", "join", "inner", "left", "right", "on", "create", "table", "alter", "drop", "index", "view", "trigger", "procedure", "function", "union", "group by", "order by", "having", "distinct", "as", "and", "or", "not", "in", "is", "null", "like", "between", "exists"
    };

    for (const auto& keyword : keywords)
    {
        size_t pos = text.find(keyword);
        while (pos != wxString::npos) {
            wxTextAttr keywordAttr(wxColour(0, 153, 51));
            textCtrl->SetStyle(pos, pos + keyword.length(), keywordAttr);
            pos = text.find(keyword, pos + 1);
        }
    }

    //data types
    std::vector<wxString> dataTypes = {
        "INT", "VARCHAR", "CHAR", "TEXT", "DATE", "FLOAT", "DOUBLE", "BOOLEAN", "DECIMAL", "BLOB",
        "int", "varchar", "char", "text", "date", "float", "double", "boolean", "decimal", "blob"
    };
    for (const auto& dtype : dataTypes)
    {
        size_t pos = text.find(dtype);
        while (pos != wxString::npos) {
            wxTextAttr typeAttr(wxColour(0, 102, 204));
            textCtrl->SetStyle(pos, pos + dtype.length(), typeAttr);
            pos = text.find(dtype, pos + 1);
        }
    }

    //symbols
    std::vector<wxString> symbols = { ",", ";", "(", ")", "=", "<", ">", "+", "-", "*", "/" };
    for (const auto& symbol : symbols)
    {
        size_t pos = text.find(symbol);
        while (pos != wxString::npos) {
            wxTextAttr symbolAttr(wxColour(255, 102, 204));
            textCtrl->SetStyle(pos, pos + symbol.length(), symbolAttr);
            pos = text.find(symbol, pos + 1);
        }
    }

    //comments
    size_t commentPos = text.find("--");
    while (commentPos != wxString::npos) {
        wxTextAttr commentAttr(wxColour(128, 128, 128));
        textCtrl->SetStyle(commentPos, text.length(), commentAttr);
        commentPos = text.find("--", commentPos + 1);
    }

    //strings
    size_t start = text.find("'");
    while (start != wxString::npos) {
        size_t end = text.find("'", start + 1);
        if (end != wxString::npos) {
            wxTextAttr stringAttr(wxColour(204, 0, 204));
            textCtrl->SetStyle(start, end + 1, stringAttr);
            start = text.find("'", end + 1);
        } else {
            break;
        }
    }
}