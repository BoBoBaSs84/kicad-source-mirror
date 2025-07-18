///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6a)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include "dialog_shim.h"
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/grid.h>
#include <wx/sizer.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_MULTICHANNEL_REPEAT_LAYOUT_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_MULTICHANNEL_REPEAT_LAYOUT_BASE : public DIALOG_SHIM
{
	private:

	protected:
		wxStaticText* m_staticText4;
		wxGrid* m_raGrid;
		wxStaticText* m_staticText1;
		wxStaticText* m_refRAName;
		wxStaticText* m_staticText2;
		wxChoice* m_refAnchorFp;
		wxCheckBox* m_cbCopyPlacement;
		wxCheckBox* m_cbCopyRouting;
		wxCheckBox* m_cbCopyOnlyConnectedRouting;
		wxCheckBox* m_cbCopyOtherItems;
		wxCheckBox* m_cbIncludeOffRAComponents;
		wxCheckBox* m_cbGroupItems;
		wxCheckBox* m_cbIncludeLockedComponents;
		wxStdDialogButtonSizer* m_sdbSizerStdButtons;
		wxButton* m_sdbSizerStdButtonsOK;
		wxButton* m_sdbSizerStdButtonsCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnInitDlg( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }


	public:

		DIALOG_MULTICHANNEL_REPEAT_LAYOUT_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Repeat Multichannel Layout"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );

		~DIALOG_MULTICHANNEL_REPEAT_LAYOUT_BASE();

};

