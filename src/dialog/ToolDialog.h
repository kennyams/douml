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

#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <tabdialog.h>
//Added by qt3to4:
#include <QPixmap>

#include "StringTable.h"
#include "UmlEnum.h"

class QPixmap;

struct ToolColumnDef {
    UmlCode kind;
    QPixmap ** pixmap;
};

class ToolDialog : public TabDialog
{
    Q_OBJECT

public:
    ToolDialog();
    virtual ~ToolDialog();

private:
    static QSize previous_size;

protected slots:
    virtual void accept();
    virtual void polish();
};

class ToolTable : public StringTable
{
    Q_OBJECT

private:
    const ToolColumnDef * cd;

public:
    ToolTable(QWidget * parent, const ToolColumnDef * tcd, unsigned ncols);

    virtual void init_row(int r);

    unsigned ntools();
    unsigned update(unsigned rank);

protected slots:
    virtual void button_pressed(const QModelIndex &index);
};

#endif
