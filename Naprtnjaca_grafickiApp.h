/***************************************************************
 * Name:      Naprtnjaca_grafickiApp.h
 * Purpose:   Defines Application Class
 * Author:    Elvis Popović (elvpopovi@foi.hr)
 * Created:   2018-01-03
 * Copyright: Elvis Popović ()
 * License:
 **************************************************************/

#ifndef NAPRTNJACA_GRAFICKIAPP_H
#define NAPRTNJACA_GRAFICKIAPP_H

#include <wx/app.h>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

class Naprtnjaca_grafickiApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // NAPRTNJACA_GRAFICKIAPP_H
