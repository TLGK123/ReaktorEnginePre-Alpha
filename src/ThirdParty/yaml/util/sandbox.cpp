#include <iostream>

#include "yaml-cpp/emitterstyle.h"
#include "yaml-cpp/eventhandler.h"
#include "yaml-cpp/yaml.h"  // IWYU pragma: keep
#include <iostream>
#include <fstream>
#include <string>
#include <vector>


// our data types //这个例子好像是取自开源游戏引擎ogre，随便说的
struct Vec3 { //位置坐标
    float x, y, z;
};

struct Power { //招式，魔法
    std::string name; //招式名字，如 葵花宝典
    int damage; //伤害值
};

struct Monster { //怪兽
    std::string name;
    Vec3 position;
    std::vector <Power> powers;
};

template<typename T>
void operator >> (const YAML::Node& node, T& i)
{
    i = node.as<T>();
}

void operator >> (const YAML::Node& node, Vec3& v) {
    node[0] >> v.x;
    node[1] >> v.y;
    node[2] >> v.z;
}

void operator >> (const YAML::Node& node, Power& power) {
    node["name"] >> power.name;
    node["damage"] >> power.damage;
}

void operator >> (const YAML::Node& node, Monster& monster) {
    node["name"] >> monster.name;
    node["position"] >> monster.position;
    const YAML::Node& powers = node["powers"];
    for(unsigned i=0;i<powers.size();i++) {
        Power power;
        powers[i] >> power;
        monster.powers.push_back(power);
    }
}


int main() //测试程序
{
//    std::ifstream fin("/Users/blue/Desktop/Gitee/TmingEngine/src/Tools/example/test.yml"); // 读入yaml配置文件。
//    YAML::Parser parser(fin); //yaml 分析输入的配文件。出错抛出YAML::ParserException
    YAML::Node doc = YAML::LoadFile("/Users/blue/Desktop/Gitee/TmingEngine/src/Tools/example/test.yml");
    for(unsigned i=0;i<doc.size();i++)
    {//i的实际值是0，1，2 ；关联yaml 中三个大的struct：ogre，dragon，wizard
        Monster monster;
        doc[i]>> monster;
        ;
        std::cout <<monster.name << "\n";
 
    }
    return 0;
}

