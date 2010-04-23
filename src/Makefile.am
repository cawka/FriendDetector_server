
bin_PROGRAMS=server

server_SOURCES=Recognizer.cpp Recognizer.h \
			   RecognizerI.cpp RecognizerI.h \
			   eigenface.cpp\
			   main.cpp

server_LDFLAGS=$(LDFLAGS) $(OPENCV_LIB) $(OPENCV_EXTRA) -lIce -lIceUtil -lcv -lcvaux 
server_CPPFLAGS=$(CPPFLAGS) $(OPENCV_INCLUDE) -I. 

