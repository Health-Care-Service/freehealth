/***************************************************************************
 *  The FreeMedForms project is a set of free, open source medical         *
 *  applications.                                                          *
 *  (C) 2008-2016 by Eric MAEKER, MD (France) <eric.maeker@gmail.com>      *
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
 *  along with this program (COPYING file).                   *
 *  If not, see <http://www.gnu.org/licenses/>.                            *
 ***************************************************************************/
/***************************************************************************
 *   Main developers : Eric MAEKER
 *  Contributors:                                                          *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 *       NAME <MAIL@ADDRESS.COM>                                           *
 ***************************************************************************/
#ifndef PATIENTS_INTERNAL_IDENTITYVIEWERWIDGET_H
#define PATIENTS_INTERNAL_IDENTITYVIEWERWIDGET_H

#include <QWidget>
QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/**
 * \file identityviewerwidget.h
 * \author Eric MAEKER
 * \version 0.8.0
 * \date 12 Sept 2012
*/
namespace Patients {
class PatientModel;

namespace Internal {
class IdentityViewerWidgetPrivate;

class IdentityViewerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IdentityViewerWidget(QWidget *parent = 0);
    ~IdentityViewerWidget();

    bool initialize();

    Patients::PatientModel *patientModel() const;

//Q_SIGNALS:

private Q_SLOTS:
    void getPatientForms();

public Q_SLOTS:
    void setCurrentPatientModel(Patients::PatientModel *model);
    void setCurrentIndex(const QModelIndex &patientIndex);

private:
    //void IdentityWidget::changeEvent(QEvent *e)

private:
    Internal::IdentityViewerWidgetPrivate *d;
};

} // namespace Internal
} // namespace Patients

#endif // PATIENTS_INTERNAL_IDENTITYVIEWERWIDGET_H

