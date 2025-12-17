/**
 * AbstractParser.h
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_EDITOR_PIANOROLL_PARSING_ABSTRACTPARSER_H
#define LMMS_GUI_EDITOR_PIANOROLL_PARSING_ABSTRACTPARSER_H

#include "../includes/DataStructures.h"

#include <QList>
#include <QString>

namespace lmms::gui::editor::pianoroll::parsing
{

/**
 * Info: This is NOT an abstract class!
 * The parser is abstract.
 */
class AbstractParser
{
    protected:
        QString _name = "";
        QString _identifier = ""; // lower cased, one-word

        QString replace_symbols(QString text);
        
    public:
        AbstractParser();
        ~AbstractParser();
        virtual void setup() = 0;
        virtual QList<NotationCell *> parse(QString text) = 0;

        QString name()
        {
            return this->_name;
        }

        QString identifier()
        {
            return this->_identifier;
        }

        QString toString() const
        {
            return _identifier;
        }

        int getPianoKey(QString note);
        void cells_to_xml(QList<NotationCell *> cells, QString &xml);
        int process_block(const QString block, QList<NotationCell *> &cells, int &position);
        int process_line(const QString line, QList<NotationCell *> &cells, int &position);
        int process_beatnotes(const QString column, QList<NotationCell *> &cells, int &position);
        int process_tone(const QString tone, QList<NotationCell *> &cells, float length, int &position);

        QList<FindAndReplace *> *replaces = new QList<FindAndReplace *>();
        QList<QString> notes = {}; // pure western names only with sharps | no flats.
        bool chord_processing = false;
        int chord_start_position = 0;
        QList<NotationCell *> chords = {};
};

}

#endif // LMMS_GUI_EDITOR_PIANOROLL_PARSING_ABSTRACTPARSER_H