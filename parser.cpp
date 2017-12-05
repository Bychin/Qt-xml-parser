#include "parser.h"


AddressBookParser::AddressBookParser(QTreeWidget* tree, const QString& title) {
        treeWidget = tree;
        currentItem = nullptr;
        parsing_title = title;
}

bool AddressBookParser::startElement(const QString&,
                                     const QString&,
                                     const QString& tagName,
                                     const QXmlAttributes& attributes) {
    if (tagName == "catalog") {
       currentItem = new QTreeWidgetItem(treeWidget);
       currentItem->setText(0, parsing_title);
    }
    else if (tagName == "array") {
        ++iteration;
        currentItem = new QTreeWidgetItem(currentItem);
        currentItem->setText(0, "element N" + QString::number(iteration));
    }
    else if (tagName == "LINK" || tagName == "WebSite") {
        currentItem = new QTreeWidgetItem(currentItem);
        currentItem->setText(0, tagName);
    } else {
        currentItem = new QTreeWidgetItem(currentItem);
    }
    return true;
}

bool AddressBookParser::characters(const QString& strText) {
    currentText = strText;
    return true;
}

bool AddressBookParser::endElement(const QString&, const QString&, const QString& str) {
    if (str != "array" && str != "catalog" && str != "LINK") {
        currentItem->setText(0, currentText);
        currentItem = currentItem->parent();
    } else if (str == "LINK" || str == "WebSite") {
        currentItem = currentItem->parent();
    } else if (str == "array") {
        currentItem = currentItem->parent();
    }

    return true;
}

bool AddressBookParser::fatalError(const QXmlParseException& exception) {
    qDebug() << "Line:" << exception.lineNumber()
             << ", Column:" << exception.columnNumber()
             << ", Message:" << exception.message();
    return false;
}
