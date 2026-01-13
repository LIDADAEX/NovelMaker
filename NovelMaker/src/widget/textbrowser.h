#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QTextBrowser>

class TextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    TextBrowser(QWidget* parent = nullptr);

    void setLineHeight(double factor);
};

#endif // TEXTBROWSER_H
