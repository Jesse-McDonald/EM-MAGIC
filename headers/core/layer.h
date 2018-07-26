#ifndef LAYER_H
#define LAYER_H
#include <vector>
#include <string>
class Layer{
	public:
		PNG layerData;
		Meta layerMetaData;
		Layer(PNG& png);
		
		Layer* parrent;
		Layer* branches;
		int xOffset;
		int yOffset;
		vector<Splice> splices;
		Layer& scanSpliceX();
		Layer& scanSpliceY();
		Layer& detectCorrupted();
		Layer& detectCorrupted(int benchmark);
		Layer& fixSplices();//calculates needed fix for splices
		Layer& removeSplice();//blackout splices
		Layer& ExtrapolateSplices();//extrapolate data for splices
		Layer& alignLandmarks(bool branch=false);
		DataObj& exportObj(DataObj& out);
		DataObj& exportObj();	
		Layer& importObj(DataObj& in);
		Layer& commitChanges(std::string path);
}


#endif
