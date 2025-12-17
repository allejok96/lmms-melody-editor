/**
 * HindustaniParser.cpp
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_EDITOR_PIANOROLL_PARSING_HINDUSTANIPARSER_CPP
#define LMMS_GUI_EDITOR_PIANOROLL_PARSING_HINDUSTANIPARSER_CPP

#include "../includes/DataStructures.h"
#include "AbstractParser.h"
#include "HindustaniParser.h"

#include <QStringList>

namespace lmms::gui::editor::pianoroll::parsing
{

    void HindustaniParser::setup()
    {
        this->_name = "SARGAM / Hindustani";
        this->_identifier = "hindustani";
    };

    /**
     * @todo Reuse data from PianoRoll
     * Usage purpose:
     *  - To validate a user input key.
     *  - To convert a key into MIDI key number
     * 
     * Expects that user types notations in Classical SARGAMS based on Roman letters.
     * 
     * Allowed letters: S, r, R, g, G, m, M, P, d, D, n, N
     * Allowed symbols: x, -, |, *, . (period), , (comma)
     * 
     * @todo Find an alternative way to replace strings
     * @see https://stackoverflow.com/questions/12048256/
     */
    QList<NotationCell *> HindustaniParser::parse(QString text)
    {
        // version: SA RE GA MA
        // version: Sa Re Ga Ma
        // version: स र ग म
        // version: सा रे ग म
        // version: s r g m
        if(text.length()<=0) return {};
        
        QString notes = this->replace_symbols(text);

        // Replace characters not used in SARGAM
        notes.replace("a", "");
        notes.replace("A", "");
        notes.replace("e", ""); // NOT a key name
        notes.replace("E", ""); // Not a key name
        notes.replace("i", "");
        notes.replace("I", "");
        //notes.replace("h", ""); // Dha => h part
        //notes.replace("ha", ""); // dha
        //notes.replace("HA", ""); // DHA
        notes.replace("h", ""); // dha
        notes.replace("H", ""); // dha
        notes.replace("u", ""); // ru

        notes.replace("(K)", "(k)"); // komal | flat
        // r(k) => R(K) => r

        // to sargam standards - multi letters
        notes.replace("s", "S");
        notes.replace("सां", "S*");
        notes.replace("Ṡ", "S*");
        notes.replace("सा", "S");
        notes.replace("स", "S");
        // some weird notations
        // notes.replace("ष", "S");
        // notes.replace("षा", "S");
        // notes.replace("शा", "S");
        // notes.replace("श", "S");
        ////////////////////////
        notes.replace("S", "S+");

        notes.replace("रें", "R*");
        notes.replace("रे॒", "r");
        notes.replace("री", "R");
        notes.replace("रि", "R");
        notes.replace("र॓", "R");
        notes.replace("रे", "R");
        notes.replace("र", "R");
        notes.replace("ऋ", "R");
        notes.replace("ॠ", "R");
        notes.replace("R(k)", "r");
        notes.replace("r(k)", "r");
        notes.replace("Ṟ", "r");
        notes.replace("Ṛ", "R.");
        notes.replace("Ṟ", "r");
        notes.replace("ṝ", "r");
        ////////////////////////
        notes.replace("r", "r+");
        notes.replace("R", "R+");
        
        notes.replace("G̱", "g");
        notes.replace("ग॒", "g");
        notes.replace("G", "G");
        notes.replace("गा", "G");
        notes.replace("ग", "G");
        notes.replace("गं", "G*");
        notes.replace("G(k)", "g");
        notes.replace("g(k)", "g");
        ////////////////////////
        notes.replace("g", "g+");
        notes.replace("G", "G+");

        notes.replace("म'", "M");
        notes.replace("मे", "M");
        notes.replace("म॑", "M"); // with long vertical bar
        notes.replace("म", "m");
        notes.replace("Ḿ", "M");
        notes.replace("M̄", "M");
        notes.replace("m'", "M");
        notes.replace("M'", "M");
        ////////////////////////
        notes.replace("m", "m+");
        notes.replace("M", "M+");

        notes.replace("p", "P");
        notes.replace("प़", "P.");
        notes.replace("प", "P");
        notes.replace("पा", "P");
        ////////////////////////
        notes.replace("P", "P+");

        notes.replace("dha", "d");
        notes.replace("Dha", "D");
        notes.replace("धै", "D");
        notes.replace("ध॒", "d"); // colliding with D?
        notes.replace("ध़", "D."); // lower octave? or komal?
        notes.replace("ध़", "D."); // lower octave? or komal?
        notes.replace("ध", "D"); // colliding D?
        notes.replace("d(k)", "d");
        notes.replace("d(k)", "d");
        ////////////////////////
        notes.replace("d", "d+");
        notes.replace("D", "D+");

        notes.replace("Ṉ", "n");
        notes.replace("नि॒", "n");
        notes.replace("नि", "N");
        notes.replace("ऩि", "N.");
        notes.replace("ऩ", "n"); // @todo: NI, nee or ni komal?
        notes.replace("नी", "N");
        notes.replace("N(k)", "n");
        notes.replace("n(k)", "n");
        ////////////////////////
        notes.replace("n", "n+");
        notes.replace("N", "N+");

        // convert to western notes
        // + sign is appended to lock replacing other notes containing same letters. eg. RE => D4 => DHA? => A
        notes.replace("S+", "C");
        notes.replace("r+", "C#");
        notes.replace("R+", "D");
        notes.replace("g+", "D#");
        notes.replace("G+", "E");
        notes.replace("m+", "F");
        notes.replace("M+", "F#");
        notes.replace("P+", "G");
        notes.replace("d+", "G#");
        notes.replace("D+", "A");
        notes.replace("n+", "A#");
        notes.replace("N+", "B");
        notes.replace("##", "#"); // MA' => F## => F#
        notes.replace("X",  "x"); // silence marker

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

#endif // LMMS_GUI_EDITOR_PIANOROLL_PARSING_HINDUSTANIPARSER_CPP