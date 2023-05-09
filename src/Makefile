CC = g+++ 
BuildF = obj/

paint:
	$(CC) -shared -fPIC -Wextra Plugins/ToolPaint.cpp Plugins/Interpolator.cpp Graphic-Library/GraphLib/Classes/Color.cpp Graphic-Library/GraphLib/functions/functions.cpp -o Plugins_so/Paint.so
eraser: 
	$(CC) -shared -fPIC -Wextra Plugins/ToolEraser.cpp Plugins/Interpolator.cpp Graphic-Library/GraphLib/Classes/Color.cpp Graphic-Library/GraphLib/functions/functions.cpp -o Plugins_so/Eraser.so
eyedropper:
	$(CC) -shared -fPIC -Wextra Plugins/ToolEyeDropper.cpp Graphic-Library/GraphLib/Classes/Color.cpp Graphic-Library/GraphLib/functions/functions.cpp Graphic-Library/GraphLib/Classes/Font.cpp -o Plugins_so/ToolEyeDropper.so 
bucket:
	$(CC) -shared -fPIC -Wextra Plugins/ToolBucket.cpp Graphic-Library/GraphLib/Classes/Color.cpp Graphic-Library/GraphLib/functions/functions.cpp -o Plugins_so/Bucket.so
style:
	$(CC) -shared -fPIC -Wextra Plugins/ToolStyle.cpp Graphic-Library/GraphLib/Classes/Color.cpp Graphic-Library/GraphLib/functions/functions.cpp -o Plugins_so/Style.so

event_handler: clean Graphic-Library/GraphLib/event_handler.o $(BuildF)main.o $(BuildF)Color.o $(BuildF)Canvas.o $(BuildF)ColorPicker.o $(BuildF)HSVwindow.o $(BuildF)OpenWindow.o $(BuildF)SaveWindow.o $(BuildF)plugin_func.o $(BuildF)ToolButton.o $(BuildF)ToolManager.o $(BuildF)Event.o
	$(CC) 			 Graphic-Library/GraphLib/event_handler.o $(BuildF)main.o $(BuildF)Color.o $(BuildF)Canvas.o $(BuildF)ColorPicker.o $(BuildF)HSVwindow.o $(BuildF)OpenWindow.o $(BuildF)SaveWindow.o $(BuildF)plugin_func.o $(BuildF)ToolButton.o $(BuildF)ToolManager.o $(BuildF)Event.o -o event_handler -lsfml-graphics -lsfml-window -lsfml-system -ldl -export-dynamic

$(BuildF)main.o:
	$(CC) -c main.cpp -o $(BuildF)main.o

$(BuildF)Canvas.o:
	$(CC) -c Custom_Widgets/Canvas.cpp -o $(BuildF)Canvas.o

$(BuildF)ColorPicker.o:
	$(CC) -c Custom_Widgets/ColorPicker.cpp -o $(BuildF)ColorPicker.o

$(BuildF)HSVpalette.o:
	$(CC) -c Custom_Widgets/HSVpalette.cpp -o $(BuildF)HSVpalette.o

$(BuildF)HSVwindow.o:
	$(CC) -c Custom_Widgets/HSVwindow.cpp -o $(BuildF)HSVwindow.o

$(BuildF)OpenWindow.o:
	$(CC) -c Custom_Widgets/OpenWindow.cpp -o $(BuildF)OpenWindow.o

$(BuildF)SaveWindow.o:
	$(CC) -c Custom_Widgets/SaveWindow.cpp -o $(BuildF)SaveWindow.o

$(BuildF)Color.o:
	$(CC) -c Custom_Widgets/Color.cpp -o $(BuildF)Color.o

$(BuildF)plugin_func.o:
	$(CC) -c Plugins/plugin_func.cpp -o $(BuildF)plugin_func.o

$(BuildF)ToolButton.o:
	$(CC) -c Tool/Widgets/ToolButton.cpp -o $(BuildF)ToolButton.o

$(BuildF)ToolManager.o:
	$(CC) -c Tool/ToolManager.cpp -o $(BuildF)ToolManager.o

$(BuildF)Interpolator.o:
	$(CC) -c Plugins/Interpolator.cpp -o $(Buildf)Interpolator.o

$(BuildF)Event.o:
	$(CC) -c Custom_Widgets/Event.cpp -o $(BuildF)Event.o

clean:
	rm -rf $(BuildF)/*.o


# $(PLUGINS_SRC)/%.cpp $(SRC)/kernel/tools.hpp
# $(CXX) $(CFLAGS) -shared -Wall -Wextra -o $@ -fPIC $<
