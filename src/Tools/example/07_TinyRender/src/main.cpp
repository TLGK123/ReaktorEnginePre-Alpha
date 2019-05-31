#include "tgaimage.h"

// https://github.com/ssloy/tinyrenderer/wiki

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

struct Vector2
{
    int x;
    int y;
public:
    Vector2(int _x, int _y )
    {
        x = _x;
        y = _y;
    }
    
};

void line(Vector2 p1, Vector2 p2, TGAImage &image, TGAColor color) {
    if(p2.x < p1.x)
    {
        Vector2 temp = p2;
        p2 =p1;
        p1= temp;
    }
    
    for (int x = p1.x ; x <= p2.x ; x+= 1 )
    {
        int  y = (int)((p2.y - p1.y ) * 1.0 / (p2.x - p1.x) * (x - p1.x)) +  p1.y;
        image.set(x, y, color);
    }
}

void triangle(Vector2 p1, Vector2 p2 , Vector2 p3 ,TGAImage &image, TGAColor color)
{
    line(p1,p2,image,color);
    line(p2,p3,image,color);
    line(p3,p1,image,color);
}


int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);
   // line( Vector2(1000,0),Vector2(0,1000), image, red);
    triangle(Vector2(20,20),Vector2(800,500),Vector2(300,900), image,red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}


    


