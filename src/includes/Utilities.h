/**
 * Utilties.h
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_EDITOR_PIANOROLL_PARSING_UTILITIES_H
#define LMMS_GUI_EDITOR_PIANOROLL_PARSING_UTILITIES_H

#include <QString>

namespace lmms::gui::editor::pianoroll::parsing
{

class Utilities
{
    public:
        /**
         * The plguin name when compiled.
         * @see CMakeLists.txt | MUST match.
         */
        const QString identifier = "melodyeditor";

        Utilities();
        ~Utilities();

        QString fileContents(QString filePath);
        
        /**
         * To not to allow large file sizes
         */ 
        bool sizeCheck(QString filePath);
    
        /**
         * 20kb notations gives around 2000 to 5000 measures.
         * This is nearly 1 hour long play time, @160 bpm.
         * Processing too large text may cause crash or delay.
         */ 
        const int MAX_INPUT_LIMIT = 20480;

        /**
         * Zoom factors on notations editor
         */
        const int min_fontsize = 10; // min: readable font size: 10
        const int max_fontsize = 28; // max 36
        const int zoom_factor = 90; // 80 to 120 | 120 default
    };

}

#endif // LMMS_GUI_EDITOR_PIANOROLL_PARSING_UTILITIES_H