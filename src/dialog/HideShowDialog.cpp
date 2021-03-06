// *************************************************************************
//
// Copyright 2004-2010 Bruno PAGES  .
// Copyright 2012-2013 Nikolai Marchenko.
// Copyright 2012-2013 Leonardo Guilherme.
//
// This file is part of the DOUML Uml Toolkit.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License Version 3.0 as published by
// the Free Software Foundation and appearing in the file LICENSE.GPL included in the
//  packaging of this file.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License Version 3.0 for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
// e-mail : doumleditor@gmail.com
// home   : http://sourceforge.net/projects/douml
//
// *************************************************************************





#include <qlayout.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QListWidget>
#include <qcheckbox.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QList>
#include "HideShowDialog.h"
#include "BrowserNode.h"
#include "ClassMemberData.h"
#include "DialogUtil.h"
#include "ListBoxBrowserNode.h"
#include "UmlDesktop.h"
#include "translate.h"

QSize HideShowDialog::previous_size;

HideShowDialog::HideShowDialog(const BrowserNodeList & a,
                               QList<BrowserNode *> & hv,
                               BooL & visible)
    : QDialog(0/*, "hide/show dialog", TRUE*/), all(a),
      hidden_visible(hv), on_visible(visible)
{
    setWindowTitle(TR("Settings dialog"));

    QVBoxLayout * vbox = new QVBoxLayout(this);
    QHBoxLayout * hbox;
    QVBoxLayout * subvbox;
    QPushButton * button;

    vbox->setMargin(5);

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    subvbox = new QVBoxLayout();
    hbox->addLayout(subvbox);
    subvbox->setMargin(5);
    subvbox->addWidget(new QLabel(TR("Visible"), this), 0, Qt::AlignHCenter);
    subvbox->addWidget(lb_visible = new QListWidget (this));
    lb_visible->setSelectionMode(QListWidget ::MultiSelection);

    subvbox = new QVBoxLayout();
    hbox->addLayout(subvbox);
    subvbox->setSizeConstraint(QLayout::SetMinimumSize);
    subvbox->setMargin(5);
    //subvbox->addWidget(new QLabel("", this));
    subvbox->addStretch(100);
    subvbox->addWidget(button = new SmallPushButton(" -> ", this));
    connect(button, SIGNAL(clicked()), this, SLOT(hide_them()));
    subvbox->addStretch(100);
    subvbox->addWidget(button = new SmallPushButton(" <- ", this));
    connect(button, SIGNAL(clicked()), this, SLOT(show_them()));
    subvbox->addStretch(100);

    subvbox = new QVBoxLayout();
    hbox->addLayout(subvbox);
    subvbox->setMargin(5);
    subvbox->addWidget(new QLabel(TR("Hidden"), this), 0, Qt::AlignHCenter);
    subvbox->addWidget(lb_hidden = new QListWidget (this));
    lb_hidden->setSelectionMode(QListWidget ::MultiSelection);

    foreach (BrowserNode *item, all) {
        QString def = item->get_data()->definition(TRUE, FALSE);

        (((hidden_visible.indexOf(item) == -1) ^ on_visible)
         ? lb_visible : lb_hidden)
        ->addItem(new ListBoxBrowserNode(item, def));
    }

    lb_visible->sortItems();
    lb_hidden->sortItems();

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * sh_all = new SmallPushButton(TR("Show all"), this);
    QPushButton * hi_all = new SmallPushButton(TR("Hide all"), this);
    QPushButton * hi_priv = new SmallPushButton(TR("Hide private ones"), this);
    QPushButton * hi_priv_prot = new SmallPushButton(TR("Hide private and\nprotected ones"), this);
    QSize bs(hi_priv_prot->sizeHint());

    sh_all->setFixedSize(bs);
    hi_all->setFixedSize(bs);
    hi_priv->setFixedSize(bs);
    hi_priv_prot->setFixedSize(bs);

    hbox->addWidget(sh_all);
    hbox->addWidget(hi_all);
    hbox->addWidget(hi_priv);
    hbox->addWidget(hi_priv_prot);

    connect(sh_all, SIGNAL(clicked()), this, SLOT(show_all()));
    connect(hi_all, SIGNAL(clicked()), this, SLOT(hide_all()));
    connect(hi_priv, SIGNAL(clicked()), this, SLOT(hide_private()));
    connect(hi_priv_prot, SIGNAL(clicked()), this, SLOT(hide_private_protected()));

    //

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);

    cb_visible = new QCheckBox(TR("Specify visible members rather than hidden ones"), this);
    cb_visible->setChecked(on_visible);
    hbox->addWidget(cb_visible);

    //

    hbox = new QHBoxLayout();
    vbox->addLayout(hbox);
    hbox->setMargin(5);
    QPushButton * ok = new QPushButton(TR("&OK"), this);
    QPushButton * cancel = new QPushButton(TR("&Cancel"), this);

    ok->setDefault(TRUE);

    bs = cancel->sizeHint();
    ok->setFixedSize(bs);
    cancel->setFixedSize(bs);

    hbox->addWidget(ok);
    hbox->addWidget(cancel);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));
}

void HideShowDialog::polish()
{
    QDialog::ensurePolished();
    UmlDesktop::limitsize_move(this, previous_size, 0.8, 0.8);
}

HideShowDialog::~HideShowDialog()
{
    previous_size = size();
}

void HideShowDialog::hide_them()
{
    unsigned int i = 0;

    while (i < lb_visible->count()) {
        QListWidgetItem * item = lb_visible->item(i);

        if (item->isSelected()) {
            lb_visible->takeItem(lb_visible->row(item));
            lb_hidden->addItem(item);
        }
        else
            i += 1;
    }
}

void HideShowDialog::show_them()
{
    unsigned int i = 0;

    while (i < lb_hidden->count()) {
        QListWidgetItem * item = lb_hidden->item(i);

        if (item->isSelected()) {
            lb_hidden->takeItem(lb_hidden->row(item));
            lb_visible->addItem(item);
        }
        else
            i += 1;
    }
}

void HideShowDialog::show_all()
{
    while (lb_hidden->count()) {
        QListWidgetItem * item = lb_hidden->item(0);

        lb_hidden->takeItem(lb_hidden->row(item));
        lb_visible->addItem(item);
    }
}

void HideShowDialog::hide_all()
{
    while (lb_visible->count()) {
        QListWidgetItem * item = lb_visible->item(0);

        lb_visible->takeItem(lb_visible->row(item));
        lb_hidden->addItem(item);
    }
}

void HideShowDialog::hide_private()
{
    lb_visible->clear();
    lb_hidden->clear();

    foreach (BrowserNode *item, all) {
        BasicData * m = item->get_data();
        QString def = m->definition(TRUE, FALSE);

        ((((ClassMemberData *) m)->get_visibility(m->get_browser_node()) != UmlPrivate)
         ? lb_visible : lb_hidden)
        ->addItem(new ListBoxBrowserNode(item, def));
    }

    lb_visible->sortItems();
    lb_hidden->sortItems();
}

void HideShowDialog::hide_private_protected()
{
    lb_visible->clear();
    lb_hidden->clear();

    foreach (BrowserNode *item, all) {
        BasicData * m = item->get_data();
        QString def = m->definition(TRUE, FALSE);
        UmlVisibility visi =
            ((ClassMemberData *) m)->get_visibility(m->get_browser_node());

        (((visi == UmlPublic) || (visi == UmlPackageVisibility))
         ? lb_visible : lb_hidden)
        ->addItem(new ListBoxBrowserNode(item, def));
    }

    lb_visible->sortItems();
    lb_hidden->sortItems();
}

void HideShowDialog::accept()
{
    hidden_visible.clear();
    on_visible = cb_visible->isChecked();

    QListWidget * lb = (on_visible) ? lb_visible : lb_hidden;

    for (unsigned int i = 0; i != lb->count(); i += 1)
        hidden_visible.append(((ListBoxBrowserNode *) lb->item(i))->browser_node);

    QDialog::accept();
}
