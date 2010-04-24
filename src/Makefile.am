
bin_PROGRAMS=server

server_SOURCES=Recognizer.cpp Recognizer.h \
			   RecognizerI.cpp RecognizerI.h \
			   iFaceIdentifier.h \
			   EigenFace.h EigenFace.cpp \
			   main.cpp


server_LDFLAGS=$(LDFLAGS) \
			   $(ICE_LIB) $(ICE_EXTRA) -lIce -lIceUtil \
			   $(OPENCV_LIB) -lcxcore -lcv -lcvaux -lhighgui 

server_CPPFLAGS=$(CPPFLAGS) $(ICE_INCLUDE) $(OPENCV_INCLUDE) -I. 

