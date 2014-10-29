/**
 * \file udp_disco_test.h
 *
 * \brief Test file of udp_driver_discover.c.
 *
 * \author Thomas Hoet
 *
 * \date 26 Oct 2014
 */
 
#ifndef UDP_DISCO_TEST_H
#define UDP_DISCO_TEST_H

#include "./../udp/udp_driver_discover.h"
#include "./../../../common-sources/src/wifiFrame.h"
#include "./../../../common-sources/src/frameTypes.h"
#include "./../udp/udp_async_driver.h"

void test_udp_disco();
void test_callback_fct(unsigned char * data, int size);

#endif
