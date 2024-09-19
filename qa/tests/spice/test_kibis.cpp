/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2024 KiCad Developers, see AUTHORS.TXT for contributors.
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

#include <qa_utils/wx_utils/unit_test_utils.h>

#include <sim/kibis/kibis.h>



BOOST_AUTO_TEST_SUITE( Kibis )


BOOST_AUTO_TEST_CASE( Null )
{
    KIBIS kibis;

    BOOST_TEST( !kibis.m_valid );

    // IBIS_ANY interface
    // If this isn't null, it's uninited and access will crash
    BOOST_REQUIRE( !kibis.m_reporter );

    // Doesn't crash (also doesn't do anything)
    kibis.Report( "Dummy", RPT_SEVERITY_INFO );
}

BOOST_AUTO_TEST_SUITE_END()