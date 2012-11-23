/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2012 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
 *  All rights reserved.                                                   *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program (COPYING.FREEMEDFORMS file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *   Main developers : Eric Maeker
 *   Contributors :                                                        *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#include "datapackquery.h"

#include <QFileInfo>

namespace DataPackPlugin {

DataPackQuery::DataPackQuery(const DataPackQuery &copy)
{
    _zipContentFile = copy._zipContentFile;
    _absPathDescription = copy._absPathDescription;
    _absPathContentFile = copy._absPathContentFile;
}

DataPackQuery &DataPackQuery::operator=(const DataPackQuery &copy)
{
    _zipContentFile = copy._zipContentFile;
    _absPathDescription = copy._absPathDescription;
    _absPathContentFile = copy._absPathContentFile;
    return *this;
}

/**
 * Check the validity of the object:
 * - Absolute file path must be defined
 * - files must exists
 */
bool DataPackQuery::isValid() const
{
    if (_absPathDescription.isEmpty() || _absPathContentFile.isEmpty())
        return false;
    if (!QFileInfo(_absPathDescription).exists() || !QFileInfo(_absPathContentFile).exists())
        return false;
    return true;
}

/** Check the equality of two objects */
bool DataPackQuery::operator==(const DataPackQuery &query) const
{
    return (_zipContentFile==query._zipContentFile) &&
            (_absPathDescription==query._absPathDescription) &&
            (_absPathContentFile==query._absPathContentFile);
}

} // namespace DataPackPlugin