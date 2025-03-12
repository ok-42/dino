#include <LiquidCrystal_I2C.h>

class Menu {
private:
    LiquidCrystal_I2C* my_lcd_p;
    int index = 10;
    char** items;
    int nItems;

public:
    Menu(LiquidCrystal_I2C* lcd, char** items, int nItems) {
        my_lcd_p = lcd;
        items = items;
        nItems = nItems;
    };

    void next();
    void prev();
    char** get();
    void show();
};

char** Menu::get() {
    auto result = (char**)calloc(nItems, sizeof(char) * 9);
    for (int i = 0; i < 2; i++) {
        result[i] = items[(index + i) % nItems];
    }
    return result;
}

// Show two menu entries on the LCD
void Menu::show() {
    auto res = get();
    auto lcd = *my_lcd_p;
    lcd.setCursor(0, 0);
    lcd.print(res[0]);
    Serial.println(res[0]);
    lcd.setCursor(0, 1);
    lcd.print(res[1]);
    Serial.println(res[1]);
}

void Menu::prev() {
    --index;
}

void Menu::next() {
    ++index;
}
