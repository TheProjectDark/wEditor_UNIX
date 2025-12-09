#include "SyntaxHighlightCPP.h"

void SyntaxHighlightCPP::ApplyCPPHighLight(wxTextCtrl* textCtrl)
{

    wxString text = textCtrl->GetValue();

    wxTextAttr normal(*wxBLACK);
    textCtrl->SetStyle(0, text.length(), normal);

    std::vector<wxString> keywords = {
        "return", "if", "else", "while"
    };

    for (const auto& word : keywords)
    {
        size_t pos = text.find(word);
        while (pos != wxString::npos) {
            wxTextAttr kw(wxColour(128, 0, 128));
            textCtrl->SetStyle(pos, pos + word.length(), kw);
            pos = text.find(word, pos + 1);
        }
    }

    std::vector<wxString> controlStructures = {
        "for", "switch", "case", "break", "continue"
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

    std::vector<wxString> symbols = {
        "{", "}", "(", ")", "[", "]", ";", ",", "."
    };
    for (const auto& symbol : symbols)
    {
        size_t pos = text.find(symbol);
        while (pos != wxString::npos) {
            wxTextAttr symAttr(wxColour(255, 0, 0));
            textCtrl->SetStyle(pos, pos + symbol.length(), symAttr);
            pos = text.find(symbol, pos + 1);
        }
    }

    std::vector<wxString> types = {
        "int", "float", "double", "char", "void", "bool", "long", "short", "unsigned", "signed", "std::string", "std::vector", "std::map", "string", "class"
    };
    for (const auto& type : types)
    {
        size_t pos = text.find(type);
        while (pos != wxString::npos) {
            wxTextAttr typeAttr(*wxBLUE);
            textCtrl->SetStyle(pos, pos + type.length(), typeAttr);
            pos = text.find(type, pos + 1);
        }   
    }

    std::vector<wxString> literals = {
        "true", "false", "NULL"
    }; 
    for (const auto& literal : literals)
    {
        size_t pos = text.find(literal);
        while (pos != wxString::npos) {
            wxTextAttr litAttr(*wxRED);
            textCtrl->SetStyle(pos, pos + literal.length(), litAttr);
            pos = text.find(literal, pos + 1);
        }
    }

    std::vector<wxString> stringDelimiters = {
        "\"", "'"
    };
    for (const auto& delimiter : stringDelimiters)
    {
        size_t pos = text.find(delimiter);
        while (pos != wxString::npos) {
            size_t endPos = text.find(delimiter, pos + 1);
            if (endPos != wxString::npos) {
                wxTextAttr stringAttr(wxColour(255, 140, 0));
                textCtrl->SetStyle(pos, endPos + 1, stringAttr);
                pos = text.find(delimiter, endPos + 1);
            } else {
                break;
            }
        }

    }

    std::vector<wxString> operators = {
        "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "++", "--"
    };
    for (const auto& op : operators)
    {
        size_t pos = text.find(op);
        while (pos != wxString::npos) {
            wxTextAttr opAttr(wxColour(255, 0, 0));
            textCtrl->SetStyle(pos, pos + op.length(), opAttr);
            pos = text.find(op, pos + 1);
        }
    }

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
                wxTextAttr commentAttr(wxColour(0, 128, 0));
                textCtrl->SetStyle(pos, endPos, commentAttr);
                pos = text.find(comment, endPos);
            } else {
                break;
            }
        }
    }

    std::vector<wxString> standardLibraryFunctions = {
        "printf", "scanf", "cout", "cin", "endl", "std::cout", "std::cin"
    };
    for (const auto& func : standardLibraryFunctions)
    {
        size_t pos = text.find(func);
        while (pos != wxString::npos) {
            wxTextAttr funcAttr(wxColour(0, 0, 255));
            textCtrl->SetStyle(pos, pos + func.length(), funcAttr);
            pos = text.find(func, pos + 1);
        }
    }

    std::vector<wxString> accessModifiers = {
        "public", "private", "protected"
    };
    for (const auto& modifier : accessModifiers)
    {
        size_t pos = text.find(modifier);
        while (pos != wxString::npos) {
            wxTextAttr modAttr(wxColour(75, 0, 130));
            textCtrl->SetStyle(pos, pos + modifier.length(), modAttr);
            pos = text.find(modifier, pos + 1);
        }
    }

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
}
