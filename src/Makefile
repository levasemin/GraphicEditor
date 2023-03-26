CC = g+++

BuildF = obj/

paint:
	$(CC) -shared -fPIC -Wextra ToolPaint.cpp Interpolator.cpp Color.cpp functions.cpp -o Plugins/Paint.so
eraser: 
	$(CC) -shared -fPIC -Wextra ToolEraser.cpp Interpolator.cpp Color.cpp functions.cpp -o Plugins/Eraser.so
eyedropper:
	$(CC) -shared -fPIC -Wextra ToolEyeDropper.cpp Color.cpp functions.cpp Font.cpp -o Plugins/ToolEyeDropper.so 
bucket:
	$(CC) -shared -fPIC -Wextra ToolBucket.cpp Color.cpp functions.cpp -o Plugins/Bucket.so


event_handler: clean Library/event_handler.o $(BuildF)main.o $(BuildF)plugin_func.o $(BuildF)ToolButton.o $(BuildF)ToolManager.o
	$(CC) 			 Library/event_handler.o $(BuildF)main.o $(BuildF)plugin_func.o $(BuildF)ToolButton.o $(BuildF)ToolManager.o -o event_handler -lsfml-graphics -lsfml-window -lsfml-system -ldl -export-dynamic

$(BuildF)main.o:
	$(CC) -c main.cpp -o $(BuildF)main.o

$(BuildF)plugin_func.o:
	$(CC) -c plugin_func.cpp -o $(BuildF)plugin_func.o

$(BuildF)ToolButton.o:
	$(CC) -c ToolButton.cpp -o $(BuildF)ToolButton.o

$(BuildF)ToolEraser.o:
	$(CC) -c ToolEraser.cpp -o $(BuildF)ToolEraser.o

$(BuildF)ToolManager.o:
	$(CC) -c ToolManager.cpp -o $(BuildF)ToolManager.o

$(BuildF)Interpolator.o:
	$(CC) -c Interpolator.cpp -o $(Buildf)Interpolator.o

clean:
	rm -rf $(BuildF)/*.o


# $(PLUGINS_SRC)/%.cpp $(SRC)/kernel/tools.hpp
# $(CXX) $(CFLAGS) -shared -Wall -Wextra -o $@ -fPIC $<
