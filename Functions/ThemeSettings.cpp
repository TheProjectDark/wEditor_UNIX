//theme for editor

#include "ThemeSettings.h"

wxColour ThemeSettings::GetBackgroundColour()
{
    return wxColour(BG_RED, BG_GREEN, BG_BLUE);
}

wxColour ThemeSettings::GetTextColour()
{
    return wxColour(TEXT_RED, TEXT_GREEN, TEXT_BLUE);
}

wxColour ThemeSettings::GetButtonBackgroundColour()
{
    return wxColour(BUTTON_BG_RED, BUTTON_BG_GREEN, BUTTON_BG_BLUE);
}

void ThemeSettings::ApplyDarkTheme(wxStyledTextCtrl* textCtrl)
{
    //set background and caret
    textCtrl->SetBackgroundColour(GetBackgroundColour());
    textCtrl->SetCaretForeground(GetTextColour());
    
    //set selection background
    textCtrl->SetSelBackground(true, wxColour(60, 60, 90));
    textCtrl->SetSelForeground(true, GetTextColour());
    
    //set font
    wxFont font(FONT_SIZE, FONT_FAMILY, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    //set default style
    textCtrl->StyleSetFont(STYLE_DEFAULT, font);
    textCtrl->StyleSetForeground(STYLE_DEFAULT, GetTextColour());
    textCtrl->StyleSetBackground(STYLE_DEFAULT, GetBackgroundColour());
    
    //set comment style
    textCtrl->StyleSetFont(STYLE_COMMENT, font);
    textCtrl->StyleSetForeground(STYLE_COMMENT, wxColour(COMMENT_RED, COMMENT_GREEN, COMMENT_BLUE));
    textCtrl->StyleSetBackground(STYLE_COMMENT, GetBackgroundColour());
    
    //set string style
    textCtrl->StyleSetFont(STYLE_STRING, font);
    textCtrl->StyleSetForeground(STYLE_STRING, wxColour(STRING_RED, STRING_GREEN, STRING_BLUE));
    textCtrl->StyleSetBackground(STYLE_STRING, GetBackgroundColour());
    
    //set keyword style
    textCtrl->StyleSetFont(STYLE_KEYWORD, font);
    textCtrl->StyleSetForeground(STYLE_KEYWORD, wxColour(KEYWORD_RED, KEYWORD_GREEN, KEYWORD_BLUE));
    textCtrl->StyleSetBackground(STYLE_KEYWORD, GetBackgroundColour());
    textCtrl->StyleSetBold(STYLE_KEYWORD, true);
    
    //set preprocessor style
    textCtrl->StyleSetFont(STYLE_PREPROCESSOR, font);
    textCtrl->StyleSetForeground(STYLE_PREPROCESSOR, wxColour(PREPROCESSOR_RED, PREPROCESSOR_GREEN, PREPROCESSOR_BLUE));
    textCtrl->StyleSetBackground(STYLE_PREPROCESSOR, GetBackgroundColour());
    
    //set namespace style
    textCtrl->StyleSetFont(STYLE_NAMESPACE, font);
    textCtrl->StyleSetForeground(STYLE_NAMESPACE, wxColour(NAMESPACE_RED, NAMESPACE_GREEN, NAMESPACE_BLUE));
    textCtrl->StyleSetBackground(STYLE_NAMESPACE, GetBackgroundColour());
    
    //set number style
    textCtrl->StyleSetFont(STYLE_NUMBER, font);
    textCtrl->StyleSetForeground(STYLE_NUMBER, wxColour(NUMBER_RED, NUMBER_GREEN, NUMBER_BLUE));
    textCtrl->StyleSetBackground(STYLE_NUMBER, GetBackgroundColour());
    
    //set operator style
    textCtrl->StyleSetFont(STYLE_OPERATOR, font);
    textCtrl->StyleSetForeground(STYLE_OPERATOR, wxColour(OPERATOR_RED, OPERATOR_GREEN, OPERATOR_BLUE));
    textCtrl->StyleSetBackground(STYLE_OPERATOR, GetBackgroundColour());
    
    //set function style
    textCtrl->StyleSetFont(STYLE_FUNCTION, font);
    textCtrl->StyleSetForeground(STYLE_FUNCTION, wxColour(FUNCTION_RED, FUNCTION_GREEN, FUNCTION_BLUE));
    textCtrl->StyleSetBackground(STYLE_FUNCTION, GetBackgroundColour());
    
    //remove line numbers
    textCtrl->SetMarginWidth(0, 0);
    
    //set margin background
    textCtrl->SetMarginBackground(0, GetBackgroundColour());
    textCtrl->SetMarginBackground(1, GetBackgroundColour());
    textCtrl->SetMarginBackground(2, GetBackgroundColour());
    textCtrl->SetFoldMarginColour(true, GetBackgroundColour());
    textCtrl->SetFoldMarginHiColour(true, GetBackgroundColour());

    //hide whitespace and eol markers
    textCtrl->SetViewWhiteSpace(wxSTC_WS_INVISIBLE);
    textCtrl->SetViewEOL(false);

    //disable caret line and two-phase draw
    textCtrl->SetCaretLineVisible(false);
    textCtrl->SetTwoPhaseDraw(false);

    //enable wrapping
    textCtrl->SetWrapMode(wxSTC_WRAP_WORD);
}
