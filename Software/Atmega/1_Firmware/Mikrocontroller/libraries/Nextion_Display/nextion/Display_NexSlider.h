#ifndef __NEXSLIDER_H__
#define __NEXSLIDER_H__
#include "../util/Display_Utilities.h"
#include "Display_NexTouch.h"
#include "Display_NexHardware.h"

/**
     * Get the value of slider. 
     * 
     * @param number - an output parameter to save the value of slider.  
     * 
     * @retval true - success. 
     * @retval false - failed. 
     */
uint8_t NexSlider_getValue(struct NexObject *slider, uint32_t *number);

/**
     * Set the value of slider.
     *
     * @param number - the value of slider.  
     *
     * @retval true - success. 
     * @retval false - failed. 
     */
uint8_t NexSlider_setValue(struct NexObject *slider, uint32_t number);

/**
     * Get bco attribute of component
     *
     * @param number - buffer storing data retur
     * @return the length of the data 
     */
uint32_t NexSlider_Get_background_color_bco(struct NexObject *slider, uint32_t *number);

/**
     * Set bco attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
uint8_t NexSlider_Set_background_color_bco(struct NexObject *slider, uint32_t number);

/**
     * Get pco attribute of component
     *
     * @param number - buffer storing data retur
     * @return the length of the data 
     */
uint32_t NexSlider_Get_font_color_pco(struct NexObject *slider, uint32_t *number);

/**
     * Set pco attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
uint8_t NexSlider_Set_font_color_pco(struct NexObject *slider, uint32_t number);

/**
     * Get wid attribute of component
     *
     * @param number - buffer storing data retur
     * @return the length of the data 
     */
uint32_t NexSlider_Get_pointer_thickness_wid(struct NexObject *slider, uint32_t *number);

/**
     * Set wid attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
uint8_t NexSlider_Set_pointer_thickness_wid(struct NexObject *slider, uint32_t number);

/**
     * Get hig attribute of component
     *
     * @param number - buffer storing data retur
     * @return the length of the data 
     */
uint32_t NexSlider_Get_cursor_height_hig(struct NexObject *slider, uint32_t *number);

/**
     * Set hig attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
uint8_t NexSlider_Set_cursor_height_hig(struct NexObject *slider, uint32_t number);

/**
     * Get maxval attribute of component
     *
     * @param number - buffer storing data retur
     * @return the length of the data 
     */
uint32_t NexSlider_getMaxval(struct NexObject *slider, uint32_t *number);

/**
     * Set maxval attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
uint8_t NexSlider_setMaxval(struct NexObject *slider, uint32_t number);

/**
     * Get minval attribute of component
     *
     * @param number - buffer storing data retur
     * @return the length of the data 
     */
uint32_t NexSlider_getMinval(struct NexObject *slider, uint32_t *number);

/**
     * Set minval attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
uint8_t NexSlider_setMinval(struct NexObject *slider, uint32_t number);

#endif /* #ifndef __NEXSLIDER_H__ */