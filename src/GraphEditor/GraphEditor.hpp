#pragma once

#include "GraphLib.hpp"

#include "SaveWindow.hpp"
#include "OpenWindow.hpp"
#include "ColorPicker.hpp"

#include "Canvas.hpp"
#include "HSVpalette.hpp"
#include "HSVwindow.hpp"
#include "HistoryWindow.hpp"

#include "Constants.hpp"
#include "ToolLibrary.hpp"

const SL::Color back_ground_color(uint8_t(69),  uint8_t(69),  uint8_t(69));
const SL::Color tool_color       (uint8_t(48),  uint8_t(48),  uint8_t(48));

CUST_SL::ColorPicker *create_color_picker();

SL::ComboBox *create_file_combobox(CUST_SL::Canvas *canvas);

CUST_SL::OpenWindow *create_open_window();

CUST_SL::SaveWindow *create_save_window();

CUST_SL::HSVwindow *create_hsv_window();