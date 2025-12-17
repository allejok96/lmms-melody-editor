/**
 * Utilities.cpp
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_PIANOROLL_PARSING_UTILITIES_CPP
#define LMMS_GUI_PIANOROLL_PARSING_UTILITIES_CPP

#include "Utilities.h"

#include <QString>
#include <QIODevice>
#include <QFile>
#include <QTextStream>

namespace lmms::gui::editor::pianoroll::parsing
{
    Utilities::Utilities()
    {

    }

    Utilities::~Utilities()
    {

    }

    QString Utilities::fileContents(QString filePath)
    {
        QString notations = "";

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            notations = in.readAll();
            
            file.close();
        }

        return notations;
    }

    bool Utilities::sizeCheck(QString filePath)
    {
        QFile file(filePath);
        return file.size() <= this->MAX_INPUT_LIMIT;
    }

}

#endif // LMMS_GUI_PIANOROLL_PARSING_UTILITIES_CPP