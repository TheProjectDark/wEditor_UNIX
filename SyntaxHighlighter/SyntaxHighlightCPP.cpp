/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlightCPP.h"

void SyntaxHighlightCPP::ApplyHighlight(wxTextCtrl* textCtrl)
{

    wxString text = textCtrl->GetValue();
    highlightRange.occupiedRanges.clear();

    wxTextAttr normal(*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    // First pass: mark strings and comments (highest priority)
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

    // Strings
    std::vector<wxString> stringDelimiters = {
        "\"", "'"
    };
    for (const auto& delimiter : stringDelimiters)
    {
        size_t pos = text.find(delimiter);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + 1)) {
                size_t endPos = text.find(delimiter, pos + 1);
                if (endPos != wxString::npos) {
                    wxTextAttr stringAttr(wxColour(255, 140, 0));
                    textCtrl->SetStyle(pos, endPos + 1, stringAttr);
                    highlightRange.Mark(pos, endPos + 1);
                    pos = text.find(delimiter, endPos + 1);
                } else {
                    break;
                }
            } else {
                pos = text.find(delimiter, pos + 1);
            }
        }
    }

    // Second pass: highlight keywords, types, etc
    //important shi like includes and stuff
    std::vector<wxString> preprocessorDirectives = {
        "#include", "#define", "#ifdef", "#ifndef", "#endif", "#pragma"
    };
    for (const auto& directive : preprocessorDirectives)
    {
        size_t pos = text.find(directive);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + directive.length())) {
                wxTextAttr preprocAttr(wxColour(0, 128, 128));
                textCtrl->SetStyle(pos, pos + directive.length(), preprocAttr);
                highlightRange.Mark(pos, pos + directive.length());
            }
            pos = text.find(directive, pos + 1);
        }
    }

    //also important shi like namespaces
    std::vector<wxString> namespaces = {
        "std", "namespace"
    };
    for (const auto& ns : namespaces)
    {
        size_t pos = text.find(ns);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + ns.length())) {
                wxTextAttr nsAttr(wxColour(0, 100, 0));
                textCtrl->SetStyle(pos, pos + ns.length(), nsAttr);
                highlightRange.Mark(pos, pos + ns.length());
            }
            pos = text.find(ns, pos + 1);
        }
    }

    //types
    std::vector<wxString> types = {
        "int", "float", "double", "char", "void", "bool", "long", "short", "unsigned", "signed", "std::string", "std::vector", "std::map", "string", "class"
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
        "printf", "scanf", "cout", "cin", "endl", "std::cout", "std::cin"
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

    //some keywords
    std::vector<wxString> keywords = {
        "return", "if", "else", "while", "override", "virtual", "const", "static", "new", "delete", "this"
    };
    for (const auto& word : keywords)
    {
        size_t pos = text.find(word);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + word.length())) {
                wxTextAttr kw(wxColour(230, 0, 230));
                textCtrl->SetStyle(pos, pos + word.length(), kw);
                highlightRange.Mark(pos, pos + word.length());
            }
            pos = text.find(word, pos + 1);
        }
    }

    //control structures
    std::vector<wxString> controlStructures = {
        "for", "switch", "case", "break", "continue"
    };
    for (const auto& cs : controlStructures)
    {
        size_t pos = text.find(cs);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + cs.length())) {
                wxTextAttr csAttr(wxColour(255, 165, 0));
                textCtrl->SetStyle(pos, pos + cs.length(), csAttr);
                highlightRange.Mark(pos, pos + cs.length());
            }
            pos = text.find(cs, pos + 1);
        }
    }

    //access modifiers
    std::vector<wxString> accessModifiers = {
        "public", "private", "protected"
    };
    for (const auto& modifier : accessModifiers)
    {
        size_t pos = text.find(modifier);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + modifier.length())) {
                wxTextAttr modAttr(wxColour(107, 107, 255));
                textCtrl->SetStyle(pos, pos + modifier.length(), modAttr);
                highlightRange.Mark(pos, pos + modifier.length());
            }
            pos = text.find(modifier, pos + 1);
        }
    }

    //literals
    std::vector<wxString> literals = {
        "true", "false", "NULL"
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
    for (const auto& symbol : symbols)
    {
        size_t pos = text.find(symbol);
        while (pos != wxString::npos) {
            if (!highlightRange.IsOccupied(pos, pos + symbol.length())) {
                wxTextAttr symAttr(wxColour(255, 102, 204));
                textCtrl->SetStyle(pos, pos + symbol.length(), symAttr);
                highlightRange.Mark(pos, pos + symbol.length());
            }
            pos = text.find(symbol, pos + 1);
        }
    }
}