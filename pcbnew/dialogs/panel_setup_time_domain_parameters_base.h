///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class STD_BITMAP_BUTTON;
class WX_GRID;
class WX_PANEL;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/grid.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/splitter.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PANEL_SETUP_TIME_DOMAIN_PARAMETERS_BASE
///////////////////////////////////////////////////////////////////////////////
class PANEL_SETUP_TIME_DOMAIN_PARAMETERS_BASE : public wxPanel
{
	private:

	protected:
		wxSplitterWindow* m_splitter;
		WX_PANEL* m_timeDomainParametersPane;
		wxStaticText* m_staticText3;
		WX_GRID* m_tracePropagationGrid;
		STD_BITMAP_BUTTON* m_addDelayProfileButton;
		STD_BITMAP_BUTTON* m_removeDelayProfileButton;
		WX_PANEL* m_timeDomainParametersPane1;
		wxStaticText* m_staticText31;
		WX_GRID* m_viaPropagationGrid;
		STD_BITMAP_BUTTON* m_addViaOverrideButton;
		STD_BITMAP_BUTTON* m_removeViaOverrideButton;

		// Virtual event handlers, override them in your derived class
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void OnSizeTraceParametersGrid( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnAddDelayProfileClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveDelayProfileClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddViaOverrideClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveViaOverrideClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		PANEL_SETUP_TIME_DOMAIN_PARAMETERS_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PANEL_SETUP_TIME_DOMAIN_PARAMETERS_BASE();

};

