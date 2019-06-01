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

void SwapVector(Vector2 & p1,Vector2 & p2)
{
    Vector2 temp = p2;
    p2 =p1;
    p1= temp;
}

void line(Vector2 p1, Vector2 p2, TGAImage &image, TGAColor color)
{
    if(std::abs(p2.x-p1.x)> std::abs(p2.y- p1.y))
    {
        if(p2.x < p1.x)
        {
           SwapVector(p2,p1);
        }
        for (int x = p1.x ; x <= p2.x ; x+= 1 )
        {
            int  y = (int)((p2.y - p1.y ) * 1.0 / (p2.x - p1.x) * (x - p1.x)) +  p1.y;
            image.set(x, y, color);
        }
   
    }else
    {
        if(p2.y < p1.y)
        {
           SwapVector(p2,p1);
        }
        for (int y = p1.y ; y <= p2.y ; y+= 1 )
        {
            int  x = (int)((p2.x - p1.x ) * 1.0 / (p2.y - p1.y) * (y - p1.y)) +  p1.x;
            image.set(x, y, color);
        }
    }
}

void triangle(Vector2 p1, Vector2 p2 , Vector2 p3 ,TGAImage &image, TGAColor color)
{
    line(p1,p2,image,color);
    line(p2,p3,image,color);
    line(p3,p1,image,color);
}

void triangleFilled(Vector2 p1, Vector2 p2 , Vector2 p3 ,TGAImage &image, TGAColor color )
{
     Vector2 t1 = p1 ;
     Vector2 t2 = p2 ;
     Vector2 t3 = p3 ;
    if(p1.y > p2.y)
    {
        SwapVector(p1,p2);
    }
    if(p1.y> p3.y)
    {
        SwapVector(p1,p3);
    }
    if(p2.y> p3.y)
    {
        SwapVector(p2,p3);
    }
    
    int maxDistanceY = p3.y - p1.y;
    
    if(t1.x > t2.x)
    {
        SwapVector(t1,t2);
    }
    if(t1.x> t3.x)
    {
        SwapVector(t1,t3);
    }
    if(t2.x > t3.x)
    {
        SwapVector(t2,t3);
    }
    
    int maxDistanceX = t3.x - t1.x;
   
    if(maxDistanceY > maxDistanceX)
    {
        int starth = p1.y ; int maxh = p3.y ;
        for (int y = starth ; y <= maxh; y++)
        {
            if(y <= p2.y)
            {
                int x1 =  (int)((p2.x - p1.x ) * 1.0 / (p2.y - p1.y) * (y - p1.y)) +  p1.x;  // y = ?  与线段 p1 p2的交点
                int x2 =  (int)((p3.x - p1.x ) * 1.0 / (p3.y - p1.y) * (y - p1.y)) +  p1.x;  // y = ?  与线段 p1 p3的交点
                line(Vector2(x1,y), Vector2(x2,y), image, color);
            }else
            {
                int x1 =  (int)((p3.x - p2.x ) * 1.0 / (p3.y - p2.y) * (y - p2.y)) +  p2.x;  // y = ?  与线段 p2 p3的交点
                int x2 =  (int)((p3.x - p1.x ) * 1.0 / (p3.y - p1.y) * (y - p1.y)) +  p1.x;  // y = ?  与线段 p1 p3的交点
                line(Vector2(x1,y), Vector2(x2,y), image, color);
            }
        }
    }else
    {
        int startw = t1.x ; int maxw = t3.x ;
        for (int x = startw ; x <= maxw; x++)
        {
            if(x <= t2.x)
            {
                int y1 =  (int)((t2.y - t1.y ) * 1.0 / (t2.x - t1.x) * (x - t1.x)) +  t1.y;  // x = ?  与线段 t1 t2的交点
                int y2 =  (int)((t3.y - t1.y ) * 1.0 / (t3.x - t1.x) * (x - t1.x)) +  t1.y;  // x = ?  与线段 t1 t3的交点
                line(Vector2(x,y1), Vector2(x,y2), image, color);
            }else
            {
                int y1 =  (int)((t3.y - t2.y ) * 1.0 / (t3.x - t2.x) * (x - t2.x)) +  t2.y;  // x = ?  与线段 t2 t3的交点
                int y2 =  (int)((t3.y - t1.y ) * 1.0 / (t3.x - t1.x) * (x - t1.x)) +  t1.y;  // x = ?  与线段 t1 t3的交点
                line(Vector2(x,y1), Vector2(x,y2), image, color);
            }
        }
    }
}


int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);
    line( Vector2(0,500),Vector2(1000,500), image, red);
    line( Vector2(500,0),Vector2(500,1000), image, red);
    //triangle(Vector2(20,20),Vector2(800,500),Vector2(300,650), image,red);
    
     triangleFilled(Vector2(20,20),Vector2(800,500),Vector2(300,650), image,red);
    
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}


    


