#ifndef QTXMLVALUEPARSER_HPP
#define QTXMLVALUEPARSER_HPP

#include <QtXml>
#include "parameterTmp.hpp"

static const bool namespace_processing = true;

class QtXMLValueParser
{


public:
    QtXMLValueParser(std::string xml_string);
    ~QtXMLValueParser();

    parameterTmp parseSimpleParameter();
    parameterTmp parseComplexParameter();


private:
    int initialize();

private:
    std::string m_xmlstring;
    QDomDocument m_qdoc;
    int *m_err_line;
    int *m_err_column;
    QString *m_error_msg;

};

#endif // QTXMLVALUEPARSER_HPP
