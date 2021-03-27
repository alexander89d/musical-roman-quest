CXX = g++
CXXFLAGS = -g -std=c++0x
HDRFILES = enterValidInt.hpp getRandomInt.hpp menu.hpp pressEnter.hpp Space.hpp Bibliotheca.hpp DomusAurea.hpp Ludus.hpp \
CircusMaximus.hpp Forum.hpp Theatrum.hpp Colosseum.hpp Thermae.hpp CampusMartius.hpp Board.hpp Game.hpp
SRCFILES = enterValidInt.cpp getRandomInt.cpp menu.cpp pressEnter.cpp Space.cpp Bibliotheca.cpp DomusAurea.cpp Ludus.cpp \
CircusMaximus.cpp Forum.cpp Theatrum.cpp Colosseum.cpp Thermae.cpp CampusMartius.cpp Board.cpp Game.cpp finalProjMain.cpp
TXTFILES = Game_Instructions.txt Board_Images.txt Bibliotheca_Description.txt DomusAurea_Description.txt Ludus_Description.txt \
Ludus_Questions.txt CircusMaximus_Description.txt Forum_Description.txt Theatrum_Description.txt Colosseum_Description.txt \
Thermae_Description.txt Thermae_Narration.txt CampusMartius_Description.txt Ending_Sequence.txt
PROJ = finalProj
ZIPNAME = FinalProj_Densmore_Alexander_Updated.zip

finalProj: ${SRCFILES} ${HDRFILES} ${TXTFILES}
	${CXX} ${CXXFLAGS} ${SRCFILES} -o ${PROJ}

clean:
	rm ${PROJ}

zip:
	zip -D ${ZIPNAME} ${HDRFILES} ${SRCFILES} ${TXTFILES} Final_Project_Documentation.pdf makefile
