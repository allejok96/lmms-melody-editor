/**
 * NashvilleParser.cpp
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#include "../includes/DataStructures.h"
#include "NashvilleParser.h"

#include <QList>

using lmms::gui::editor::pianoroll::parsing::NotationCell;

namespace lmms::gui::editor::pianoroll::parsing
{
    void NashvilleParser::setup()
    {
        this->_name = "Numeric System";
        this->_identifier = "nashville";
    };

    // https://www.grossepointemusicacademy.com/nashville-number-system/
    // eg. 1-4-5-4 progression in the key of C => chords C, F, G, and F.
    // Same progression in the key of A => A, D, E, and D.
    QList<NotationCell *> NashvilleParser::parse(QString text)
    {
        if(text.length()<=0) return {};

        QList<NotationCell *> cells = {};
        // NotationCell *cell = new NotationCell();
        // cells.append(cell);
        return cells;
    }
}
