/**
 * \file udp_async_test.h
 *
 * \brief Test file of udp_async_driver.c.
 *
 * \author Thomas Hoet
 *
 * \date 26 Oct 2014
 */
 
#ifndef UDP_ASYNC_TEST_H
#define UDP_ASYNC_TEST_H

#include "./../udp/udp_async_driver.h"

void test_udp_async();
void test_callback_receive(unsigned char * data, int size);

#endif
