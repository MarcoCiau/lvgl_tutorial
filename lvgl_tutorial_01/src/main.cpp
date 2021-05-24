#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */

static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

void hello_world(); //hello world example 

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors(&color_p->full, w * h, true);
    tft.endWrite();

    lv_disp_flush_ready(disp);
}



void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */

    lv_init(); /* Init Library*/

#if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

    tft.begin(); /* TFT init */
    tft.setRotation(3); /* Landscape orientation */
    
   //  uint16_t calData[5] = { 275, 3620, 264, 3532, 1 };//TODO
   //  tft.setTouch(calData);//TODO

    lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

    /*Initialize the display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = 320;
    disp_drv.ver_res = 240;
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.buffer = &disp_buf;
    lv_disp_drv_register(&disp_drv);

	hello_world();//execute example
}

void loop()
{
    lv_task_handler(); /* let the GUI do its work */
    delay(5);
}


void hello_world(void)
{
    /*  Title Label */
    lv_obj_t * hello_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(hello_label, "Hello World!");
    /* Position the label */
    lv_obj_align(hello_label, NULL, LV_ALIGN_CENTER, 0, -40);
    

    /* Button */
    lv_obj_t * label;
    lv_obj_t * btn1 = lv_btn_create(lv_scr_act(), NULL);
    // lv_obj_set_event_cb(btn1, event_handler); //TODO
    lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 0, 40);

    label = lv_label_create(btn1, NULL);
    lv_label_set_text(label, "Button");
}