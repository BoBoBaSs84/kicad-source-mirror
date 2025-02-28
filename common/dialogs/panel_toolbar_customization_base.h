///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6-dirty)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class STD_BITMAP_BUTTON;

#include "widgets/resettable_panel.h"
#include <wx/string.h>
#include <wx/checkbox.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statline.h>
#include <wx/choice.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <widgets/split_button.h>
#include <wx/listctrl.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class PANEL_TOOLBAR_CUSTOMIZATION_BASE
///////////////////////////////////////////////////////////////////////////////
class PANEL_TOOLBAR_CUSTOMIZATION_BASE : public RESETTABLE_PANEL
{
	private:

	protected:
		wxCheckBox* m_customToolbars;
		wxStaticLine* m_staticline1;
		wxChoice* m_tbChoice;
		wxTreeCtrl* m_toolbarTree;
		STD_BITMAP_BUTTON* m_btnToolDelete;
		STD_BITMAP_BUTTON* m_btnToolMoveUp;
		STD_BITMAP_BUTTON* m_btnToolMoveDown;
		SPLIT_BUTTON* m_insertButton;
		STD_BITMAP_BUTTON* m_btnAddTool;
		wxListCtrl* m_actionsList;

		// Virtual event handlers, override them in your derived class
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void onCustomizeTbCb( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolMoveUp( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnToolMoveDown( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAddTextVar( wxCommandEvent& event ) { event.Skip(); }


	public:

		PANEL_TOOLBAR_CUSTOMIZATION_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

		~PANEL_TOOLBAR_CUSTOMIZATION_BASE();

};

