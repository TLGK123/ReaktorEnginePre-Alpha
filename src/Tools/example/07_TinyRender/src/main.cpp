//#include "tgaimage.h"
//#include "model.h"
//#include "geometry.h"
//
//namespace TinyRender {
//
//// https://github.com/ssloy/tinyrenderer/wiki
//
//const TGAColor white = TGAColor(255, 255, 255, 255);
//const TGAColor red   = TGAColor(255, 0,   0,   255);
//const TGAColor green = TGAColor(0, 255,   0,   255);
//
//const int ScreenWidth  = 1000;
//const int ScreenHeight = 1000;
//
//Model *model = NULL;
//Vec3f light_dir(1,1,1);
//
//struct Vector2
//{
//    int x;
//    int y;
//public:
//    Vector2(int _x, int _y )
//    {
//        x = _x;
//        y = _y;
//    }
//    
//};
//
//void SwapVector(Vector2 & p1,Vector2 & p2)
//{
//    Vector2 temp = p2;
//    p2 =p1;
//    p1= temp;
//}
//
//
//void point(Vec2i p ,TGAImage &image, TGAColor color)
//{
//      image.set(p.x, p.y, color);
//}
//
//void line(Vector2 p1, Vector2 p2, TGAImage &image, TGAColor color)
//{
//    if(std::abs(p2.x-p1.x)> std::abs(p2.y- p1.y))
//    {
//        if(p2.x < p1.x)
//        {
//           SwapVector(p2,p1);
//        }
//        for (int x = p1.x ; x <= p2.x ; x+= 1 )
//        {
//            int  y = (int)((p2.y - p1.y ) * 1.0 / (p2.x - p1.x) * (x - p1.x)) +  p1.y;
//            image.set(x, y, color);
//        }
//   
//    }else
//    {
//        if(p2.y < p1.y)
//        {
//           SwapVector(p2,p1);
//        }
//        for (int y = p1.y ; y <= p2.y ; y+= 1 )
//        {
//            int  x = (int)((p2.x - p1.x ) * 1.0 / (p2.y - p1.y) * (y - p1.y)) +  p1.x;
//            image.set(x, y, color);
//        }
//    }
//}
//
//void triangle(Vector2 p1, Vector2 p2 , Vector2 p3 ,TGAImage &image, TGAColor color)
//{
//    line(p1,p2,image,color);
//    line(p2,p3,image,color);
//    line(p3,p1,image,color);
//}
//
//void line(Vec2i p1, Vec2i p2,TGAImage &image, TGAColor color)
//{
//    line( Vector2(p1.x ,p1.y), Vector2(p2.x,p2.y), image, color);
//}
//
//
//void triangleFilled(Vector2 p1, Vector2 p2 , Vector2 p3 ,TGAImage &image, TGAColor color )
//{
//     Vector2 t1 = p1 ;
//     Vector2 t2 = p2 ;
//     Vector2 t3 = p3 ;
//    if(p1.y > p2.y)
//    {
//        SwapVector(p1,p2);
//    }
//    if(p1.y> p3.y)
//    {
//        SwapVector(p1,p3);
//    }
//    if(p2.y> p3.y)
//    {
//        SwapVector(p2,p3);
//    }
//    
//    int maxDistanceY = p3.y - p1.y;
//    
//    if(t1.x > t2.x)
//    {
//        SwapVector(t1,t2);
//    }
//    if(t1.x> t3.x)
//    {
//        SwapVector(t1,t3);
//    }
//    if(t2.x > t3.x)
//    {
//        SwapVector(t2,t3);
//    }
//    
//    int maxDistanceX = t3.x - t1.x;
//   
//    if(maxDistanceY > maxDistanceX)
//    {
//        int starth = p1.y ; int maxh = p3.y ;
//        for (int y = starth ; y <= maxh; y++)
//        {
//            if(y <= p2.y)
//            {
//                int x1 =  (int)((p2.x - p1.x ) * 1.0 / (p2.y - p1.y) * (y - p1.y)) +  p1.x;  // y = ?  与线段 p1 p2的交点
//                int x2 =  (int)((p3.x - p1.x ) * 1.0 / (p3.y - p1.y) * (y - p1.y)) +  p1.x;  // y = ?  与线段 p1 p3的交点
//                line(Vector2(x1,y), Vector2(x2,y), image, color);
//            }else
//            {
//                int x1 =  (int)((p3.x - p2.x ) * 1.0 / (p3.y - p2.y) * (y - p2.y)) +  p2.x;  // y = ?  与线段 p2 p3的交点
//                int x2 =  (int)((p3.x - p1.x ) * 1.0 / (p3.y - p1.y) * (y - p1.y)) +  p1.x;  // y = ?  与线段 p1 p3的交点
//                line(Vector2(x1,y), Vector2(x2,y), image, color);
//            }
//        }
//    }else
//    {
//        int startw = t1.x ; int maxw = t3.x ;
//        for (int x = startw ; x <= maxw; x++)
//        {
//            if(x <= t2.x)
//            {
//                int y1 =  (int)((t2.y - t1.y ) * 1.0 / (t2.x - t1.x) * (x - t1.x)) +  t1.y;  // x = ?  与线段 t1 t2的交点
//                int y2 =  (int)((t3.y - t1.y ) * 1.0 / (t3.x - t1.x) * (x - t1.x)) +  t1.y;  // x = ?  与线段 t1 t3的交点
//                line(Vector2(x,y1), Vector2(x,y2), image, color);
//            }else
//            {
//                int y1 =  (int)((t3.y - t2.y ) * 1.0 / (t3.x - t2.x) * (x - t2.x)) +  t2.y;  // x = ?  与线段 t2 t3的交点
//                int y2 =  (int)((t3.y - t1.y ) * 1.0 / (t3.x - t1.x) * (x - t1.x)) +  t1.y;  // x = ?  与线段 t1 t3的交点
//                line(Vector2(x,y1), Vector2(x,y2), image, color);
//            }
//        }
//    }
//}
//
//void triangleFilled(Vec2i p1, Vec2i p2 , Vec2i p3 ,TGAImage &image, TGAColor color )
//{
//    triangleFilled(Vector2(p1.x ,p1.y),Vector2(p2.x,p2.y),Vector2(p3.x,p3.y),image,color);
//}
//
//int main(int argc, char** argv) {
//    TGAImage image(ScreenWidth, ScreenHeight, TGAImage::RGB);
//    //line( Vector2(0,ScreenHeight/2),Vector2(ScreenWidth,ScreenHeight/2), image, red);
//    //line( Vector2(ScreenWidth /2,0),Vector2(ScreenWidth /2,ScreenHeight), image, red);
//    //triangle(Vector2(10,10),Vector2(400,250),Vector2(150,325), image,red);
//    
//    //triangleFilled(Vector2(20,20),Vector2(800,500),Vector2(300,650), image,red);
//    //triangleFilled(Vector2(200,230),Vector2(650,500),Vector2(777,450), image,green);
//    // model = new Model("/Users/blue/Desktop/Gitee/TmingEngine/src/Tools/example/07_TinyRender/obj/african_head.obj");
//    model = new Model("/Users/blue/Desktop/Gitee/TmingEngine/resources/objects/rock/rock.obj");
// 
//  //
//    for (int i=0 ; i< model->nfaces(); i++)
//    {
//        std::vector<int> face = model->face(i);
//        
//        //------线框模型
////        for (int j=0; j< 3; j++)
////        {
////            auto v0 = model->vert(face[j]);
////            auto v1 = model->vert(face[(j+1)%3]);
////
////            int  x0 = (v0.x + 1.0f) * ScreenWidth /2;
////            int  y0 = (v0.y + 1.0f) * ScreenHeight /2;
////
////            int  x1 = (v1.x + 1.0f) * ScreenWidth /2;
////            int  y1 = (v1.y + 1.0f) * ScreenHeight /2;
////
////            line(Vector2(x0,y0), Vector2(x1,y1), image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
////        }
//        //------线框模型---end
//        
//        //-------填随机色块模型
////        std::vector<Vector2> facePoint;
////        for (int  j=0; j <3; j++)
////        {
////             auto v0 = model->vert(face[j]);
////             int  x0 = (v0.x + 1.0f) * ScreenWidth /2;
////             int  y0 = (v0.y + 1.0f) * ScreenHeight /2;
////             facePoint.push_back(Vector2(x0,y0));
////        }
////        triangleFilled(facePoint[0],facePoint[1],facePoint[2],image, TGAColor(rand()%255, rand()%255, rand()%255, 255));
//        //-------填随机色块模型----end
//        
//        Vec2i screen_coords[3];
//        Vec3f world_coords[3];
//
//        for (int  j=0; j <3; j++)
//        {
//            auto v0 = model->vert(face[j]);
//            int  x0 = (v0.x + 1.0f) * ScreenWidth / 2.0f;
//            int  y0 = (v0.y + 1.0f) * ScreenHeight / 2.0f;
//            screen_coords[j] = Vec2i(x0,y0);
//             world_coords[j] = v0;
//            point(screen_coords[j], image, red);
//        }
//        
//      //  Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
//      //  n.normalize();
//        
//     //   line(screen_coords[0],Vec2i((n.x + 1.0f) * ScreenWidth / 2.0f ,  (n.y + 1.0f) * ScreenHeight / 2.0f) , image, red);
//        
////        float intensity = n * light_dir;
////        if(intensity>0)
////        {
////            triangleFilled(screen_coords[0],screen_coords[1],screen_coords[2],image, TGAColor(255 * intensity, 255 * intensity, 255 * intensity, 255));
////        }
//
//    }
//    
//    
//    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
//    image.write_tga_file("output.tga");
//    return 0;
//}
//
//}
//    
//
//
