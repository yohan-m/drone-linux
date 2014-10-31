/**
 * \file usb_async_test.h
 *
 * \brief Test file of usb_async_driver.c.
 *
 * \author Thomas Hoet
 *
 * \date 31 Oct 2014
 */
 
#ifndef USB_ASYNC_TEST_H
#define USB_ASYNC_TEST_H

#include "./../usb/usb_async_driver.h"

void test_usp_async();
void test_callback_receive_usb(unsigned char * data, int size);

#endif
