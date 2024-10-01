//
// Created by Nick Menshikov on 25.08.2024.
//
#include "utils/config_utils.h"

#include <iostream>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <QtCore/QString>
#include <QFile>

boost::property_tree::ptree config::loadConfig(const std::string &filename)
{
    boost::property_tree::ptree root;
    try {
        read_ini(filename, root);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return root;
}

QString config::getServerUrl(const std::string &filename)
{
    const boost::property_tree::ptree pt = loadConfig(filename);
    const auto server_url = pt.get<std::string>("Server.URL");
    return QString::fromStdString(server_url);
}


void config::loadStyles(QMessageBox &message_box, const std::string &filename) {
    const std::string file_path = "resources/styles/" + filename;
    if (QFile file(QString::fromStdString(file_path)); file.open(QFile::ReadOnly)) {
        const QString style_sheet = file.readAll();
        message_box.setStyleSheet(style_sheet);
    } else {
        qDebug() << "Cannot open style file.";
    }
}
