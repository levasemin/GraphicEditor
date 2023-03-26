CC = g+++

BuildF = obj/

event_handler: clean         $(BuildF)EventManager.o $(BuildF)Application.o $(BuildF)Window.o $(BuildF)functions.o $(BuildF)Color.o $(BuildF)Vector2d.o $(BuildF)Event.o $(BuildF)Button.o $(BuildF)Font.o 
	 		ld -relocatable	 $(BuildF)EventManager.o $(BuildF)Application.o $(BuildF)Window.o $(BuildF)functions.o $(BuildF)Color.o $(BuildF)Vector2d.o $(BuildF)Event.o $(BuildF)Button.o $(BuildF)Font.o -o event_handler.o

$(BuildF)Application.o:
	$(CC) -c Application.cpp -o $(BuildF)Application.o 

$(BuildF)EventManager.o:
	$(CC) -c EventManager.cpp -o $(BuildF)EventManager.o 

$(BuildF)Window.o:
	$(CC) -c Window.cpp -o $(BuildF)Window.o -lsfml-graphics -lsfml-window -lsfml-system -ldl -export-dynamic

$(BuildF)functions.o:
	$(CC) -c functions.cpp -o $(BuildF)functions.o 

$(BuildF)Color.o:
	$(CC) -c Color.cpp -o $(BuildF)Color.o

$(BuildF)Vector2d.o:
	$(CC) -c Vector2d.cpp -o $(BuildF)Vector2d.o

$(BuildF)Event.o:
	$(CC) -c Event.cpp -o $(BuildF)Event.o

$(BuildF)Button.o:
	$(CC) -c Button.cpp -o $(BuildF)Button.o

$(BuildF)Font.o:
	$(CC) -c Font.cpp -o $(BuildF)Font.o


clean:
	rm -rf $(BuildF)/*.o


# $(PLUGINS_SRC)/%.cpp $(SRC)/kernel/tools.hpp
# $(CXX) $(CFLAGS) -shared -Wall -Wextra -o $@ -fPIC $<
