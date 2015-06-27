all : asd

asd : asd.cc
	g++ -D _SUNOS asd.cc timer.cc main.cc ../tests/ltest_liniowe2.so -o asd 
	
del :
	rm asd
debug : asd.cc
	g++ -g -D _SUNOS asd.cc timer.cc main.cc ../tests/ltest_liniowe2.so -o asd_debug
	gdb asd_debug 
	

view:
	lynx info/index.html
