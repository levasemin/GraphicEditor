#include "GraphLib.hpp"

#include "SaveWindow.hpp"
#include "OpenWindow.hpp"
#include "ColorPicker.hpp"

#include "Canvas.hpp"
#include "HSVpalette.hpp"
#include "HSVwindow.hpp"
#include "HistoryWindow.hpp"

const CUST_SL::Color back_ground_color(uint8_t(69),  uint8_t(69),  uint8_t(69));
const CUST_SL::Color tool_color       (uint8_t(48),  uint8_t(48),  uint8_t(48));

ColorPicker *create_color_picker();

SL::ComboBox *create_file_combobox(Canvas *canvas);

OpenWindow *create_open_window();

SaveWindow *create_save_window();

HSVwindow *create_hsv_window();