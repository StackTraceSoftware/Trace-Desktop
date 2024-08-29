//
// Created by Nick Menshikov on 25.08.2024.
//

#ifndef CONFIG_UTILS_H
#define CONFIG_UTILS_H
#pragma once
#include <QMessageBox>
#include <boost/property_tree/ptree_fwd.hpp>
#include <QtCore/QString>

namespace config
{
    boost::property_tree::ptree load_config(const std::string &filename);
    QString get_server_url(const std::string &filename);
    void load_styles(QMessageBox &message_box, const std::string &filename); //TODO move this method to another util file
}

#endif //CONFIG_UTILS_H
