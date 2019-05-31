#include "tgaimage.h"

// https://github.com/ssloy/tinyrenderer/wiki

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);


void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
    
    for (int x = x0;x <= x1 ; x+=1) {
        int  y   = (int)((y1 - y0 ) * 1.0 / (x1 - x0) * (x - x0 )) +  y0;
        image.set(x, y, color);
    }
}

int main(int argc, char** argv) {
	TGAImage image(1000, 1000, TGAImage::RGB);
//	image.set(52, 41, red);
    
    line(0,0,800,500, image,red);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");
	return 0;
}


    


