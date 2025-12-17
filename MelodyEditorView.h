/**
 * MelodyEditorView.h
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_MELODY_EDITOR_VIEW_H
#define LMMS_GUI_MELODY_EDITOR_VIEW_H

#include "ToolPluginView.h"

#include "MelodyEditorTextArea.h"
#include "src/parsers/ParsersFactory.h"

using lmms::gui::editor::pianoroll::parsing::ParsersFactory;

namespace lmms
{
class MelodyEditor;
}

namespace lmms::gui
{

class MelodyEditorView : public ToolPluginView
{
private:
	Q_OBJECT

	MelodyEditor* m_plugin;

public:
	MelodyEditorView(MelodyEditor* plugin);
	void updateMidiClip();
	
	MelodyEditorTextArea *pte = new MelodyEditorTextArea();
	ParsersFactory *pf = new ParsersFactory();
	
	// defaults to first registered parser into the factory.
	// despite of -1 as placeholder.
	int parser_id = 0;
	
	void openNotationsFileSelector();

protected:
	void closeEvent(QCloseEvent*) override;
};

} // namespace lmms::gui

#endif // LMMS_GUI_MELODY_EDITOR_VIEW_H
