#include "TextToolBar.h"
#include <QFontDialog>
#include <QIcon>

TextToolBar::TextToolBar(QMainWindow* mainWindow, CanvasWidget* canvas)
    : QObject(mainWindow), canvas(canvas), mainWindow(mainWindow),
      textSettingsMenu(nullptr), textSettingsButton(nullptr), textToolBar(nullptr)
{
    createActions();
    createToolbars();
}

void TextToolBar::createActions()
{
    // Text tool action with icon
    textToolAction = new QAction(TextToolBar::tr("Text Tool"), this);
    connect(textToolAction, &QAction::triggered, this, &TextToolBar::selectTextTool);

    // Select Font action
    selectFontAction = new QAction(TextToolBar::tr("Select Font"), this);
    connect(selectFontAction, &QAction::triggered, this, &TextToolBar::selectFont);
}

void TextToolBar::createToolbars()
{
    // Create the text toolbar
    textToolBar = new QToolBar(TextToolBar::tr("Text Tools"), mainWindow);
    textToolBar->setObjectName("TextToolBar"); // For saving toolbar state
    
    // Create dropdown menu for text settings
    textSettingsMenu = new QMenu(TextToolBar::tr("Text Settings"), mainWindow);
    textSettingsMenu->addAction(textToolAction);
    textSettingsMenu->addAction(selectFontAction);

    
    // Create tool button with dropdown and icon
    textSettingsButton = new QToolButton(textToolBar);
    textSettingsButton->setIcon(QIcon(":/icons/text.png"));
    textSettingsButton->setText(TextToolBar::tr("Text"));
    textSettingsButton->setToolTip(TextToolBar::tr("Text Settings"));
    textSettingsButton->setMenu(textSettingsMenu);
    textSettingsButton->setPopupMode(QToolButton::InstantPopup);
    textSettingsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    
    // Add the button to the toolbar
    textToolBar->addWidget(textSettingsButton);
    
    // Add the toolbar to the main window 
    mainWindow->addToolBar(Qt::TopToolBarArea, textToolBar);
}

void TextToolBar::selectTextTool()
{
    canvas->setTool(CanvasWidget::Tool::TextTool);
}

void TextToolBar::selectFont()
{
    static QFont currentFont("Arial", 12); //use Qt dialog box to get font 
    bool ok;
    QFont font = QFontDialog::getFont(&ok, currentFont, mainWindow, TextToolBar::tr("Select Text Font"));
    
    if (ok) {
        currentFont = font;
        canvas->setFont(font);
    }
}
