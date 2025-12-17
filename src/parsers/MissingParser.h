/**
 * MissingParser.h
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_EDITOR_PIANOROLL_PARSING_MISSINGPARSER_H
#define LMMS_GUI_EDITOR_PIANOROLL_PARSING_MISSINGPARSER_H

#include "AbstractParser.h"

namespace lmms::gui::editor::pianoroll::parsing
{

    // for wrongly chosen parser, serve as if not available
    class MissingParser: public AbstractParser
    {
        public:
            virtual void setup() override;
            virtual QList<NotationCell *> parse(QString text) override;
    };

}

#endif // LMMS_GUI_EDITOR_PIANOROLL_PARSING_MISSINGPARSER_H