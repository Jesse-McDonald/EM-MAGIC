#this file is not required for building projects, its soul purpose is quickly packing any changed file into a quick deplay project file
qpf=open("prepDir.py",'w')
qpf.write("#this file is not required for building projects, its soul purpose is to quickly setup a directory as a project")
qpf.write("from subprocess import call")
qpf.write("import os ")
build=open("scripts/build.py",'r').read()
qpf.write("build=\"\"\"")
qpf.write(build)
qpf.write("\"\"\"")
tree=open("scripts/tree.py").read()
qpf.write("tree=\"\"\"",'-r')
qpf.write(tree)
qpf.write("\"\"\"")
make=open("Makefile").read()
qpf.write("make=\"\"\"",'-r')
qpf.write(make)
qpf.write("\"\"\"")
qpf.write("""
call("mkdir scripts src headers")

dir_path = 
projectName=os.path.dirname(os.path.realpath(__file__))
buildFile=open(

""")

qpf.close()
