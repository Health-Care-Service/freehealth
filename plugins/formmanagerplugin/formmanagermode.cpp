/***************************************************************************
 *   FreeMedicalForms                                                      *
 *   (C) 2008-2010 by Eric MAEKER, MD                                     **
 *   eric.maeker@free.fr                                                   *
 *   All rights reserved.                                                  *
 *                                                                         *
 *   This program is a free and open source software.                      *
 *   It is released under the terms of the new BSD License.                *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *   - Redistributions of source code must retain the above copyright      *
 *   notice, this list of conditions and the following disclaimer.         *
 *   - Redistributions in binary form must reproduce the above copyright   *
 *   notice, this list of conditions and the following disclaimer in the   *
 *   documentation and/or other materials provided with the distribution.  *
 *   - Neither the name of the FreeMedForms' organization nor the names of *
 *   its contributors may be used to endorse or promote products derived   *
 *   from this software without specific prior written permission.         *
 *                                                                         *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS     *
 *   FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE        *
 *   COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,  *
 *   INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,  *
 *   BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;      *
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER      *
 *   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT    *
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN     *
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
 *   POSSIBILITY OF SUCH DAMAGE.                                           *
 ***************************************************************************/
#include "formmanagermode.h"

#include <coreplugin/icore.h>
//#include <coreplugin/isettings.h>
#include <coreplugin/itheme.h>
#include <coreplugin/constants.h>

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

using namespace Form;
using namespace Internal;

static inline Core::ITheme *theme()  { return Core::ICore::instance()->theme(); }


FormManagerMode::FormManagerMode(QObject *parent) :
        Core::BaseMode(parent)
{
    setName(tr("Patients Files"));
    setIcon(theme()->icon(Core::Constants::ICONPATIENTFILES, Core::ITheme::BigIcon));
    setPriority(Core::Constants::P_MODE_PATIENT_FILE);
    setUniqueModeName(Core::Constants::MODE_PATIENT_FILE);
//    const QList<int> &context;
//    setContext();
    w = new QWidget;
    QGridLayout *lay = new QGridLayout(w);
    QLabel *l = new QLabel("I'm alive", w);
    lay->addWidget(l);
    setWidget(w);
}

FormManagerMode::~FormManagerMode()
{
//    delete w;
}


