all:
	g++ `root-config --cflags` raytrace.C `root-config --glibs` -o raytrace
