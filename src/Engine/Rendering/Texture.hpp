//
//  Texture.h
//  TmingEngine
//
//  Created by Blue on 2019/7/5.
//

#ifndef Texture_h
#define Texture_h
#include<string>
using namespace std;
struct Texture {
    unsigned int id;
    string type;
    string path;
};

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

#endif /* Texture_h */
