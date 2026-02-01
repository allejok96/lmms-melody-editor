/**
 * SimpleParser.h
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef MELODY_EDITOR_ABC_PARSER_H
#define MELODY_EDITOR_ABC_PARSER_H

#include "Note.h"
#include "AbstractParser.h"


namespace lmms::melodyeditor
{

class ABCParser : public AbstractParser
{
public:
	QString name() const override { return "ABC Parser"; }
	std::string icon() const override { return "TODO"; }
	QString help() const override { return "TODO"; }
	QString logMessages() const override { return "TODO"; }

	void parse(const QString& string) override;

	// Since we only write to piano roll, it's safe to write if piano roll was previously changed
	bool isSafeToWrite(const MidiClip* clipInPianoRoll, const std::vector<const Model*>& previous)
	{
		return std::find(previous.begin(), previous.end(), clipInPianoRoll) != previous.end();
	}

	std::vector<const Model*> write(MidiClip* clipInPianoRoll) override;

private:
	std::vector<Note> m_notes;
};

}

#endif // MELODY_EDITOR_ABC_PARSER_H
