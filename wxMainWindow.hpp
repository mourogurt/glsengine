#include <iostream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

using std::cerr;
using std::cout;
using std::endl;

class EngApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MFrame : public wxFrame
{
public:
	MFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};

enum
{
	ID_Hello = 1
};

