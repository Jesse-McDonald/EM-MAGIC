#include <png.h>
#include <lodepng.h>
#include <cmath>
using namespace std;
PNG::PNG(){
	pixels=vector<int>();
}
PNG::PNG(std::string target){
	PNG();
	load(target);
}
int& PNG::operator[](int i){
	return (pixels[i]);
}
int& PNG::get(int x, int y){
	return (*this)[x+y*width];
}
PNG& PNG::set(int x, int y, int c){
	this->get(x,y)=c;
}
bool PNG::load(std::string file){
	std::vector<unsigned char> image; //the raw pixels
	error = lodepng::decode(image, width, height, file);
	pixels.clear();
	pixels.resize(image.size()/4);

	unsigned char buffer[4];
	for(int i=0;i<image.size()/4;i++){
		buffer[3]=image[i*4+3];//a
		buffer[0]=image[i*4+2];//r
		buffer[1]=image[i*4+1];//g
		buffer[2]=image[i*4+0];//b
	
		pixels[i]=*((int*)((void*)buffer));

	}
	return error==0;
}
bool PNG::save(std::string file){
	std::vector<unsigned char> image; //the raw pixels
	image.resize(pixels.size()*4);

	
	unsigned char buffer[4];
	for(int i=0;i<pixels.size();i++){
		*((int*)((void*)buffer))=pixels[i];
		image[i*4+3]=buffer[3];//I got sick of structuring a for loop for this so a
		image[i*4+0]=buffer[2];//r
		image[i*4+1]=buffer[1];//g
		image[i*4+2]=buffer[0];//b
		
	}
	error = lodepng::encode(file,image, width, height);

	return error==0;

}
std::string PNG::getError(){
	return lodepng_error_text(error);
}
unsigned int PNG::size(){
	return pixels.size();
}

int PNG::color(int r, int g, int b, int a){
	if(r>255) r=255;
	if(r<0) r=0;
	if(g>255) g=255;
	if(g<0) g=0;
	if(b>255) b=255;
	if(b<0) b=0;
	if(a>255) a=255;
	if(a<0) a=0;
	unsigned char buffer[4];
	buffer[3]=a;
	buffer[2]=r;
	buffer[1]=g;
	buffer[0]=b;
	return *((int*)((void*)buffer));
}
int PNG::color(int gray,int a){
	return color(gray,gray,gray,a);
}
int PNG::color(float r, float g, float b, float a){
	return color((int)r*255,(int) g*255, (int)b*255,(int) a*255);
}
int PNG::color(float gray, float a){
	return color(gray,gray,gray,a);
}
int PNG::red(int c){
	return (c&0x00ff0000)>>16;
}
int PNG::blue(int c){
	return (c&0x000000ff);
}
int PNG::green(int c){
	return (c&0x0000ff00)>>8;
}
int PNG::alpha(int c){
	return (c&0xff000000)>>24;
}
int PNG::gray(int c){
	return round(red(c)*.3+green(c)*.59+blue(c)*.11);//this works as a transformation, not sure how well, but gray comes out gray and that is really all that matters
}
int PNG::colorDif(int c1, int c2){
	return round(sqrt(colorDifSq(c1,c2)));//take the raw... and square root it
}
int PNG::colorDifSq(int c1, int c2){//for faster speed, no square root
	return 2*pow(red(c1)-red(c2),2)+4*pow(green(c1)-green(c2),2)+3*pow(blue(c1)-blue(c2),2);//according to wikepedia, this is the right formula
}
