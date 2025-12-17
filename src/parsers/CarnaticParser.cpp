/**
 * CarnaticParser.cpp
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_EDITOR_PIANOROLL_PARSING_CARNATICPARSER_CPP
#define LMMS_GUI_EDITOR_PIANOROLL_PARSING_CARNATICPARSER_CPP

#include "../includes/DataStructures.h"
#include "AbstractParser.h"
#include "CarnaticParser.h"

#include <QList>
#include <QMap>
#include <QString>

namespace lmms::gui::editor::pianoroll::parsing
{
    void CarnaticParser::setup()
    {
        this->_name = "SARGAM / Carnatic";
        this->_identifier = "carnatic";
    };
    
    QList<NotationCell *> CarnaticParser::parse(QString text)
    {
        if(text.length()<=0) return {};
        
        QString notes = this->replace_symbols(text).toUpper();
        notes.replace("₁", "1");
        notes.replace("₂", "2");
        notes.replace("₃", "3");
        notes.replace("₁", "1"); // different set of sub-numbering?
        notes.replace("₂", "2"); // different set of sub-numbering?
        notes.replace("₃", "3"); // different set of sub-numbering?
        notes.replace("SA", "S");
        notes.replace("RE", "R");
        notes.replace("RI", "R");
        notes.replace("GA", "G");
        notes.replace("MA", "M");
        notes.replace("PA", "P");
        notes.replace("DHA", "D");
        notes.replace("DA", "D");
        notes.replace("NI", "N");
        notes.replace("Ṡ", "S*");
        notes.replace("Ṡ", "S*");
        notes.replace("’", "*");

        for (const QString& key : mapping.keys()) {
            QString value = mapping[key];
            notes.replace(key, value);
        }

        // S R₁ G₁ M₁ P D₁ N₁ Ṡ
        // S R₂ G₂ M₁ P D₁ N₃ Ṡ
        // S R₃ G₃ M₁ P D₃ N₃ Ṡ
        // notes.replace("s", "C");
        // notes.replace("Ṡ", "C*");
        // notes.replace("P", "G");
        // notes.replace("P", "G");

        QStringList blocks = notes.split("#//");
        
        int errors = 0;
        int position = 0;        
        QList<NotationCell *> cells = {};
        for (const QString& block : blocks)
        {
            errors += process_block(block, cells, position);
        }
        
        return cells;
    }
}


#endif // LMMS_GUI_EDITOR_PIANOROLL_PARSING_CARNATICPARSER_CPP