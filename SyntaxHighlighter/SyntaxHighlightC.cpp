/*
 * wEditor
 * Copyright (C) 2026 TheProjectDark
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "SyntaxHighlightC.h"

void SyntaxHighlightC::ApplyHighlight(wxTextCtrl* textCtrl)
{

    wxString text = textCtrl->GetValue();
    highlightRange.occupiedRanges.clear();

    wxTextAttr normal(*wxWHITE);
    textCtrl->SetStyle(0, text.length(), normal);

    //important shi like includes and stuff
    std::vector<wxString> preprocessorDirectives = {
        "#include", "#define", "#ifdef", "#ifndef", "#endif", "#pragma"
    };
    for (const auto& directive : preprocessorDirectives)
    {
        size_t pos = text.find(directive);
        while (pos != wxString::npos) {
            wxTextAttr preprocAttr(wxColour(0, 128, 128));
            textCtrl->SetStyle(pos, pos + directive.length(), preprocAttr);
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
            wxTextAttr nsAttr(wxColour(0, 100, 0));
            textCtrl->SetStyle(pos, pos + ns.length(), nsAttr);
            pos = text.find(ns, pos + 1);
        }
    }

    //highlighting for functions, methods and procedures
    std::vector<wxString> controlStatements = {
        "if", "while", "for", "switch", "catch"
    };
    size_t pos = text.find("(");
    while (pos != wxString::npos) {
        if (!highlightRange.IsOccupied(pos, pos + 1)) {
            //Check if this is a control statement
            bool isControlStatement = false;
            for (const auto& stmt : controlStatements) {
                size_t checkPos = pos;
                //Skip backwards over whitespace
                while (checkPos > 0 && (text[checkPos - 1] == ' ' || text[checkPos - 1] == '\t')) {
                    checkPos--;
                }
                //Check if the keyword is there
                if (checkPos >= stmt.length() && 
                    text.substr(checkPos - stmt.length(), stmt.length()) == stmt &&
                    (checkPos == stmt.length() || !isalnum(text[checkPos - stmt.length() - 1]))) {
                    isControlStatement = true;
                    break;
                }
            }
            
            if (!isControlStatement) {
                //Finding the start of the functions name
                size_t nameEnd = pos;
                size_t nameStart = pos;
                
                //Move backwards to find the start of identifier
                while (nameStart > 0) {
                    char ch = text[nameStart - 1];
                    if (isalnum(ch) || ch == '_' || ch == ':') {
                        nameStart--;
                    } else {
                        break;
                    }
                }
                
                //Only highlight if we found a valid name
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
        "int", "float", "double", "char", "void", "bool", "long", "short", "unsigned", "signed", "string"
    };
    for (const auto& type : types)
    {
        size_t pos = text.find(type);
        while (pos != wxString::npos) {
            wxTextAttr typeAttr(wxColour(51, 153, 255));
            textCtrl->SetStyle(pos, pos + type.length(), typeAttr);
            pos = text.find(type, pos + 1);
        }
    }

    //standard lib functions
    std::vector<wxString> standardLibraryFunctions = {
        "printf", "scanf", "endl", 
    };
    for (const auto& func : standardLibraryFunctions)
    {
        size_t pos = text.find(func);
        while (pos != wxString::npos) {
            wxTextAttr funcAttr(wxColour(128, 179, 255));
            textCtrl->SetStyle(pos, pos + func.length(), funcAttr);
            pos = text.find(func, pos + 1);
        }
    }

    //some keywords
    std::vector<wxString> keywords = {
        "return", "if", "else", "while", "override", "virtual", "const", "static", "new", "delete", "this"
    };
    for (const auto& word: keywords)
    {
        size_t pos = text.find(word);
        while (pos != wxString::npos) {
            wxTextAttr keywordsAttr(wxColour(230, 0, 230));
            textCtrl->SetStyle(pos, pos + word.length(), keywordsAttr);
            pos = text.find(word, pos + 1);
        }
    }

    //control structures
    std::vector<wxString> controlStructures = {
        "for", "while", "do", "switch", "case", "break"
    };
    for (const auto& cs : controlStructures)
    {
        size_t pos = text.find(cs);
        while (pos != wxString::npos) {
            wxTextAttr csAttr(wxColour(255, 165, 0));
            textCtrl->SetStyle(pos, pos + cs.length(), csAttr);
            pos = text.find(cs, pos + 1);
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
            wxTextAttr amAttr(wxColour(107, 107, 255));
            textCtrl->SetStyle(pos, pos + am.length(), amAttr);
            pos = text.find(am, pos + 1);
        }
    }

    //literals
    std::vector<wxString> literals = {
        "true", "false", "NULL"
    };
    for (const auto& literal: literals)
    {
        size_t pos = text.find(literal);
        while (pos != wxString::npos) {
            wxTextAttr litAttr(*wxRED);
            textCtrl->SetStyle(pos, pos + literal.length(), litAttr);
            pos = text.find(literal, pos + 1);
        }
    }

    //strings
    std::vector<wxString> stringDelimiters = {
        "\"", "'"
    };
    for (const auto& delimiter : stringDelimiters)
    {        size_t pos = text.find(delimiter);
        while (pos != wxString::npos) {
            size_t endPos = text.find(delimiter, pos + 1);
            if (endPos != wxString::npos) {
                wxTextAttr strAttr(wxColour(255, 140, 0));
                textCtrl->SetStyle(pos, endPos + 1, strAttr);
                pos = text.find(delimiter, endPos + 1);
            } else {
                break;
            }
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
            wxTextAttr opAttr(wxColour(255, 0, 0));
            textCtrl->SetStyle(pos, pos + op.length(), opAttr);
            pos = text.find(op, pos + 1);
        }
    }
    for (const auto& op : operators_single)
    {
        size_t pos = text.find(op);
        while (pos != wxString::npos) {
            wxTextAttr opAttr(wxColour(255, 0, 0));
            textCtrl->SetStyle(pos, pos + op.length(), opAttr);
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
            wxTextAttr symAttr(wxColour(255, 102, 204));
            textCtrl->SetStyle(pos, pos + symbol.length(), symAttr);
            pos = text.find(symbol, pos + 1);
        }
    }

    //comms
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
            } else if (comment == "/*") {
                endPos = text.find("*/", pos) + 2;
            } else {
                pos = text.find(comment, pos + 1);
                continue;
            }
            if (endPos != wxString::npos) {
                wxTextAttr commentAttr(wxColour(128, 255, 170));
                textCtrl->SetStyle(pos, endPos, commentAttr);
                pos = text.find(comment, endPos);
            } else {
                break;
            }
        }
    }
}