#include <styles/qsspreprocessor.h>

QssPreProcessor::QssPreProcessor(QObject *parent)
    : QObject{parent}
{}

QssPreProcessor::QssPreProcessor(QString styleFilePath, QObject *parent)
    : m_styleFilePath(styleFilePath), QObject{parent}
{

}

QssPreProcessor::QssPreProcessor(QDir stylePath, QObject *parent)
    : m_stylePath(stylePath), QObject{parent}
{

}

void QssPreProcessor::startPreProcess()
{

}
