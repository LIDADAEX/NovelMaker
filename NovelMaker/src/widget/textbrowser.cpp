#include "textbrowser.h"

TextBrowser::TextBrowser(QWidget *parent)
    :QTextBrowser(parent)
{}

void TextBrowser::setLineHeight(double factor)
{
    QTextCursor cursor = this->textCursor();

    // 2. 创建并设置文本块格式
    QTextBlockFormat blockFormat;
    // 设置为比例行高，factor 为行高倍数，例如 1.5, 2.0 等
    blockFormat.setLineHeight(factor * 100, QTextBlockFormat::ProportionalHeight);

    // 3. 应用格式到选中的文本块
    cursor.select(QTextCursor::Document); // 选中所有文本
    cursor.setBlockFormat(blockFormat);

    // 4. 清除选中状态
    cursor.clearSelection();
    this->setTextCursor(cursor);
}
