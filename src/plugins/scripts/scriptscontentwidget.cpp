/***********************************************************************************************************************
**
** Copyright (C) 2021 BaseALT Ltd. <org@basealt.ru>
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**
***********************************************************************************************************************/

#include "scriptscontentwidget.h"
#include "ui_scriptscontentwidget.h"

#include "scriptsdialog.h"

#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewitem.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

#include <QDataWidgetMapper>

namespace scripts_plugin
{
ScriptsContentWidget::ScriptsContentWidget(ScriptsSnapIn *sn, QWidget *parent)
    : QWidget(parent)
    , model(std::make_unique<QStringListModel>())
    , ui(new Ui::ScriptsContentWidget())
    , snapIn(sn)
{
    ui->setupUi(this);

    buildModel();
}

ScriptsContentWidget::~ScriptsContentWidget()
{
    delete ui;
}

void ScriptsContentWidget::setNamespace(bool machineNamespace)
{
    isMachineNamespace = machineNamespace;

    buildModel();
}

void ScriptsContentWidget::buildModel()
{
    model = std::make_unique<QStringListModel>();

    QString startupItem  = "Logon";
    QString shutdownItem = "Logoff";

    if (isMachineNamespace)
    {
        startupItem  = "Startup";
        shutdownItem = "Shutdow";
    }

    QStringList list;
    list << startupItem << shutdownItem;
    model.get()->setStringList(list);

    ui->listView->setModel(model.get());

    connect(ui->listView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
            this,
            SLOT(startDialog(QItemSelection)));
}

void ScriptsContentWidget::startDialog(QItemSelection item)
{
    if (!item.indexes().isEmpty())
    {
        auto displayName = model.get()->data(item.indexes().first()).toString();

        if ((displayName.compare("Logon") == 0) || (displayName.compare("Startup") == 0))
        {
            isStartupScripts = true;
        }
        else
        {
            isStartupScripts = false;
        }

        auto dialog = new ScriptsDialog(this);

        if (isMachineNamespace)
        {
            dialog->setModels(snapIn->d->machineScriptsModel.get(),
                              snapIn->d->machinePowerScriptsModel.get(),
                              isStartupScripts);
        }
        else
        {
            dialog->setModels(snapIn->d->userScriptsModel.get(),
                              snapIn->d->userPowerScriptsModel.get(),
                              isStartupScripts);
        }

        dialog->exec();
    }
}

} // namespace scripts_plugin
