/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2010 SoftPLC Corporation, Dick Hollenbeck <dick@softplc.com>
 * Copyright The KiCad Developers, see AUTHORS.TXT for contributors.
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

#include "template_fieldnames.h"

#include <mutex>

#include <template_fieldnames_lexer.h>
#include <string_utils.h>

using namespace TFIELD_T;

// N.B. Do not change these values without transitioning the file format
#define REFERENCE_CANONICAL "Reference"
#define VALUE_CANONICAL "Value"
#define FOOTPRINT_CANONICAL "Footprint"
#define DATASHEET_CANONICAL "Datasheet"
#define DESCRIPTION_CANONICAL "Description"

// N.B. Do not change these values without transitioning the file format
#define SHEET_NAME_CANONICAL "Sheetname"
#define SHEET_FILE_CANONICAL "Sheetfile"
#define USER_FIELD_CANONICAL "Field%d"

static wxString s_CanonicalReference( REFERENCE_CANONICAL );
static wxString s_CanonicalValue( VALUE_CANONICAL );
static wxString s_CanonicalFootprint( FOOTPRINT_CANONICAL );
static wxString s_CanonicalDatasheet( DATASHEET_CANONICAL );
static wxString s_CanonicalDescription( DESCRIPTION_CANONICAL );
static wxString s_CanonicalSheetName( SHEET_NAME_CANONICAL );
static wxString s_CanonicalSheetFile( SHEET_FILE_CANONICAL );


wxString GetDefaultFieldName( int aFieldNdx, bool aTranslateForHI, KICAD_T aParentType )
{
    int mandatoryCount = 0;

    if( aParentType == SCH_SYMBOL_T )
        mandatoryCount = SYMBOL_MANDATORY_FIELDS;
    else if( aParentType == SCH_SHEET_T )
        mandatoryCount = SHEET_MANDATORY_FIELDS;
    else if( aParentType == PCB_FOOTPRINT_T )
        mandatoryCount = FP_MANDATORY_FIELDS;
    else
        wxFAIL_MSG( "Unsupported field parentType" );

    if( !aTranslateForHI )
    {
        if( aFieldNdx >= mandatoryCount )
            return wxString::Format( wxS( USER_FIELD_CANONICAL ), aFieldNdx );

        if( aParentType == SCH_SHEET_T )
        {
            switch( aFieldNdx )
            {
            case  SHEETNAME:     return s_CanonicalSheetName;
            case  SHEETFILENAME: return s_CanonicalSheetFile;
            }
        }

        switch( aFieldNdx )
        {
        case REFERENCE_FIELD:   return s_CanonicalReference;   // The symbol reference, R1, C1, etc.
        case VALUE_FIELD:       return s_CanonicalValue;       // The symbol value
        case FOOTPRINT_FIELD:   return s_CanonicalFootprint;   // The footprint for use with Pcbnew
        case DATASHEET_FIELD:   return s_CanonicalDatasheet;   // Link to a datasheet for symbol
        case DESCRIPTION_FIELD: return s_CanonicalDescription; // The symbol description
        }
    }
    else
    {
        if( aFieldNdx >= mandatoryCount )
            return wxString::Format( _( USER_FIELD_CANONICAL ), aFieldNdx );

        if( aParentType == SCH_FIELD_T )
        {
            switch( aFieldNdx )
            {
            case  SHEETNAME:     return _( SHEET_NAME_CANONICAL );
            case  SHEETFILENAME: return _( SHEET_FILE_CANONICAL );
            }
        }

        switch( aFieldNdx )
        {
        case REFERENCE_FIELD:   return _( REFERENCE_CANONICAL );   // The symbol reference, R1, C1, etc.
        case VALUE_FIELD:       return _( VALUE_CANONICAL );       // The symbol value
        case FOOTPRINT_FIELD:   return _( FOOTPRINT_CANONICAL );   // The footprint for use with Pcbnew
        case DATASHEET_FIELD:   return _( DATASHEET_CANONICAL );   // Link to a datasheet for symbol
        case DESCRIPTION_FIELD: return _( DESCRIPTION_CANONICAL ); // The symbol description
        }
    }

    return wxEmptyString;   // Shouldn't be possible to get here....
}


void TEMPLATE_FIELDNAME::Format( OUTPUTFORMATTER* out ) const
{
    out->Print( "(field (name %s)",  out->Quotew( m_Name ).c_str() );

    if( m_Visible )
        out->Print( " visible" );

    if( m_URL )
        out->Print( " url" );

    out->Print( ")" );
}


void TEMPLATE_FIELDNAME::Parse( TEMPLATE_FIELDNAMES_LEXER* in )
{
    T    tok;

    in->NeedLEFT();     // begin (name ...)

    if( ( tok = in->NextTok() ) != T_name )
        in->Expecting( T_name );

    in->NeedSYMBOLorNUMBER();

    m_Name = From_UTF8( in->CurText() );

    in->NeedRIGHT();    // end (name ...)

    while( (tok = in->NextTok() ) != T_RIGHT && tok != T_EOF )
    {
        // "visible" has no '(' prefix, "value" does, so T_LEFT is optional.
        if( tok == T_LEFT )
            tok = in->NextTok();

        switch( tok )
        {
        case T_value:
            // older format; silently skip
            in->NeedSYMBOLorNUMBER();
            in->NeedRIGHT();
            break;

        case T_visible:
            m_Visible = true;
            break;

        case T_url:
            m_URL = true;
            break;

        default:
            in->Expecting( "value|url|visible" );
            break;
        }
    }
}


void TEMPLATES::Format( OUTPUTFORMATTER* out, bool aGlobal ) const
{
    // We'll keep this general, and include the \n, even though the only known
    // use at this time will not want the newlines or the indentation.
    out->Print( "(templatefields" );

    const TEMPLATE_FIELDNAMES& source = aGlobal ? m_globals : m_project;

    for( const TEMPLATE_FIELDNAME& temp : source )
    {
        if( !temp.m_Name.IsEmpty() )
            temp.Format( out );
    }

    out->Print( ")" );
}


void TEMPLATES::parse( TEMPLATE_FIELDNAMES_LEXER* in, bool aGlobal )
{
    T  tok;

    while( ( tok = in->NextTok() ) != T_RIGHT && tok != T_EOF )
    {
        if( tok == T_LEFT )
            tok = in->NextTok();

        switch( tok )
        {
        case T_templatefields:  // a token indicating class TEMPLATES.

            // Be flexible regarding the starting point of the TEMPLATE_FIELDNAMES_LEXER
            // stream.  Caller may not have read the first two tokens out of the
            // stream: T_LEFT and T_templatefields, so ignore them if seen here.
            break;

        case T_field:
            {
                // instantiate on stack, so if exception is thrown,
                // destructor runs
                TEMPLATE_FIELDNAME  field;

                field.Parse( in );

                // add the field
                if( !field.m_Name.IsEmpty() )
                    AddTemplateFieldName( field, aGlobal );
            }
            break;

        default:
            in->Unexpected( in->CurText() );
            break;
        }
    }
}


/**
 * Flatten project and global templates into a single list.  (Project templates take
 * precedence.)
 */
void TEMPLATES::resolveTemplates()
{
    m_resolved = m_project;

    // Note: order N^2 algorithm.  Would need changing if fieldname template sets ever
    // get large.

    for( const TEMPLATE_FIELDNAME& global : m_globals )
    {
        bool overriddenInProject = false;

        for( const TEMPLATE_FIELDNAME& project : m_project )
        {
            if( global.m_Name == project.m_Name )
            {
                overriddenInProject = true;
                break;
            }
        }

        if( !overriddenInProject )
            m_resolved.push_back( global );
    }

    m_resolvedDirty = false;
}


void TEMPLATES::AddTemplateFieldName( const TEMPLATE_FIELDNAME& aFieldName, bool aGlobal )
{
    // Ensure that the template fieldname does not match a fixed fieldname.
    // We use SCH_SYMBOL_T here as it contains a superset of SCH_SYMBOL_T's and PCB_FOOTPRINT_T's
    // field names.
    for( int i = 0; i < SYMBOL_MANDATORY_FIELDS; ++i )
    {
        if( GetCanonicalFieldName( i, SCH_SYMBOL_T ) == aFieldName.m_Name )
            return;
    }

    TEMPLATE_FIELDNAMES& target = aGlobal ? m_globals : m_project;

    // ensure uniqueness, overwrite any template fieldname by the same name.
    for( TEMPLATE_FIELDNAME& temp : target )
    {
        if( temp.m_Name == aFieldName.m_Name )
        {
            temp = aFieldName;
            m_resolvedDirty = true;
            return;
        }
    }

    // the name is legal and not previously added to the config container, append
    // it and return its index within the container.
    target.push_back( aFieldName );
    m_resolvedDirty = true;
}


void TEMPLATES::AddTemplateFieldNames( const wxString& aSerializedFieldNames )
{
    TEMPLATE_FIELDNAMES_LEXER field_lexer( TO_UTF8( aSerializedFieldNames ) );

    try
    {
        parse( &field_lexer, true );
    }
    catch( const IO_ERROR& )
    {
    }
}


void TEMPLATES::DeleteAllFieldNameTemplates( bool aGlobal )
{
    if( aGlobal )
    {
        m_globals.clear();
        m_resolved = m_project;
    }
    else
    {
        m_project.clear();
        m_resolved = m_globals;
    }

    m_resolvedDirty = false;
}


const TEMPLATE_FIELDNAMES& TEMPLATES::GetTemplateFieldNames()
{
    if( m_resolvedDirty )
        resolveTemplates();

    return m_resolved;
}


const TEMPLATE_FIELDNAMES& TEMPLATES::GetTemplateFieldNames( bool aGlobal )
{
    if( aGlobal )
        return m_globals;
    else
        return m_project;
}


const TEMPLATE_FIELDNAME* TEMPLATES::GetFieldName( const wxString& aName )
{
    if( m_resolvedDirty )
        resolveTemplates();

    for( const TEMPLATE_FIELDNAME& field : m_resolved )
    {
        if( field.m_Name == aName )
            return &field;
    }

    return nullptr;
}

