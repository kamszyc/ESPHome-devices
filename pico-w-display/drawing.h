void drawCommon(Display& it, bool alert = false) {
    it.filled_rectangle(0, 0, it.get_width(), 40, my_blue);

    it.print(10, 10, font_24, my_light_gray, TextAlign::TOP_LEFT, "szyc.dev");

    if (system_status->state) {
        it.print(230, 10, font_24, my_green, TextAlign::TOP_RIGHT, "Online");
    }
    else {
        it.print(230, 10, font_24, my_red, TextAlign::TOP_RIGHT, "Offline");
    }
    
    if (!alert) {
        it.filled_triangle(20, 120, 40, 120+10, 40, 120-10, my_gray); // left arrow
        it.filled_triangle(240-20, 120, 240-40, 120+10, 240-40, 120-10, my_gray); // right arrow
    }
}

void drawAlert(Display& it, const char* line1, const char* line2) {
    it.print((240 / 2), (140 / 3) * 2 + 5, font_48, my_gray, TextAlign::CENTER, line1);
    it.print((240 / 2), (140 / 3) * 3 + 5, font_48, my_gray, TextAlign::CENTER, line2);
}

void drawLaundryAlert(Display& it) {
    drawAlert(it, "PRANIE", "GOTOWE");
}

void drawSingleValueName(Display& it, const char* sensorName) {
    it.print((240 / 2), (140 / 3) * 2 + 5, font_24, my_gray, TextAlign::CENTER, sensorName);
}

void drawPlusMinus(Display& it, bool isMin, bool isMax) {
    it.print(120, 60, font_bold_48, isMax ? my_dark_gray : my_gray, TextAlign::CENTER, "+");
    it.print(120, 200, font_bold_48, isMin ? my_dark_gray : my_gray, TextAlign::CENTER, "–");
}

void drawBrightnessPageInternal(Display& it, const char* sensorName, const char* format, float state, bool isMin, bool isMax) {
    drawSingleValueName(it, sensorName);
    it.printf((240 / 2), (140 / 3) * 3 + 5, font_48, my_gray, COLOR_OFF, TextAlign::CENTER, format, state);
    drawPlusMinus(it, isMin, isMax);
}

void drawBrightnessPageInternal(Display& it, const char* sensorName, const char* state, bool isMin, bool isMax) {
    drawSingleValueName(it, sensorName);
    it.printf((240 / 2), (140 / 3) * 3 + 5, font_48, my_gray, COLOR_OFF, TextAlign::CENTER, state);
    drawPlusMinus(it, isMin, isMax);
}

void drawBrightnessPage(Display& it, bool laundryAlertDisplayed, const char* sensorName, bool enabled, float state) {
    drawCommon(it, laundryAlertDisplayed);
    if (laundryAlertDisplayed) {
        drawLaundryAlert(it);
    }
    else if (!enabled) {
        drawBrightnessPageInternal(it, sensorName, "OFF", true, false);
    }
    else {
        int brightness = (state / 255.0)*100;
        drawBrightnessPageInternal(it, sensorName, "%.0f%%", brightness, false, brightness >= 99);
    }
}