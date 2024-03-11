//
// Created by florian on 01.09.22.
//
#include "Controls.hpp"
#include <lv_btn.h>
#include <lv_disp.h>
#include <lv_label.h>

Controls::Controls()
{
    lv_style_init(&mFontStyle);
    lv_style_set_text_font(&mFontStyle, LV_STATE_DEFAULT, &lv_font_montserrat_12);

    mXButton = lv_btn_create(lv_layer_sys(), nullptr);
    lv_obj_set_size(mXButton, 20, 20);
    lv_obj_set_pos(mXButton, 20, 90);
    lv_obj_add_style(mXButton, LV_LABEL_PART_MAIN, &mFontStyle);
    lv_obj_set_event_cb(mXButton, &Controls::xButtonPressed);

    mXButtonLabel = lv_label_create(mXButton, nullptr);
    lv_label_set_text(mXButtonLabel, LV_SYMBOL_CLOSE);

    mOButton = lv_btn_create(lv_layer_sys(), nullptr);
    lv_obj_set_size(mOButton, 20, 20);
    lv_obj_set_pos(mOButton, 50, 90);
    lv_obj_add_style(mOButton, LV_LABEL_PART_MAIN, &mFontStyle);
    lv_obj_set_event_cb(mOButton, &Controls::oButtonPressed);

    mOButtonLabel = lv_label_create(mOButton, nullptr);
    lv_label_set_text(mOButtonLabel, LV_SYMBOL_OK);

    mUpButton = lv_btn_create(lv_layer_sys(), nullptr);
    lv_obj_set_size(mUpButton, 20, 20);
    lv_obj_set_pos(mUpButton, 190, 90);
    lv_obj_add_style(mUpButton, LV_LABEL_PART_MAIN, &mFontStyle);
    lv_obj_set_event_cb(mUpButton, &Controls::upButtonPressed);

    mUpButtonLabel = lv_label_create(mUpButton, nullptr);
    lv_label_set_text(mUpButtonLabel, LV_SYMBOL_UP);

    mDownButton = lv_btn_create(lv_layer_sys(), nullptr);
    lv_obj_set_size(mDownButton, 20, 20);
    lv_obj_set_pos(mDownButton, 220, 90);
    lv_obj_add_style(mDownButton, LV_LABEL_PART_MAIN, &mFontStyle);
    lv_obj_set_event_cb(mDownButton, &Controls::downButtonPressed);

    mDownButtonLabel = lv_label_create(mDownButton, nullptr);
    lv_label_set_text(mDownButtonLabel, LV_SYMBOL_DOWN);
}

Controls::~Controls()
{
    lv_obj_del(mXButton);
    lv_obj_del(mXButtonLabel);
    lv_obj_del(mOButton);
    lv_obj_del(mOButtonLabel);
    lv_obj_del(mUpButton);
    lv_obj_del(mUpButtonLabel);
    lv_obj_del(mDownButton);
    lv_obj_del(mDownButtonLabel);
}

void Controls::xButtonPressed(lv_obj_t* obj, lv_event_t event)
{
    if (event != LV_EVENT_CLICKED) {
        return;
    }

    lv_key_t keyType = LV_KEY_ESC;
    lv_event_send(lv_scr_act(), LV_EVENT_KEY, static_cast<void const*>(&keyType));
}

void Controls::oButtonPressed(lv_obj_t* obj, lv_event_t event)
{
    if (event != LV_EVENT_CLICKED) {
        return;
    }

    lv_key_t keyType = LV_KEY_ENTER;
    lv_event_send(lv_scr_act(), LV_EVENT_KEY, static_cast<void const*>(&keyType));
}
void Controls::upButtonPressed(lv_obj_t* obj, lv_event_t event)
{
    if (event != LV_EVENT_CLICKED) {
        return;
    }

    lv_key_t keyType = LV_KEY_UP;
    lv_event_send(lv_scr_act(), LV_EVENT_KEY, static_cast<void const*>(&keyType));
}

void Controls::downButtonPressed(lv_obj_t* obj, lv_event_t event)
{
    if (event != LV_EVENT_CLICKED) {
        return;
    }

    lv_key_t keyType = LV_KEY_DOWN;
    lv_event_send(lv_scr_act(), LV_EVENT_KEY, static_cast<void const*>(&keyType));
}
