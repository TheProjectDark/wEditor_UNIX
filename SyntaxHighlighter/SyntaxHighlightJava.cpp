#include "SyntaxHighlightJava.h"

void SyntaxHighlightJava::ApplyHighlight(wxTextCtrl* textCtrl)
{
    wxString text = textCtrl->GetValue();
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
            wxTextAttr importAttr(wxColour(0, 128, 128));
            textCtrl->SetStyle(pos, pos + imp.length(), importAttr);
            pos = text.find(imp, pos + 1);
        }
    }

    //types
    std::vector<wxString> types = {
        "int", "float", "double", "char", "void", "boolean", "long", "short", "byte", "String", "class", "interface"
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
        "System.out.println", "System.in", "main"
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

    //keywords
    std::vector<wxString> keywords = {
        "public", "private", "protected", "static", "final", "if", "else", "switch", "case", "for", "while", "do", "return", "new", "this", "super", "extends", "implements", "try", "catch", "finally", "throw", "throws"
    };
    for (const auto& keyword : keywords)
    {
        size_t pos = text.find(keyword);
        while (pos != wxString::npos) {
            wxTextAttr keywordAttr(wxColour(230, 0, 230));
            textCtrl->SetStyle(pos, pos + keyword.length(), keywordAttr);
            pos = text.find(keyword, pos + 1); 
        }
    }
}