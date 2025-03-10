/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright The KiCad Developers, see AUTHORS.TXT for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/gpl-3.0.html
 * or you may search the http://www.gnu.org website for the version 3 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "pcb_scripting_tool.h"

#include <action_plugin.h>
#include <kiface_ids.h>
#include <kiway.h>
#include <macros.h>
#include <pgm_base.h>
#include <python_scripting.h>
#include <tools/pcb_actions.h>

#include <pybind11/eval.h>

#include <Python.h>
#include <wx/string.h>
#include <launch_ext.h>

#ifdef KICAD_IPC_API
#include <api/api_plugin_manager.h>
#endif

using initfunc = PyObject* (*)(void);

SCRIPTING_TOOL::SCRIPTING_TOOL() :
        PCB_TOOL_BASE( "pcbnew.ScriptingTool" )
{}


SCRIPTING_TOOL::~SCRIPTING_TOOL()
{}


void SCRIPTING_TOOL::Reset( RESET_REASON aReason )
{
}


bool SCRIPTING_TOOL::Init()
{
    PyLOCK    lock;
    std::string pymodule( "_pcbnew" );

    if( !SCRIPTING::IsModuleLoaded( pymodule ) )
    {
        KIFACE* kiface = frame()->Kiway().KiFACE( KIWAY::FACE_PCB );
        initfunc pcbnew_init = reinterpret_cast<initfunc>( kiface->IfaceOrAddress( KIFACE_SCRIPTING_LEGACY ) );
        PyImport_AddModule( pymodule.c_str() );
        PyObject* mod = pcbnew_init();
        PyObject* sys_mod = PyImport_GetModuleDict();
        PyDict_SetItemString( sys_mod, "_pcbnew", mod );
        Py_DECREF( mod );

        // plugins will be loaded later via ReloadPlugins()
    }

    return true;
}


void SCRIPTING_TOOL::ReloadPlugins()
{
    // Reload Python plugins if they are newer than the already loaded, and load new plugins
    // Remove all action plugins so that we don't keep references to old versions
    ACTION_PLUGINS::UnloadAll();

    try
    {
        PyLOCK lock;
        callLoadPlugins();
    }
    catch( ... )
    {}
}


int SCRIPTING_TOOL::reloadPlugins( const TOOL_EVENT& aEvent )
{
    // Reload Python plugins if they are newer than the already loaded, and load new plugins
    // Remove all action plugins so that we don't keep references to old versions
    ACTION_PLUGINS::UnloadAll();

    try
    {
        PyLOCK lock;
        callLoadPlugins();
    }
    catch( ... )
    {
        return -1;
    }

#ifdef KICAD_IPC_API
    // TODO move this elsewhere when SWIG plugins are removed
    if( Pgm().GetCommonSettings()->m_Api.enable_server )
        Pgm().GetPluginManager().ReloadPlugins();
#endif

    if( !m_isFootprintEditor )
    {
        // Action plugins can be modified, therefore the plugins menu must be updated:
        frame()->ReCreateMenuBar();
        // Recreate top toolbar to add action plugin buttons
        frame()->ReCreateHToolbar();
        // Post a size event to force resizing toolbar by the AUI manager:
        frame()->PostSizeEvent();
    }

    return 0;
}


void SCRIPTING_TOOL::callLoadPlugins()
{
    // Load pcbnew inside Python and load all the user plugins and package-based plugins
    using namespace pybind11::literals;

    auto locals = pybind11::dict(
            "sys_path"_a = TO_UTF8( SCRIPTING::PyScriptingPath( SCRIPTING::PATH_TYPE::STOCK ) ),
            "user_path"_a = TO_UTF8( SCRIPTING::PyScriptingPath( SCRIPTING::PATH_TYPE::USER ) ),
            "third_party_path"_a =
                    TO_UTF8( SCRIPTING::PyPluginsPath( SCRIPTING::PATH_TYPE::THIRDPARTY ) ) );

    pybind11::exec( R"(
import sys
import pcbnew
pcbnew.LoadPlugins( sys_path, user_path, third_party_path )
    )",
                    pybind11::globals(), locals );
}


void SCRIPTING_TOOL::ShowPluginFolder()
{
    wxString pluginpath( SCRIPTING::PyPluginsPath( SCRIPTING::PATH_TYPE::USER ) );
    LaunchExternal( pluginpath );
}


int SCRIPTING_TOOL::showPluginFolder( const TOOL_EVENT& aEvent )
{
    ShowPluginFolder();
    return 0;
}


void SCRIPTING_TOOL::setTransitions()
{
    Go( &SCRIPTING_TOOL::reloadPlugins,     ACTIONS::pluginsReload.MakeEvent() );
    Go( &SCRIPTING_TOOL::showPluginFolder,  PCB_ACTIONS::pluginsShowFolder.MakeEvent() );
}
