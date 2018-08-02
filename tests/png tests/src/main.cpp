#include <iostream>
#include <png.h>

using namespace std;

int main(int argc, char* argv[]){
	cout<<std::hex<<PNG::alpha(PNG::color(0xff,0xee,0xdd,0xcc))<<endl;
	
	PNG png = PNG("test.png");
	for(int i=0;i<png.size();i++){
		//cout<<png[i]<<endl;
		png[i]=png[i]&0xff0000ff;
		//cout<<png[i]<<endl<<endl;
	}
	
	png.save("out.png");
	return 0;
}

