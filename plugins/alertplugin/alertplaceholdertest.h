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
 *   Main Developpers:                                                     *
 *       Eric MAEKER, <eric.maeker@gmail.com>,                             *
 *       Pierre-Marie Desombre <pm.desombre@gmail.com>                     *
 *   Contributors :                                                        *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef ALERTPLACEHOLDERTEST_H
#define ALERTPLACEHOLDERTEST_H

#include <alertplugin/ialertplaceholder.h>
#include <QWidget>

namespace Alert {
namespace Ui {
class AlertPlaceHolderTest;
}

class AlertPlaceHolderTest : public IAlertPlaceHolder
{
    Q_OBJECT
    
public:
    explicit AlertPlaceHolderTest(QWidget *parent = 0);
    ~AlertPlaceHolderTest();
    
    // identification
    QString uuid() const;

    // for UI presentation of the place holder
    QString name(const QString &lang = QString::null) const;
    QString category(const QString &lang = QString::null) const;
    QString description(const QString &lang = QString::null) const;

    // AlertItem management
    void clear();
    bool addAlert(const AlertItem &alert);
    bool removeAlert(const AlertItem &alert);
    bool highlightAlert(const AlertItem &alert);

private:
    Ui::AlertPlaceHolderTest *ui;
};

}  // namespace Alert

#endif // ALERTPLACEHOLDERTEST_H
