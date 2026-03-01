/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlightJava.h"

void SyntaxHighlightJava::ApplyHighlight(wxTextCtrl* textCtrl)
{
    wxString text = textCtrl->GetValue();
    highlightRange.occupiedRanges.clear();
    wxTextAttr normal (*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    //imports
    std::vector<wxString> imports = {
        "import", "package"
    };
    for (const auto& imp : imports)
    {
        size_t pos = text.find(imp);;
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + imp.length())) {
                wxTextAttr importAttr(wxColour(0, 128, 128));
                textCtrl->SetStyle(pos, pos + imp.length(), importAttr);
                highlightRange.Mark(pos, pos + imp.length());
            }
            pos = text.find(imp, pos + 1);
        }
    }

    //highlighting for functions, methods and procedures
    std::vector<wxString> controlStatements = {
        "if", "else if", "while", "for", "switch", "catch"
    };
    size_t pos = text.find("(");
    while (pos != wxString::npos) {
        if (!highlightRange.IsOccupied(pos, pos + 1)) {
            bool isControlStatement = false;
            for (const auto& stmt : controlStatements) {
                size_t checkPos = pos;
                while (checkPos > 0 && (text[checkPos - 1] == ' ' || text[checkPos - 1] == '\t')) {
                    checkPos--;
                }
                if (checkPos >= stmt.length() && 
                    text.substr(checkPos - stmt.length(), stmt.length()) == stmt &&
                    (checkPos == stmt.length() || !isalnum(text[checkPos - stmt.length() - 1]))) {
                    isControlStatement = true;
                    break;
                }
            }

            if (!isControlStatement) {
                size_t nameEnd = pos;
                size_t nameStart = pos;

                while (nameStart > 0) {
                    char ch = text[nameStart -1];
                    if (isalnum(ch) || ch == '_' || ch == ':') {
                        nameStart--;
                    } else {
                        break;
                    }
                }

                if (nameStart < nameEnd) {
                    wxTextAttr funcAttr(wxColour(128, 179, 255));
                    textCtrl->SetStyle(nameStart, pos, funcAttr);
                    highlightRange.Mark(nameStart, pos);
                }
            }
        }
        pos = text.find("(", pos + 1);
    }

    //types
    std::vector<wxString> types = {
        "int", "float", "double", "char", "void", "boolean", "long", "short", "byte", "String", "class", "interface"
    };
    for (const auto& type : types)
    {
        size_t pos = text.find(type);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + type.length())) {
                wxTextAttr typeAttr(wxColour(51, 153, 255));
                textCtrl->SetStyle(pos, pos + type.length(), typeAttr);
                highlightRange.Mark(pos, pos + type.length());
            }
            pos = text.find(type, pos + 1);
        }
    }

    //standard lib functions
    std::vector<wxString> standardLibraryFunctions = {
        "System.out.println", "System.in", "main"
    };
    for (const auto& func : standardLibraryFunctions)
    {
        size_t pos = text.find(func);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + func.length())) {
                wxTextAttr funcAttr(wxColour(128, 179, 255));
                textCtrl->SetStyle(pos, pos + func.length(), funcAttr);
                highlightRange.Mark(pos, pos + func.length());
            }
            pos = text.find(func, pos + 1);
        }
    }

    //keywords
    std::vector<wxString> keywords = {
        "public", "private", "protected", "static", "final", "if", "else", "switch", "case", "for", "while", "do", "return", "new", "this", "super", "extends", "implements", "try", "catch", "finally", "throw", "throws"
    };
    for (const auto& keyword : keywords)
    {
        size_t pos = text.find(keyword);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + keyword.length())) {
                wxTextAttr keywordAttr(wxColour(230, 0, 230));
                textCtrl->SetStyle(pos, pos + keyword.length(), keywordAttr);
                highlightRange.Mark(pos, pos + keyword.length());
            }
            pos = text.find(keyword, pos + 1); 
        }
    }

    //acces modifiers
    std::vector<wxString> accessModifiers = {
        "public", "private", "protected"
    };
    for (const auto& am : accessModifiers)
    {
        size_t pos = text.find(am);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + am.length())) {
                wxTextAttr amAttr(wxColour(107, 107, 255));
                textCtrl->SetStyle(pos, pos + am.length(), amAttr);
                highlightRange.Mark(pos, pos + am.length());
            }
            pos = text.find(am, pos + 1);
        }
    }

    //literals
    std::vector<wxString> literals = {
        "true", "false", "null"
    };
    for (const auto& literal : literals)
    {
        size_t pos = text.find(literal);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + literal.length())) {
                wxTextAttr litAttr(*wxRED);
                textCtrl->SetStyle(pos, pos + literal.length(), litAttr);
                highlightRange.Mark(pos, pos + literal.length());
            }
            pos = text.find(literal, pos + 1);
        }
    }

    //strings
    std::vector<wxString> stringDelimiters = {
        "\"", "'"
    };
    for (const auto& delimiter : stringDelimiters)
    {
        size_t pos = text.find(delimiter);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + delimiter.length())) {
                wxTextAttr stringAttr(wxColour(255, 140, 0));
                textCtrl->SetStyle(pos, pos + delimiter.length(), stringAttr);
                highlightRange.Mark(pos, pos + delimiter.length());
            }
            pos = text.find(delimiter, pos + 1);
        }
    }

    //operators
    std::vector<wxString> operators_multi = {
        "==", "!=", "<=", ">=", "&&", "||", "++", "--"
    };
    std::vector<wxString> operators_single = {
        "+", "-", "*", "/", "=", "<", ">", 
    };
    for (const auto& op : operators_multi)
    {
        size_t pos = text.find(op);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + op.length())) {
                wxTextAttr opAttr(wxColour(255, 0, 0));
                textCtrl->SetStyle(pos, pos + op.length(), opAttr);
                highlightRange.Mark(pos, pos + op.length());
            }
            pos = text.find(op, pos + 1);
        }
    }
    for (const auto& op : operators_single)
    {
        size_t pos = text.find(op);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + op.length())) {
                wxTextAttr opAttr(wxColour(255, 0, 0));
                textCtrl->SetStyle(pos, pos + op.length(), opAttr);
                highlightRange.Mark(pos, pos + op.length());
            }
            pos = text.find(op, pos + 1);
        }
    }

    //symbols
    std::vector<wxString> symbols = {
        "{", "}", "(", ")", "[", "]", ";", ",", "."
    };
    for (const auto& sym : symbols)
    {
        size_t pos = text.find(sym);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + sym.length())) {
                wxTextAttr symAttr(wxColour(255, 102, 204));
                textCtrl->SetStyle(pos, pos + sym.length(), symAttr);
                highlightRange.Mark(pos, pos + sym.length());
            }
            pos = text.find(sym, pos + 1);
        }
    }

    // Comments
    std::vector<wxString> comments = {
        "//", "/*", "*/"
    };
    for (const auto& comment : comments)
    {
        size_t pos = text.find(comment);
        while (pos != wxString::npos) {
            size_t endPos;
            if (comment == "//") {
                endPos = text.find("\n", pos);
                if (endPos == wxString::npos) endPos = text.length();
            } else if (comment == "/*") {
                endPos = text.find("*/", pos);
                if (endPos != wxString::npos) endPos += 2;
                else endPos = text.length();
            } else {
                pos = text.find(comment, pos + 1);
                continue;
            }
            wxTextAttr commentAttr(wxColour(128, 255, 170));
            textCtrl->SetStyle(pos, endPos, commentAttr);
            highlightRange.Mark(pos, endPos);
            pos = text.find(comment, endPos);
        }
    }
}