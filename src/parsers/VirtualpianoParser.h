/**
 * VirtualpianoParser.h
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#include "../includes/DataStructures.h"
#include "AbstractParser.h"

#include <QList>
#include <QString>

namespace lmms::gui::editor::pianoroll::parsing
{
    class VirtualpianoParser: public AbstractParser
    {
        public:
            QList<FindAndReplace *> vkr = QList<FindAndReplace *>();
            virtual void setup() override;
            
            QList<NotationCell *> parse(QString text) override;
    };
}