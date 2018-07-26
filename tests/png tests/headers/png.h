#ifndef PNG_H
#define PNG_H
#include <vector>
#include <string>
class PNG{
	public:
		std::vector<int> pixels;//if I need, I can compress this later like I did in CASTER, I dont think I will need to
		unsigned int width, height, error;
		PNG();
		PNG(std::string);
		int& operator[](int i);
		int& get(int x, int y);
		PNG& set(int x, int y, int c);
		bool save(std::string);
		bool load(std::string);
		std::string getError();	
		unsigned int size();	
		static int color(int r, int g, int b, int a=255);
		static int color(int gray,int a=255);
		static int color(float r, float g, float b, float a=1);
		static int color(float gray, float a=1);
		static int red(int c);
		static int blue(int c);
		static int green(int c);
		static int alpha(int c);
		static int gray(int c);
		static int colorDif(int c1, int c2);
		static int colorDifSq(int c1, int c2);
		//fleshout later as we see what we need
};

#endif
