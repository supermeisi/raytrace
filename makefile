all:
	g++ `root-config --cflags` raytrace.C rays.cc box.cc `root-config --glibs` -o raytrace
