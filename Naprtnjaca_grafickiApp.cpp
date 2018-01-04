/***************************************************************
 * Name:      Naprtnjaca_grafickiApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Elvis Popović (elvpopovi@foi.hr)
 * Created:   2018-01-03
 * Copyright: Elvis Popović ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "Naprtnjaca_grafickiApp.h"
#include "Naprtnjaca_grafickiMain.h"

IMPLEMENT_APP(Naprtnjaca_grafickiApp);

bool Naprtnjaca_grafickiApp::OnInit()
{

    Naprtnjaca_grafickiFrame* frame = new Naprtnjaca_grafickiFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
