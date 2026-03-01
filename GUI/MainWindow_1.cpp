#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <QColorDialog>
#include <QIcon>
#include <QString>
//#include <iostream>

void MainWindow::openFile() {
    QString filename = QFileDialog::getOpenFileName(
        this, tr("Open File"), "", tr("SVG Files (*.svg);;All Files (*)")
    );
    if (filename.isEmpty()) return;
    
    std::ifstream file(filename.toStdString());
    if (!file.is_open()) {
        QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
        return;
    }
    
    std::stringstream buffer; // Read the entire file into a string
    buffer << file.rdbuf(); //outputs the contents of the file into the stringstream buffer
    std::string svgContent = buffer.str(); // Convert the stringstream to a std::string
    file.close(); // Close the file after reading
    XmlTokenizer tokenizer; 
    std::vector<XMLToken> tokens = tokenizer.tokenizeXML(svgContent); // Tokenize the SVG content into XML tokens for parsing
    //std::cout << "Number of tokens: " << tokens.size() << std::endl;
    SVGParser parser;
    SVGDocument loadedDoc = parser.parseSVG(tokens); // Parse the tokens to create an SVGDocument object 
    //std::cout << "Number of parsed elements: " << loadedDoc.getElements().size() << std::endl;
    canvas->loadSVGDocument(loadedDoc); // Load the SVGDocument into the canvas
}
void MainWindow::saveFile() {
    QString filename = QFileDialog::getSaveFileName(
        this, tr("Save File"), "", tr("SVG Files (*.svg);;All Files (*)")
    );   
    if (filename.isEmpty()) return;
    
    try {
        SVGDocument currentDocument = canvas->getSVGDocument(); // Get the current SVGDocument from the canvas 

        SVGWriter::writeSVG(currentDocument, filename); // Write the SVGDocument to a file using SVGWriter
        
        QMessageBox::information(this, tr("Success"), 
            tr("File saved successfully with %1 elements").arg(currentDocument.getElements().size()));
    } catch (const std::exception& e) {
        QMessageBox::warning(this, tr("Error"), tr("Could not save file: ") + e.what());
    }
}

void MainWindow::changeBrushColor() {
    QColor color = QColorDialog::getColor(brushColor, this, tr("Select Brush Color")); //getting new color 
    if (color.isValid()) {
        brushColor = color;
        canvas->setBrushColor(color);
    }
}

void MainWindow::changeBrushSize() {
    bool ok; //getting new brush size from user input
    int size = QInputDialog::getInt(
        this, tr("Brush Size"), tr("Enter Brush Size:"), 
        brushSize, 1, 100, 1, &ok
    );
    if (ok) {
        brushSize = size;
        canvas->setBrushSize(size);
    }
}

void MainWindow::changeFillColor() {
    QColor color = QColorDialog::getColor(fillColor, this, tr("Select Fill Color"));
    if (color.isValid()) {
        fillColor = color;
        canvas->setFillColor(color);
    }
}

void MainWindow::createToolbars() 
{
    fileToolBar = addToolBar(tr("Pen Tools"));
    
    // Create dropdown menu for brush settings
    brushSettingsMenu = new QMenu(this);
    brushSettingsMenu->addAction(brushColorAction);
    brushSettingsMenu->addAction(brushSizeAction);
    brushSettingsMenu->addAction(fillColorAction);
    
    // Create tool button with dropdown
    brushSettingsButton = new QToolButton(this);
    brushSettingsButton->setIcon(QIcon(":/icons/brush.png"));
    brushSettingsButton->setText(tr("Brush"));
    brushSettingsButton->setToolTip(tr("Brush Settings"));
    brushSettingsButton->setMenu(brushSettingsMenu);
    brushSettingsButton->setPopupMode(QToolButton::InstantPopup);
    brushSettingsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    
    // Add the button to toolbar
    fileToolBar->addWidget(brushSettingsButton);
}

