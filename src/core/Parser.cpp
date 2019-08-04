#include "Parser.hpp"

#include <fstream>
#include "json/json.h"

std::ifstream core::Parser::getRoot(const std::string &name)
{
    // open the conf.json
    std::ifstream conf(name, std::ios::in);
    std::cout << (conf.is_open() ? "conf.json opened" : "conf.json NOT opened")
              << std::endl;
    return conf;
}

void core::Parser::parse(std::string name, std::vector<core::Block> &all)
{
    Json::Value root;
    core::Parser::getRoot(name) >> root;

    const Json::Value blocks = root["blocks"]; // get the main object
    all.clear();
    std::cout << std::endl << "parsing..." << std::endl;

    // foreach BLOCK
    std::for_each(blocks.begin(), blocks.end(), [&](const Json::Value &block) {
        std::vector<core::Group> g;
        int byteCont = 0;

        // name
        if (!block.isMember("name"))
            std::cout << "unnamed block" << std::endl;
        std::string blockName = block["name"].asString();

        // start
        if (!block.isMember("start"))
            std::cout << blockName << " no start" << std::endl;

        // groups
        if (!block.isMember("groups"))
            std::cout << blockName << " no groups" << std::endl;

        std::for_each( // foreach GROUP
            block["groups"].begin(), block["groups"].end(),
            [&](const Json::Value &group) {
                std::vector<core::Byte> b;

                // type
                if (!group.isMember("type"))
                    std::cout << "no group type in block "
                              << block["name"].asString() << std::endl;
                char groupType = group["type"].asString()[0];
                if (groupType != 'j' && groupType != 'm' && groupType != 'v')
                    std::cout << groupType << " not a valid type in block "
                              << block["name"].asString() << std::endl;

                // write
                if (!group.isMember("write"))
                    std::cout << "no group write in block "
                              << block["name"].asString() << std::endl;

                // bytes
                if (!group.isMember("bytes"))
                    std::cout << "no group bytes in block "
                              << block["name"].asString() << std::endl;

                // foreach BYTE
                std::for_each(
                    group["bytes"].begin(), group["bytes"].end(),
                    [&](const Json::Value &byte) {
                        std::vector<bool> v;
                        std::vector<std::string> s;
                        int sz;

                        // name
                        if (!byte.isMember("name"))
                            std::cout << "unnamed byte";
                        std::string tbName = std::to_string(byteCont++) + " " +
                                             byte["name"].asString();

                        // desc
                        if (!byte.isMember("desc"))
                            std::cout << tbName << " no description"
                                      << std::endl;
                        auto byteDesc = byte["desc"];
                        sz            = byteDesc.size();
                        if (sz != 0 && sz != 8)
                            std::cout << tbName << " wrong desc size"
                                      << std::endl;
                        for (int l = 0; l < sz; ++l)
                            s.push_back(byteDesc[l].asString());

                        // values
                        if (!byte.isMember("values"))
                            std::cout << tbName << " no values" << std::endl;
                        auto byteValues = byte["values"];
                        sz              = byteValues.size();
                        if (sz != 8)
                            std::cout << tbName << " wrong values size"
                                      << std::endl;
                        for (int l = 0; l < sz; ++l)
                            v.push_back(byteValues[l].asBool());

                        // add a byte
                        core::Byte tb(v, s, tbName);
                        b.push_back(tb);
                    }); // end foreach BYTE
                // add a group
                core::Group tg(b, groupType, group["write"].asBool());
                g.push_back(tg);
            }); // end foreach GROUP
        // add a block
        core::Block tblock(g, block["start"].asInt(), blockName);
        all.push_back(tblock);
    }); // end foreach BLOCK
}

void core::Parser::getSettings(std::string name, core::Settings &s)
{
    Json::Value root;
    core::Parser::getRoot(name) >> root;
    const auto &settings = root["settings"]; // get the main object

    s.portName      = settings["portName"].asString();
    s.Parity        = settings["Parity"].asInt();
    s.BaudRate      = settings["BaudRate"].asInt();
    s.DataBits      = settings["DataBits"].asInt();
    s.StopBits      = settings["StopBits"].asInt();
    s.ServerAddress = settings["ServerAddress"].asInt();
    s.refreshTime   = settings["refreshTime"].asInt();
}
