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

#include "dialog_shim.h"
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/srchctrl.h>
#include <wx/statline.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/splitter.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class DIALOG_LIB_FIELDS_TABLE_BASE
///////////////////////////////////////////////////////////////////////////////
class DIALOG_LIB_FIELDS_TABLE_BASE : public DIALOG_SHIM
{
	private:

	protected:
		wxSplitterWindow* m_splitterMainWindow;
		wxPanel* m_leftPanel;
		WX_GRID* m_viewControlsGrid;
		STD_BITMAP_BUTTON* m_addFieldButton;
		STD_BITMAP_BUTTON* m_renameFieldButton;
		STD_BITMAP_BUTTON* m_removeFieldButton;
		wxPanel* m_rightPanel;
		wxSearchCtrl* m_filter;
		wxStaticLine* m_staticline31;
		wxChoice* m_choiceScope;
		wxStaticLine* m_staticline311;
		wxCheckBox* m_groupSymbolsBox;
		STD_BITMAP_BUTTON* m_bRefresh;
		WX_GRID* m_grid;
		STD_BITMAP_BUTTON* m_sidebarButton;
		wxStdDialogButtonSizer* m_sdbSizer;
		wxButton* m_sdbSizerOK;
		wxButton* m_sdbSizerApply;
		wxButton* m_sdbSizerCancel;

		// Virtual event handlers, override them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnViewControlsCellChanged( wxGridEvent& event ) { event.Skip(); }
		virtual void OnSizeViewControlsGrid( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnAddField( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRenameField( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRemoveField( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFilterMouseMoved( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnFilterText( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnScope( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGroupSymbolsToggled( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRegroupSymbols( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTableValueChanged( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableCellClick( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableItemContextMenu( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableCmdCellClick( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableColSize( wxGridSizeEvent& event ) { event.Skip(); }
		virtual void OnEditorShown( wxGridEvent& event ) { event.Skip(); }
		virtual void OnTableSelectCell( wxGridEvent& event ) { event.Skip(); }
		virtual void OnSidebarToggle( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnApply( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOk( wxCommandEvent& event ) { event.Skip(); }


	public:

		DIALOG_LIB_FIELDS_TABLE_BASE( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Library Fields Table (%s)"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxRESIZE_BORDER );

		~DIALOG_LIB_FIELDS_TABLE_BASE();

};

