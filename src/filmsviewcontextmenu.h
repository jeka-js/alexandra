/*************************************************************************************************
 *                                                                                                *
 *  file: filmsviewcontextmenu.h                                                                  *
 *                                                                                                *
 *  Alexandra Video Library                                                                       *
 *  Copyright (C) 2014-2015 Eugene Melnik <jeka7js@gmail.com>                                     *
 *                                                                                                *
 *  Alexandra is free software; you can redistribute it and/or modify it under the terms of the   *
 *  GNU General Public License as published by the Free Software Foundation; either version 2 of  *
 *  the License, or (at your option) any later version.                                           *
 *                                                                                                *
 *  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;     *
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.     *
 *  See the GNU General Public License for more details.                                          *
 *                                                                                                *
 *  You should have received a copy of the GNU General Public License along with this program.    *
 *  If not, see <http://www.gnu.org/licenses/>.                                                   *
 *                                                                                                *
  *************************************************************************************************/

#ifndef FILMSVIEWCONTEXTMENU_H
#define FILMSVIEWCONTEXTMENU_H

#include <QAction>
#include <QMenu>

#include "film.h"

class FilmsViewContextMenu : public QMenu
{
    Q_OBJECT

    public:
        FilmsViewContextMenu( QWidget* parent = nullptr );

        void SetState( const Film* film );

    signals:
        void actionPlay();
        void actionShowInfo();
        void actionIsViewed( bool );
        void actionIsFavourite( bool );
        void actionEdit();
        void actionRemove();
        void actionRemoveFile();

    private slots:
        void actionPlaySlot();
        void actionShowInfoSlot();
        void actionIsViewedSlot( bool b );
        void actionIsFavouriteSlot( bool b );
        void actionEditSlot();
        void actionRemoveSlot();
        void actionRemoveFileSlot();

    private:
        QAction* cmaIsViewed = nullptr;
        QAction* cmaIsFavourite = nullptr;
};

#endif // FILMSVIEWCONTEXTMENU_H
