/*************************************************************************************************
 *                                                                                                *
 *  file: abstractparser.h                                                                        *
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

#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include "film.h"
#include "debug.h"
#include "networkrequest.h"

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QUrl>

// TODO: need to comment //

class AbstractParser : public QObject
{
    Q_OBJECT

    public:
        AbstractParser()
        {
            connect( &request, &NetworkRequest::DataLoaded, this, &AbstractParser::DataLoaded );
            connect( &request, &NetworkRequest::DataLoadError, this, [this] (const QString& e) { emit Error( e ); } );
            connect( &request, &NetworkRequest::Progress, this, [this] (quint64 received, quint64 total) { emit Progress( received, total ); } );
        }

        virtual void SearchFor( const QString& title, const QString& year = QString() )
        {
            DebugPrintFuncA( "AbstractParser::SearchFor", title );
            QUrl url;

            if( year.isEmpty() )
            {
                url = searchUrl.arg( title );
            }
            else
            {
                url = searchUrlWithYear.arg( title ).arg( year );
            }

            request.run( url );
        }

        virtual void SyncSearchFor( Film* filmSaveTo, QString* posterFileNameSaveTo,
                                    const QString& title, const QString& year = QString() )
        {
            DebugPrintFuncA( "AbstractParser::SyncSearchFor", title );
            QUrl url;

            if( year.isEmpty() )
            {
                url = searchUrl.arg( title );
            }
            else
            {
                url = searchUrlWithYear.arg( title ).arg( year );
            }

            QByteArray data = request.runSync( QUrl( searchUrl ) );
            QString poster = Parse( data );

            if( filmSaveTo != nullptr )
            {
                // We must to save filename
                QString fileName = filmSaveTo->GetFileName();
                filmSaveTo->SetNewData( f );
                filmSaveTo->SetFileName( fileName );
            }

            if( posterFileNameSaveTo != nullptr )
            {
                *posterFileNameSaveTo = poster;
            }
        }

        virtual ~AbstractParser() = default;

    protected slots:
        // This slot must be overridden by concrete parser
        virtual QString Parse( const QByteArray& data ) = 0;

        virtual void DataLoaded( const QByteArray& data )
        {
            DebugPrintFuncA( "AbstractParser::DataLoaded", data.size() );
            Parse( data );
        }

    signals:
        void Progress( quint64 received, quint64 total );
        void Loaded( const Film& f, const QString& posterFileName );
        void Error( const QString& e);

    protected:
        QString searchUrlWithYear;
        QString searchUrl;

        NetworkRequest request;
        Film f;
};

#endif // ABSTRACTPARSER_H
