#include "QtXMLValueParser.hpp"

#include <frontend/libqt/SimpleParameter.hpp>

namespace sd {
  
  namespace libqt {

QtXMLValueParser::QtXMLValueParser(std::string xml_string) : m_xmlstring(xml_string)
{
    initialize();
}



QtXMLValueParser::~QtXMLValueParser(){}



int QtXMLValueParser::initialize()
{

    bool hasParsed = m_qdoc.setContent(QString::fromStdString(m_xmlstring), namespace_processing,
                      m_error_msg, m_err_line, m_err_column);

    if(!hasParsed)
    {
        std::cout << "Parser failed line " << m_err_line << ", column " << m_err_column << " : ";
        std::cout << m_error_msg->toStdString() << std::endl;
    }

    return 1;

}

sd::libqt::Parameter *QtXMLValueParser::parseSimpleParameter()
{
    int value;
    QDomElement param_root = m_qdoc.firstChildElement("parameter");
    std::string name = param_root.attributeNode("name").value().toStdString();
    std::string type = param_root.attributeNode("type").value().toStdString();


    QDomElement param_elem = param_root.firstChildElement();

    value = param_elem.text().toInt();

    sd::libqt::Parameter *p = new SimpleIntParameter(name, 0, 0, 0);
    //p.toString();
    return p;

}

sd::libqt::Parameter *QtXMLValueParser::parseComplexParameter() 
{
    return nullptr;
}

}}





