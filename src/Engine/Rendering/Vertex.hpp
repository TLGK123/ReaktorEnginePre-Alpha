//
//  Vertex.h
//  TmingEngine
//
//  Created by lillteblue on 2019/7/5.
//

#ifndef Vertex_h
#define Vertex_h
#include "im.h"

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
};


#endif /* Vertex_h */
