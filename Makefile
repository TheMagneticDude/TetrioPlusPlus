GITBINARY := git
PINGURL := google.com
LIBRARYREPO := simulator_libraries

# SDL2 Directories
SDL2_INCLUDE := -I/usr/include/SDL2
SDL2_LIBS := -L/usr/lib -lSDL2

ifeq ($(OS),Windows_NT)	
	SHELL := CMD
	SDL2_INCLUDE := -IC:/path/to/SDL2/include
	SDL2_LIBS := -LC:/path/to/SDL2/lib -lSDL2main -lSDL2
endif

all: update
ifeq ($(OS),Windows_NT)	
	@cd $(LIBRARYREPO) && mingw32-make SDL2_INCLUDE="$(SDL2_INCLUDE)" SDL2_LIBS="$(SDL2_LIBS)"
else
	@cd $(LIBRARYREPO) && make SDL2_INCLUDE="$(SDL2_INCLUDE)" SDL2_LIBS="$(SDL2_LIBS)"
endif

update:
ifeq ($(OS),Windows_NT)	
	@ping -n 1 -w 1000 $(PINGURL) > NUL & \
	if errorlevel 1 \
	( \
		( echo Warning: No internet connection! ) \
	) \
	else \
	( \
		( if exist "$(LIBRARYREPO)" \
		( \
			cd $(LIBRARYREPO) && \
			cd .. \
		) \
		else \
		( \
			$(GITBINARY) config --global http.sslVerify false  && \
			$(GITBINARY) clone https://code.osu.edu/fehelectronics/proteus_software/$(LIBRARYREPO).git \
		) \
		) \
	) 
else
	@ping -c 1 -W 1000 $(PINGURL) > /dev/null ; \
	if [ "$$?" -ne 0 ]; then \
		echo Warning: No internet connection!; \
	else \
		if [ -d "$(LIBRARYREPO)" ]; then \
			cd $(LIBRARYREPO) ; \
      		cd .. ; \
		else \
      		$(GITBINARY) clone https://code.osu.edu/fehelectronics/proteus_software/$(LIBRARYREPO).git ; \
		fi \
	fi \

endif

clean:
ifeq ($(OS),Windows_NT)	
	@cd $(LIBRARYREPO) && mingw32-make clean
else
	@cd $(LIBRARYREPO) && make clean
endif
