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
#include "baseformwidgets.h"

#include <formmanagerplugin/iformitem.h>
#include <utils/global.h>

#include <QStringList>
#include <QMessageBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QComboBox>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QStringListModel>

using namespace BaseWidgets;
//using namespace BaseWidgets::Internal;

namespace {
    enum TypeEnum {
        Type_Undefined = 0,
        Type_Form,
        Type_Radio,
        Type_Check,
        Type_Combo,
        Type_MultiCheck,
        Type_UniqueList,
        Type_MultiList,
        Type_Spin,
        Type_DoubleSpin,
        Type_ShortText,
        Type_LongText,
        Type_HelpText,
        Type_File,
        Type_Group,
        Type_Date,
        Type_Button,
        Type_MaxType
    };

    static const QStringList widgetsName =
            QStringList() << "undef" << "form" << "radio" << "check" << "combo"
            << "multicheck" << "uniquelist" << "multilist" << "spin" << "doublespin"
            << "shorttext" << "longtext" << "helptext" << "file" << "group" << "date" << "button";

    const char * const  EXTRAS_KEY              = "option";
    const char * const  EXTRAS_KEY_COLUMN       = "column";
    const char * const  EXTRAS_COMPACT_VIEW     = "compact";
    const char * const  EXTRAS_GROUP_CHECKABLE  = "checkable";
    const char * const  EXTRAS_GROUP_CHECKED    = "checked";
    const char * const  EXTRAS_ALIGN_VERTICAL   = "vertical";
    const char * const  EXTRAS_ALIGN_HORIZONTAL = "horizontal";

    const char * const  DATE_EXTRAS_KEY         = "dateformat";

    const char * const  SPIN_EXTRAS_KEY_MIN         = "min";
    const char * const  SPIN_EXTRAS_KEY_MAX         = "max";
    const char * const  SPIN_EXTRAS_KEY_STEP        = "step";

}

inline static int getNumberOfColumns(Form::FormItem *item, int defaultValue = 1)
{
    if (!item->extraDatas().value(::EXTRAS_KEY_COLUMN).isEmpty())
        return item->extraDatas().value(::EXTRAS_KEY_COLUMN).toInt();
    else
        return defaultValue;
}

inline static int isCompactView(Form::FormItem *item, bool defaultValue = false)
{
    if (item->extraDatas().value(::EXTRAS_KEY).contains(::EXTRAS_COMPACT_VIEW))
        return true;
    else
        return defaultValue;
}

inline static int isGroupCheckable(Form::FormItem *item, bool defaultValue = false)
{
    if (item->extraDatas().value(::EXTRAS_KEY).contains(::EXTRAS_GROUP_CHECKABLE))
        return true;
    else
        return defaultValue;
}

inline static int isGroupChecked(Form::FormItem *item, bool defaultValue = false)
{
    if (item->extraDatas().value(::EXTRAS_KEY).contains(::EXTRAS_GROUP_CHECKED))
        return true;
    else
        return defaultValue;
}

inline static int isRadioHorizontalAlign(Form::FormItem *item, bool defaultValue = true)
{
    if (item->extraDatas().value(::EXTRAS_KEY).contains(::EXTRAS_ALIGN_HORIZONTAL))
        return true;
    else
        return defaultValue;
}

inline static QString getDateFormat(Form::FormItem *item, const QString & defaultValue = "dd MM yyyy")
{
    if (!item->extraDatas().value(::DATE_EXTRAS_KEY).isEmpty()) {
        return item->extraDatas().value(::DATE_EXTRAS_KEY);
    }
    return defaultValue;
}


BaseWidgetsFactory::BaseWidgetsFactory(QObject *parent) :
        IFormWidgetFactory(parent)
{
}

BaseWidgetsFactory::~BaseWidgetsFactory()
{}

bool BaseWidgetsFactory::initialize(const QStringList &arguments, QString *errorString)
{
    return true;
}

bool BaseWidgetsFactory::extensionInitialized()
{
    return true;
}

bool BaseWidgetsFactory::isInitialized() const
{
    return true;
}

QStringList BaseWidgetsFactory::providedWidgets() const
{
    return ::widgetsName;
}

bool BaseWidgetsFactory::isContainer( const int idInStringList ) const
{
    return ( idInStringList == ::Type_Form ) ||
            ( idInStringList == ::Type_Group );
}

Form::IFormWidget *BaseWidgetsFactory::createWidget(const QString &name, Form::FormItem *formItem, QWidget *parent)
{
    int id = ::widgetsName.indexOf(name);
    if (id == -1)
        return 0;
    switch (id)
    {
    case ::Type_Form : return new BaseForm(formItem,parent);
    case ::Type_Group : return new BaseGroup(formItem,parent);
    case ::Type_Check : return new BaseCheck(formItem,parent);
    case ::Type_Radio : return new BaseRadio(formItem,parent);
    case ::Type_ShortText : return new BaseSimpleText(formItem,parent,true);
    case ::Type_LongText : return new BaseSimpleText(formItem,parent,false);
    case ::Type_HelpText : return new BaseHelpText(formItem,parent);
    case ::Type_MultiList : return new BaseList(formItem,parent,false);
    case ::Type_UniqueList : return new BaseList(formItem,parent,true);
    case ::Type_Combo : return new BaseCombo(formItem,parent);
    case ::Type_Date : return new BaseDate(formItem,parent);
    case ::Type_Spin : return new BaseSpin(formItem,parent);
    case ::Type_DoubleSpin : return new BaseSpin(formItem,parent,true);
    case ::Type_Button : return new BaseButton(formItem,parent);
    default: return 0;
    }
    return 0;
}



/** \todo Verify usage of clear() in all itemData() --> originalValue ? */


//--------------------------------------------------------------------------------------------------------
//-------------------------------------- BaseForm implementation ---------------------------------------
//--------------------------------------------------------------------------------------------------------
/** \class BaseForm
   \brief Creates a form
   Manages some Form::FormItem::extraDatas() (that is a QHash<QString, QString>) :
   - "col=" ; "numberOfColumns"
*/

BaseForm::BaseForm(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent), m_ContainerLayout( 0 )
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    QWidget *mainWidget = new QWidget;
    mainLayout->addWidget(mainWidget);
    mainLayout->addStretch();

    m_ContainerLayout = new QGridLayout(mainWidget);
    IFormWidget::createLabel(m_FormItem->spec()->label(), Qt::AlignCenter );
    m_Label->setFrameStyle(FormLabelFrame);
    QFont font = m_Label->font();
    font.setBold(true);
    m_Label->setFont(font);
    QSizePolicy sizePolicy = m_Label->sizePolicy();
    sizePolicy.setVerticalPolicy( QSizePolicy::Fixed );
    m_Label->setSizePolicy( sizePolicy );

    // Retrieve the number of columns for the gridlayout (lays in extraDatas() of linked FormItem)
    numberColumns = getNumberOfColumns(m_FormItem);
    if (isCompactView(m_FormItem)) {
        mainLayout->setMargin(0);
        mainLayout->setSpacing(2);
        m_ContainerLayout->setMargin(0);
        m_ContainerLayout->setSpacing(2);
    }
    m_ContainerLayout->addWidget(m_Label, 0, 0,  1, numberColumns);
    i = numberColumns;
    row = 0;
    col = 0;
}

BaseForm::~BaseForm()
{
}

void BaseForm::addWidgetToContainer(IFormWidget * widget)
{
    if (!widget)
        return;
    if (!m_ContainerLayout)
        return;
    // it is not possible to add a form inside a container
    if (widget->formItem()->spec()->pluginName() == ::widgetsName[::Type_Form])
        return;
    col = (i % numberColumns);
    row = (i / numberColumns);
    m_ContainerLayout->addWidget(widget , row, col);
    i++;
}

void BaseForm::retranslate()
{
    /** \todo iformitem --> one spec per language ? */
    //     m_Label->setText( m_FormItem->spec()->label() );
}



//--------------------------------------------------------------------------------------------------------
//-------------------------------------- BaseGroup implementation --------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseGroup::BaseGroup(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent), m_Group(0), m_ContainerLayout(0)
{
    QVBoxLayout * vblayout = new QVBoxLayout( this );
    m_Group = new QGroupBox( this );
    m_Group->setTitle(m_FormItem->spec()->label());
    vblayout->addWidget( m_Group );
    this->setLayout( vblayout );

    // Retrieve the number of columns for the gridlayout (lays in extraDatas() of linked FormItem)
    numberColumns = getNumberOfColumns(m_FormItem, 2);

    // Create the gridlayout with all the widgets
    m_ContainerLayout = new QGridLayout( m_Group );
    i = 0;
    row = 0;
    col = 0;
    if (isCompactView(m_FormItem)) {
        vblayout->setMargin(0);
        vblayout->setSpacing(2);
        m_ContainerLayout->setMargin(0);
        m_ContainerLayout->setSpacing(2);
    }

    if (isGroupCheckable(m_FormItem, false)) {
        m_Group->setCheckable( true );
        m_Group->setChecked(isGroupChecked(m_FormItem,false));
        //          connect( m_Group, SIGNAL( clicked( bool ) ),
        //                   this,    SLOT  ( updateObject( bool ) ) );
        //          connect( mfo(m_FormItem), SIGNAL( valueChanged() ),
        //                   this,     SLOT  ( updateWidget() ) );
    }
    m_Group->setLayout(m_ContainerLayout);
}

BaseGroup::~BaseGroup()
{
}

void BaseGroup::addWidgetToContainer(IFormWidget * widget)
{
    if (!widget)
        return;
    if (!m_ContainerLayout)
        return;
    // it is not possible to add a form inside a container
    if (widget->formItem()->spec()->pluginName() == ::widgetsName[::Type_Form])
        return;
    col = (i % numberColumns);
    row = (i / numberColumns);
    m_ContainerLayout->addWidget(widget , row, col);
    i++;
}

void BaseGroup::retranslate()
{
    //     m_Group->setTitle( mfo(m_FormItem)->label() );
}


//--------------------------------------------------------------------------------------------------------
//--------------------------------------------- BaseCheck ----------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseCheck::BaseCheck(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent), m_Check(0)
{
    QHBoxLayout * hb = new QHBoxLayout(this);
    // Add Buttons
    m_Check = new QCheckBox(this);
    m_Check->setObjectName("Checkbox_" + m_FormItem->uuid());
    hb->addWidget(m_Check);
    retranslate();
    // create itemdata
    m_ItemData = new BaseCheckData(formItem);
    m_ItemData->setCheckBox(m_Check);
    formItem->setItemDatas(m_ItemData);
}

BaseCheck::~BaseCheck()
{
}

void BaseCheck::retranslate()
{
    m_Check->setText(m_FormItem->spec()->label());
}

////////////////////////////////////////// ItemData /////////////////////////////////////////////
BaseCheckData::BaseCheckData(Form::FormItem *item) :
        m_FormItem(item), m_Check(0)
{}

BaseCheckData::~BaseCheckData()
{}

void BaseCheckData::setCheckBox(QCheckBox *chk)
{
    m_Check = chk;
    clear();
}

void BaseCheckData::clear()
{
    const QString &s = m_FormItem->valueReferences()->defaultValue().toString();
    m_Check->setChecked(false);

    if (s.isEmpty())
        return;

    if (s.compare("checked", Qt::CaseInsensitive)==0)
        m_Check->setChecked(true);
    else if (s.compare("unchecked", Qt::CaseInsensitive)==0)
        m_Check->setChecked(false);
    else if (s.compare("partial", Qt::CaseInsensitive)==0)
        m_Check->setCheckState(Qt::PartiallyChecked);
}

bool BaseCheckData::isModified() const
{
    return m_OriginalValue != m_Check->checkState();
}

void BaseCheckData::setData(const QVariant &data, const int role)
{
    qWarning() << "BaseCheckData::setData" << data << role;
    if (role==Qt::EditRole || role==Qt::DisplayRole) {
        if (data.canConvert(QVariant::Int))  { // Tristate
            m_Check->setCheckState(Qt::CheckState(data.toInt()));
        }
    }
}

QVariant BaseCheckData::data(const int role) const
{
    return m_Check->checkState();
}

void BaseCheckData::setStorableData(const QVariant &data)
{
    if (!data.isValid())
        return;
    Qt::CheckState state = Qt::CheckState(data.toInt());
    m_Check->setCheckState(state);
    m_OriginalValue = state;
}

QVariant BaseCheckData::storableData() const
{
    return m_Check->checkState();
}

//--------------------------------------------------------------------------------------------------------
//--------------------------------------------- BaseRadio ----------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseRadio::BaseRadio(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent)
{
    // Prepare Widget Layout and label
    QBoxLayout * hb = getBoxLayout(Label_OnLeft, m_FormItem->spec()->label(), this );

    // Add QLabel
    m_Label->setSizePolicy( QSizePolicy::Preferred , QSizePolicy::Preferred );
    hb->addWidget(m_Label);

    // Add Buttons
    QGroupBox *gb = new QGroupBox( this );
    //     gb->setFlat( true );
    //     QSizePolicy sizePolicy = gb->sizePolicy();
    //     sizePolicy.setHorizontalPolicy( QSizePolicy::Fixed );
    //     gb->setSizePolicy( sizePolicy );
    QBoxLayout *radioLayout = 0;
    if (isRadioHorizontalAlign(m_FormItem)) {
        radioLayout = new QBoxLayout( QBoxLayout::LeftToRight, gb );
    } else {
        radioLayout = new QBoxLayout( QBoxLayout::TopToBottom, gb );
    }
    radioLayout->setContentsMargins(1, 0, 1, 0);
    QRadioButton *rb = 0;
    int i = 0;

//    qWarning() << m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Possible);
//    qWarning() << m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid);

    foreach (const QString &v, m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Possible) ) {
        rb = new QRadioButton(this);
        rb->setObjectName(m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid).at(i));
        rb->setText(v);
        rb->setProperty("id", m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid).at(i));
        i++;
        radioLayout->addWidget(rb);
        m_RadioList.append(rb);
    }
    hb->addWidget(gb);

    // create the FormItemData
    BaseRadioData *data = new BaseRadioData(m_FormItem);
    data->setBaseRadio(this);
    m_FormItem->setItemDatas(data);
}

BaseRadio::~BaseRadio()
{ }

void BaseRadio::retranslate()
{
    m_Label->setText(m_FormItem->spec()->label());

    if ( m_RadioList.size() ) {
        const QStringList &list = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Possible);
        if ( list.count() != m_RadioList.count() ) {
            Utils::warningMessageBox(
                    tr("Wrong form's translations"),
                    tr("You asked to change the language of the form to %1.\n"
                       "But this an error while reading translation of %2.\n"
                       "Number of items of the translation (%3) are wrong.")
                    .arg(QLocale().name(), m_FormItem->spec()->label()).arg(list.count()));
            return;
        }
        int i = 0;
        foreach (QRadioButton *button, m_RadioList) {
            button->setText(list.at(i));
            i++;
        }
    }
}


////////////////////////////////////////// ItemData /////////////////////////////////////////////
BaseRadioData::BaseRadioData(Form::FormItem *item) :
        m_FormItem(item), m_Radio(0)
{
}

BaseRadioData::~BaseRadioData()
{}

/** \brief Set the widget to the default value \sa FormItem::FormItemValue*/
void BaseRadioData::clear()
{
    QString id = m_FormItem->valueReferences()->defaultValue().toString();
    foreach(QRadioButton *b, m_Radio->m_RadioList) {
        if (b->property("id").toString()==id) {
            b->setChecked(true);
            break;
        }
    }
}

bool BaseRadioData::isModified() const
{
    foreach(QRadioButton *but, m_Radio->m_RadioList) {
        if (but->isChecked()) {
//            qWarning() << "Radio selected" << but->property("id").toString() << "modified" << (m_OriginalValue != but->property("id").toString());
            return m_OriginalValue != but->property("id").toString();
        }
    }
    return true;
}

void BaseRadioData::setData(const QVariant &data, const int role)
{
//    qWarning() << "BaseCheckData::setData" << data << role;
//    if (role==Qt::EditRole || role==Qt::DisplayRole) {
//        if (data.canConvert(QVariant::Int))  { // Tristate
//            m_Check->setCheckState(Qt::CheckState(data.toInt()));
//        }
//    }
}

QVariant BaseRadioData::data(const int role) const
{
    return QVariant();
}

void BaseRadioData::setStorableData(const QVariant &data)
{
    // Storable data == id of the selected radio button
    if (!data.isValid())
        return;
    QString id = data.toString();
    foreach(QRadioButton *b, m_Radio->m_RadioList) {
        if (b->property("id").toString()==id) {
            b->setChecked(true);
            break;
        }
    }
    m_OriginalValue = id;
//    qWarning() << "Radio orig" << id;
}

QVariant BaseRadioData::storableData() const
{
    foreach(QRadioButton *but, m_Radio->m_RadioList) {
        if (but->isChecked())
            return but->property("id");
    }
    /** \todo return the default value ? */
    return QVariant();
}



//--------------------------------------------------------------------------------------------------------
//------------------------------------------- BaseSimpleText -------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseSimpleText::BaseSimpleText(Form::FormItem *formItem, QWidget *parent, bool shortText)
        : Form::IFormWidget(formItem,parent), m_Line(0), m_Text(0)
{
    // Prepare Widget Layout and label
    QBoxLayout * hb = getBoxLayout(Label_OnLeft, m_FormItem->spec()->label(), this);
    hb->addWidget(m_Label);

    // Add List and manage size
    if (shortText) {
        //          if (!(mfo(m_FormItem)->options() & mfObjectFundamental::LabelOnTop))
        //          {
        //               Qt::Alignment alignment = m_Label->alignment();
        //               alignment &= ~( Qt::AlignVertical_Mask );
        //               alignment |= Qt::AlignVCenter;
        //               m_Label->setAlignment( alignment );
        //          }

        m_Line = new QLineEdit( this );
        m_Line->setObjectName( "Line_" + m_FormItem->uuid());
        m_Line->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Fixed);
        //          m_Line->setInputMask( mfo(m_FormItem)->mask() );
        //          m_Line->setCursorPosition(0);
        hb->addWidget(m_Line);
    } else {
        m_Text = new QTextEdit(this);
        m_Text->setObjectName( "Text_" + m_FormItem->uuid());
        m_Text->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
        hb->addWidget(m_Text);
    }

    // Create the FormItemData
    BaseSimpleTextData *data = new BaseSimpleTextData(m_FormItem);
    data->setBaseSimpleText(this);
    m_FormItem->setItemDatas(data);
}

BaseSimpleText::~BaseSimpleText()
{
}

void BaseSimpleText::retranslate()
{
    m_Label->setText(m_FormItem->spec()->label());
}

////////////////////////////////////////// ItemData /////////////////////////////////////////////
BaseSimpleTextData::BaseSimpleTextData(Form::FormItem *item) :
        m_FormItem(item), m_Text(0)
{
}

BaseSimpleTextData::~BaseSimpleTextData()
{}

/** \brief Set the widget to the default value \sa FormItem::FormItemValue*/
void BaseSimpleTextData::clear()
{
    const QString &s = m_FormItem->valueReferences()->defaultValue().toString();
    if (m_Text->m_Line)
        m_Text->m_Line->setText(s);
    else if (m_Text->m_Text)
        m_Text->m_Text->setPlainText(s);
}

bool BaseSimpleTextData::isModified() const
{
    if (m_Text->m_Line)
        return m_OriginalValue != m_Text->m_Line->text();
    else if (m_Text->m_Text)
        return m_OriginalValue != m_Text->m_Text->toPlainText();
    return true;
}

void BaseSimpleTextData::setData(const QVariant &data, const int role)
{
}

QVariant BaseSimpleTextData::data(const int role) const
{
    return QVariant();
}

void BaseSimpleTextData::setStorableData(const QVariant &data)
{
    m_OriginalValue = data.toString();
    if (m_Text->m_Line)
        m_Text->m_Line->setText(m_OriginalValue);
    else if (m_Text->m_Text)
        m_Text->m_Text->setPlainText(m_OriginalValue);
}

QVariant BaseSimpleTextData::storableData() const
{
    if (m_Text->m_Line)
        return m_Text->m_Line->text();
    else if (m_Text->m_Text)
        return m_Text->m_Text->toPlainText();
    return QVariant();
}


//--------------------------------------------------------------------------------------------------------
//----------------------------------------- BaseHelpText -----------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseHelpText::BaseHelpText(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent)
{
    QHBoxLayout * hb = new QHBoxLayout( this );
    // Add QLabel
    createLabel(m_FormItem->spec()->label(), Qt::AlignJustify);
    // Setting objectName to hide/show via a simple option button
    m_Label->setObjectName("HelpText_" + m_FormItem->uuid());
    hb->addWidget(m_Label);
}

BaseHelpText::~BaseHelpText()
{
}

void BaseHelpText::retranslate()
{
    m_Label->setText(m_FormItem->spec()->label());
}

//--------------------------------------------------------------------------------------------------------
//----------------------------------------- BaseLists --------------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseList::BaseList(Form::FormItem *formItem, QWidget *parent, bool uniqueList)
        : Form::IFormWidget(formItem,parent), m_List( 0 )
{
    // Prepare Widget Layout and label
    QBoxLayout * hb = getBoxLayout(Label_OnLeft, m_FormItem->spec()->label(), this);
    hb->addWidget(m_Label);

    // Add List and manage size
    m_List = new QListView(this);
    m_List->setObjectName("List_" + m_FormItem->uuid());
    m_List->setUniformItemSizes(true);
    m_List->setAlternatingRowColors(true);
    m_List->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Expanding);
    if (uniqueList)
        m_List->setSelectionMode(QAbstractItemView::SingleSelection);
    else
        m_List->setSelectionMode(QAbstractItemView::MultiSelection);

    const QStringList &possibles = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Possible);
    m_Model = new QStringListModel(possibles, this);
    m_List->setModel(m_Model);

    hb->addWidget(m_List);

    // create FormItemData
    BaseListData *data = new BaseListData(m_FormItem);
    data->setBaseList(this);
    m_FormItem->setItemDatas(data);
}

BaseList::~BaseList()
{
}

void BaseList::retranslate()
{
    m_Label->setText(m_FormItem->spec()->label());
    if (m_List) {
        const QStringList &list = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Possible);
        if (list.count() != m_Model->rowCount()) {
            Utils::warningMessageBox(
                    tr("Wrong form's translations"),
                    tr("You asked to change the language of the form to %1.\n"
                       "But this an error while reading translation of %2.\n"
                       "Number of items of the translation (%3) are wrong.")
                    .arg(QLocale().name(), m_FormItem->spec()->label()).arg(list.count()));
            return;
        }
//        int i = 0;
//        for (i = 0; i < m_List->count(); i++) {
//            m_List->item(i)->setText(list[i]);
//        }
    }
}

////////////////////////////////////////// ItemData /////////////////////////////////////////////
BaseListData::BaseListData(Form::FormItem *item) :
        m_FormItem(item), m_List(0)
{
}

BaseListData::~BaseListData()
{
}

void BaseListData::setSelectedItems(const QString &s)
{
    QItemSelectionModel *selModel = m_List->m_List->selectionModel();
    selModel->clearSelection();
    if (s.isEmpty())
        return;

    const QStringList &uuids = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid);
    if (s.contains("`@`")) {
        // multilist
        foreach(const QString &i, s.split("`@`", QString::SkipEmptyParts)) {
            int row = uuids.lastIndexOf(i);
            QModelIndex idx = m_List->m_Model->index(row, 0);
            selModel->select(idx, QItemSelectionModel::Select);
        }
    } else {
        int row = uuids.lastIndexOf(s);
        QModelIndex idx = m_List->m_Model->index(row, 0);
        selModel->select(idx, QItemSelectionModel::Select);
    }
}

/** \brief Set the widget to the default value \sa FormItem::FormItemValue*/
void BaseListData::clear()
{
    setSelectedItems(m_FormItem->valueReferences()->defaultValue().toString());
}

bool BaseListData::isModified() const
{
    QStringList actual = storableData().toStringList();
    return actual != m_OriginalValue;
}

void BaseListData::setData(const QVariant &data, const int role)
{
}

QVariant BaseListData::data(const int role) const
{
    return QVariant();
}

void BaseListData::setStorableData(const QVariant &data)
{    
    setSelectedItems(data.toString());
    m_OriginalValue = data.toStringList();
    qSort(m_OriginalValue);
}

/** \brief Storable data of a List is the uuids of the selected items sorted in alphabetic order. */
QVariant BaseListData::storableData() const
{
    QItemSelectionModel *selModel = m_List->m_List->selectionModel();

    if (!selModel->hasSelection())
        return QVariant();

    QStringList selected;
    const QStringList &uuids = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid);
    foreach(const QModelIndex &idx, selModel->selectedIndexes()) {
        selected.append(uuids.at(idx.row()));
    }
    qSort(selected);
    return selected.join("`@`");
}


//--------------------------------------------------------------------------------------------------------
//----------------------------------------- BaseCombo --------------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseCombo::BaseCombo(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent), m_Combo( 0 )
{
    // Prepare Widget Layout and label
    QBoxLayout * hb = getBoxLayout(Label_OnLeft, m_FormItem->spec()->label(), this);
    hb->addWidget(m_Label);
    //     if ( !( mfo(m_FormItem)->options() & mfObjectFundamental::LabelOnTop ) )
    //     {
    //          Qt::Alignment alignment = m_Label->alignment();
    //          alignment &= ~( Qt::AlignVertical_Mask );
    //          alignment |= Qt::AlignVCenter;
    //          m_Label->setAlignment( alignment );
    //     }

    // Add List and manage size
    m_Combo = new QComboBox(this);
    m_Combo->setObjectName("Combo_" + m_FormItem->uuid());
    m_Combo->addItems(m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Possible));
    hb->addWidget(m_Combo);
    //     if ( mfo(m_FormItem)->options() & mfObjectFundamental::SizePreferred )
    //          m_Combo->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
    //     else
    //          m_Combo->setSizePolicy( QSizePolicy::Expanding , QSizePolicy::Fixed );

    // create FormItemData
    BaseComboData *data = new BaseComboData(m_FormItem);
    data->setBaseCombo(this);
    m_FormItem->setItemDatas(data);
}

BaseCombo::~BaseCombo()
{
}

void BaseCombo::retranslate()
{
    m_Label->setText(m_FormItem->spec()->label());
    if (m_Combo) {
        const QStringList &list = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Possible);
        if (list.count() != m_Combo->count()) {
            Utils::warningMessageBox(
                    tr("Wrong form's translations"),
                    tr("You asked to change the language of the form to %1.\n"
                       "But this an error while reading translation of %2.\n"
                       "Number of items of the translation (%3) are wrong.")
                    .arg(QLocale().name(), m_FormItem->spec()->label()).arg(list.count()));
            return;
        }
        // refresh combo items
        int id = m_Combo->currentIndex();
        m_Combo->clear();
        m_Combo->addItems(list);
        m_Combo->setCurrentIndex(id);
    }
}

////////////////////////////////////////// ItemData /////////////////////////////////////////////
BaseComboData::BaseComboData(Form::FormItem *item) :
        m_FormItem(item), m_Combo(0)
{
}

BaseComboData::~BaseComboData()
{
}

int BaseComboData::selectedItem(const QString &s)
{
    m_Combo->m_Combo->setCurrentIndex(-1);
    if (s.isEmpty())
        return -1;

    const QStringList &uuids = m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid);
    int row = uuids.lastIndexOf(s);
    m_Combo->m_Combo->setCurrentIndex(row);
    return row;
}

/** \brief Set the widget to the default value \sa FormItem::FormItemValue*/
void BaseComboData::clear()
{
    selectedItem(m_FormItem->valueReferences()->defaultValue().toString());
}

bool BaseComboData::isModified() const
{
    return m_OriginalValue != m_Combo->m_Combo->currentIndex();
}

void BaseComboData::setData(const QVariant &data, const int role)
{
}

QVariant BaseComboData::data(const int role) const
{
    return QVariant();
}

void BaseComboData::setStorableData(const QVariant &data)
{
    m_OriginalValue = selectedItem(data.toString());
}

QVariant BaseComboData::storableData() const
{
    int row = m_Combo->m_Combo->currentIndex();
    if (row < 0)
        return QVariant();
    return m_FormItem->valueReferences()->values(Form::FormItemValues::Value_Uuid).at(row);
}


//--------------------------------------------------------------------------------------------------------
//----------------------------------------- BaseDate ---------------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseDate::BaseDate(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent), m_Date( 0 )
{
    // Prepare Widget Layout and label
    QBoxLayout * hb = getBoxLayout(Label_OnLeft, m_FormItem->spec()->label(), this);
    hb->addWidget( m_Label );
    //     if ( !( mfo(m_FormItem)->options() & mfObjectFundamental::LabelOnTop ) )
    //     {
    //          Qt::Alignment alignment = m_Label->alignment();
    //          alignment &= ~( Qt::AlignVertical_Mask );
    //          alignment |= Qt::AlignVCenter;
    //          m_Label->setAlignment( alignment );
    //     }

    // Add Date selector and manage date format
    m_Date = new QDateTimeEdit(this);
    m_Date->setObjectName("Date_" + m_FormItem->uuid());
    m_Date->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Fixed);
    m_Date->setDisplayFormat(getDateFormat(m_FormItem));
    m_Date->setCalendarPopup(true);
    hb->addWidget(m_Date);

    // Initialize mfo and dateedit with mfo options
    //     const QStringList &options = mfo(m_FormItem)->param( mfObject::Param_Options ).toStringList();
    //     if ( options.contains( "now" ) )
    //          m_Date->setDateTime( QDateTime::currentDateTime() );

    // create FormItemData
    BaseDateData *data = new BaseDateData(m_FormItem);
    data->setBaseDate(this);
    m_FormItem->setItemDatas(data);
}

BaseDate::~BaseDate()
{
}

void BaseDate::retranslate()
{
    m_Label->setText(m_FormItem->spec()->label());
}

////////////////////////////////////////// ItemData /////////////////////////////////////////////
BaseDateData::BaseDateData(Form::FormItem *item) :
        m_FormItem(item), m_Date(0)
{
}

BaseDateData::~BaseDateData()
{
}

void BaseDateData::setDate(const QString &s)
{
    m_Date->m_Date->clear();
    m_Date->m_Date->setDateTime(QDateTime::fromString(s, Qt::ISODate));
}

/** \brief Set the widget to the default value \sa FormItem::FormItemValue*/
void BaseDateData::clear()
{
    m_OriginalValue = m_FormItem->valueReferences()->defaultValue().toString();
    setDate(m_OriginalValue);
}

bool BaseDateData::isModified() const
{
    return m_OriginalValue != m_Date->m_Date->dateTime().toString(Qt::ISODate);
}

void BaseDateData::setData(const QVariant &data, const int role)
{
}

QVariant BaseDateData::data(const int role) const
{
    return QVariant();
}

void BaseDateData::setStorableData(const QVariant &data)
{
    setDate(data.toString());
    m_OriginalValue = data.toString();
}

QVariant BaseDateData::storableData() const
{
    return m_Date->m_Date->dateTime().toString(Qt::ISODate);
}


//--------------------------------------------------------------------------------------------------------
//------------------------------------------ BaseSpin --------------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseSpin::BaseSpin(Form::FormItem *formItem, QWidget *parent, bool doubleSpin)
        : Form::IFormWidget(formItem,parent), m_Spin(0)
{
    // Prepare Widget Layout and label
    QBoxLayout * hb = getBoxLayout(Label_OnLeft, m_FormItem->spec()->label(), this);
    hb->addWidget(m_Label);
    //     if ( !( mfo(m_FormItem)->options() & mfObjectFundamental::LabelOnTop ) )
    //     {
    //          Qt::Alignment alignment = m_Label->alignment();
    //          alignment &= ~( Qt::AlignVertical_Mask );
    //          alignment |= Qt::AlignVCenter;
    //          m_Label->setAlignment( alignment );
    //     }

    // Add spin
    if (doubleSpin) {
        QDoubleSpinBox *spin = new QDoubleSpinBox(this);
        spin->setObjectName("DoubleSpin_" + m_FormItem->uuid());
        spin->setMinimum(formItem->extraDatas().value(::SPIN_EXTRAS_KEY_MIN, "0").toDouble());
        spin->setMaximum(formItem->extraDatas().value(::SPIN_EXTRAS_KEY_MAX, "10000").toDouble());
        spin->setSingleStep(formItem->extraDatas().value(::SPIN_EXTRAS_KEY_STEP, "0.1").toDouble());
        m_Spin = spin;
    } else {
        QSpinBox *spin = new QSpinBox(this);
        spin->setObjectName("Spin_" + m_FormItem->uuid());
        spin->setMinimum(formItem->extraDatas().value(::SPIN_EXTRAS_KEY_MIN, "0").toInt());
        spin->setMaximum(formItem->extraDatas().value(::SPIN_EXTRAS_KEY_MAX, "10000").toInt());
        spin->setSingleStep(formItem->extraDatas().value(::SPIN_EXTRAS_KEY_STEP, "1").toInt());
        m_Spin = spin;
    }
    m_Spin->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Fixed);
    hb->addWidget(m_Spin);

    // manage options
    ;

    // create FormItemData
    BaseSpinData *data = new BaseSpinData(m_FormItem);
    data->setBaseSpin(this);
    m_FormItem->setItemDatas(data);
}

BaseSpin::~BaseSpin()
{}

void BaseSpin::retranslate()
{
    m_Label->setText(m_FormItem->spec()->label());
}

////////////////////////////////////////// ItemData /////////////////////////////////////////////
BaseSpinData::BaseSpinData(Form::FormItem *item) :
        m_FormItem(item), m_Spin(0)
{
}

BaseSpinData::~BaseSpinData()
{
}

/** \brief Set the widget to the default value \sa FormItem::FormItemValue*/
void BaseSpinData::clear()
{
    m_OriginalValue = m_FormItem->valueReferences()->defaultValue().toDouble();
    QSpinBox *spin = qobject_cast<QSpinBox*>(m_Spin->m_Spin);
    if (spin) {
        spin->setValue(m_FormItem->valueReferences()->defaultValue().toInt());
    } else {
        QDoubleSpinBox *dspin = qobject_cast<QDoubleSpinBox*>(m_Spin->m_Spin);
        if (dspin) {
            dspin->setValue(m_OriginalValue);
        }
    }
}

bool BaseSpinData::isModified() const
{
    return m_OriginalValue != storableData().toDouble();
}

void BaseSpinData::setData(const QVariant &data, const int role)
{
}

QVariant BaseSpinData::data(const int role) const
{
    return QVariant();
}

void BaseSpinData::setStorableData(const QVariant &data)
{
    m_OriginalValue = data.toDouble();
    QSpinBox *spin = qobject_cast<QSpinBox*>(m_Spin->m_Spin);
    if (spin) {
        spin->setValue(data.toInt());
        return;
    }
    QDoubleSpinBox *dspin = qobject_cast<QDoubleSpinBox*>(m_Spin->m_Spin);
    if (dspin) {
        dspin->setValue(data.toDouble());
    }
}

QVariant BaseSpinData::storableData() const
{
    QSpinBox *spin = qobject_cast<QSpinBox*>(m_Spin->m_Spin);
    if (spin) {
        return spin->value();
    }
    QDoubleSpinBox *dspin = qobject_cast<QDoubleSpinBox*>(m_Spin->m_Spin);
    if (dspin) {
        return dspin->value();
    }
    return QVariant();
}

//--------------------------------------------------------------------------------------------------------
//------------------------------------------ BaseButton ------------------------------------------------
//--------------------------------------------------------------------------------------------------------
BaseButton::BaseButton(Form::FormItem *formItem, QWidget *parent)
        : Form::IFormWidget(formItem,parent), m_Button( 0 )
{
    QHBoxLayout * hb = new QHBoxLayout(this);
    hb->addStretch();

    m_Button = new QPushButton( this );
    m_Button->setObjectName("Button_" + m_FormItem->uuid());
    m_Button->setText(m_FormItem->spec()->label() );
    m_Button->setSizePolicy(QSizePolicy::Expanding , QSizePolicy::Fixed);
    hb->addWidget(m_Button);
    connect( m_Button, SIGNAL(clicked()) , this , SLOT(buttonClicked()));
}

BaseButton::~BaseButton()
{}

void BaseButton::buttonClicked()
{
    /** \todo run script */
//    m_FormItem->scripts()->runScript();
}

void BaseButton::retranslate()
{
    m_Button->setText(m_FormItem->spec()->label());
}

