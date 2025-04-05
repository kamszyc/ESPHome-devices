enum Direction {
    UP,
    DOWN
};

void handle_joystick(Direction direction) {
    backlight_short->execute();

    if (!backlight->current_values.is_on()) {
        return;
    }
    
    if (my_display->get_active_page() == page_yeelight) {
        if (direction == UP)
            yeelight_control->trigger("yeelight_brighten");
        else
            yeelight_control->trigger("yeelight_dim");
    }
    else if (my_display->get_active_page() == page_lamp) {
        if (direction == UP)
            lamp_control->trigger("lamp_brighten");
        else
            lamp_control->trigger("lamp_dim");
    }
    else if (my_display->get_active_page() == page_yeelight_ambilight) {
        if (direction == UP)
            yeelight_ambilight_control->trigger("yeelight_ambilight_brighten");
        else
            yeelight_ambilight_control->trigger("yeelight_ambilight_dim");
    }
    else if (my_display->get_active_page() == page_display_brightness) {
        float b;
        if (direction == UP)
            b = std::min(1.0f, backlight->current_values.get_brightness() + 0.1f);
        else
            b = std::max(0.1f, backlight->current_values.get_brightness() - 0.1f);

        backlight->make_call().set_brightness(b).perform();
        my_display->update();
    }
}