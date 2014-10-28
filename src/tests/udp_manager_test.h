/**
 * \file udp_manager_test.h
 *
 * \brief Test file of the UDP protocol on the drone.
 *
 * \author Thomas Hoet
 *
 * \date 28 Oct 2014
 */
 
#ifndef UDP_MANAGER_TEST_H
#define UDP_MANAGER_TEST_H

#include "./../../../common-sources/src/wifiFrame.h"
#include "./../../../common-sources/src/frameTypes.h"
#include "./../udp/udp_async_driver.h"

void test_udp_manager();
void test_callback_receive_manager(unsigned char * data, int size);

#endif
