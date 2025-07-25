/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright The KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#pragma once

#include <map>

#include <wx/event.h>
#include <wx/window.h>

class wxListBox;


// Declare LISTBOX_TRICKS events
wxDECLARE_EVENT( EDA_EVT_LISTBOX_COPY, wxCommandEvent );
wxDECLARE_EVENT( EDA_EVT_LISTBOX_CUT, wxCommandEvent );
wxDECLARE_EVENT( EDA_EVT_LISTBOX_PASTE, wxCommandEvent );
wxDECLARE_EVENT( EDA_EVT_LISTBOX_DELETE, wxCommandEvent );
wxDECLARE_EVENT( EDA_EVT_LISTBOX_DUPLICATE, wxCommandEvent );

// The event when the tricks change something
wxDECLARE_EVENT( EDA_EVT_LISTBOX_CHANGED, wxCommandEvent );


class LISTBOX_TRICKS : public wxEvtHandler
{
public:
    LISTBOX_TRICKS( wxWindow& aWindow, wxListBox& aListBox );
    ~LISTBOX_TRICKS();

    /**
     * These are the ids for the menu.
     */
    enum MENU_ID
    {
        ID_COPY = wxID_HIGHEST + 1,
        ID_CUT,
        ID_PASTE,
        ID_DELETE,
        ID_DUPLICATE,
    };

private:
    // Custom event handlers
    void OnListBoxCopy( wxCommandEvent& aEvent );
    void OnListBoxCut( wxCommandEvent& aEvent );
    void OnListBoxPaste( wxCommandEvent& aEvent );
    void OnListBoxDelete( wxCommandEvent& aEvent );
    void OnListBoxDuplicate( wxCommandEvent& aEvent );

    // UI event handlers
    void OnListBoxRDown( wxMouseEvent& aEvent );
    void OnListBoxKeyDown( wxKeyEvent& aEvent );

    // Internals
    void listBoxCopy();
    void listBoxCut();
    void listBoxPaste();

    wxArrayString listBoxGetSelected() const;

    /**
     * Delete the selected filters.
     *
     * Returns the indexes of the deleted filters (which won't be valid anymore).
     */
    wxArrayInt listBoxDeleteSelected();

    /**
     * Duplicate the selected filters.
     */
    void listBoxDuplicateSelected();

    wxWindow&  m_parent;
    wxListBox& m_listBox;
};
