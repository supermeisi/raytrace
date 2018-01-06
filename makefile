all:
	g++ `root-config --cflags` raytrace.C box.cc `root-config --glibs` -o raytrace
