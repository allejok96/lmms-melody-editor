/**
 * ParserFactory.cpp- List of registered melody parsers
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#include "ParsersFactory.h"

#include "CarnaticParser.h"
#include "EnglishParser.h"
#include "GermanParser.h"
#include "HindustaniParser.h"
#include "MissingParser.h"
#include "NashvilleParser.h"
#include "VirtualpianoParser.h"

namespace lmms::gui::editor::pianoroll::parsing
{
    ParsersFactory::ParsersFactory()
    {
        // If parser is not completed: Do not expose it.
        this->parsers = {};
        this->parsers.append(new HindustaniParser());
        this->parsers.append(new CarnaticParser());
        this->parsers.append(new EnglishParser());
        //this->parsers.append(new GermanParser());
        //this->parsers.append(new NashvilleParser());
        //this->parsers.append(new VirtualpianoParser());
        // LMMS Mac Build keyboard layout
        // LMMS Windows Build keyboard layout
        // LMMS Linux Build keyboard layout
        
        if(!this->parsers.count())
        {
            // DO NOT queue it as a general purpose parser.
            this->parsers.append(new MissingParser());
        }

        int len = this->parsers.length();
        for(int i=0; i<len; ++i)
        {
            this->parsers[i]->setup();
        }
    }

    ParsersFactory::~ParsersFactory()
    {

    }
}