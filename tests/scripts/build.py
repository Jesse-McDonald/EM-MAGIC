build="g++"
options="-std=c++11"
Name="EM-MAGIC"
from tree import tree 
import os
#call([build,"main.cpp",options,"-o "+name])
cwd = os.getcwd()
files=tree(cwd+"/src")
include=tree(cwd+"/headers","d")
buildScript=""
linking=""
for i in range(len(include)):	
	buildScript+="mkdir -p "+"\""+include[i].replace("/headers","/build")+"\""+'\n'
	include[i]="-I"+"\""+include[i]+"\""
for item in files:
	name=item
	name=name.replace("/src","/build")
	name=name.replace(".cpp",".o");
	if not(os.path.exists(name) and os.path.getmtime(item)<os.path.getmtime(name)):
		buildScript+=(" ".join([build,"-c","\""+item+"\"",options]+include+["-o "+"\""+name+"\""]))+'\n'
	
	linking+="\""+name+"\" "
buildFile=open(cwd+"/scripts/build",'w');
buildFile.write(buildScript)
buildFile.write(build+" "+linking+options+" -o "+Name+'\n')
buildFile.close()
