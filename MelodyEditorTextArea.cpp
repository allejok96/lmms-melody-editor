/**
 * MelodyEditorTextArea.cpp
 *
 * Copyright (c) 2025 - 2025 Bimal Poudel <anytizer@users.noreply.github.com>
 */

#ifndef LMMS_GUI_MELODY_EDITOR_TEXTAREA_CPP
#define LMMS_GUI_MELODY_EDITOR_TEXTAREA_CPP

#include "MelodyEditorTextArea.h"
#include "src/includes/Utilities.h"

#include <QMimeData>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QFont>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextCursor>
#include <QPlainTextEdit>
#include <QDebug>

using lmms::gui::editor::pianoroll::parsing::Utilities;

namespace lmms::gui
{

MelodyEditorTextArea::MelodyEditorTextArea()
{
	this->setAcceptDrops(true);

	// Try to be OS neutral and printer friendly.
	// Make a room for zoom out also.
	QFont font("Consolas", this->u->min_fontsize+4); // Consolas | sans-serif @ 14 points
	this->setFont(font);
	//this->styleSheet("font-family: Menlo, Consolas, 'Ubuntu Mono', 'Roboto Mono', 'DejaVu Sans Mono', monospace;");

	this->setCursor(Qt::IBeamCursor);

	// @todo Placeholder Text is not experienced.
	// QPlainTextEdit::
	this->setPlainText("# Double-Click to choose a song notation file.");
	this->setPlaceholderText("# Type or paste melody notations...");
	
	// Disable right click menus
	this->setContextMenuPolicy(Qt::NoContextMenu);
	
	// Prepare to enforce scrollbars on zooming
	this->setLineWrapMode(QPlainTextEdit::NoWrap);
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

MelodyEditorTextArea::~MelodyEditorTextArea()
{
}

bool MelodyEditorTextArea::loadNotationsFile(QString filename)
{
	bool loadable = u->sizeCheck(filename);
	if(loadable)
	{
		QString notations = u->fileContents(filename);
		this->setPlainText(notations);
	}

	return loadable;
}


void MelodyEditorTextArea::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
		QString filename = QFileDialog::getOpenFileName(
            this,                                   // Parent widget
            QObject::tr("Open Notations"),          // Dialog caption
            "~/Desktop",                            // Initial directory
            "Notations File (*."+this->MELODY_EXTENSION+");;" // File filters: double semi-colons
        );

		if (!filename.isEmpty())
		{
			this->loadNotationsFile(filename);
        }
    }
}


/**
 * Custom zoom logic on ctrl+wheel
 */
void MelodyEditorTextArea::wheelEvent(QWheelEvent *event)
{
	if (event->modifiers() & Qt::ControlModifier)
	{
		QFont font = this->font();
		int pointsize = font.pointSize() + (event->angleDelta().y() / u->zoom_factor);
		if(pointsize<u->min_fontsize) pointsize = u->min_fontsize;
		if(pointsize>u->max_fontsize) pointsize = u->max_fontsize;
	 	font.setPointSize(pointsize);
		this->setFont(font);

	 	event->accept();
	}
}


void MelodyEditorTextArea::dragEnterEvent(QDragEnterEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	if (mimeData->hasUrls())
	{
        QList<QUrl> urls = mimeData->urls();
        for (const QUrl &url : urls)
		{
            if (url.isLocalFile())
			{
                QString filename = url.toLocalFile();
                QFileInfo fileInfo(filename);
                if (fileInfo.suffix().toLower() == this->MELODY_EXTENSION)
				{
					event->acceptProposedAction();
					break;
                }
            }
        }
	}
}

void MelodyEditorTextArea::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasUrls())
	{
		QList<QUrl> urls = event->mimeData()->urls();
		for (const QUrl &url : urls)
		{
			QString filename = url.toLocalFile();
			QFileInfo fileInfo(filename);
			if (fileInfo.isFile() && fileInfo.suffix().toLower() == this->MELODY_EXTENSION)
			{
				this->loadNotationsFile(filename);
				break;
			}
		}
	}
	event->acceptProposedAction();
}

} // lmms::gui

#endif // LMMS_GUI_MELODY_EDITOR_TEXTAREA_CPP